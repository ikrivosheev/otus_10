#ifndef THREAD_CONSOLE_HANDLER_H
#define THREAD_CONSOLE_HANDLER_H

#include <mutex>
#include <thread>
#include "handler.h"
#include "queue.h"

class ThreadConsoleHandler: public IHandler {
    public:
        ThreadConsoleHandler();
        void flush() override;
        void emit(std::shared_ptr<Record>) override;
        
        ~ThreadConsoleHandler();
    private:
        void worker();

        bool shutdown = false;
        std::mutex _mutex;
        Queue<std::shared_ptr<Record>> _queue;
        std::thread _thread;
};

#endif // THREAD_CONSOLE_HANDLER_H
