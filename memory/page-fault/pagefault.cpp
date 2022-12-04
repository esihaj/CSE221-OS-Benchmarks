#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <set>
#include <climits>
#include <fcntl.h>
#include <chrono>
#include "../../drop_file_cache.h"

using namespace std;

const int BLOCK_SIZE = 4096;
const int ACCESS_COUNT = 10000;
const int SIZE = INT_MAX / BLOCK_SIZE;
const int STRIDE_LIMIT = (SIZE - 1) / ACCESS_COUNT;
typedef std::chrono::steady_clock Clock;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Error: No argument passed to program. should we drop the cache? drop|no_drop" << std::endl;
        return 1;
    }

    bool should_drop = string(argv[1]) == "drop" ? true : false;

    std::srand(42);
    cout << "selected MAPPING BLOCK COUNT " << SIZE << endl;

    const char *file_address = "rand-large.bin";
    if (should_drop)
        drop_file_cache();
    int file_read = open(file_address, O_RDONLY, 0);
    if (file_read == -1)
    {
        cerr << "could not open file " << file_address << endl;
        exit(1);
    }
    char *buffer = reinterpret_cast<char *>(
        mmap(nullptr, BLOCK_SIZE * SIZE, PROT_READ, MAP_PRIVATE, file_read, 0));
    if (buffer == MAP_FAILED)
    {
        cerr << "could not map";
        exit(1);
    }

    unsigned long counter = 0;

    size_t current_index = 0;
    assert(STRIDE_LIMIT - 10 > 0);
    auto start = Clock::now();
    for (int i = 0; i < ACCESS_COUNT; i++)
    {
        size_t index_page = rand() % (STRIDE_LIMIT - 10) + 10; // each access is at least 10 4KB blocks away
        current_index += index_page;
        counter += buffer[current_index * BLOCK_SIZE];
    };
    auto end = Clock::now();
    cerr << "don't optimize away garbage: " << counter << endl;
    auto duration = chrono::duration_cast<chrono::milliseconds>((end - start)).count();
    cout << "duration: " << duration  << " ms"<< endl;
}