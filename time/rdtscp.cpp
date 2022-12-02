#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>
#include <random>
#include "rdtscp_timer.h"

using namespace std;

int a;

inline int func(long count)
{
    long sum = 0;
    for (long i = 0; i < count; i++)
        sum += i;
    return sum;
}

inline void sleep()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

inline int get_a(int count)
{
    return a;
}

void measure_cycles(long count)
{
    RdtscpTimer timer;
    timer.start();
    auto sum = get_a(count);
    timer.end();
    cout << count << " raw time " << timer.duration() << "res " << sum << "\n";
    // cout << " per element time: " <<  duration / (double)count << " gc" << sum << "\n";
}

int main()
{
    a = std::rand();
    for (long i = 1; i < 50; i++)
        measure_cycles(i);
}