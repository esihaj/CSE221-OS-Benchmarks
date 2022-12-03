#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>
#include <iostream>
#include <vector>
#include "stdev.h"
#include "time/rdtscp_timer.h"
#include "../hdr.h"

const int ITERATIONS = 1'000'000;
const std::string EXPERIMENT_HDR_NAME = "context-switch.hdr";


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

    pid_t p_id = fork();

    if (p_id == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (p_id == 0)
    { // child
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1)
        {
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < ITERATIONS; i++)
        {
            int len;
            len = read(first_pipefd[0], NULL, 0);
            if (len < 0)
                std::cerr << "could not read! " << p_id << "\n";
            len = write(second_pipefd[1], NULL, 0);
            if (len < 0)
                std::cerr << "could not write! " << p_id << "\n";
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
            int len;
            timer.start();
            len = write(first_pipefd[1], NULL, 0);
            if (len < 0)
                std::cerr << "could not write! " << p_id << "\n";
            len = read(second_pipefd[0], NULL, 0);
            if (len < 0)
                std::cerr << "could not read! " << p_id << "\n";
            timer.finish();
            measurements.push_back(timer.duration());
        }
        std::cout << "process context switch cycles:\n";
        vec_print(measurements);
        print_hdr(measurements, EXPERIMENT_HDR_NAME);
    }

    return 0;
}