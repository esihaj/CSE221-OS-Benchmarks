#include <iostream>
#include <chrono>
#include <cassert>
#include "memset.h"

using namespace std;

const size_t STEP_SIZE = 8;
const int MIN_ACCESS_COUNT = 1'000'000'000;

int find_min_iterations(int size)
{
    return max(1.0, MIN_ACCESS_COUNT / (double)size);
}

Memory::Memory(long size) : size(size)
{
    src = new DATA_TYPE[size];
    random_index = std::rand();
    memset(src, 1, total_size_bytes());
}

Memory::~Memory()
{
    delete[] src;
}

int Memory::set(int iterations)
{
    int sum = 0;
    for (int iter = 0; iter < iterations; iter += 1)
    {
        memset(src, iter % 100, total_size_bytes());
        sum += src[random_index % (size-1)];
    }
    return sum;
}

long Memory::total_size_bytes() {
    return size*sizeof(DATA_TYPE);
}

void Memory::measure(int iterations)
{
    auto start = chrono::steady_clock::now();
    auto garbage = set(iterations);
    auto end = chrono::steady_clock::now();
    auto duration_ms = chrono::duration_cast<chrono::milliseconds>((end - start)).count();
    // cout << "du" << duration_ms <<;
    cerr << "garbage: " << garbage << "\n";
    cout << size << " -> " << (size * iterations * sizeof(DATA_TYPE) / 1024)/ (double)duration_ms << " MB/S iterations: " << iterations << "\n";
}


// int main()
// {
//     cout << "data size " << sizeof(DATA_TYPE) << " bytes" << endl;
//     for (long i = 8; i < 1024 * 1024 * 1024L * 16; i *= 2)
//     {
//         Memory memory(i);
//         memory.measure(find_min_iterations(i));
//     }
// }