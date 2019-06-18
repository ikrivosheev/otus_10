#include <sstream>
#include "thread_file_handler.h"


ThreadFileHandler::ThreadFileHandler(const std::string& base_dir, std::size_t thread_count): _base_dir(base_dir) {
    for (std::size_t i = 0; i < thread_count; ++i) {
        std::thread thread(&ThreadFileHandler::worker, this);
        _threads.push_back(std::move(thread));
    }
}

ThreadFileHandler::ThreadFileHandler(const std::string& base_dir, const std::string& prefix, std::size_t thread_count):
    _base_dir(base_dir), _prefix(prefix) {

    for (std::size_t i = 0; i < thread_count; ++i) {
        std::thread thread(&ThreadFileHandler::worker, this);
        _threads.push_back(std::move(thread));
    } 
}


void ThreadFileHandler::flush() {
}

void ThreadFileHandler::emit(std::shared_ptr<Record> record) {
    _queue.push(record);
}

void ThreadFileHandler::worker() {
    std::ofstream stream;
    
    while (!shutdown) {
        auto record = _queue.pop();
        if (!stream.is_open()) {
            std::stringstream ss;
            ss << _base_dir << _prefix << record->time() << "-" << std::this_thread::get_id() << ".log";
            stream.open(ss.str());
        }
        stream << record->str().data() << ThreadFileHandler::TERMINATOR;
    }
    std::cout << "END!!!" << std::endl;
    while (!_queue.empty()) {
        auto record = _queue.pop();
        stream << record->str() << ThreadFileHandler::TERMINATOR;
    }
    std::cout << "End!!" << std::endl;
    stream.flush();
    stream.close();
}

ThreadFileHandler::~ThreadFileHandler() {
    std::cout << "Destroy" << std::endl;
    shutdown = true;
    for (auto& thread: _threads) {
        thread.join();
    }
}

