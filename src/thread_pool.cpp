#include "thread_pool.h"
#include "display.h"
#include <iostream>

using namespace std;

ThreadPool::ThreadPool(size_t threads) {
    for(size_t i = 0; i < threads; ++i) {
        workers.emplace_back([this] {
            for(;;) {
                function<void()> task;
                {
                    unique_lock<mutex> lock(this->queue_mutex);
                    this->condition.wait(lock, [this]{ return this->stop || !this->tasks.empty(); });
                    if(this->stop && this->tasks.empty()) return;
                    task = move(this->tasks.front());
                    this->tasks.pop();
                }
                try {
                    task();
                } catch (const exception& e) {
                    cout << Display::ERROR_ICON << " Thread pool task error: " << e.what() << endl;
                }
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        unique_lock<mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(thread &worker: workers) {
        worker.join();
    }
}