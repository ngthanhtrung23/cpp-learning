#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <cassert>
#include <ranges>
#include <thread>
#include <set>
#include "../debug.h"

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
