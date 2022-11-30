OUT	= *.out
CC	 = g++
BOOST = /Users/esihaj/workspace/boost_1_80_0/
FLAGS	 = -O3 -g -Wall -std=gnu++2a -I$(BOOST) -Wno-deprecated-declarations

server.out: server.cpp
	$(CC) $(FLAGS) server.cpp -o server.out

client.out: client.cpp
	$(CC) $(FLAGS) client.cpp -o client.out

ping-icmp.out: icmp/icmp_header.hpp icmp/ipv4_header.hpp icmp/ping.cpp
	$(CC) $(FLAGS) icmp/ping.cpp -o ping-icmp.out

bw-client.out: bandwidth/client.cpp
	$(CC) $(FLAGS) bandwidth/client.cpp -o bw-client.out

bw-server.out: bandwidth/server.cpp
	$(CC) $(FLAGS) bandwidth/server.cpp -o bw-server.out

clean:
	rm -f $(OUT)
	