#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename T>
class Queue {
    public:
        T pop() {
            std::unique_lock<std::mutex> u_lock(_mutex);
            while (_queue.empty()) {
                _cond.wait(u_lock);
            }
            auto item = _queue.front();
            _queue.pop();
            return item;
        }

        void push (T item) {
            {
                std::unique_lock<std::mutex> u_lock(_mutex);
                _queue.push(item);
            }
            _cond.notify_one();
        }

        bool empty() {
            std::unique_lock<std::mutex> u_lock(_mutex);
            return _queue.empty();
        }

    private:
        std::queue<T> _queue;
        std::mutex _mutex;
        std::condition_variable _cond;
};

#endif // QUEUE_H
