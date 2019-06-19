#ifndef STATISTIC_H
#define STATISTIC_H

#include <iostream>
#include <thread>


struct MainThread {
    MainThread() = default;
    MainThread(const MainThread&) = default;
    MainThread& operator = (const MainThread&) = default;

    std::size_t lines = 0;
    std::size_t commands = 0;
    std::size_t blocks = 0;
};

std::ostream& operator << (std::ostream& out, const MainThread&);


struct WorkerThread {
    WorkerThread() = default;
    WorkerThread(const WorkerThread&) = default;
    WorkerThread& operator = (const WorkerThread&) = default;

    std::thread::id id = std::this_thread::get_id();
    std::size_t commands = 0;
    std::size_t blocks = 0;
};

std::ostream& operator << (std::ostream& out, const WorkerThread&);


#endif // STATISTIC_H
