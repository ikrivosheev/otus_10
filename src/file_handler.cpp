#include <sstream>
#include "file_handler.h"


FileHandler::FileHandler(const std::string& base_dir) {
    _base_dir = base_dir;
}

FileHandler::FileHandler(const std::string& base_dir, const std::string& prefix) {
    _base_dir = base_dir;
    _prefix = prefix;
}


void FileHandler::flush() {
    _stream.flush();
}


std::vector<WorkerThread> FileHandler::stat() const {
    std::vector<WorkerThread> v{_stat};
    return v;
}

void FileHandler::stop() {
    if (_stream.is_open()) {
        flush();
        _stream.close();
    }
}

void FileHandler::emit(std::shared_ptr<Record> record) {
    if (!_stream.is_open()) {
        std::stringstream ss;
        ss << _base_dir << _prefix << record->time() << ".log";
        _stream.open(ss.str());
    }
    _stat.commands += record->size();
    if (record->type() == RecordType::BLOCK) {
        ++_stat.blocks;
    }
    
    _stream << record->str() << FileHandler::TERMINATOR;
}

FileHandler::~FileHandler() {
   stop(); 
}

