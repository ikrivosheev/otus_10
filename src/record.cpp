#include "record.h"


Record::Record(RecordType type, const std::vector<std::string>& c): _commands(c), _type(type) {
    _time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

Record::Record(RecordType type, const std::vector<std::string>& c, const std::time_t& time): 
    _commands(c), _time(time), _type(type) {}

const std::string Record::str() const {
    std::stringstream ss;
    ss << "bulk: ";
    for (auto it = _commands.cbegin(); it != _commands.cend(); ++it) {
        if ( it != _commands.cbegin()) {
            ss << ", ";
        }
        ss  << (*it);
    }
    return ss.str();
}

const std::size_t Record::size() const {
    _commands.size();
}

const std::time_t& Record::time() const {
    return _time;
}

RecordType Record::type() const {
    return _type;
}
