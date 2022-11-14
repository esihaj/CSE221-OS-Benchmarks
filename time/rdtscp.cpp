
#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

int a;

inline int func(long count)
{
    long sum = 0;
    for (long i = 0; i < count; i++)
        sum += i;
    return sum;
}

inline void sleep() {
    std::this_thread::sleep_for (std::chrono::milliseconds(1));
}

inline int get_a(int count) {
    return a;
} 

void measure_cycles(long count)
{
    unsigned long long start, end;
    unsigned int cycles_low, cycles_high, cycles_low1, cycles_high1;
    asm volatile("CPUID\n\t"
                 "RDTSC\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 : "=r"(cycles_high), "=r"(cycles_low)::"%rax", "%rbx", "%rcx", "%rdx");
    auto sum = get_a(count);
    asm volatile("RDTSCP\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 "CPUID\n\t"
                 : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

    start = (((uint64_t)cycles_high << 32) | cycles_low);
    end = (((uint64_t)cycles_high1 << 32) | cycles_low1);

    auto duration = (end - start);
    cout << count << " raw time " << duration << "res " << sum << "\n";
    // cout << " per element time: " <<  duration / (double)count << " gc" << sum << "\n";
}

int main()
{
    a = std::rand();
    for (long i = 1; i < 50; i++)
        measure_cycles(i);
}