#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
using namespace std;

const int BUFFER_SIZE = 10; // Buffer size
queue<int> buffer;     // Shared buffer
mutex mtx;             // Mutex for critical section
condition_variable cv; // Condition variable for synchronization

void producer(int id, int produce_count) {
    for (int i = 0; i < produce_count; ++i) {
        unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        // Produce an item and add it to the buffer
        int item = i;
        buffer.push(item);
        cout << "Producer " << id << " produced: " << item << std::endl;

        // Notify one of the consumers
        cv.notify_all();

        // Simulate time taken to produce an item
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(int id, int consume_count) {
    for (int i = 0; i < consume_count; ++i) {
        unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty(); });

        // Consume an item from the buffer
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed: " << item << std::endl;

        // Notify one of the producers
        cv.notify_all();

        // Simulate time taken to consume an item
        this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {
    const int produce_count = 20;
    const int consume_count = 20;

    // Create producer and consumer threads
    thread producer1(producer, 1, produce_count);
    thread producer2(producer, 2, produce_count);
    thread consumer1(consumer, 1, consume_count);
    thread consumer2(consumer, 2, consume_count);

    // Join threads with the main thread
    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();

    return 0;
}
