#include "state_machine.h"


StateMachine::StateMachine(int bulk_size) {
    _bulk_size = bulk_size;
}

STATE StateMachine::current_state() {
    return _cstate;
}

const MainThread& StateMachine::stat() const {
    return _stat;
}

void StateMachine::push_command(const std::string& command) {
    ++_stat.lines;
    switch(_cstate) {
        case STATE::COMMAND:
            if (command == "{") {
                _stack.push('{');
                execute(RecordType::COMMAND);
                _cstate = STATE::BLOCK;
            }
            else {
                ++_stat.commands;
                _commands.push_back(command);
                if (_commands.size() == 1) {
                    time(&_time);
                }
                if (_commands.size() == _bulk_size) {
                    execute(RecordType::COMMAND);
                }
            }
            break;
        case STATE::BLOCK:
            if (command == "{") {
                _stack.push('{');
                break;
            }
            else if (command == "}") {
                _stack.pop();
                if (_stack.empty()) {
                    ++_stat.blocks;
                    execute(RecordType::BLOCK);
                    _cstate = STATE::COMMAND;
                }
            }
            else {
                ++_stat.commands;
                _commands.push_back(command);
            }
            break;
    }
}

void StateMachine::execute(RecordType type) {
    if (!_commands.size()) return;
    Logger::get()->log(type, _commands, _time);
    _commands.clear();
}

