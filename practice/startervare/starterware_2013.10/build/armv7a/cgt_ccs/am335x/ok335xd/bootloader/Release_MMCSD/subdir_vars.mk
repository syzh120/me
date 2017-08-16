################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../boot.cmd 

ASM_SRCS += \
Z:/starterware_2013.10/bootloader/src/armv7a/cgt/bl_init.asm \
Z:/starterware_2013.10/system_config/armv7a/cgt/cp15.asm 

C_SRCS += \
Z:/starterware_2013.10/bootloader/src/bl_copy.c \
Z:/starterware_2013.10/bootloader/src/bl_hsmmcsd.c \
Z:/starterware_2013.10/bootloader/src/bl_main.c \
Z:/starterware_2013.10/bootloader/src/armv7a/am335x/bl_platform.c \
Z:/starterware_2013.10/system_config/armv7a/cache.c \
Z:/starterware_2013.10/system_config/armv7a/am335x/device.c \
Z:/starterware_2013.10/third_party/fatfs/port/fat_mmcsd.c \
Z:/starterware_2013.10/third_party/fatfs/src/ff.c \
Z:/starterware_2013.10/system_config/armv7a/mmu.c 

OBJS += \
./bl_copy.obj \
./bl_hsmmcsd.obj \
./bl_init.obj \
./bl_main.obj \
./bl_platform.obj \
./cache.obj \
./cp15.obj \
./device.obj \
./fat_mmcsd.obj \
./ff.obj \
./mmu.obj 

ASM_DEPS += \
./bl_init.pp \
./cp15.pp 

C_DEPS += \
./bl_copy.pp \
./bl_hsmmcsd.pp \
./bl_main.pp \
./bl_platform.pp \
./cache.pp \
./device.pp \
./fat_mmcsd.pp \
./ff.pp \
./mmu.pp 

C_DEPS__QUOTED += \
"bl_copy.pp" \
"bl_hsmmcsd.pp" \
"bl_main.pp" \
"bl_platform.pp" \
"cache.pp" \
"device.pp" \
"fat_mmcsd.pp" \
"ff.pp" \
"mmu.pp" 

OBJS__QUOTED += \
"bl_copy.obj" \
"bl_hsmmcsd.obj" \
"bl_init.obj" \
"bl_main.obj" \
"bl_platform.obj" \
"cache.obj" \
"cp15.obj" \
"device.obj" \
"fat_mmcsd.obj" \
"ff.obj" \
"mmu.obj" 

ASM_DEPS__QUOTED += \
"bl_init.pp" \
"cp15.pp" 

C_SRCS__QUOTED += \
"Z:/starterware_2013.10/bootloader/src/bl_copy.c" \
"Z:/starterware_2013.10/bootloader/src/bl_hsmmcsd.c" \
"Z:/starterware_2013.10/bootloader/src/bl_main.c" \
"Z:/starterware_2013.10/bootloader/src/armv7a/am335x/bl_platform.c" \
"Z:/starterware_2013.10/system_config/armv7a/cache.c" \
"Z:/starterware_2013.10/system_config/armv7a/am335x/device.c" \
"Z:/starterware_2013.10/third_party/fatfs/port/fat_mmcsd.c" \
"Z:/starterware_2013.10/third_party/fatfs/src/ff.c" \
"Z:/starterware_2013.10/system_config/armv7a/mmu.c" 

ASM_SRCS__QUOTED += \
"Z:/starterware_2013.10/bootloader/src/armv7a/cgt/bl_init.asm" \
"Z:/starterware_2013.10/system_config/armv7a/cgt/cp15.asm" 


