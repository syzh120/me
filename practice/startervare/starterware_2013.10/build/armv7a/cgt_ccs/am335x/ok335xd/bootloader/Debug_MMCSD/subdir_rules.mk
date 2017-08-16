################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
bl_copy.obj: Z:/starterware_2013.10/bootloader/src/bl_copy.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="bl_copy.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

bl_hsmmcsd.obj: Z:/starterware_2013.10/bootloader/src/bl_hsmmcsd.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="bl_hsmmcsd.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

bl_init.obj: Z:/starterware_2013.10/bootloader/src/armv7a/cgt/bl_init.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="bl_init.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

bl_main.obj: Z:/starterware_2013.10/bootloader/src/bl_main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="bl_main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

bl_platform.obj: Z:/starterware_2013.10/bootloader/src/armv7a/am335x/bl_platform.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="bl_platform.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cache.obj: Z:/starterware_2013.10/system_config/armv7a/cache.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="cache.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cp15.obj: Z:/starterware_2013.10/system_config/armv7a/cgt/cp15.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="cp15.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

device.obj: Z:/starterware_2013.10/system_config/armv7a/am335x/device.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="device.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

fat_mmcsd.obj: Z:/starterware_2013.10/third_party/fatfs/port/fat_mmcsd.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fat_mmcsd.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ff.obj: Z:/starterware_2013.10/third_party/fatfs/src/ff.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="ff.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mmu.obj: Z:/starterware_2013.10/system_config/armv7a/mmu.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/" --include_path="../../../../../../../nandlib/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../bootloader/include" --include_path="../../../../../../../bootloader/include/armv7a/am335x" --include_path="../../../../../../../mmcsdlib/include" --include_path="../../../../../../../third_party/xmodem" --gcc --define=am335x --define=ok335xd --define=MMCSD --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="mmu.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


