################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SA.cpp \
../src/Square.cpp \
../src/TS.cpp \
../src/exchange.pb.cpp \
../src/falter.cpp \
../src/main.cpp \
../src/sender.cpp 

OBJS += \
./src/SA.o \
./src/Square.o \
./src/TS.o \
./src/exchange.pb.o \
./src/falter.o \
./src/main.o \
./src/sender.o 

CPP_DEPS += \
./src/SA.d \
./src/Square.d \
./src/TS.d \
./src/exchange.pb.d \
./src/falter.d \
./src/main.d \
./src/sender.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


