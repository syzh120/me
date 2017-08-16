################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
dmtimerCounter.obj: Z:/starterware_2013.10/examples/ok335xd/dmtimer/dmtimerCounter.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --diag_warning=225 --preproc_with_compile --preproc_dependency="dmtimerCounter.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


