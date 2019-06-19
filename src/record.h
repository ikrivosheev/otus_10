#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>


enum class RecordType {
    COMMAND,
    BLOCK
};


class Record {
    public:
        Record(RecordType, const std::vector<std::string>&);
        Record(RecordType, const std::vector<std::string>&, const std::time_t&);
        Record(const Record&) = default;
        
        RecordType type() const;
        const std::string str() const;
        const std::size_t size() const;
        const std::time_t& time() const;
        ~Record() = default; 

    private:
        std::vector<std::string> _commands;
        std::time_t _time;
        RecordType _type;
};

#endif // RECORD_H
