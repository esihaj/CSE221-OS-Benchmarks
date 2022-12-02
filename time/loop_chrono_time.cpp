#include <chrono>
#include <iostream>
#include <iomanip>
#include "rdtscp_timer.h"
using namespace std;

unsigned long long loop_count = 10'000'000;
unsigned long long warmup_count = 1'000'000;

void chrono_timer() {
    std::cout << std::fixed << std::setprecision(9) << std::left;
    auto start = chrono::high_resolution_clock::now();
    auto end = start;
    for (auto i = 0ull; i < warmup_count; i++)
    {
        end = chrono::high_resolution_clock::now();
    }
    start = chrono::high_resolution_clock::now();
    for (auto i = 0ull; i < loop_count; i++)
    {
        end = chrono::high_resolution_clock::now();
    }

    std::chrono::duration<double, nano> duration = end - start;
    duration /= loop_count;
    // duration *= 100÷0;
    cout << "time = " << duration.count() << " ns" << endl;
}

void rdtscp_timer() {
    std::cout << std::fixed << std::setprecision(9) << std::left;
    RdtscpTimer timer;
    
    for (auto i = 0ull; i < warmup_count; i++)
    {
        timer.start();
    }
    for (auto i = 0ull; i < loop_count; i++)
    {
        timer.finish();
    }

    unsigned long long duration = timer.duration();
    duration /= loop_count;
    cout << "time = " << duration << " cycles" << endl;
}

int main()
{
    chrono_timer();
    cout << "***********\n";
    rdtscp_timer();
}