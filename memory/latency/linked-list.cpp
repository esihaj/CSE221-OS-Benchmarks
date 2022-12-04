#include <iostream>
#include <cassert>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>
#include <algorithm>
#include "../../time/rdtscp_timer.h"
#include "../../hdr.h"

using namespace std;

#define KiB *1024
#define MiB *1024 * 1204

const int MIN_ACCESS_COUNT = 100'000;

class Node
{
public:
    Node *next;
    int data;
};

class LinkedList
{
private:
    Node *head;
    size_t size;
    RdtscpTimer timer;

public:
    LinkedList(int size) : size(size)
    {
        Node *contiguous = new Node[size];
        assert(contiguous != nullptr);

        head = &(contiguous[0]);
        Node *current = head;
        for (auto index : random_list(size))
        {
            current->next = &(contiguous[index]);
            current = current->next;
        }
        current->next = nullptr;
    }

    ~LinkedList()
    {
        delete[] head;
    }

    vector<size_t> random_list(int max)
    {
        vector<size_t> values(max - 1);
        iota(std::begin(values), std::end(values), 1);
        shuffle(std::begin(values), std::end(values), std::random_device());
        return values;
    }

    long traverse(int iterations)
    {
        Node *node;
        long count = 0;
        for (int i = 0; i < iterations; i++)
        {
            node = head;
            Node *prev;
            while (node)
            {
                prev = node;
                node = node->next;
            }
            count += prev->data;
        }
        return count;
    }

    long traverse_once()
    {
        Node *node = head;
        Node *prev;
        long counter = 0;
        while (node)
        {
            prev = node;
            node = node->next;
            counter++;
        }
        if (counter != size)
        {
            cout << "traversed the wrong number of times " << counter << "\n";
        }
        return prev->data;
    }

    void measure(int iterations)
    {
        vector<double> measurements;
        measurements.reserve(iterations);
        auto garbage = traverse_once(); // load into cache
        for (int i = 0; i < iterations; i++)
        {
            timer.start();
            garbage += traverse_once();
            timer.finish();
            measurements.push_back(timer.duration() / (double)(size));
        }
        cerr << "garbage: " << garbage << "\n";
        cout << size * sizeof(Node) / 1024.0 << " KiB. Elements: " << size << ", Iterations: " << iterations << ". cycles/element:"
             << "\n";
        print_hdr(measurements);
    }
};

int find_min_iterations(int size)
{
    return max(256.0, MIN_ACCESS_COUNT / (double)size);
}

int main()
{
    for (int i = 2; i <= 32 * 1024 * 1024; i *= 1.5)
    {
        LinkedList list(i);
        list.measure(find_min_iterations(i));
        cout << "------------------------------------------------\n";
    }

    double node_size = sizeof(Node);
    cout << "32-5 KiB\n";
    LinkedList(((32 - 5) KiB) / node_size).measure(256);
    cout << "----------------------\n";
    cout << "32+5 KiB\n";
    LinkedList(((32 + 5) KiB) / node_size).measure(256);

    cout << "------------------------------------------------\n";
    cout << "\n";
    cout << "256-10 KiB\n";
    LinkedList(((256 - 10) KiB) / node_size).measure(256);

    cout << "----------------------\n";
    cout << "256+10 KiB\n";
    LinkedList(((256 + 10) KiB) / node_size).measure(256);

    cout << "------------------------------------------------\n";
    cout << "\n";
    cout << "20-2 MiB\n";
    LinkedList(((20 - 2) MiB) / node_size).measure(256);

    cout << "----------------------\"n";
    cout << "20+2 MiB\n";
    LinkedList(((20 + 2) MiB) / node_size).measure(256);

    cout << "------------------------------------------------\n";
}