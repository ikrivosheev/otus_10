#include <sstream>
#include "thread_file_handler.h"


ThreadFileHandler::ThreadFileHandler(const std::string& base_dir, std::size_t thread_count): _base_dir(base_dir) {
    _stat.resize(thread_count);
    _threads.reserve(thread_count);
    for (std::size_t i = 0; i < thread_count; ++i) {
        std::thread thread(&ThreadFileHandler::worker, this);
        _threads.push_back(std::move(thread));
    }
}

ThreadFileHandler::ThreadFileHandler(const std::string& base_dir, const std::string& prefix, std::size_t thread_count):
    _base_dir(base_dir), _prefix(prefix) {

    _stat.resize(thread_count);
    _threads.reserve(thread_count);
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
    WorkerThread s;
    
    while (!shutdown) {
        auto record = _queue.pop();
        if (record == nullptr) {
            continue;
        }
        if (!stream.is_open()) {
            std::stringstream ss;
            ss << _base_dir << _prefix << record->time() << "-" << std::this_thread::get_id() << ".log";
            stream.open(ss.str());
        }
        s.commands += record->size();
        if (record->type() == RecordType::BLOCK) {
            ++s.blocks;
        }
        stream << record->str().data() << ThreadFileHandler::TERMINATOR;
    }
    while (!_queue.empty()) {
        auto record = _queue.pop();
        if (record == nullptr) {
            continue;
        }
        s.commands += record->size();
        if (record->type() == RecordType::BLOCK) {
            ++s.blocks;
        }
        stream << record->str() << ThreadFileHandler::TERMINATOR;
    }
    stream.flush();
    stream.close();
    {
        std::unique_lock<std::mutex> u_lock(_mutex);
        _stat.emplace_back(std::move(s));
    }
}

std::vector<WorkerThread> ThreadFileHandler::stat() const {
    return _stat;
}

void ThreadFileHandler::stop() {
    shutdown = true;
    _queue.stop();
    for (auto& thread: _threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

ThreadFileHandler::~ThreadFileHandler() {
   stop(); 
}

