OBJS	= nanobench.o
HEADER	= nano/nanobench.h
OUT	= *.out
CC	 = clang++
FLAGS	 = -O0 -g -Wall -std=c++17
LFLAGS	 = 

NANO_FLAGS = -I./nanobench/

# all: $(OBJS)
# 	$(CC) $(NANO_FLAGS) -g $(OBJS) -o $(OUT) $(LFLAGS)

nanobench.o: nanobench/nanobench.cpp
	$(CC) $(NANO_FLAGS) $(FLAGS) -c nanobench/nanobench.cpp

clean:
	rm -f $(OBJS) $(OUT)

syscall: syscall.cpp $(NANO_OBJ)
	$(CC) $(NANO_FLAGS) $(FLAGS) nanobench.o syscall.cpp -o syscall.out 

thread: thread.cpp $(NANO_OBJ)
	$(CC) $(NANO_FLAGS) $(FLAGS) nanobench.o thread.cpp -o thread.out 
	