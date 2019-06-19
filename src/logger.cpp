#include "logger.h"


void Logger::log(std::shared_ptr<Record> record) {
    for (auto& handler: _handlers) {
        handler.get()->emit(record);
    }
}

void Logger::log(RecordType type, const std::vector<std::string>& c) {
    std::shared_ptr<Record> record = std::make_shared<Record>(type, c);
    log(record);
}

void Logger::log(RecordType type, const std::vector<std::string>& c, const std::time_t& time) {
    std::shared_ptr<Record> record = std::make_shared<Record>(type, c, time);
    log(record);
}

void Logger::stop() {
    for (auto& handler: _handlers) {
        handler->stop();
    }
}

std::vector<WorkerThread> Logger::stat() const {
    std::vector<WorkerThread> statistic;
    for (auto& handler: _handlers) {
        for (auto& s: handler->stat()) {
            statistic.push_back(s);
        }
    }
    return statistic;
}
