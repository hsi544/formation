CC = gcc
CC_FLAGS = -W -Wall -fopenmp
EXE = helloWorld

all : $(EXE)

$(EXE) : hello.c
	$(CC) $(CC_FLAGS) $< -o $@

clean :
	rm -f $(EXE)
