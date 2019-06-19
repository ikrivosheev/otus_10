#include "record.h"


Record::Record(RecordType type, const std::string& str): _str(str), _type(type) {
    _time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

Record::Record(RecordType type, const std::string& str, const std::time_t& time): 
    _str(str), _time(time), _type(type) {}

const std::string Record::str() const {
    return _str;
}

const std::time_t& Record::time() const {
    return _time;
}

RecordType Record::type() const {
    return _type;
}
