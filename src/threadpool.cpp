#include "threadpool.h"

ThreadPool::ThreadPool(int num_threads) : m_stop(false) {
    for (int i = 0; i < num_threads; ++i) {
        m_threads.emplace_back(std::bind(&ThreadPool::worker_thread, this));
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_stop = true;
        m_cv.notify_all();
    }
    for (auto& thread : m_threads) {
        thread.join();
    }
}

void ThreadPool::add_task(std::function<void()> task) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_tasks.push(task);
    m_cv.notify_one();
}

void ThreadPool::worker_thread() {
    while (true) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this]() { return !m_tasks.empty() || m_stop; });
        if (m_stop && m_tasks.empty()) {
            return;
        }
        auto task = m_tasks.front();
        m_tasks.pop();
        lock.unlock();
        task();
    }
}

