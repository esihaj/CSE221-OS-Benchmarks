//https://think-async.com/Asio/boost_asio_1_24_0/doc/html/boost_asio/example/cpp11/echo/blocking_tcp_echo_server.cpp
// blocking_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>
#include <boost/asio.hpp>
#include "config.h"

using boost::asio::ip::tcp;


const std::string EXPECTED_PING = "ping";
const std::string RESPONSE_PONG = "pong";

int packet_len = PACKET_LENGTH_START;

void session(tcp::socket sock)
{
  std::vector<char> data(packet_len);
  try
  {
    boost::system::error_code error;
    size_t length = sock.read_some(boost::asio::buffer(data), error);
    if (error == boost::asio::error::eof)
      return; // Connection closed cleanly by peer.
    else if (error)
      throw boost::system::system_error(error); // Some other error.

    if (length != EXPECTED_PING.length())
      std::cout << "partial read " << length << std::endl;

    size_t total = 0;
    while (total < MAX_TRANSFER)
    {
      size_t write_len = boost::asio::write(sock, boost::asio::buffer(data, packet_len));
      total += write_len;
    }
    std::cout << "total " << total << "\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
  packet_len *= 2;

}

void server(boost::asio::io_context& io_context, unsigned short port)
{
  tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    std::thread(session, a.accept()).detach();
  }
}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    server(io_context, std::atoi(argv[1]));
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
