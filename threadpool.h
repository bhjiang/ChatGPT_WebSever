#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
public:
    ThreadPool(int num_threads);
    ~ThreadPool();
    void add_task(std::function<void()> task);
private:
    void worker_thread();

    std::queue<std::function<void()>> m_tasks;
    std::vector<std::thread> m_threads;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_stop;
};

#endif // THREADPOOL_H

/*
线程池中的任务队列使用std::queue来存储待执行的任务，工作线程使用std::thread来创建，并在worker_thread函数中执行任务。线程池管理器的主要作用是管理线程池的启动、停止和管理工作线程的数量，这里通过构造函数创建指定数量的工作线程来实现。当有新的任务到来时，调用add_task函数将任务添加到任务队列中，然后通过std::condition_variable来通知工作线程有新任务到来。工作线程从任务队列中取出任务并执行，执行完毕后再返回任务队列等待下一个任务。线程池的析构函数中，先将m_stop标志设置为true，然后通过std::condition_variable来通知所有的工作线程退出。
*/
