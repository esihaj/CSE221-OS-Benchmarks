OUT	= *.out
CC	 = g++
FLAGS	 = -O3 -g -Wall -std=gnu++2a

file_cache.out: file_cache.cpp
	$(CC) $(FLAGS) file_cache.cpp -o file_cache.out

read.out: read.cpp
	$(CC) $(FLAGS) read.cpp -o read.out

clean:
	rm -f $(OUT)
	