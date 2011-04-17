CC = gcc
CC_FLAGS = -W -Wall -fopenmp
EXE_1 = piSerial 
EXE_2 = piParallel1

all : $(EXE_1) $(EXE_2)

$(EXE_1) : pi_serial.c
	$(CC) $(CC_FLAGS) $< -o $@

$(EXE_2) : pi_parallel1.c
	$(CC) $(CC_FLAGS) $< -o $@

clean :
	rm -f $(EXE_1) $(EXE_2)
