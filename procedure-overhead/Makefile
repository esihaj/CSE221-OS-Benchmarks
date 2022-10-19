HEADER	= nano/nanobench.h
OUT	= *.out
CC	 = clang++
FLAGS	 = -O0 -g -Wall -std=c++17
LFLAGS	 = 

NANO_FLAGS = -I../nanobench/
NANO_OBJ = ../nanobench.o

overhead: procedure-overhead.cpp $(NANO_OBJ)
	$(CC) $(NANO_FLAGS) $(FLAGS) $(NANO_OBJ) procedure-overhead.cpp -o overhead.out 

clean:
	rm -f $(OUT)