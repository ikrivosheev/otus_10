#include "statistic.h"

std::ostream& operator << (std::ostream& out, const MainThread& stat) {
    out << "Main thread: " << stat.lines << " lines, " << stat.commands << " commands, " << stat.blocks << " blocks";
    return out;
}

std::ostream& operator << (std::ostream& out, const WorkerThread& stat) {
    out << "Thread: " << stat.id << " " << stat.commands << " commands, " << stat.blocks << " blocks";
    return out;
}
