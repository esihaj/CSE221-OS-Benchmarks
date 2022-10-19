#include <nanobench.h>

int global = 0;

__attribute__((inline))
inline int my_function_inline() {
    return global++;
}

__attribute__((optnone))
int my_function() {
    return global++;
}

__attribute__((noinline))
int my_function(int val1) {
    global += val1;
    return global;
}

__attribute__((noinline))
int my_function(int val1, int val2) {
    global += val1;
    return global;
}

__attribute__((noinline))
int my_function(int val1, int val2, int val3) {
    global += val1;
    return global;
}

__attribute__((noinline))
int my_function(int val1, int val2, int val3, int val4) {
    global += val1;
    return global;
}

__attribute__((noinline))
int my_function(int val1, int val2, int val3, int val4, int val5) {
    global += val1;
    return global;
}

__attribute__((noinline))
int my_function(int val1, int val2, int val3, int val4, int val5, int val6) {
    global += val1;
    return global;
}

__attribute__((noinline))
int my_function(int val1, int val2, int val3, int val4, int val5, int val6, int val7) {
    global += val1;
    return global;
}

int main() {
  ankerl::nanobench::Bench().minEpochIterations(10'000'000).run("procedure call args = 0 INLINE", [&] {
        ankerl::nanobench::doNotOptimizeAway(my_function_inline());
    });

 global = 1;   
 ankerl::nanobench::Bench().minEpochIterations(10'000'000).run("procedure call args = 0", [&] {
        ankerl::nanobench::doNotOptimizeAway(my_function());
    });

 global = 1;
 ankerl::nanobench::Bench().minEpochIterations(1'000'000).run("procedure call args = 1", [&] {
        ankerl::nanobench::doNotOptimizeAway(my_function(global));
    });
 global = 1;
 ankerl::nanobench::Bench().minEpochIterations(1'000'000).run("procedure call args = 2", [&] {
        ankerl::nanobench::doNotOptimizeAway(my_function(global, global));
    });
 global = 1;
 ankerl::nanobench::Bench().minEpochIterations(1'000'000).run("procedure call args = 3", [&] {
        ankerl::nanobench::doNotOptimizeAway(my_function(global, global, global));
    });
 global = 1;
 ankerl::nanobench::Bench().minEpochIterations(1'000'000).run("procedure call args = 4", [&] {
        ankerl::nanobench::doNotOptimizeAway(my_function(global, global, global, global));
    });
 global = 1;
 ankerl::nanobench::Bench().minEpochIterations(1'000'000).run("procedure call args = 5", [&] {
        ankerl::nanobench::doNotOptimizeAway(my_function(global, global, global, global, global));
    });
 global = 1;
 ankerl::nanobench::Bench().minEpochIterations(1'000'000).run("procedure call args = 6", [&] {
        ankerl::nanobench::doNotOptimizeAway(my_function(global, global, global, global, global, global));
    });
 global = 1;
 ankerl::nanobench::Bench().minEpochIterations(1'000'000).run("procedure call args = 7", [&] {
        ankerl::nanobench::doNotOptimizeAway(my_function(global, global, global, global, global, global, global));
    });
}