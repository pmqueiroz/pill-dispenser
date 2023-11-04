#include "./includes/time.h"
#include <Arduino.h>

Time parseTimeString(String input) {
  Time result;
  sscanf(input.c_str(), "%d:%d[%d,%d,%d,%d,%d,%d,%d]",
         &result.hour, &result.minute,
         &result.daysOfWeek[0], &result.daysOfWeek[1], &result.daysOfWeek[2],
         &result.daysOfWeek[3], &result.daysOfWeek[4], &result.daysOfWeek[5],
         &result.daysOfWeek[6]);
  return result;
}
