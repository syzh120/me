################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
hs_mmcsdlib.obj: Z:/starterware_2013.10/mmcsdlib/hs_mmcsdlib.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../include/armv7a/am335x" --include_path="../../../../../include/armv7a" --include_path="../../../../../mmcsdlib/include" --include_path="../../../../../include" --include_path="../../../../../include/hw" --gcc --diag_warning=225 --preproc_with_compile --preproc_dependency="hs_mmcsdlib.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mmcsd_proto.obj: Z:/starterware_2013.10/mmcsdlib/mmcsd_proto.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../include/armv7a/am335x" --include_path="../../../../../include/armv7a" --include_path="../../../../../mmcsdlib/include" --include_path="../../../../../include" --include_path="../../../../../include/hw" --gcc --diag_warning=225 --preproc_with_compile --preproc_dependency="mmcsd_proto.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


