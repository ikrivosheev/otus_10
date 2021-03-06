#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stack>
#include <vector>
#include <memory>
#include <ctime>
#include <sstream>
#include "record.h"
#include "logger.h"
#include "statistic.h"


enum class STATE {
    COMMAND,
    BLOCK,
};


class StateMachine {
    public:
        StateMachine(int);
        StateMachine(const StateMachine&) = default;
        ~StateMachine() = default;
        
        STATE current_state();
        const MainThread& stat() const;
        void push_command(const std::string& command);
        void execute(RecordType);
    
    private:
        
        int _bulk_size;
        STATE _cstate = STATE::COMMAND;
        std::time_t _time = 0;
        std::stack<char> _stack;
        std::vector<std::string> _commands;
        MainThread _stat;
};

#endif // STATE_MACHINE_H
