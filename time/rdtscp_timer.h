#ifndef RDTSCP_TIMER_H
#define RDTSCP_TIMER_H
#include <cstdint>

class RdtscpTimer
{
private:
    unsigned long long start_time, end_time;

public:
    void start()
    {
        unsigned int cycles_low, cycles_high;
        asm volatile("CPUID\n\t"
                     "RDTSC\n\t"
                     "mov %%edx, %0\n\t"
                     "mov %%eax, %1\n\t"
                     : "=r"(cycles_high), "=r"(cycles_low)::"%rax", "%rbx", "%rcx", "%rdx");
        start_time = (((uint64_t)cycles_high << 32) | cycles_low);
    }

    void finish()
    {
        unsigned int cycles_low, cycles_high;
        asm volatile("RDTSCP\n\t"
                     "mov %%edx, %0\n\t"
                     "mov %%eax, %1\n\t"
                     "CPUID\n\t"
                     : "=r"(cycles_high), "=r"(cycles_low)::"%rax", "%rbx", "%rcx", "%rdx");
        end_time = (((uint64_t)cycles_high << 32) | cycles_low);
    }

    unsigned long long duration()
    {
        return (end_time - start_time);
    }
};

#endif