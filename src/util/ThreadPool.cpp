//
// Created by cory on 11/14/24.
//

// ThreadPool.cpp
#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threads) : stop(false) {
    for(size_t i = 0; i < threads; ++i)
        workers.emplace_back([this] {
            while(true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    condition.wait(lock, [this] { return stop || !tasks.empty(); });
                    if(stop && tasks.empty()) return;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();
}