#include "console_handler.h"


void ConsoleHandler::flush() {
    std::cout.flush();
}

void ConsoleHandler::emit(std::shared_ptr<Record> record) {
    _stat.commands += record->size();
    if (record->type() == RecordType::BLOCK) {
        ++_stat.blocks;
    }
    std::cout << record->str() << ConsoleHandler::TERMINATOR;
}

void ConsoleHandler::stop() {
    flush();
}

std::vector<WorkerThread> ConsoleHandler::stat() const {
    std::vector<WorkerThread> v{_stat};
    return v;
}

ConsoleHandler::~ConsoleHandler() {
    flush();
}
