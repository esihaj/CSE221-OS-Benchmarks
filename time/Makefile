HEADER	= nano/nanobench.h
OUT	= *.out
CC	 = g++
FLAGS	 = -O0 -g -Wall -std=c++17
LFLAGS	 = 
RFLAGS = -lhdr_histogram

NANO_FLAGS = -I../nanobench/
NANO_OBJ = ../nanobench.o

nano: nano_chrono_high_res_clock.cpp $(NANO_OBJ)
	$(CC) $(NANO_FLAGS) $(FLAGS) $(NANO_OBJ) nano_chrono_high_res_clock.cpp -o nano.out $(RFLAGS)

loop_time: loop_time.cpp
	$(CC) $(FLAGS) loop_time.cpp -o loop_time.out $(RFLAGS)

rdtscp: rdtscp.cpp rdtscp_timer.h
	$(CC) $(FLAGS) rdtscp.cpp -o rdtscp.out $(RFLAGS)

loop_overhead: loop_overhead.cpp rdtscp_timer.h
	$(CC) $(FLAGS) loop_overhead.cpp -o loop_overhead.out $(RFLAGS)

clean:
	rm -f $(OUT)