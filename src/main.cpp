#include <iostream>
#include <memory>
#include <csignal>

#include "logger.h"
#include "thread_console_handler.h"
#include "thread_file_handler.h"
#include "state_machine.h"



int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage bulk <bulk size>" << std::endl;
        return 1;
    }
    
    int bulk_size;
    try {
        bulk_size = std::stoi(argv[1]);
    }
    catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    Logger::get()->add_handler<ThreadConsoleHandler>();
    Logger::get()->add_handler<ThreadFileHandler>("/tmp/", "bulk", 2);
    StateMachine state(bulk_size);
    for (std::string line; std::getline(std::cin, line);) {
        state.push_command(line);
    }
    Logger::get()->stop();
    std::cout << state.stat() << std::endl;
    for (auto& stat: Logger::get()->stat()) {
        std::cout << stat << std::endl;
    }
    delete Logger::get();
    return 0;
}
