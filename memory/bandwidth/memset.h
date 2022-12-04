#ifndef _MEMSET_H_
#define _MEMSET_H_

#include <cstdint>
#include <cstring>

typedef uint64_t DATA_TYPE;

class Memory
{
private:
    DATA_TYPE *src;
    long size;
    size_t random_index;

public:
    Memory(long size);
    ~Memory();
    int set(int iterations);
    void measure(int iterations);
    long total_size_bytes();
};

#endif