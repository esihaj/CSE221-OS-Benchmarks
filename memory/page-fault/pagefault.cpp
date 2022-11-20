#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <cstdlib>

using namespace std;

const int ACCESS_COUNT = 1000;
const int SIZE = 200'000;

int main() {
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

    for(int i = 0; i < ACCESS_COUNT; i++) {
        size_t index_page = rand() % SIZE;
        // cout << "accessing page " << index_page << endl;
        counter += buffer[index_page * 4096];    
    };

    cout << "don't optimize away " << counter << endl;
}