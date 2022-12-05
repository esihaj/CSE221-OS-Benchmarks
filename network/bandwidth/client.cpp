// https://think-async.com/Asio/boost_asio_1_24_0/doc/html/boost_asio/example/cpp11/echo/blocking_tcp_echo_client.cpp
//  blocking_tcp_echo_client.cpp
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <chrono>
#include <boost/asio.hpp>
#include "config.h"
#include "../../hdr.h"

using boost::asio::ip::tcp;
using namespace std;

const std::string MESSAGE_PING = "ping";
const std::string EXPECTED_PONG = "pong";
const int MAX_MEASUREMENTS = 100;

double measure_bandwidth(boost::asio::io_context &io_context, tcp::resolver::results_type &resolved_result, int packet_len)
{
  tcp::socket s(io_context);
  boost::asio::connect(s, resolved_result);

  size_t request_length = MESSAGE_PING.length();
  // initial message
  boost::asio::write(s, boost::asio::buffer(MESSAGE_PING, request_length));

  auto start = chrono::steady_clock::now();
  size_t total = 0;
  while (total < MAX_TRANSFER)
  {
    // char reply[packet_len];
    std::vector<char> reply(packet_len);
    size_t reply_length = boost::asio::read(s,
                                            boost::asio::buffer(reply, packet_len));
    total += reply_length;
  }
  auto end = chrono::steady_clock::now();
  auto duration_ms = chrono::duration_cast<chrono::milliseconds>((end - start)).count();
  return MAX_TRANSFER / (double)duration_ms / 1024; // MB/s
}
int main(int argc, char *argv[])
{
  vector<double> measurements;
  measurements.reserve(MAX_MEASUREMENTS);

  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    auto resolved_result = resolver.resolve(argv[1], argv[2]);
    int packet_len = PACKET_LENGTH;
    for (int i = 0; i < MAX_MEASUREMENTS; i++) {
      measurements.push_back(measure_bandwidth(io_context,resolved_result, packet_len));
      // cout << "packet: " << packet_len << " = " << measurements[i] << "\n";
      // packet_len *= 2;
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  print_hdr(measurements);
  return 0;
}
