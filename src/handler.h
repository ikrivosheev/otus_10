#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <memory>
#include <iostream>
#include "record.h"

class IHandler {
    public:
        static const char TERMINATOR = '\n';
        virtual void flush() = 0;
        virtual void emit(std::shared_ptr<Record>) = 0;
};

#endif // HANDLER_H
