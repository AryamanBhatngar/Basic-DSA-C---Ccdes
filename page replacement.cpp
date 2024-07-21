#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

// Function to find page faults using FIFO page replacement algorithm
int fifoPageFaults(const std::vector<int>& pages, int capacity) {
    std::unordered_map<int, int> pageTable;
    std::queue<int> fifoQueue;
    int pageFaults = 0;

    for (int page : pages) {
        if (pageTable.find(page) == pageTable.end()) {
            // Page fault occurs
            pageFaults++;
            if (fifoQueue.size() == capacity) {
                // Remove the oldest page
                int oldest = fifoQueue.front();
                fifoQueue.pop();
                pageTable.erase(oldest);
            }
            // Add the new page
            fifoQueue.push(page);
            pageTable[page] = 1;
        }
    }
    return pageFaults;
}

// Function to find page faults using LRU page replacement algorithm
int lruPageFaults(const std::vector<int>& pages, int capacity) {
    std::unordered_map<int, int> pageTable;
    std::vector<int> lruQueue;
    int pageFaults = 0;

    for (int page : pages) {
        auto it = std::find(lruQueue.begin(), lruQueue.end(), page);
        if (it == lruQueue.end()) {
            // Page fault occurs
            pageFaults++;
            if (lruQueue.size() == capacity) {
                // Remove the least recently used page
                int lruPage = lruQueue.front();
                lruQueue.erase(lruQueue.begin());
                pageTable.erase(lruPage);
            }
        } else {
            // Move the accessed page to the end (most recently used)
            lruQueue.erase(it);
        }
        lruQueue.push_back(page);
        pageTable[page] = 1;
    }
    return pageFaults;
}

// Function to find page faults using Optimal page replacement algorithm
int optimalPageFaults(const std::vector<int>& pages, int capacity) {
    std::unordered_map<int, int> pageTable;
    std::vector<int> frames;
    int pageFaults = 0;

    for (size_t i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (pageTable.find(page) == pageTable.end()) {
            // Page fault occurs
            pageFaults++;
            if (frames.size() == capacity) {
                // Find the page to be replaced
                int farthest = i, replaceIndex = 0;
                for (size_t j = 0; j < frames.size(); ++j) {
                    size_t k;
                    for (k = i + 1; k < pages.size(); ++k) {
                        if (pages[k] == frames[j]) {
                            if (k > farthest) {
                                farthest = k;
                                replaceIndex = j;
                            }
                            break;
                        }
                    }
                    if (k == pages.size()) {
                        replaceIndex = j;
                        break;
                    }
                }
                pageTable.erase(frames[replaceIndex]);
                frames[replaceIndex] = page;
            } else {
                frames.push_back(page);
            }
            pageTable[page] = 1;
        }
    }
    return pageFaults;
}

int main() {
    std::vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int capacity = 3;

    int fifoFaults = fifoPageFaults(pages, capacity);
    int lruFaults = lruPageFaults(pages, capacity);
    int optimalFaults = optimalPageFaults(pages, capacity);

    std::cout << "Page faults using FIFO: " << fifoFaults << std::endl;
    std::cout << "Page faults using LRU: " << lruFaults << std::endl;
    std::cout << "Page faults using Optimal: " << optimalFaults << std::endl;

    return 0;
}
