#ifndef CONSOLE_HANDLER_H
#define CONSOLE_HANDLER_H

#include <memory>
#include <ostream>
#include "statistic.h"
#include "handler.h"


class ConsoleHandler: public IHandler {
    public:
        void flush() override;
        void emit(std::shared_ptr<Record>) override;
        std::vector<WorkerThread> stat() const override;
        void stop() override;

        ~ConsoleHandler();

    private:
        WorkerThread _stat;

};

#endif // CONSOLE_HANDLER_H
