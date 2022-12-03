#include <chrono>
#include <iostream>
#include <iomanip>
#include "rdtscp_timer.h"
#include "../hdr.h"
using namespace std;

unsigned long long loop_count = 10'000'000;
unsigned long long warmup_count = 1'000'000;

const int MAX_MEASUREMENTS = 100;

double chrono_timer()
{
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
    return duration.count();
}

double rdtscp_timer()
{
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
    return duration;
}

int main()
{
    std::cout << std::fixed << std::setprecision(9) << std::left;
    std::vector<double> chrono_measurements;
    std::vector<double> rdtscp_measurements;

    cout << "ns\n";
    for (int i = 0; i < MAX_MEASUREMENTS; i++)
        chrono_measurements.push_back(chrono_timer());
    print_hdr(chrono_measurements);
    cout << "***********\n";
    cout << "cycles\n";
    for (int i = 0; i < MAX_MEASUREMENTS; i++)
        rdtscp_measurements.push_back(rdtscp_timer());
    print_hdr(rdtscp_measurements);
}