#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { 
    return pid_;
}

float Process::CpuUtilization() {
    cpuUtilization_ = LinuxParser::ActiveJiffies(pid_) * 1.0f/ LinuxParser::Jiffies(); 
    return cpuUtilization_; 
}

string Process::Command() { 
    command_ = LinuxParser::Command(pid_);
    return command_; 
}

string Process::Ram() { 
    ram_ = LinuxParser::Ram(pid_);
    return ram_; 
}

string Process::User() { 
    user_ = LinuxParser::User(pid_);
    return user_; 
}

long int Process::UpTime() { 
    upTime_ = LinuxParser::UpTime(pid_);
    return upTime_; 
}

bool Process::operator<(Process const& a) const { 
    return this->cpuUtilization_ > a.cpuUtilization_; 
}
