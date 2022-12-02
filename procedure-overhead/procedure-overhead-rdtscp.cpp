#include "../stdev.h"
#include "../time/rdtscp_timer.h"
#include <iostream>
using namespace std;

const int MAX_MEASUREMENT = 10'000'000;

int global = 0;

__attribute__((inline)) inline int my_function_inline()
{
    return global++;
}

__attribute__((optnone)) int my_function()
{
    return global++;
}

__attribute__((noinline)) int my_function(int val1)
{
    global += val1;
    return global;
}

__attribute__((noinline)) int my_function(int val1, int val2)
{
    global += val1;
    return global;
}

__attribute__((noinline)) int my_function(int val1, int val2, int val3)
{
    global += val1;
    return global;
}

__attribute__((noinline)) int my_function(int val1, int val2, int val3, int val4)
{
    global += val1;
    return global;
}

__attribute__((noinline)) int my_function(int val1, int val2, int val3, int val4, int val5)
{
    global += val1;
    return global;
}

__attribute__((noinline)) int my_function(int val1, int val2, int val3, int val4, int val5, int val6)
{
    global += val1;
    return global;
}

__attribute__((noinline)) int my_function(int val1, int val2, int val3, int val4, int val5, int val6, int val7)
{
    global += val1;
    return global;
}
#define START_LOOP                            \
    global = 1;                               \
    for (int i = 0; i < MAX_MEASUREMENT; i++) \
    {                                         \
        timer.start();

#define END_LOOP                              \
    timer.finish();                           \
    measurements.push_back(timer.duration()); \
    }                                         \
    cerr << "garbage " << global << "\n";

#define PRINT_LOOP           \
    vec_print(measurements); \
    cout << "\n";            \
    measurements.clear();

int main()
{
    vector<double> measurements;
    RdtscpTimer timer;

    START_LOOP
    global++;
    END_LOOP
    cout << "cycles: inline function\n";
    PRINT_LOOP

    START_LOOP
    my_function();
    END_LOOP
    cout << "cycles: 0 param function\n";
    PRINT_LOOP

    START_LOOP
    my_function(global);
    END_LOOP
    cout << "cycles: 1 param function\n";
    PRINT_LOOP

    START_LOOP
    my_function(global, global);
    END_LOOP
    cout << "cycles: 2 param function\n";
    PRINT_LOOP

    START_LOOP
    my_function(global, global, global);
    END_LOOP
    cout << "cycles: 3 param function\n";
    PRINT_LOOP

    START_LOOP
    my_function(global, global, global, global);
    END_LOOP
    cout << "cycles: 4 param function\n";
    PRINT_LOOP

    START_LOOP
    my_function(global, global, global, global, global);
    END_LOOP
    cout << "cycles:  5param function\n";
    PRINT_LOOP

    START_LOOP
    my_function(global, global, global, global, global, global);
    END_LOOP
    cout << "cycles: 6 param function\n";
    PRINT_LOOP

    START_LOOP
    my_function(global, global, global, global, global, global, global);
    END_LOOP
    cout << "cycles: 7 param function\n";
    PRINT_LOOP
}