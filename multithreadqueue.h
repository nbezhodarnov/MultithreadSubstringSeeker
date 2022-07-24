#ifndef MULTITHREADQUEUE_H
#define MULTITHREADQUEUE_H


#include <shared_mutex>
#include <mutex>
#include <queue>

template <typename T>
class MultithreadQueue {
public:
    explicit MultithreadQueue() = default;
    bool empty();
    int size();
    T front();
    T back();
    void push(const T &element);
    void pop();
    void clear();

private:
    std::queue<T> queue;
    std::shared_mutex mutex;
};

template <typename T>
bool MultithreadQueue<T>::empty()
{
    std::shared_lock<std::shared_mutex> lock(mutex);
    return queue.empty();
}

template <typename T>
int MultithreadQueue<T>::size()
{
    std::shared_lock<std::shared_mutex> lock(mutex);
    return queue.size();
}

template <typename T>
T MultithreadQueue<T>::front()
{
    std::shared_lock<std::shared_mutex> lock(mutex);
    return queue.front();
}

template <typename T>
T MultithreadQueue<T>::back()
{
    std::shared_lock<std::shared_mutex> lock(mutex);
    return queue.back();
}

template <typename T>
void MultithreadQueue<T>::push(const T& element)
{
    std::unique_lock<std::shared_mutex> lock(mutex);
    queue.push(element);
}

template <typename T>
void MultithreadQueue<T>::pop()
{
    std::unique_lock<std::shared_mutex> lock(mutex);
    queue.pop();
}

template <typename T>
void MultithreadQueue<T>::clear()
{
    std::unique_lock<std::shared_mutex> lock(mutex);
    queue = std::queue<T>();
}

#endif // MULTITHREADQUEUE_H
