################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
touch.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_dev_mouse/touch.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../examples/evmskAM335x/usb_dev_mouse" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --gcc --define=am335x --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="touch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usb_dev_mouse.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_dev_mouse/usb_dev_mouse.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../examples/evmskAM335x/usb_dev_mouse" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --gcc --define=am335x --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="usb_dev_mouse.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usb_mouse_structs.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_dev_mouse/usb_mouse_structs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../examples/evmskAM335x/usb_dev_mouse" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --gcc --define=am335x --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="usb_mouse_structs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


