#include <string>

#include "format.h"

using std::string;
using std::to_string;



string Format::Helper(string number) {
  if (stoi(number) < 10)
    return "0" + number;
  else
    return number;
}

string Format::ElapsedTime(long seconds) {
  const int sInM = 60;
  const int sInH = 3600;

  const long hours = seconds / sInH;
  const int minutes = (seconds - hours * sInH) / sInM;
  const int secs = seconds - hours * sInH - minutes * sInM;

  return Helper(to_string(hours)) + ":" + Helper(to_string(minutes)) + ":" +
         Helper(to_string(secs));
}