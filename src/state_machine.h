#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stack>
#include <vector>
#include <memory>
#include <ctime>
#include "logger.h"


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
        void push_command(const std::string& command);
        void execute();
    
    private:
        
        int _bulk_size;
        STATE _cstate = STATE::COMMAND;
        std::time_t _time = 0;
        std::stack<char> _stack;
        std::vector<std::string> _commands;
};

#endif // STATE_MACHINE_H
