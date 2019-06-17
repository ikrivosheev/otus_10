#include "logger.h"


void Logger::log(const Record& record) {
    for (auto& handler: _handlers) {
        handler.get()->emit(record);
    }
}

void Logger::log(const std::string& str) {
    Record record(str);
    log(record);
}

void Logger::log(const std::string& str, const std::time_t& time) {
    Record record(str, time);
    log(record);
}
