#include "console_handler.h"


void ConsoleHandler::flush() {
    std::cout.flush();
}

void ConsoleHandler::emit(std::shared_ptr<Record> record) {
    std::cout << record->str() << ConsoleHandler::TERMINATOR;
}

ConsoleHandler::~ConsoleHandler() {
    flush();
}
