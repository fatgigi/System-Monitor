#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include "linux_parser.h"
#include "format.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// choose the formula: (memTotal - memFree)/ memTotal
float LinuxParser::MemoryUtilization() { 
  string key;
  float memTotal, memFree, value;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    for (int i = 0; i < 2; i++) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:") {
        memTotal = value;
      } else {
        memFree = value;
      } 
    }
  }
  return (memTotal - memFree) / memTotal; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key;
  int processes, value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") {
        processes = value;
      } 
    }
  }
  return processes; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  int procsRunning, value;
  string line, key;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running") {
        procsRunning = value;
      } 
    }
  }
  return procsRunning; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime;
  string line;
  long value;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
    return value;
  }
  return 0; 
}

// TODO: Read and return CPU utilization
vector<std::string> LinuxParser::CpuUtilization() { 
  string line, key, value;
  vector<std::string> cpu_data{};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> key;
    while (linestream >> value) {
      cpu_data.push_back(value);
    }
  }
  assert(cpu_data.size() == 10);
  return cpu_data; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  vector<string> data = CpuUtilization();
  return stol(data[CPUStates::kUser_]) + stol(data[CPUStates::kNice_]) +
        stol(data[CPUStates::kSystem_]) + stol(data[CPUStates::kIRQ_]) +
        stol(data[CPUStates::kIdle_]) + stol(data[CPUStates::kIOwait_]) +
        stol(data[CPUStates::kSoftIRQ_]) + stol(data[CPUStates::kSteal_]) +
        stol(data[CPUStates::kGuest_]) + stol(data[CPUStates::kGuestNice_]);
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string key, line;
  long int value{0}, active_jiffies{0};
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < 13; ++i) {
      linestream >> key;
    }
    for (int i = 0; i < 4; ++i) {
      linestream >> value;
      active_jiffies += value;
    }
    return active_jiffies;
  }
  return active_jiffies;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  vector<string> data = CpuUtilization();
  return stol(data[CPUStates::kUser_]) + stol(data[CPUStates::kNice_]) +
        stol(data[CPUStates::kSystem_]) + stol(data[CPUStates::kIRQ_]) +
        stol(data[CPUStates::kSoftIRQ_]) + stol(data[CPUStates::kSteal_]);
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  vector<string> data = CpuUtilization();
  return stol(data[CPUStates::kIdle_]) + stol(data[CPUStates::kIOwait_]); 
}


string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    return line;
  }
  return string{};
}

string LinuxParser::Ram(int pid) { 
  string key, line, value;
  const int kToM = 1000;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          return to_string(stol(value) / kToM);
        }
      }
    }
  }
  return string{};
}


string LinuxParser::Uid(int pid) { 
  string key, line, value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return string{};
}


string LinuxParser::User(int pid) { 
  string uid = Uid(pid);
  string line, key, value;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), 'x', ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> value >> key) {
        if (key == uid) {
          return value;
        }
      }
    }
  }
  return string();
}


long LinuxParser::UpTime(int pid) { 
  string key, line;
  long int value;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < 21; ++i) {
      linestream >> key;
    }
    linestream >> value;
    value = (value*1.0) / sysconf(_SC_CLK_TCK);
    return value;
  }
  return 0;
}