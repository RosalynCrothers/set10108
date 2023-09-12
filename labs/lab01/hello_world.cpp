#include <thread>
#include <chrono>
#include <random>
#include <vector>
#include <iostream>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

constexpr size_t num_threads = 100;

/*
This is the function called by the thread
*/
void hello_world()
{
    cout << "Hello from thread " << get_id() << endl ;
}

void task(size_t n, int val)
{
    //string s = "Thread: " + n + " Random Value: " + val;
    cout << "Thread: " << n << " Random Value: " << val << endl;
}

int main(int argc, char **argv)
{
    /*
    // Create a new thread
    thread t(hello_world);
    // Wait for thread to finish (join it)
    t.join();
    */

    // C++ style of creating a random
    // Seed with real random number if available
    std::random_device r;
    // Create random number generator
    default_random_engine e(r());

    //create a vector of threads
    vector<thread> threads;

    //go through a loop of 100, giving the threads an index and random number
    for (size_t i = 0; i < num_threads; ++i)
        threads.push_back(thread(task, i, e()));

    // Use C++ ranged for loop to join the threads
    // Same as foreach in C#
    for (auto& t : threads)
        t.join();

    // Return 0 (OK)
    return 0;
}