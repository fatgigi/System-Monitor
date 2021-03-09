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
// TODO: Return the system's CPU
Processor& System::Cpu() { 
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    std::vector<int> pids = LinuxParser::Pids();
    for (auto pid : pids) {
        processes_.emplace_back(Process{pid});
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    kernel_ = LinuxParser::Kernel();
    return kernel_; 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    memoryUtilization_ = LinuxParser::MemoryUtilization();
    return memoryUtilization_; 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    operatingSystem_ = LinuxParser::OperatingSystem();
    return operatingSystem_; 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    runningProcesses_ = LinuxParser::RunningProcesses();
    return runningProcesses_; 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
    totalProcesses_ = LinuxParser::TotalProcesses(); 
    return totalProcesses_; 
}

// TODO: Return the number of seconds since the system started running
long System::UpTime() { 
    upTime_ = LinuxParser::UpTime();
    //std::cout << "hello: " << upTime_ << Format::ElapsedTime(upTime_) << std::endl;
    return upTime_; 
}