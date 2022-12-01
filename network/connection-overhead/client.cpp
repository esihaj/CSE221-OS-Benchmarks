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

using boost::asio::ip::tcp;
using namespace std;

enum
{
  max_length = 8
};

const std::string MESSAGE_PING = "ping";
const std::string EXPECTED_PONG = "pong";

class Measurement
{
  public:
  long long setup, teardown;
};

Measurement connect(boost::asio::io_context &io_context, tcp::resolver::results_type &resolved_results)
{
  tcp::socket s(io_context);
  try
  {
    auto start = chrono::steady_clock::now();
    boost::asio::connect(s, resolved_results);
    auto end = chrono::steady_clock::now();
    auto setup_micros = chrono::duration_cast<chrono::microseconds>((end - start)).count();

    start = chrono::steady_clock::now();
    s.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    s.close();
    end = chrono::steady_clock::now();
    auto teardown_micros = chrono::duration_cast<chrono::microseconds>((end - start)).count();

    return {setup_micros, teardown_micros};
  }

  catch (std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return {-1,-1};
}

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type resolved_result = resolver.resolve(argv[1], argv[2]);

    for (int i = 0; i < 100; i++)
    {
      Measurement m = connect(io_context, resolved_result);
      cout << m.setup << ',' << m.teardown << '\n';
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
