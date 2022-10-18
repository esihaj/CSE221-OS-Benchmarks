#include <nanobench.h>
#include <chrono>

int main() {
    ankerl::nanobench::Bench().minEpochIterations(10'000'000).run("chrono::high_resolution_clock::now()", [&] {
        auto start = std::chrono::high_resolution_clock::now();
        ankerl::nanobench::doNotOptimizeAway(start);
    });
}