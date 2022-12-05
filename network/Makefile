OUT	= *.out
CC	 = g++
BOOST = ../../boost_1_80_0/
FLAGS	 = -O3 -g -Wall -std=gnu++2a -I$(BOOST) -Wno-deprecated-declarations
RFLAGS = -lhdr_histogram

server.out: server.cpp
	$(CC) $(FLAGS) server.cpp -o server.out

client.out: client.cpp
	$(CC) $(FLAGS) client.cpp -o client.out $(RFLAGS)

ping-icmp.out: icmp/icmp_header.hpp icmp/ipv4_header.hpp icmp/ping.cpp
	$(CC) $(FLAGS) icmp/ping.cpp -o ping-icmp.out

bw-client.out: bandwidth/client.cpp bandwidth/config.h 
	$(CC) $(FLAGS) bandwidth/client.cpp -o bw-client.out $(RFLAGS)

bw-server.out: bandwidth/server.cpp bandwidth/config.h
	$(CC) $(FLAGS) bandwidth/server.cpp -o bw-server.out

connection-client.out: connection-overhead/client.cpp
	$(CC) $(FLAGS) connection-overhead/client.cpp -o connection-client.out

connection-server.out: connection-overhead/server.cpp
	$(CC) $(FLAGS) connection-overhead/server.cpp -o connection-server.out
	
clean:
	rm -f $(OUT)
	