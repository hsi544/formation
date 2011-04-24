CC = gcc
CC_FLAGS = -W -Wall -fopenmp
EXE_1 = piSerial 
EXE_2 = piParallel1
EXE_3 = piParallel3
EXE_4 = piParallel4

all : $(EXE_1) $(EXE_2) $(EXE_3) $(EXE_4)

$(EXE_1) : pi_serial.c
	$(CC) $(CC_FLAGS) $< -o $@

$(EXE_2) : pi_parallel1.c
	$(CC) $(CC_FLAGS) $< -o $@

$(EXE_3) : pi_parallel2.c
	$(CC) $(CC_FLAGS) $< -o $@

$(EXE_4) : pi_parallel3.c
	$(CC) $(CC_FLAGS) $< -o $@

clean :
	rm -f $(EXE_1) $(EXE_2) $(EXE_3) $(EXE_4)
