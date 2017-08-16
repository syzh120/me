################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ramdisk.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_dev_msc/ramdisk.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../examples/evmskAM335x/usb_dev_msc" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --gcc --define=am335x --define=DMA_MODE --diag_warning=225 --display_error_number --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="ramdisk.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usb_dev_msc.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_dev_msc/usb_dev_msc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../examples/evmskAM335x/usb_dev_msc" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --gcc --define=am335x --define=DMA_MODE --diag_warning=225 --display_error_number --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="usb_dev_msc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usb_msc_structs.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_dev_msc/usb_msc_structs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../examples/evmskAM335x/usb_dev_msc" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --gcc --define=am335x --define=DMA_MODE --diag_warning=225 --display_error_number --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="usb_msc_structs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usbdmscglue.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_dev_msc/usbdmscglue.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../examples/evmskAM335x/usb_dev_msc" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --gcc --define=am335x --define=DMA_MODE --diag_warning=225 --display_error_number --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="usbdmscglue.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


