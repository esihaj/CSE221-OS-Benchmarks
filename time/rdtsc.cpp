#include <iostream>
#include <cstdio>
using namespace std;


int global = 0;

void dosomething() {
    global++;
}

int main() {
    double sum = 0;
    const uint32_t numloops = 100000000;
    for ( uint32_t j=0; j<numloops; ++j ) {
        uint64_t t0 = __builtin_ia32_rdtsc();
        dosomething();
        uint64_t t1 = __builtin_ia32_rdtsc();
        uint64_t elapsed = t1-t0;
        sum += elapsed;
    }
    cout << "Average: " << sum/numloops << endl;
    cout << "global: " << global << endl;
}