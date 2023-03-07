################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Appello1Settembre.c \
../Gestione_clienti.c \
../Gestione_ordini.c \
../Gestione_prodotti.c 

OBJS += \
./Appello1Settembre.o \
./Gestione_clienti.o \
./Gestione_ordini.o \
./Gestione_prodotti.o 

C_DEPS += \
./Appello1Settembre.d \
./Gestione_clienti.d \
./Gestione_ordini.d \
./Gestione_prodotti.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


