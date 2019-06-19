#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <memory>
#include <type_traits>
#include "handler.h"
#include "record.h"
#include "statistic.h"


class Logger {
    public:
        template<typename T, typename... Args>
        Logger& add_handler(Args&&... args) {
            static_assert(std::is_base_of<IHandler, T>::value, "Handler must be extend IHandler");
            _handlers.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
            return (*this);
        }
        void log(const Record&);
        void log(RecordType, const std::vector<std::string>&);
        void log(RecordType, const std::vector<std::string>&, const std::time_t&);
        void stop();

        std::vector<WorkerThread> stat() const;

        ~Logger() = default; 

        static Logger* get() {
            static Logger* logger = new Logger();
            return logger;
        }

    private:
        Logger() {};
        Logger(const Logger&);
        Logger& operator=(Logger&);
        void log(std::shared_ptr<Record>);

        std::vector<std::unique_ptr<IHandler>> _handlers;
};

#endif // LOGGER_H
