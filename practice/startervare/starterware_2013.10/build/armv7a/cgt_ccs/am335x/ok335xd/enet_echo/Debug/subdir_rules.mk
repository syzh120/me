################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
echod.obj: Z:/starterware_2013.10/third_party/lwip-1.4.0/apps/echoserver_raw/echod.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../third_party/lwip-1.4.0" --include_path="../../../../../../../third_party/lwip-1.4.0/src/include" --include_path="../../../../../../../third_party/lwip-1.4.0/src/include/ipv4" --include_path="../../../../../../../third_party/lwip-1.4.0/src/include/lwip" --include_path="../../../../../../../third_party/lwip-1.4.0/ports/cpsw/include" --include_path="../../../../../../../third_party/lwip-1.4.0/apps/echoserver_raw" --include_path="../../../../../../../examples/evmskAM335x/enet_echo" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --gcc --define=am335x --define=evmskAM335x --diag_warning=225 --preproc_with_compile --preproc_dependency="echod.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

enetEcho.obj: Z:/starterware_2013.10/examples/evmskAM335x/enet_echo/enetEcho.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../third_party/lwip-1.4.0" --include_path="../../../../../../../third_party/lwip-1.4.0/src/include" --include_path="../../../../../../../third_party/lwip-1.4.0/src/include/ipv4" --include_path="../../../../../../../third_party/lwip-1.4.0/src/include/lwip" --include_path="../../../../../../../third_party/lwip-1.4.0/ports/cpsw/include" --include_path="../../../../../../../third_party/lwip-1.4.0/apps/echoserver_raw" --include_path="../../../../../../../examples/evmskAM335x/enet_echo" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --gcc --define=am335x --define=evmskAM335x --diag_warning=225 --preproc_with_compile --preproc_dependency="enetEcho.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

lwiplib.obj: Z:/starterware_2013.10/third_party/lwip-1.4.0/ports/cpsw/lwiplib.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --include_path="D:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="../../../../../../../third_party/lwip-1.4.0" --include_path="../../../../../../../third_party/lwip-1.4.0/src/include" --include_path="../../../../../../../third_party/lwip-1.4.0/src/include/ipv4" --include_path="../../../../../../../third_party/lwip-1.4.0/src/include/lwip" --include_path="../../../../../../../third_party/lwip-1.4.0/ports/cpsw/include" --include_path="../../../../../../../third_party/lwip-1.4.0/apps/echoserver_raw" --include_path="../../../../../../../examples/evmskAM335x/enet_echo" --include_path="../../../../../../../include" --include_path="../../../../../../../include/hw" --include_path="../../../../../../../include/armv7a/am335x" --include_path="../../../../../../../include/armv7a" --gcc --define=am335x --define=evmskAM335x --diag_warning=225 --preproc_with_compile --preproc_dependency="lwiplib.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


