#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include <fstream>
#include "statistic.h"
#include "handler.h"


class FileHandler: public IHandler {
    public:
        FileHandler(const std::string&);
        FileHandler(const std::string&, const std::string&);
        
        void flush() override;
        void emit(std::shared_ptr<Record>) override;
        std::vector<WorkerThread> stat() const;
        void stop() override;

        ~FileHandler();

    private:
        std::string _base_dir;
        std::string _prefix;
        WorkerThread _stat;
        std::ofstream _stream;
};

#endif // FILE_HANDLER_H
