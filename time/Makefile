HEADER	= nano/nanobench.h
OUT	= *.out
CC	 = g++
FLAGS	 = -O0 -g -Wall -std=c++17
LFLAGS	 = 

NANO_FLAGS = -I../nanobench/
NANO_OBJ = ../nanobench.o

nano: nano_chrono_high_res_clock.cpp $(NANO_OBJ)
	$(CC) $(NANO_FLAGS) $(FLAGS) $(NANO_OBJ) nano_chrono_high_res_clock.cpp -o nano.out

loop_time: loop_chrono_time.cpp $(NANO_OBJ)
	$(CC) $(NANO_FLAGS) $(FLAGS) $(NANO_OBJ) loop_chrono_time.cpp -o loop_time.out

rdtscp: rdtscp.cpp rdtscp_timer.h
	$(CC) $(FLAGS) rdtscp.cpp -o rdtscp.out

clean:
	rm -f $(OUT)