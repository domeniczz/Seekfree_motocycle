################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/infineon_libraries/iLLD/TC37A/Tricore/Hssl/Std/IfxHssl.c 

OBJS += \
./Libraries/infineon_libraries/iLLD/TC37A/Tricore/Hssl/Std/IfxHssl.o 

COMPILED_SRCS += \
./Libraries/infineon_libraries/iLLD/TC37A/Tricore/Hssl/Std/IfxHssl.src 

C_DEPS += \
./Libraries/infineon_libraries/iLLD/TC37A/Tricore/Hssl/Std/IfxHssl.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/infineon_libraries/iLLD/TC37A/Tricore/Hssl/Std/%.src: ../Libraries/infineon_libraries/iLLD/TC37A/Tricore/Hssl/Std/%.c Libraries/infineon_libraries/iLLD/TC37A/Tricore/Hssl/Std/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc "-fD:/CodeField/AURIX152_workspace/Seekfree_motocycle/Seekfree_TC377_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/infineon_libraries/iLLD/TC37A/Tricore/Hssl/Std/%.o: ./Libraries/infineon_libraries/iLLD/TC37A/Tricore/Hssl/Std/%.src Libraries/infineon_libraries/iLLD/TC37A/Tricore/Hssl/Std/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


