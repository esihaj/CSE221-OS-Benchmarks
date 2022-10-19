#include <nanobench.h>
#include <thread>
#include <iostream>
#include <vector>

#include <unistd.h>

using namespace std;

long global = 0;

void counter() {
}


int main() {
    const int SIZE = 10000;
    ankerl::nanobench::Bench().minEpochIterations(SIZE).run("create process fork()", [&] {
        if (fork() == 0){
            exit(0);
        }
    });

    ankerl::nanobench::Bench().minEpochIterations(SIZE).run("create and run thread", [&] {
        thread t(counter);
        t.join();
        ankerl::nanobench::doNotOptimizeAway(t);
    });

    ankerl::nanobench::Bench().minEpochIterations(SIZE).run("create thread", [&] {
        thread t(counter);
        t.detach();
        ankerl::nanobench::doNotOptimizeAway(t);
    });

}