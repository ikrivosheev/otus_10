#include <iostream>
#include <memory>
#include "logger.h"
#include "console_handler.h"
#include "file_handler.h"
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
    Logger::get().add_handler<ConsoleHandler>();
    Logger::get().add_handler<FileHandler>("/tmp/", "bulk");
    StateMachine state(bulk_size);
    while (true) {
        std::string tmp;
        std::cin >> tmp;
        state.push_command(tmp);
    }
    return 0;
}
