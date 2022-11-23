OBJS	= nanobench.o
OUT	= *.out
CC	 = g++
FLAGS	 = -O3 -g -Wall -std=gnu++2a
LFLAGS	 = 

# all: $(OBJS)
# 	$(CC) $(NANO_FLAGS) -g $(OBJS) -o $(OUT) $(LFLAGS)

random-access.out: latency/random-access.cpp
	$(CC) $(FLAGS) latency/random-access.cpp -o random-access.out

linked-list.out: latency/linked-list.cpp
	$(CC) $(FLAGS) latency/linked-list.cpp -o linked-list.out

memcopy.out: bandwidth/memcopy.cpp
	$(CC) $(FLAGS) bandwidth/memcopy.cpp -o memcopy.out

memset.out: bandwidth/memset.cpp bandwidth/memset.h
	$(CC) $(FLAGS) bandwidth/memset.cpp -o memset.out

parallel_memset.out: bandwidth/parallel_memset.cpp bandwidth/memset.h
	$(CC) $(FLAGS) bandwidth/memset.cpp bandwidth/parallel_memset.cpp -o parallel_memset.out

traverse_memory.out: bandwidth/traverse_memory.cpp
	$(CC) $(FLAGS) bandwidth/traverse_memory.cpp -o traverse_memory.out


clean:
	rm -f $(OBJS) $(OUT)
	