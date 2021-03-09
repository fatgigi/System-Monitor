#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include "format.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

using namespace LinuxParser;
Processor& System::Cpu() { 
    return cpu_; 
}

vector<Process>& System::Processes() { 
    std::vector<int> pids = LinuxParser::Pids();
    for (auto pid : pids) {
        processes_.emplace_back(Process{pid});
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_; 
}

std::string System::Kernel() { 
    kernel_ = LinuxParser::Kernel();
    return kernel_; 
}

float System::MemoryUtilization() { 
    memoryUtilization_ = LinuxParser::MemoryUtilization();
    return memoryUtilization_; 
}

std::string System::OperatingSystem() { 
    operatingSystem_ = LinuxParser::OperatingSystem();
    return operatingSystem_; 
}

int System::RunningProcesses() { 
    runningProcesses_ = LinuxParser::RunningProcesses();
    return runningProcesses_; 
}

int System::TotalProcesses() {
    totalProcesses_ = LinuxParser::TotalProcesses(); 
    return totalProcesses_; 
}


long System::UpTime() { 
    upTime_ = LinuxParser::UpTime();
    return upTime_; 
}
