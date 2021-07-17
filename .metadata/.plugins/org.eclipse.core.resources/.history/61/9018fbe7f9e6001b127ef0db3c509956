################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/TI/MSP432/MSP432_CSS_WorkSpace/Button_ExternalInterrupts" --include_path="E:/TI/MSP432/MSP432_CSS_WorkSpace/Button_ExternalInterrupts/Debug" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/kernel/nortos" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/kernel/nortos/posix" --include_path="C:/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="E:/TI/MSP432/MSP432_CSS_WorkSpace/Button_ExternalInterrupts/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1844142817: ../Button_ExternalInterrupts.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1031/ccs/utils/sysconfig_1.8.1/sysconfig_cli.bat" -s "C:/ti/simplelink_msp432p4_sdk_3_40_01_02/.metadata/product.json" --script "E:/TI/MSP432/MSP432_CSS_WorkSpace/Button_ExternalInterrupts/Button_ExternalInterrupts.syscfg" -o "syscfg"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1844142817 ../Button_ExternalInterrupts.syscfg
syscfg/ti_drivers_config.h: build-1844142817
syscfg/syscfg_c.rov.xs: build-1844142817
syscfg/: build-1844142817

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/TI/MSP432/MSP432_CSS_WorkSpace/Button_ExternalInterrupts" --include_path="E:/TI/MSP432/MSP432_CSS_WorkSpace/Button_ExternalInterrupts/Debug" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/kernel/nortos" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/kernel/nortos/posix" --include_path="C:/ti/ccs1031/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="E:/TI/MSP432/MSP432_CSS_WorkSpace/Button_ExternalInterrupts/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


