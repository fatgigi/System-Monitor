#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   
  std::vector<Process>& Processes();  
  float MemoryUtilization();         
  long UpTime(); 
  int TotalProcesses();     
  int RunningProcesses();
  std::string Kernel();        
  std::string OperatingSystem();     

 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  float memoryUtilization_ = 0.0f;
  long upTime_ = 0l;
  int totalProcesses_ = 0;
  int runningProcesses_ = 0;
  std::string kernel_;
  std::string operatingSystem_;
};

#endif
