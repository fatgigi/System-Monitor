#include "processor.h"
#include "linux_parser.h"

float Processor::Utilization() { 
    GetLinuxParseCpuData(cur_cpu_data_);
    array<long, 2> diff_data_ {};
    GetDiffData(prev_cpu_data_, cur_cpu_data_, diff_data_);
    utilization_ = CalculateDiffUtilization(diff_data_);
    prev_cpu_data_.swap(cur_cpu_data_);// update the previous
    return utilization_; 
}

void Processor::GetDiffData(array<long, 2>& prev, array<long, 2>& cur,  array<long, 2>& diff) {
    diff[0] = cur[0] - prev[0];
    diff[1] = cur[1] - prev[1];
}

void Processor::GetLinuxParseCpuData(array<long, 2>& cpu) {
    cpu[0] = LinuxParser::ActiveJiffies();
    cpu[1] = LinuxParser::Jiffies();
}

float Processor::CalculateDiffUtilization(array<long, 2>& diff_data_) {
    return (diff_data_[0] * 1.0f)/ diff_data_[1];
}
