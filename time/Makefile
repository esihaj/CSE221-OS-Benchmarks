HEADER	= nano/nanobench.h
OUT	= *.out
CC	 = clang++
FLAGS	 = -O0 -g -Wall
LFLAGS	 = 

NANO_FLAGS = -I../nanobench/
NANO_OBJ = ../nanobench.o

nano: nano_chrono_high_res_clock.cpp $(NANO_OBJ)
	$(CC) $(NANO_FLAGS) $(FLAGS) $(NANO_OBJ) nano_chrono_high_res_clock.cpp -std=c++17 -o nano.out

loop_time: loop_chrono_time.cpp $(NANO_OBJ)
	$(CC) $(NANO_FLAGS) $(FLAGS) $(NANO_OBJ) loop_chrono_time.cpp -std=c++17 -o loop_time.out

clean:
	rm -f $(OUT)