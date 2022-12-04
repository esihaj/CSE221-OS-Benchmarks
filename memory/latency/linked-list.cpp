#include <iostream>
#include <cassert>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>
#include <algorithm>
#include "../../time/rdtscp_timer.h"

using namespace std;

const int MIN_ACCESS_COUNT = 100'000;

class Node {
    public:
    Node* next;
    int data;
};

class LinkedList {
    private:
    Node* head;
    size_t size;
    RdtscpTimer timer;
    public:

    LinkedList(int size) : size(size) {
        Node* contiguous = new Node[size];
        assert(contiguous != nullptr);

        head = &(contiguous[0]);
        Node * current = head;

        for (auto index: random_list(size)) {
            current->next = &(contiguous[index]);
            current = current->next;
        }
        current->next = nullptr;
    }

    ~LinkedList() {
        delete[] head;
    }

    vector<size_t> random_list(int max) {
        vector<size_t> values(max-1);
        iota(std::begin(values), std::end(values), 1);
        shuffle(std::begin(values), std::end(values), std::random_device());
        return values;
    }

    long traverse(int iterations) {
        Node * node;
        long count = 0;
        for(int i = 0; i < iterations; i++) {
            node = head;
            Node * prev;
            while (node) {
                prev = node;
                node = node->next;
            }
            count += prev->data;
        }
        return count;
    }

    void measure(int iterations) {
        auto garbage = traverse(1); // load into cache
        timer.start();
        garbage += traverse(iterations);
        timer.finish();
        cerr << "garbage: " << garbage << "\n";
        cout << size * sizeof(Node) / 1024.0 << " KiB -> Cycles:" << timer.duration() / (double)(size * sizeof(Node) * iterations) << " iterations: " << iterations << "\n";
    }
};

int find_min_iterations(int size) {
    return max(1.0, MIN_ACCESS_COUNT / (double) size);
}

int main() {
    for (int i = 2; i < 1024*1024*1024; i *= 2) {
        LinkedList list(i);
        list.measure(find_min_iterations(i));
    }
}