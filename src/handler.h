#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "statistic.h"
#include "record.h"

class IHandler {
    public:
        static const char TERMINATOR = '\n';
        virtual void flush() = 0;
        virtual void emit(std::shared_ptr<Record>) = 0;
        virtual void stop() = 0;
        virtual std::vector<WorkerThread> stat() const = 0;
        virtual ~IHandler() {};
};

#endif // HANDLER_H
