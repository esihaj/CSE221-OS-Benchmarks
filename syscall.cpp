#include <nanobench.h>
#include <unistd.h>
#include <ctime>


int main() {
    ankerl::nanobench::Bench().minEpochIterations(1'000'000).run("syscall getuid()", [&] {
        ankerl::nanobench::doNotOptimizeAway(getuid());
    });

    struct timespec start;
    ankerl::nanobench::Bench().minEpochIterations(1'000'000).run("syscall clock_gettime()", [&] {
        clock_gettime(CLOCK_REALTIME, &start);
        ankerl::nanobench::doNotOptimizeAway(start);
    });
}