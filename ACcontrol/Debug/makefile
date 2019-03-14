################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/c2000_6.2.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"D:/ECT/project/ECT-2017-8-29/F2812.cmd" \
"D:/ECT/project/ECT-2017-8-29/Debug/main.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP28_Xintf.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP28_SysCtrl.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP28_Sci.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP28_PieVect.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP28_PieCtrl.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP28_InitPeripherals.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP28_Gpio.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP28_GlobalVariableDefs.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP28_DefaultIsr.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP28_CpuTimers.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP281x_usDelay.obj" \
"D:/ECT/project/ECT-2017-8-29/Debug/DSP281x_CodeStartBranch.obj" \
"D:/ECT/project/ECT-2017-8-29/DSP281x_Headers_nonBIOS2.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
D:/ECT/project/ECT-2017-8-29/ACcontrol/../Debug/ACcontrol.out \

EXE_OUTPUTS__QUOTED += \
"D:\ECT\project\ECT-2017-8-29\Debug\ACcontrol.out" \

BIN_OUTPUTS += \
D:/ECT/project/ECT-2017-8-29/Debug/ACcontrol.hex \

BIN_OUTPUTS__QUOTED += \
"D:\ECT\project\ECT-2017-8-29\Debug\ACcontrol.hex" \


# All Target
all: D:/ECT/project/ECT-2017-8-29/ACcontrol/../Debug/ACcontrol.out

# Tool invocations
D:/ECT/project/ECT-2017-8-29/ACcontrol/../Debug/ACcontrol.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --obj_directory="D:/ECT/project/ECT-2017-8-29/Debug" -z -m"D:/ECT/project/ECT-2017-8-29/Debug/ACcontrol.map" --stack_size=800 --warn_sections -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -i"D:/ECT/project/ECT-2017-8-29/ACcontrol" -i"D:/ECT/project/ECT-2017-8-29" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="ACcontrol_linkInfo.xml" --rom_model -o "D:/ECT/project/ECT-2017-8-29/ACcontrol/../Debug/ACcontrol.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

D:/ECT/project/ECT-2017-8-29/Debug/ACcontrol.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/hex2000"  -o "D:/ECT/project/ECT-2017-8-29/Debug/ACcontrol.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "DSP28_CpuTimers.pp" "DSP28_DefaultIsr.pp" "DSP28_GlobalVariableDefs.pp" "DSP28_Gpio.pp" "DSP28_InitPeripherals.pp" "DSP28_PieCtrl.pp" "DSP28_PieVect.pp" "DSP28_Sci.pp" "DSP28_SysCtrl.pp" "DSP28_Xintf.pp" "main.pp" 
	-$(RM) "D:\ECT\project\ECT-2017-8-29\Debug\DSP281x_CodeStartBranch.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP281x_usDelay.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP28_CpuTimers.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP28_DefaultIsr.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP28_GlobalVariableDefs.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP28_Gpio.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP28_InitPeripherals.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP28_PieCtrl.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP28_PieVect.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP28_Sci.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP28_SysCtrl.obj" "D:\ECT\project\ECT-2017-8-29\Debug\DSP28_Xintf.obj" "D:\ECT\project\ECT-2017-8-29\Debug\main.obj" 
	-$(RM) "DSP281x_CodeStartBranch.pp" "DSP281x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

