#ifndef THREAD_FILE_HANDLER_H
#define THREAD_FILE_HANDLER_H

#include <string>
#include <fstream>
#include <thread>
#include "handler.h"
#include "queue.h"


class ThreadFileHandler: public IHandler {
    public:
        ThreadFileHandler(const std::string&, std::size_t);
        ThreadFileHandler(const std::string&, const std::string&, std::size_t);
        void flush() override;
        void emit(std::shared_ptr<Record>) override;
        ~ThreadFileHandler();

    private:
        void worker();

        std::string _base_dir;
        std::string _prefix;

        bool shutdown = false;
        std::vector<std::thread> _threads;
        Queue<std::shared_ptr<Record>> _queue;
};

#endif // THREAD_FILE_HANDLER_H
