#include "thread_console_handler.h"


ThreadConsoleHandler::ThreadConsoleHandler() {
    _thread = std::thread(&ThreadConsoleHandler::worker, this);
}

ThreadConsoleHandler::~ThreadConsoleHandler() {
    shutdown = true;
    _queue.stop();
    _thread.join();
}

void ThreadConsoleHandler::flush() {
    {
        std::unique_lock<std::mutex> u_lock(_mutex);
        std::cout.flush();
    }
}

void ThreadConsoleHandler::emit(std::shared_ptr<Record> record) {
    _queue.push(record);
}

void ThreadConsoleHandler::worker() {
   while (!shutdown) {
       auto record = _queue.pop();
       if (record == nullptr) {
            continue;
       }
       {
           std::unique_lock<std::mutex> u_lock(_mutex);
           std::cout << record->str() << ThreadConsoleHandler::TERMINATOR;
       }
   }
   while (!_queue.empty()) {
       auto record = _queue.pop();
       {
           std::unique_lock<std::mutex> u_lock(_mutex);
           std::cout << record->str() << ThreadConsoleHandler::TERMINATOR;
       }
   }
   flush();
}

