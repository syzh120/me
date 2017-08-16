################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Usb_dev_serial.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_dev_serial/Usb_dev_serial.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --include_path="../../../../../../../examples/evmskAM335x/usb_dev_serial" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --gcc --define=am335x --diag_warning=225 --display_error_number --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="Usb_dev_serial.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usb_serial_structs.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_dev_serial/usb_serial_structs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --include_path="../../../../../../../examples/evmskAM335x/usb_dev_serial" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --gcc --define=am335x --diag_warning=225 --display_error_number --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="usb_serial_structs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ustdlib.obj: Z:/starterware_2013.10/examples/evmskAM335x/usb_dev_serial/ustdlib.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../usblib/include" --include_path="../../../../../../../grlib/include" --include_path="../../../../../../../examples/evmskAM335x/usb_dev_serial" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --gcc --define=am335x --diag_warning=225 --display_error_number --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="ustdlib.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


