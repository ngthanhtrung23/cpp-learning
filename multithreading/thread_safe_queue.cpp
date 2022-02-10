#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <cassert>
#include <ranges>
#include <thread>
#include <set>
#include "debug.h"

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;

    void push(T value) {
        std::lock_guard<std::mutex> lock(mtx);
        qu.push(value);

        // unblock waiting pop()
        cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        // need to wait until queue is not empty
        cv.wait(lock, [this] { return !qu.empty(); });

        T res = qu.front();
        qu.pop();
        return res;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return qu.empty();
    }

private:
    std::mutex mtx;
    std::queue<T> qu;
    std::condition_variable cv;
};

int main(int argc, char** argv) {
    assert(argc == 2);
    int N = std::stoi(argv[1]);
    DEBUG(N);

    ThreadSafeQueue<int> qu;
    
    // create N threads
    std::vector<std::thread> ts;
    std::set<int> all_values;
    for (int i : std::views::iota(0, N)) {
        ts.push_back(std::thread(
                [&qu] (int i) { qu.push(i); },
                i));
        ts.push_back(std::thread(
                [&qu, &all_values] () { all_values.insert(qu.pop()); }));
    }

    for (auto& t : ts) {
        t.join();
    }

    DEBUG(all_values.size());
}
