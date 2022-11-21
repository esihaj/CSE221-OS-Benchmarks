#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <set>

using namespace std;

const int ACCESS_COUNT = 10000;
const int SIZE = 4'000'000;
const int STRIDE_LIMIT = (SIZE - 1) / ACCESS_COUNT;

int main() {
    std::srand(42);
    char * file_address = "/home/ehsan/rand-large.bin";
    int file_read = open(file_address, O_RDONLY, 0);
    if (file_read == -1) {
        cerr << "could not open file " << file_address << endl;
        exit(1);
    }
    char *buffer = reinterpret_cast<char*>(
        mmap(nullptr, 4096*SIZE, PROT_READ, MAP_SHARED, file_read, 0));
    if (buffer == MAP_FAILED) {
        cerr << "could not map";
        exit(1);
    }

    unsigned long counter = 0;

    size_t current_index = 0;

    for(int i = 0; i < ACCESS_COUNT; i++) {
        assert(STRIDE_LIMIT - 10 > 0);
        size_t index_page = rand() % (STRIDE_LIMIT-10) + 10; // each access is at least 10 4KB blocks away
        current_index += index_page;
        counter += buffer[current_index * 4096];    
    };
    cout << "don't optimize away " << counter << endl;
}