################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
fat_usbmsc.obj: Z:/starterware_2013.10/third_party/fatfs/port/fat_usbmsc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --gcc --define=am335x --define=DMA_MODE --diag_warning=225 --display_error_number --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="fat_usbmsc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ff.obj: Z:/starterware_2013.10/third_party/fatfs/src/ff.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --gcc --define=am335x --define=DMA_MODE --diag_warning=225 --display_error_number --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="ff.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usb_host_msc.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_host_msc/usb_host_msc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../third_party/fatfs/src" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --gcc --define=am335x --define=DMA_MODE --diag_warning=225 --display_error_number --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="usb_host_msc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

