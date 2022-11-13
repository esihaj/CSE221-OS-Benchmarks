#include <iostream>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <chrono>

using namespace std;

const int MAX_SIZE = 30;
const int MIN_SIZE = 6;
const int ACCESS_COUNT = 10'000'000;

class Data {

private:
    vector<int> access_indicies;
    int * back_store;
    size_t size;

    vector<int> random_list(int max) {
        vector<int> values(max);
        iota(std::begin(values), std::end(values), 0);
        shuffle(std::begin(values), std::end(values), std::random_device());
        return values;
    }

    void fill() {
        int fill_counter = 0;
        for (int i = 0; i < size; i++) {
            back_store[i] = fill_counter++;
        }
    }

public:
    Data(int pow_size) {
        size = pow(2, pow_size);
        access_indicies = random_list(size);
        assert(access_indicies.size() == size);

        back_store = new int[size];
        // fill();
    }

    void clean() {
        delete[] back_store;
    }

    int access() {
        int counter = 0;
        for (int iter = 0; iter < ACCESS_COUNT; iter++) {
            auto index = access_indicies[iter % access_indicies.size()];
            // cout << index << ", ";
            counter += back_store[index];
        }
        cout << endl;
        return counter;
    }
};






void benchmark_memory_access(int pow_size) {
    Data data(pow_size);
    chrono::steady_clock clock;
    
    auto start = clock.now();
    auto res = data.access();
    auto end = clock.now();
    
    auto duration = duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "pow size: " << pow_size << ", access time: " << duration << " per elem: " << duration / (double)ACCESS_COUNT \
         << " ns. Total Access Count: " << ACCESS_COUNT << ". garbage: " << res/10000000 << "\n";
    
    data.clean();
}


int main () {
    for (int pow_size = MIN_SIZE; pow_size < MAX_SIZE; pow_size++) {
        benchmark_memory_access(pow_size);
    }
    cout << endl;
}