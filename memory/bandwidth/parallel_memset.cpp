#include <barrier>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <vector>
#include "memset.h"
#include "../../hdr.h"

using namespace std;

const int THREADS = 4;
const long SIZE = 64 * 1024;
const long ITERATIONS = 102400;

void single_thread()
{
  Memory mem(SIZE);
  vector<double> measurements; // in MB/S
  measurements.reserve(ITERATIONS);
  int garbage;
  std::cout << "size in bytes: " << mem.total_size_bytes() << "\n";
  for (int i = 0; i < ITERATIONS; i++)
  {
    auto start = chrono::steady_clock::now();
    garbage = mem.set_once();
    auto end = chrono::steady_clock::now();
    double duration_micros = chrono::duration_cast<chrono::microseconds>((end - start)).count();
    measurements.push_back(mem.total_size_bytes() / duration_micros);
  }
  std::cerr << "garbage: " << garbage << "\n";
  std::cout << "MB/S\n";
  print_hdr(measurements);
  // cout << "du" << duration_ms <<;
  
}

double parallel() {
  vector<Memory *> workers; //(THREADS, Memory(SIZE));
  for (int i = 0; i < THREADS; i++)
    workers.push_back(new Memory(SIZE));
  
  long bytes = workers[0]->total_size_bytes();

  auto start = chrono::steady_clock::now();
  auto on_completion = [&start]() noexcept
  {
    // std::cout << "sync point reached by all threads.\n";
    start = chrono::steady_clock::now();
  };

  std::barrier sync_point(std::ssize(workers), on_completion);

  int global_garbage = 0;
  auto work = [&](Memory *memory)
  {
    sync_point.arrive_and_wait(); // wait until every thread is ready.
    global_garbage += memory->set(128);
  };

  std::vector<std::thread> threads;
  for (Memory *worker : workers)
  {
    threads.emplace_back(work, worker);
  }
  for (auto &thread : threads)
  {
    thread.join();
  }
  auto end = chrono::steady_clock::now();
  double duration_micros = chrono::duration_cast<chrono::microseconds>((end - start)).count();
  // g
  for (Memory *m : workers)
    delete m;

  return (bytes * THREADS * 128) / duration_micros;
}

int main()
{
  single_thread();

  vector<double> measurements;
  measurements.reserve(ITERATIONS);
  for (int i = 0; i < ITERATIONS; i++) {
    measurements.push_back(parallel());
  }
  cout << "************\n";
  cout << "parallel:\n";g
  print_hdr(measurements);
}