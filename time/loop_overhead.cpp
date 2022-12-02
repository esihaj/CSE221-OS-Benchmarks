#include <iostream>
#include "rdtscp_timer.h"
using namespace std;

const int MAX_ITERATIONS = 1'000'000;
int main() {
    RdtscpTimer timer;
    timer.start();
    for (int i =0; i < MAX_ITERATIONS; i++);
    timer.finish();
    cout << "loop cost / iteration " << timer.duration() / (double) MAX_ITERATIONS << "cycles" << endl;
}