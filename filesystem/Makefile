OUT	= *.out
CC	 = g++
FLAGS	 = -O3 -g -Wall -std=gnu++2a
RFLAGS = -lhdr_histogram 

file_cache.out: file_cache.cpp
	$(CC) $(FLAGS) file_cache.cpp -o file_cache.out $(RFLAGS)

read.out: read.cpp rand-large.bin
	$(CC) $(FLAGS) read.cpp -o read.out

rand-large.bin:
	dd if=/dev/urandom of=rand-large.bin bs=4K count=5M

clean:
	rm -f $(OUT)
	