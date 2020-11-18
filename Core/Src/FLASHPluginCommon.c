#include "FLASHPluginConfig.h"
#include "FLASHPluginInterface.h"
#include "w25qxx.h"
#include <string.h>

#ifndef MINIMUM_PROGRAMMED_BLOCK_SIZE
#error Please define MINIMUM_PROGRAMMED_BLOCK_SIZE in your FLASHPluginConfig.h
#endif

typedef struct {
  unsigned erase;
  unsigned write;
  unsigned init;
  unsigned load;
  unsigned protect;
} plugin_timeouts;

typedef struct {
  unsigned size;
  plugin_timeouts timeouts;
} image_plugin_timeouts;

__attribute__((weak)) image_plugin_timeouts FLASHPlugin_TimeoutTable = {.size = sizeof(plugin_timeouts),
                                                                        .timeouts = {
                                                                            .erase = 600000,
                                                                            .write = 10000,
                                                                            .init = 10000,
                                                                            .load = 100000,
                                                                            .protect = 10000,
                                                                        }};

volatile void *__attribute__((used)) g_FunctionTable[] = {
    (void *)&FLASHPlugin_Unload,         (void *)&FLASHPlugin_Probe,
    (void *)&FLASHPlugin_FindWorkArea,   (void *)&FLASHPlugin_EraseSectors,
    (void *)&FLASHPlugin_ProgramSync,

    (void *)&FLASHPlugin_ProtectSectors, (void *)&FLASHPlugin_CheckSectorProtection,
};

void FLASHPlugin_InitDone() {
  __asm volatile("cpsid i");
  g_FunctionTable[0] = (void *)&FLASHPlugin_TimeoutTable;
}

int FLASHPlugin_NotImplemented() { return -1; }

int FLASHPlugin_CheckSectorProtection(unsigned firstSector, unsigned sectorCount, unsigned char *pBuffer)
    __attribute__((weak, alias("FLASHPlugin_NotImplemented")));
int FLASHPlugin_ProtectSectors(unsigned protect, unsigned firstSector, unsigned sectorCount) __attribute__((weak, alias("FLASHPlugin_NotImplemented")));

FLASHBankInfo FLASHPlugin_Probe(unsigned base, unsigned size, unsigned width1, unsigned width2) {
  __asm volatile("cpsie i");

  FLASHBankInfo result = {.BaseAddress = base, .BlockCount = w25qxx.SectorCount, .BlockSize = w25qxx.SectorSize, .WriteBlockSize = w25qxx.PageSize};

  __asm volatile("cpsid i");
  return result;
}

WorkAreaInfo FLASHPlugin_FindWorkArea(void *endOfStack) {
  __asm volatile("cpsie i");

  WorkAreaInfo info = {.Address = endOfStack, .Size = 4096};

  __asm volatile("cpsid i");
  return info;
}

int FLASHPlugin_EraseSectors(unsigned firstSector, unsigned sectorCount) {
  __asm volatile("cpsie i");

  for (unsigned i = 0; i < sectorCount; i++)
    W25qxx_EraseSector(firstSector + i);

  __asm volatile("cpsid i");
  return sectorCount;
}

int FLASHPlugin_DoProgramSync(unsigned startOffset, const void *pData, int bytesToWrite) {
  W25qxx_WritePage((uint8_t *)pData, startOffset / W25Q128_PAGE_SIZE, 0, bytesToWrite);
  return bytesToWrite;
}

int FLASHPlugin_Unload() {
  HAL_SPI_DeInit(&hspi1);
  HAL_DeInit();
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

  for (int i = 0; i < sizeof(NVIC->ICER) / sizeof(NVIC->ICER[0]); i++)
    NVIC->ICER[0] = -1;

  return 0;
}

int FLASHPlugin_ProgramSync(unsigned startOffset, const void *pData, unsigned bytesToWrite) {
  __asm volatile("cpsie i");
  unsigned ptr = 0;
  while (bytesToWrite != 0) {
    if (bytesToWrite > W25Q128_PAGE_SIZE) {
      W25qxx_WritePage((uint8_t *)(pData + ptr), (startOffset + ptr) / W25Q128_PAGE_SIZE, 0, W25Q128_PAGE_SIZE);
      bytesToWrite -= W25Q128_PAGE_SIZE;
      ptr += W25Q128_PAGE_SIZE;
    } else {
      uint8_t pageBuffer[256];
      memcpy(pageBuffer, (uint8_t *)(pData + ptr), bytesToWrite);
      for (int i = bytesToWrite; i < W25Q128_PAGE_SIZE; i++) {
        pageBuffer[i] = 0xFF;
      }
      W25qxx_WritePage((uint8_t *)(pageBuffer), (startOffset + ptr) / W25Q128_PAGE_SIZE, 0, W25Q128_PAGE_SIZE);
      ptr += bytesToWrite;
      bytesToWrite = 0;
    }
  }
  __asm volatile("cpsid i");
  return ptr;
}
