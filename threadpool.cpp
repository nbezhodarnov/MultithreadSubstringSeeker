#include "threadpool.h"

ThreadPool::ThreadPool(const int &threadsNumber)
{
    std::unique_lock lock(mutex);
    stoping = false;
    canceling = false;
    threads.reserve(threadsNumber);
    for (int i = 0; i < threadsNumber; i++) {
        threads.emplace_back(std::bind(&ThreadPool::threadFunction, this));
    }
}

void ThreadPool::terminate()
{
    std::unique_lock lock(mutex);
    if (!isRunning()) {
        return;
    }
    stoping = true;
    condition.notify_all();
    for (auto &thread : threads) {
        thread.join();
    }
}

void ThreadPool::cancel()
{
    std::unique_lock lock(mutex);
    if (!isRunning()) {
        return;
    }
    canceling = true;
    tasksQueue.clear();
    condition.notify_all();
    for (auto &thread : threads) {
        thread.join();
    }
}

bool ThreadPool::isRunning() const
{
    return !canceling && !stoping;
}

int ThreadPool::size()
{
    return tasksQueue.size();
}

ThreadPool::~ThreadPool() {
    terminate();
}

void ThreadPool::threadFunction()
{
    for (;;) {
        bool taskRecieved = false;
        std::function<void()> task;
        
        // Wait for new task or stop (cancel) command
        {
            std::unique_lock<std::shared_mutex> lock(mutex);
            condition.wait(lock, [this, &taskRecieved, &task] {
                if (!tasksQueue.empty()) {
                    task = tasksQueue.front();
                    tasksQueue.pop();
                    taskRecieved = true;
                } else {
                    taskRecieved = false;
                }
                return canceling || stoping || taskRecieved;
            });
        }
        
        if (canceling || (stoping && !taskRecieved)) {
            return;
        }
        
        task();
    }
}
