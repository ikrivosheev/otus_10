#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <memory>
#include <type_traits>
#include "handler.h"
#include "record.h"


class Logger {
    public:
        template<typename T, typename... Args>
        Logger& add_handler(Args&&... args) {
            static_assert(std::is_base_of<IHandler, T>::value, "Handler must be extend IHandler");
            // std::unique_ptr<IHandler> handler = std::make_unique<T>(std::forward<Args>(args)...);
            _handlers.push_back(std::make_unique<T>(std::forward<Args>(args)...));
            return (*this);
        }
        void log(const Record&);
        void log(const std::string&);
        void log(const std::string&, const std::time_t&);

        ~Logger() = default;

        static Logger& get() {
            static Logger logger;
            return logger;
        }

    private:
        Logger() {};
        Logger(const Logger&);
        Logger& operator=(Logger&);

        std::vector<std::unique_ptr<IHandler>> _handlers;
};

#endif // LOGGER_H
