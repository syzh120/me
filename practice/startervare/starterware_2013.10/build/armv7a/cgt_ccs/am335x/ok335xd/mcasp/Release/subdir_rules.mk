################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
aic31.obj: Z:/starterware_2013.10/examples/evmskAM335x/mcasp/aic31.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --diag_warning=225 --preproc_with_compile --preproc_dependency="aic31.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

codecif.obj: Z:/starterware_2013.10/examples/evmskAM335x/mcasp/codecif.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --diag_warning=225 --preproc_with_compile --preproc_dependency="codecif.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mcaspPlayTone.obj: Z:/starterware_2013.10/examples/evmskAM335x/mcasp/mcaspPlayTone.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --diag_warning=225 --preproc_with_compile --preproc_dependency="mcaspPlayTone.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


