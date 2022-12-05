// https://stackoverflow.com/questions/47292714/read-and-write-files-open-read
#include <iostream>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include "../drop_file_cache.h"

using namespace std;

#define KiB *1024l
#define MiB *1024l * 1024
#define GiB *1024l * 1024 * 1024

const int REPETITIONS_PER_SIZE = 5;
const int STEP_SIZE = 4 KiB;

const long READ_SIZES[] = {512 MiB, 1 GiB, 2 GiB, 4 GiB, 8 GiB, 12 GiB};
const char *file_name = "rand-large.bin";

typedef std::chrono::steady_clock Clock;

void check_file_size()
{
    struct stat file_stat;
    stat(file_name, &file_stat);
    size_t size = file_stat.st_size;
    if (size < READ_SIZES[std::size(READ_SIZES) - 1])
    {
        cout << "file size is smaller than experiment needs. file size = ";
        cout << size / (1 MiB) << " MB. While max read size is " << READ_SIZES[std::size(READ_SIZES) - 1];
        exit(1);
    }
}

int open_file()
{
    int fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        cout << "could not open file " << endl;
        exit(1);
    }
    check_file_size();
    return fd;
}

int main()
{
    int fd = open_file();
    char *buff = new char[STEP_SIZE];

    for (int size_index = 0; size_index < std::size(READ_SIZES); size_index++)
    {
        long read_size = READ_SIZES[size_index];
        cout << "read size: " << read_size / (1 MiB) << "MB\n";
        size_t step_count = read_size / STEP_SIZE;
        int black_hole = 0;

        lseek(fd, 0, SEEK_SET);
        drop_file_cache();

        for (size_t i = 0; i < step_count; i++)
        {
            read(fd, buff, STEP_SIZE);
            black_hole += buff[0];
        }
        cerr << "garbage: " << black_hole << "\n";

        for (int rep = 0; rep < REPETITIONS_PER_SIZE; rep++)
        {
            lseek(fd, 0, SEEK_SET);
            auto start = Clock::now();
            for (size_t i = 0; i < step_count; i++)
            {
                auto len = read(fd, buff, STEP_SIZE);
                black_hole += buff[0];
                if (len < STEP_SIZE)
                    cout << "read " << len << "\n";
            }
            auto end = Clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>((end - start)).count();
            cout << "bandwidth: " << READ_SIZES[size_index] / (double)duration / 1024 << "MB/S\n";
        }
        cout << "*******\n\n";
    }
}