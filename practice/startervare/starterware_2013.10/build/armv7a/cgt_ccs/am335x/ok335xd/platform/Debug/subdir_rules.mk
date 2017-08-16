################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
board.obj: Z:/starterware_2013.10/platform/evmAM335x/board.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="board.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cpsw.obj: Z:/starterware_2013.10/platform/ok335xd/cpsw.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="cpsw.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ctlregcontext.obj: Z:/starterware_2013.10/platform/ok335xd/ctlregcontext.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="ctlregcontext.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dcan.obj: Z:/starterware_2013.10/platform/ok335xd/dcan.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="dcan.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dmtimer.obj: Z:/starterware_2013.10/platform/ok335xd/dmtimer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="dmtimer.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

edma.obj: Z:/starterware_2013.10/platform/ok335xd/edma.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="edma.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

eeprom.obj: Z:/starterware_2013.10/platform/ok335xd/eeprom.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="eeprom.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

gpio.obj: Z:/starterware_2013.10/platform/ok335xd/gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="gpio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

hs_mmcsd.obj: Z:/starterware_2013.10/platform/ok335xd/hs_mmcsd.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="hs_mmcsd.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

hsi2c.obj: Z:/starterware_2013.10/platform/ok335xd/hsi2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="hsi2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

lcd.obj: Z:/starterware_2013.10/platform/ok335xd/lcd.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="lcd.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mcasp.obj: Z:/starterware_2013.10/platform/ok335xd/mcasp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="mcasp.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pwmss.obj: Z:/starterware_2013.10/platform/ok335xd/pwmss.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="pwmss.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rtc.obj: Z:/starterware_2013.10/platform/ok335xd/rtc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="rtc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sysdelay.obj: Z:/starterware_2013.10/platform/ok335xd/sysdelay.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="sysdelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sysperf.obj: Z:/starterware_2013.10/platform/ok335xd/sysperf.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="sysperf.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tscAdc.obj: Z:/starterware_2013.10/platform/ok335xd/tscAdc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="tscAdc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart.obj: Z:/starterware_2013.10/platform/ok335xd/uart.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="uart.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uartConsole.obj: Z:/starterware_2013.10/platform/ok335xd/uartConsole.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="uartConsole.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usb.obj: Z:/starterware_2013.10/platform/ok335xd/usb.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="usb.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

watchdog.obj: Z:/starterware_2013.10/platform/ok335xd/watchdog.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../include" --include_path="../../../../../../../include/armv7a" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/hw" --gcc --define=DMA_MODE --diag_warning=225 --unaligned_access=on --enum_type=packed --preproc_with_compile --preproc_dependency="watchdog.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


