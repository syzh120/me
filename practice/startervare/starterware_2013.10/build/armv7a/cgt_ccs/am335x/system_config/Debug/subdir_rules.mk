################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
cache.obj: Z:/starterware_2013.10/system_config/armv7a/cache.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../include/hw" --include_path="../../../../../../include/armv7a" --include_path="../../../../../../include/armv7a/am335x" --gcc --diag_warning=225 --unaligned_access=on --enum_type=packed --neon --preproc_with_compile --preproc_dependency="cache.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

clock.obj: Z:/starterware_2013.10/system_config/armv7a/am335x/clock.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../include/hw" --include_path="../../../../../../include/armv7a" --include_path="../../../../../../include/armv7a/am335x" --gcc --diag_warning=225 --unaligned_access=on --enum_type=packed --neon --preproc_with_compile --preproc_dependency="clock.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cp15.obj: Z:/starterware_2013.10/system_config/armv7a/cgt/cp15.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../include/hw" --include_path="../../../../../../include/armv7a" --include_path="../../../../../../include/armv7a/am335x" --gcc --diag_warning=225 --unaligned_access=on --enum_type=packed --neon --preproc_with_compile --preproc_dependency="cp15.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cpu.obj: Z:/starterware_2013.10/system_config/armv7a/cgt/cpu.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../include/hw" --include_path="../../../../../../include/armv7a" --include_path="../../../../../../include/armv7a/am335x" --gcc --diag_warning=225 --unaligned_access=on --enum_type=packed --neon --preproc_with_compile --preproc_dependency="cpu.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

device.obj: Z:/starterware_2013.10/system_config/armv7a/am335x/device.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../include/hw" --include_path="../../../../../../include/armv7a" --include_path="../../../../../../include/armv7a/am335x" --gcc --diag_warning=225 --unaligned_access=on --enum_type=packed --neon --preproc_with_compile --preproc_dependency="device.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

exceptionhandler.obj: Z:/starterware_2013.10/system_config/armv7a/am335x/cgt/exceptionhandler.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../include/hw" --include_path="../../../../../../include/armv7a" --include_path="../../../../../../include/armv7a/am335x" --gcc --diag_warning=225 --unaligned_access=on --enum_type=packed --neon --preproc_with_compile --preproc_dependency="exceptionhandler.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

init.obj: Z:/starterware_2013.10/system_config/armv7a/cgt/init.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../include/hw" --include_path="../../../../../../include/armv7a" --include_path="../../../../../../include/armv7a/am335x" --gcc --diag_warning=225 --unaligned_access=on --enum_type=packed --neon --preproc_with_compile --preproc_dependency="init.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

interrupt.obj: Z:/starterware_2013.10/system_config/armv7a/am335x/interrupt.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../include/hw" --include_path="../../../../../../include/armv7a" --include_path="../../../../../../include/armv7a/am335x" --gcc --diag_warning=225 --unaligned_access=on --enum_type=packed --neon --preproc_with_compile --preproc_dependency="interrupt.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mmu.obj: Z:/starterware_2013.10/system_config/armv7a/mmu.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../include/hw" --include_path="../../../../../../include/armv7a" --include_path="../../../../../../include/armv7a/am335x" --gcc --diag_warning=225 --unaligned_access=on --enum_type=packed --neon --preproc_with_compile --preproc_dependency="mmu.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup.obj: Z:/starterware_2013.10/system_config/armv7a/am335x/startup.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../include/hw" --include_path="../../../../../../include/armv7a" --include_path="../../../../../../include/armv7a/am335x" --gcc --diag_warning=225 --unaligned_access=on --enum_type=packed --neon --preproc_with_compile --preproc_dependency="startup.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


