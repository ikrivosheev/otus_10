#include "thread_console_handler.h"


ThreadConsoleHandler::ThreadConsoleHandler() {
    _thread = std::thread(&ThreadConsoleHandler::worker, this);
}

ThreadConsoleHandler::~ThreadConsoleHandler() {
    stop();
}

void ThreadConsoleHandler::flush() {
    std::unique_lock<std::mutex> u_lock(_mutex);
    std::cout.flush();
}

void ThreadConsoleHandler::emit(std::shared_ptr<Record> record) {
    _queue.push(record);
}

void ThreadConsoleHandler::worker() {
    _stat.id = std::this_thread::get_id();
    while (!shutdown) {
        auto record = _queue.pop();
        if (record == nullptr) {
             continue;
        }
        
        _stat.commands += record->size();
        if (record->type() == RecordType::BLOCK) {
            ++_stat.blocks;
        }
        {
            std::unique_lock<std::mutex> u_lock(_mutex);
            std::cout << record->str() << ThreadConsoleHandler::TERMINATOR;
        }
    }
    while (!_queue.empty()) {
        auto record = _queue.pop();
        if (record == nullptr) {
            continue;
        }
        _stat.commands += record->size();
        if (record->type() == RecordType::BLOCK) {
            ++_stat.blocks;
        }
        {
            std::unique_lock<std::mutex> u_lock(_mutex);
            std::cout << record->str() << ThreadConsoleHandler::TERMINATOR;
        }
    }
    flush();
}

void ThreadConsoleHandler::stop() {
    shutdown = true;
    _queue.stop();
    if (_thread.joinable()) {
        _thread.join();
    }
}

std::vector<WorkerThread> ThreadConsoleHandler::stat() const {
    std::vector<WorkerThread> vector{_stat};
    return vector;
}
