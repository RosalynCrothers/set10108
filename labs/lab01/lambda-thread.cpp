#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;
using namespace std::chrono;

void work(int& n)
{
    n = 0;
    for (size_t i = 0; i < 1000000; i++)
    {
        ++n;
    }
}

int main(int argc, char **argv)
{
    // Create a thread using a lambda expression
    thread t([]{ cout << "Hello from lambda thread!" << endl; });
    // Join thread
    t.join();

    ofstream data("data1.csv", ofstream::out);
    uint64_t total_ns = 0;
    // We’re going to gather 100 readings , so create a thread and join it 100 times
    for (int i = 0; i < 100; ++i)
    {
        // Get start time
        auto start = system_clock::now();
        // Start thread. Pass n as a reference, so that we can write to it from the thread
        int n = 0;
        thread t(work, ref(n));
        t.join();
        // Get end time
        auto end = system_clock::now();
        // Calculate the duration
        auto total = end - start;
        // Write to file
        total_ns += total.count();
        data << total.count() << endl;
    }
    data.close();
    cout << "mean: " << total_ns / 100 << endl;

    return 0;
}