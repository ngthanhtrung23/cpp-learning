#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <condition_variable>
#include <functional>
#include "thread_safe_queue.hpp"
#include "../debug.h"

using Job = std::function<void()>;
class ThreadPool {
public:
    ThreadPool(int n_threads) {
        for ([[maybe_unused]] auto i : std::views::iota(0, n_threads)) {
            threads.push_back(std::thread(&ThreadPool::infinite_loop_fn, this));
        }
        done = false;
    }

    ~ThreadPool() {
        done = true;
        cv_not_empty.notify_all();
        for (auto& t : threads) {
            t.join();
        }
    }

    void infinite_loop_fn() {
        while (true) {
            Job job;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv_not_empty.wait(lock, [this] { return done || !qu.empty(); });
                if (qu.empty()) break;

                job = qu.pop();
            }
            job();
            cv_empty.notify_one();
        }
    }

    void add_job(const Job& job) {
        std::unique_lock<std::mutex> lock(mtx);
        qu.push(job);
        cv_not_empty.notify_one();
    }

    void wait_for_stop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv_empty.wait(lock, [this] { return qu.empty(); });
    }

private:
    std::atomic<bool> done;
    std::vector<std::thread> threads;
    std::mutex mtx;
    std::condition_variable cv_not_empty;
    std::condition_variable cv_empty;
    ThreadSafeQueue<Job> qu;
};

int main(int argc, char** argv) {
    assert(argc == 2);
    int N = std::stoi(argv[1]);
    DEBUG(N);
    
    ThreadPool pool(std::thread::hardware_concurrency());
    std::atomic<int> x = 0;
    auto inc_x = [&x] () { x++; };

    for (int i = 0; i < N; i++) {
        pool.add_job(inc_x);
    }
    pool.wait_for_stop();
    cout << "x = " << x << endl;
}
