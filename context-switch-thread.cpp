#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>
#include <iostream>
#include <vector>
#include <thread>
#include "time/rdtscp_timer.h"
#include "hdr.h"

const int ITERATIONS = 1'000'000;
const std::string EXPERIMENT_HDR_NAME = "context-switch.hdr";

int first_pipefd[2], second_pipefd[2];

void pong()
{
    for (size_t i = 0; i < ITERATIONS; i++)
    {
        int len;
        len = read(first_pipefd[0], NULL, 0);
        if (len < 0)
            std::cerr << "could not read! pong\n";
        len = write(second_pipefd[1], NULL, 0);
        if (len < 0)
            std::cerr << "could not write! pong\n";
    }
}

void setup_pipes()
{
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
}

int main(int argc, char *argv[])
{
    RdtscpTimer timer;
    std::vector<double> measurements;
    measurements.reserve(ITERATIONS);

    setup_pipes();

    std::thread ping_thread(pong);

    for (size_t i = 0; i < ITERATIONS; i++)
    {
        int len;
        timer.start();
        len = write(first_pipefd[1], NULL, 0);
        if (len < 0)
            std::cerr << "could not write! ping\n";
        len = read(second_pipefd[0], NULL, 0);
        if (len < 0)
            std::cerr << "could not read! ping\n";
        timer.finish();
        measurements.push_back(timer.duration());
    }
    std::cout << "thread context switch cycles:\n";
    print_hdr(measurements);
    ping_thread.join();

    return 0;
}