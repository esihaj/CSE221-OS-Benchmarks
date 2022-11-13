OBJS	= nanobench.o
OUT	= *.out
CC	 = clang++
FLAGS	 = -O3 -g -Wall -std=gnu++20
LFLAGS	 = 

# all: $(OBJS)
# 	$(CC) $(NANO_FLAGS) -g $(OBJS) -o $(OUT) $(LFLAGS)

random-access.out: latency/random-access.cpp
	$(CC) $(FLAGS) latency/random-access.cpp -o random-access.out

linked-list.out: latency/linked-list.cpp
	$(CC) $(FLAGS) latency/linked-list.cpp -o linked-list.out

memcopy.out: bandwidth/memcopy.cpp
	$(CC) $(FLAGS) bandwidth/memcopy.cpp -o memcopy.out


clean:
	rm -f $(OBJS) $(OUT)
	