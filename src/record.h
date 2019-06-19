#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>


enum class RecordType {
    COMMAND,
    BLOCK
};


class Record {
    public:
        Record(RecordType, const std::string&);
        Record(RecordType, const std::string&, const std::time_t&);
        Record(const Record&) = default;
        
        RecordType type() const;
        const std::string str() const;
        const std::time_t& time() const;
        ~Record() = default; 

    private:
        std::string _str;
        std::time_t _time;
        RecordType _type;
};

#endif // RECORD_H
