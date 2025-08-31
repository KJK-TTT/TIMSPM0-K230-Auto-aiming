################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/Board" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/BSP/OLED" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/BSP" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/Debug" -I"C:/ti/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-2008811585: ../empty.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2020/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/empty.syscfg" -o "." -s "C:/ti/mspm0_sdk_2_05_01_00/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-2008811585 ../empty.syscfg
device.opt: build-2008811585
device.cmd.genlibs: build-2008811585
ti_msp_dl_config.c: build-2008811585
ti_msp_dl_config.h: build-2008811585
Event.dot: build-2008811585

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/Board" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/BSP/OLED" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/BSP" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/Debug" -I"C:/ti/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/ti/mspm0_sdk_2_05_01_00/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/Board" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/BSP/OLED" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/BSP" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3" -I"C:/Users/ek/workspace_ccstheia/ds25_e_v1.3/Debug" -I"C:/ti/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


