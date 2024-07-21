#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <vector>
using namespace std;
const int NUM_READERS = 3;
const int NUM_WRITERS = 2;

mutex mtx; // Mutex for critical section
condition_variable cv_read, cv_write; // Condition variables for synchronization

atomic<int> readers_count(0); // Count of active readers
atomic<bool> writer_writing(false); // Flag to indicate if a writer is currently writing

void reader(int id) {
    while (true) {
        // Simulate reading process
        this_thread::sleep_for(chrono::milliseconds(100));

        // Acquire lock to update readers_count
        {
            unique_lock<mutex> lock(mtx);
            cv_read.wait(lock, [] { return !writer_writing; }); // Wait until no writer is writing

            readers_count++;
            cout << "Reader " << id << " is reading. Readers count: " << readers_count << endl;
        }

        // Simulate reading process
        this_thread::sleep_for(chrono::milliseconds(300));

        // Release lock
        {
            unique_lock<mutex> lock(mtx);
            readers_count--;
            cout << "Reader " << id << " finished reading. Readers count: " << readers_count << endl;

            // Notify waiting writers if no readers left
            if (readers_count == 0) {
                cv_write.notify_one();
            }
        }
    }
}

void writer(int id) {
    while (true) {
        // Simulate writing process
        this_thread::sleep_for(chrono::milliseconds(500));

        // Acquire lock to update writer_writing
        {
            unique_lock<mutex> lock(mtx);
            cv_write.wait(lock, [] { return readers_count == 0 && !writer_writing; }); // Wait until no readers and no other writer

            writer_writing = true;
            cout << "Writer " << id << " is writing." << endl;
        }

        // Simulate writing process
        this_thread::sleep_for(chrono::milliseconds(800));

        // Release lock
        {
            unique_lock<mutex> lock(mtx);
            writer_writing = false;
            cout << "Writer " << id << " finished writing." << endl;

            // Notify waiting readers or other writers
            cv_write.notify_one();
            cv_read.notify_all();
        }
    }
}

int main() {
    vector<thread> readers, writers;

    // Create reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        readers.push_back(thread(reader, i + 1));
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writers.push_back(thread(writer, i + 1));
    }

    // Join reader threads
    for (auto& reader_thread : readers) {
        if (reader_thread.joinable()) {
            reader_thread.join();
        }
    }

    // Join writer threads
    for (auto& writer_thread : writers) {
        if (writer_thread.joinable()) {
            writer_thread.join();
        }
    }

    return 0;
}
