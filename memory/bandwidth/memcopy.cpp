#include <iostream>
#include <chrono>
#include <cassert>
#include <cstring>

using namespace std;

typedef uint64_t DATA_TYPE;
const size_t STEP_SIZE = 8;
const int MIN_ACCESS_COUNT = 1'000'000'000;

int find_min_iterations(int size)
{
    return max(1.0, MIN_ACCESS_COUNT / (double)size);
}

class Memory
{
private:
    DATA_TYPE *src;
    DATA_TYPE *dst;
    long size;

public:
    Memory(long size) : size(size)
    {
        assert(size % STEP_SIZE == 0);
        src = new DATA_TYPE[size];
        dst = new DATA_TYPE[size];
        for (int i = 0; i < size; i++)
        {
            src[i] = i;
        }
    }

    ~Memory()
    {
        delete[] src;
        delete[] dst;
    }

    int copy(int iterations)
    {
        int sum = 0;
        for (int iter = 0; iter < iterations; iter += 1)
        {
            for (int i = 0; i < size - STEP_SIZE; i += STEP_SIZE)
            {
                memcpy(dst + i, src +i, STEP_SIZE);
            }
            sum += iter * dst[size - 1];
        }
        return sum;
    }

    void measure(int iterations)
    {
        auto start = chrono::steady_clock::now();
        auto garbage = copy(iterations);
        auto end = chrono::steady_clock::now();
        auto duration_ms = chrono::duration_cast<chrono::milliseconds>((end - start)).count();
        // cout << "du" << duration_ms <<;
        cerr << "garbage: " << garbage << "\n";
        cout << size << " -> " << (size * iterations * sizeof(DATA_TYPE) / 1024)/ (double)duration_ms << " MB/S iterations: " << iterations << "\n";
    }
};

int main()
{
    cout << "data size " << sizeof(DATA_TYPE) << " bytes" << endl;
    for (long i = 8; i < 1024 * 1024 * 1024L * 16; i *= 2)
    {
        Memory memory(i);
        memory.measure(find_min_iterations(i));
    }
}
