#include <barrier>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <vector>
#include "memset.h"

using namespace std;

const int THREADS = 4;
const long SIZE = 64 * 1024;
const long ITERATIONS = 102400;

void single_thread()
{
  Memory mem(SIZE);
  auto start = chrono::steady_clock::now();
  auto garbage = mem.set(ITERATIONS);
  auto end = chrono::steady_clock::now();
  auto duration_ms = chrono::duration_cast<chrono::milliseconds>((end - start)).count();
  // cout << "du" << duration_ms <<;
  cerr << "garbage: " << garbage << "\n";
  cout << (SIZE * ITERATIONS * sizeof(DATA_TYPE) / 1024.0) / (double)duration_ms << " MB/S"
       << "\n";
}

int main()
{
  // const auto workers = { "thread_1", "thread_2", "thread_3" };
  // const auto workers = { Memory(SIZE), Memory(SIZE), Memory(SIZE), Memory(SIZE) };
  // const auto workers = { Memory(SIZE), Memory(SIZE), Memory(SIZE), Memory(SIZE) };
  single_thread();
  vector<Memory *> workers; //(THREADS, Memory(SIZE));
  for (int i = 0; i < THREADS; i++)
    workers.push_back(new Memory(SIZE));

  auto start = chrono::steady_clock::now();
  auto on_completion = [&start]() noexcept
  {
    std::cout << "sync point reached by all threads.\n";
    start = chrono::steady_clock::now();
  };

  std::barrier sync_point(std::ssize(workers), on_completion);

  int global_garbage = 0;
  auto work = [&](Memory *memory)
  {
    sync_point.arrive_and_wait(); // wait until every thread is ready.
    global_garbage += memory->set(ITERATIONS);
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
  auto duration_ms = chrono::duration_cast<chrono::milliseconds>((end - start)).count();
  // cout << "du" << duration_ms <<;
  cerr << "garbage: " << global_garbage << "\n";
  cout << (SIZE * ITERATIONS * THREADS * sizeof(DATA_TYPE) / 1024) / (double)duration_ms << " MB/S"
       << "\n";
  for (Memory *m : workers)
    delete m;
}