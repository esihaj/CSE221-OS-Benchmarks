//https://think-async.com/Asio/boost_asio_1_24_0/doc/html/boost_asio/example/cpp11/echo/blocking_tcp_echo_client.cpp
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <chrono>
#include <boost/asio.hpp>
#include "config.h"

using boost::asio::ip::tcp;
using namespace std;

const std::string MESSAGE_PING = "ping";
const std::string EXPECTED_PONG = "pong";

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::socket s(io_context);
    tcp::resolver resolver(io_context);
    boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));


    size_t request_length = MESSAGE_PING.length();
    cout << "round trip times in milliseconds" << std::endl;
    
    boost::asio::write(s, boost::asio::buffer(MESSAGE_PING, request_length ));

    auto start = chrono::steady_clock::now();
    size_t total = 0;
    while (total < MAX_TRANSFER) {
        char reply[PACKET_LENGTH];
        size_t reply_length = boost::asio::read(s,
            boost::asio::buffer(reply, PACKET_LENGTH));
        total += reply_length;
    }
    auto end = chrono::steady_clock::now();
    auto duration_ms = chrono::duration_cast<chrono::milliseconds>((end - start)).count();
    std::cout << duration_ms << "\n";
    std::cout << "bandwidth: " << MAX_TRANSFER / (double) duration_ms / 1024 << "MB/S\n";
    std::cout << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
