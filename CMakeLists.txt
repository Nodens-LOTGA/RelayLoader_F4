cmake_minimum_required(VERSION 3.15)

project(RelayLoader_F4 LANGUAGES C CXX ASM)

find_bsp(ID com.sysprogs.arm.stm32
	VERSION 2020.10
	MCU STM32F446RC
	HWREGISTER_LIST_FILE STM32F4xxxx/DeviceDefinitions/stm32f446xx.xml
	CONFIGURATION com.sysprogs.bspoptions.primary_memory=sram)

bsp_compile_flags()
register_imported_project(NAME RelayLoader_F4
	PATH RelayLoader.gpdsc
	LEVEL 0)
add_bsp_based_executable(NAME RelayLoader_F4
	SOURCES
		${RelayLoader_F4_LOCATION}/Core/Src/gpio.c
		${RelayLoader_F4_LOCATION}/Core/Src/spi.c
		${RelayLoader_F4_LOCATION}/Core/Src/stm32f4xx_it.c
		${RelayLoader_F4_LOCATION}/Core/Src/stm32f4xx_hal_msp.c
		${RelayLoader_F4_LOCATION}/Core/Src/main.c
		${RelayLoader_F4_LOCATION}/Core/Inc/gpio.h
		${RelayLoader_F4_LOCATION}/Core/Inc/spi.h
		${RelayLoader_F4_LOCATION}/Core/Inc/stm32f4xx_it.h
		${RelayLoader_F4_LOCATION}/Core/Inc/stm32f4xx_hal_conf.h
		${RelayLoader_F4_LOCATION}/Core/Inc/main.h
		${RelayLoader_F4_LOCATION}/Drivers/CMSIS/Include/core_cm4.h
		${RelayLoader_F4_LOCATION}/Core/Src/system_stm32f4xx.c
		${RelayLoader_F4_LOCATION}/Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h
		${RelayLoader_F4_LOCATION}/Drivers/CMSIS/Device/ST/STM32F4xx/Include/system_stm32f4xx.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma_ex.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_spi.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ramfunc.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h
		${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h
		${RelayLoader_F4_LOCATION}/Core/Src/FLASHPluginCommon.c
		${RelayLoader_F4_LOCATION}/Core/Src/w25qxx.c
		${RelayLoader_F4_LOCATION}/Core/Inc/FLASHPluginConfig.h
		${RelayLoader_F4_LOCATION}/Core/Inc/FLASHPluginInterface.h
		${RelayLoader_F4_LOCATION}/Core/Inc/w25qxx.h
		${RelayLoader_F4_LOCATION}/Core/Inc/w25qxxConf.h
	GENERATE_BIN
	GENERATE_MAP)
target_compile_options(RelayLoader_F4 PRIVATE -Os -ffunction-sections -fdata-sections)
target_include_directories(RelayLoader_F4
	PRIVATE
	${RelayLoader_F4_LOCATION}/Core/Inc
	${RelayLoader_F4_LOCATION}/Drivers/CMSIS/Include
	${RelayLoader_F4_LOCATION}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
	${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc
	${RelayLoader_F4_LOCATION}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy)

target_compile_definitions(RelayLoader_F4
	PRIVATE
	flash_layout
	STM32F446xx)

