#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int ACCESS_COUNT = 1000000;
int SIZE = 200000;
const int PAGE_SIZE = 4096;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "usage: ./program mem_page_count access_count" << endl;
        exit(1);
    }
    else {
        SIZE = stoi(argv[1]);
        ACCESS_COUNT = stoi(argv[2]);
        cout << "size is set to " << SIZE << ". which is ~" << SIZE*PAGE_SIZE / 1024 << "KB, "; 
        cout << SIZE*PAGE_SIZE/1024/1024 << "MB" << endl;
        cout << "access count is " << ACCESS_COUNT << endl;
    }
    char * arr = new char[SIZE*PAGE_SIZE];
    cout << "allocated " << SIZE*PAGE_SIZE/1024 << " K bytes" << endl;

    unsigned long counter = 0;

    int initial_sweep_page_count = SIZE;
    for (int i =0; i < initial_sweep_page_count; i++) {
        for (int j = 0; j < PAGE_SIZE; j++) {
            arr[i*PAGE_SIZE + j] = counter++;
        }    
    }
    counter = 0;
    cout << "initialized " << initial_sweep_page_count*PAGE_SIZE / 1024 / 1024 << "MB" << endl;

    for(int i = 0; i < ACCESS_COUNT; i++) {
        size_t index_page = rand() % (SIZE-51200) + 51200;
        // cout << "accessing page " << index_page << endl;
        arr[index_page * 4096] = rand();
        counter += arr[index_page * 4096+1];    
    };

    cout << "don't optimize away " << counter << endl;
}