################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
board_init.obj: ../board_init.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/imac/Documents/TI_CCS_workspace/adc_dma_data_6led_compact_MSP_EXP432P401R" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source/third_party/CMSIS/Include" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="board_init.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/imac/Documents/TI_CCS_workspace/adc_dma_data_6led_compact_MSP_EXP432P401R" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source/third_party/CMSIS/Include" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system_msp432p401r.obj: ../system_msp432p401r.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/imac/Documents/TI_CCS_workspace/adc_dma_data_6led_compact_MSP_EXP432P401R" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source/third_party/CMSIS/Include" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="system_msp432p401r.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

x9c104.obj: ../x9c104.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/imac/Documents/TI_CCS_workspace/adc_dma_data_6led_compact_MSP_EXP432P401R" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source/third_party/CMSIS/Include" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="x9c104.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

xgboost_msp432.obj: ../xgboost_msp432.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/imac/Documents/TI_CCS_workspace/adc_dma_data_6led_compact_MSP_EXP432P401R" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source/third_party/CMSIS/Include" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="xgboost_msp432.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


