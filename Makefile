OBJS	= nanobench.o
HEADER	= nano/nanobench.h
OUT	= *.out
CC	 = clang++
FLAGS	 = -O0 -g -Wall
LFLAGS	 = 

NANO_FLAGS = -I./nanobench/

# all: $(OBJS)
# 	$(CC) $(NANO_FLAGS) -g $(OBJS) -o $(OUT) $(LFLAGS)

nanobench.o: nanobench/nanobench.cpp
	$(CC) $(NANO_FLAGS) $(FLAGS) -c nanobench/nanobench.cpp -std=c++17

clean:
	rm -f $(OBJS) $(OUT)