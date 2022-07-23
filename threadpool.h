#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <functional>
#include <atomic>
#include <chrono>
#include <future>
#include <thread>
#include <mutex>

#include "multithreadqueue.h"

class ThreadPool {
public:
    ThreadPool(const int &threadsNumber = std::thread::hardware_concurrency());
    
    void terminate();
    void cancel();
    bool isRunning() const;
    int size();
    
    template <typename Function, typename... Arguments>
    auto addTask(Function&& function, Arguments&&... arguments) -> std::future<decltype(function(arguments...))>;
    
    ~ThreadPool();

private:
    std::atomic<bool> stoping;
    std::atomic<bool> canceling;
    std::vector<std::thread> threads;
    std::shared_mutex mutex;
    std::condition_variable_any condition;
    MultithreadQueue<std::function<void()>> tasksQueue;

    void threadFunction();
};

template <typename Function, typename... Arguments>
auto ThreadPool::addTask(Function&& function, Arguments&&... arguments) -> std::future<decltype(function(arguments...))>
{
    using returnType = decltype(function(arguments...));
    using taskType = std::packaged_task<returnType()>;

    if (stoping || canceling) {
        throw std::runtime_error("ThreadPool: Trying to add tasks in stopped thread pool!");
    }

    auto bindFuncion = std::bind(std::forward<Function>(function), std::forward<Arguments>(arguments)...);
    std::shared_ptr<taskType> task = std::make_shared<taskType>(std::move(bindFuncion));
    std::future<returnType> futureValue = task->get_future();
    tasksQueue.push([task]() -> void { (*task)(); });
    condition.notify_one();
    return futureValue;
}

#endif // THREADPOOL_H
