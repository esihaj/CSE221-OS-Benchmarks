#include <iostream>
#include "rdtscp_timer.h"
#include "../hdr.h"
using namespace std;

const int MAX_ITERATIONS = 1'000'000;
const int MAX_MEASUREMENTS = 1000;
int main()
{
    RdtscpTimer timer;
    std::vector<double> measurements;
    measurements.reserve(MAX_MEASUREMENTS);
    for (int measurement = 0; measurement < MAX_MEASUREMENTS; measurement++)
    {
        timer.start();
        for (int i = 0; i < MAX_ITERATIONS; i++)
            ;
        timer.finish();
        measurements.push_back(timer.duration() / (double)MAX_ITERATIONS);
    }
    cout << "cycles: \n"; 
    print_hdr(measurements);
}