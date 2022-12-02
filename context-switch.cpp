#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>
#include <iostream>
#include <vector>
#include "stdev.h"
#include "time/rdtscp_timer.h"

const int ITERATIONS = 1'000'000;

int main(int argc, char *argv[])
{
    RdtscpTimer timer;
    std::vector<double> measurements;
    measurements.reserve(ITERATIONS);

    
    // measure context switch
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);

    int first_pipefd[2], second_pipefd[2];
    if (pipe(first_pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(second_pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t cpid = fork();

    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (cpid == 0)
    { // child
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1)
        {
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < ITERATIONS; i++)
        {
            read(first_pipefd[0], NULL, 0);
            write(second_pipefd[1], NULL, 0);
        }
    }
    else
    { // parent
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1)
        {
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < ITERATIONS; i++)
        {
            timer.start();
            write(first_pipefd[1], NULL, 0);
            read(second_pipefd[0], NULL, 0);
            timer.finish();
            measurements.push_back(timer.duration());
        }
        std::cout << "process context switch cycles:\n";
        vec_print(measurements);
    }
    return 0;
}