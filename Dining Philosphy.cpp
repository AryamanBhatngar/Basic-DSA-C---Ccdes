#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
using namespace std;
const int NUM_PHILOSOPHERS = 5;

mutex mtx;
condition_variable cv;
vector<mutex> forks(NUM_PHILOSOPHERS);

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    // To avoid deadlock, ensure that philosophers with even IDs pick the right fork first
    if (id % 2 == 0) {
        swap(left_fork, right_fork);
    }

    while (true) {
        {
            unique_lock<mutex> lock(mtx);
            cout << "Philosopher " << id << " is thinking." <<endl;
        }

        // Simulate thinking time
        this_thread::sleep_for(std::chrono::milliseconds(100));

        {
            unique_lock<mutex> lock(forks[left_fork]);
            unique_lock<mutex> lock2(forks[right_fork]);

            unique_lock<mutex> lock(mtx);
            cout << "Philosopher " << id << " is eating." << endl;
        }

        // Simulate eating time
        this_thread::sleep_for(chrono::milliseconds(200));

        {
            unique_lock<mutex> lock(mtx);
            cout << "Philosopher " << id << " finished eating." << endl;
        }

        // Simulate returning forks and thinking again
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    vector<thread> philosophers;

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.push_back(thread(philosopher, i));
    }

    // Join philosopher threads
    for (auto& philosopher_thread : philosophers) {
        if (philosopher_thread.joinable()) {
            philosopher_thread.join();
        }
    }

    return 0;
}
