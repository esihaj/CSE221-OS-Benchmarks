
#include <iostream>
#include <cstdint>
using namespace std;

inline int func(long count)
{
    long sum = 0;
    for (long i = 0; i < count; i++)
        sum += i;
    return sum;
}

// typedef unsigned long long uint64_t;
void measure_cycles(long count)
{
    unsigned long long start, end;
    unsigned int cycles_low, cycles_high, cycles_low1, cycles_high1;
    asm volatile("CPUID\n\t"
                 "RDTSC\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 : "=r"(cycles_high), "=r"(cycles_low)::"%rax", "%rbx", "%rcx", "%rdx");
    auto sum = func(count);
    asm volatile("RDTSCP\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 "CPUID\n\t"
                 : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

    start = (((uint64_t)cycles_high << 32) | cycles_low);
    end = (((uint64_t)cycles_high1 << 32) | cycles_low1);

    cout << count << " time " << (end - start) / (double)count << " gc" << sum << "\n";
}

int main()
{
    for (long i = 1; i < 1'000'000'000; i *= 10)
        measure_cycles(i);
}