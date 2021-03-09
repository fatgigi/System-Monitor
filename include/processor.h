#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <array>
#include <vector>

using std::vector;
using std::array;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  void GetDiffData(array<long, 2>&, array<long, 2>&, array<long, 2>&);
  void GetLinuxParseCpuData(array<long, 2>&);
  float CalculateDiffUtilization(array<long, 2>&);

  // cpu_data[0] is the active jiffies
  // cpu_data[1] is the total jiffies
  array<long, 2> cur_cpu_data_;
  array<long, 2> prev_cpu_data_;
  float utilization_;
};

#endif