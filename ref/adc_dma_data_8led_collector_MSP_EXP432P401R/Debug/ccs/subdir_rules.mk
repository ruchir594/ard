################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ccs/startup_msp432p401r_ccs.obj: ../ccs/startup_msp432p401r_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/imac/Documents/TI_CCS_workspace/adc_dma_data_8led_collector_MSP_EXP432P401R" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source" --include_path="/Users/imac/ti/simplelink_msp432_sdk_1_40_01_00/source/third_party/CMSIS/Include" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="ccs/startup_msp432p401r_ccs.d" --obj_directory="ccs" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


