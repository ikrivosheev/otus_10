#ifndef CONSOLE_HANDLER_H
#define CONSOLE_HANDLER_H

#include <memory>
#include <ostream>
#include "handler.h"


class ConsoleHandler: public IHandler {
    public:
        void flush() override;
        void emit(std::shared_ptr<Record>) override;
        ~ConsoleHandler();
};

#endif // CONSOLE_HANDLER_H
