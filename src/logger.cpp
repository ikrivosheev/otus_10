#include "logger.h"


void Logger::log(std::shared_ptr<Record> record) {
    for (auto& handler: _handlers) {
        handler.get()->emit(record);
    }
}

void Logger::log(const std::string& str) {
    std::shared_ptr<Record> record = std::make_shared<Record>(str);
    log(record);
}

void Logger::log(const std::string& str, const std::time_t& time) {
    std::shared_ptr<Record> record = std::make_shared<Record>(str, time);
    log(record);
}
