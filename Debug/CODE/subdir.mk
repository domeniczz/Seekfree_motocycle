################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/Angle_handle.c \
../CODE/Attitude_Calculation.c \
../CODE/GY901S.c \
../CODE/Init.c \
../CODE/SoftIIC.c \
../CODE/data_sheet.c \
../CODE/direction.c \
../CODE/duoji.c \
../CODE/icm20602.c \
../CODE/image_processing.c \
../CODE/mohuduoji.c \
../CODE/select_median.c \
../CODE/situation.c \
../CODE/speed_measure.c 

OBJS += \
./CODE/Angle_handle.o \
./CODE/Attitude_Calculation.o \
./CODE/GY901S.o \
./CODE/Init.o \
./CODE/SoftIIC.o \
./CODE/data_sheet.o \
./CODE/direction.o \
./CODE/duoji.o \
./CODE/icm20602.o \
./CODE/image_processing.o \
./CODE/mohuduoji.o \
./CODE/select_median.o \
./CODE/situation.o \
./CODE/speed_measure.o 

COMPILED_SRCS += \
./CODE/Angle_handle.src \
./CODE/Attitude_Calculation.src \
./CODE/GY901S.src \
./CODE/Init.src \
./CODE/SoftIIC.src \
./CODE/data_sheet.src \
./CODE/direction.src \
./CODE/duoji.src \
./CODE/icm20602.src \
./CODE/image_processing.src \
./CODE/mohuduoji.src \
./CODE/select_median.src \
./CODE/situation.src \
./CODE/speed_measure.src 

C_DEPS += \
./CODE/Angle_handle.d \
./CODE/Attitude_Calculation.d \
./CODE/GY901S.d \
./CODE/Init.d \
./CODE/SoftIIC.d \
./CODE/data_sheet.d \
./CODE/direction.d \
./CODE/duoji.d \
./CODE/icm20602.d \
./CODE/image_processing.d \
./CODE/mohuduoji.d \
./CODE/select_median.d \
./CODE/situation.d \
./CODE/speed_measure.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/%.src: ../CODE/%.c CODE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fE:/smartcar/AURIX-v1.5.4-workspace/Seekfree_TC377_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/%.o: ./CODE/%.src CODE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


