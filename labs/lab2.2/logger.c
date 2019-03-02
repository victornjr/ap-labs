#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>

time_t currentTime;
struct tm * localT;

void getTime(){
  char timeHMS[9];
  time(&currentTime);
  localT = localtime(&currentTime);
  strftime(timeHMS, sizeof(timeHMS), "%H:%M:%S", localT);
  fputs(timeHMS,stdout);
}

int infof(const char *format, ...){
  int result;
  va_list args;
  va_start(args, format);
  getTime();
  fputs(" INFO ", stdout);
  result = vfprintf(stdout, format, args);
  va_end(args);
  return result;
}
int warnf(const char *format, ...){
  int result;
  va_list args;
  va_start(args, format);
  getTime();
  fputs(" WARN ", stdout);
  result = vfprintf(stdout, format, args);
  va_end(args);
  return result;
}
int errorf(const char *format, ...){
  int result;
  va_list args;
  va_start(args, format);
  getTime();
  fputs(" ERROR ", stdout);
  result = vfprintf(stdout, format, args);
  va_end(args);
  return result;
}
int panicf(const char *format, ...){
  int result;
  va_list args;
  va_start(args, format);
  getTime();
  fputs(" PANIC ", stdout);
  result = vfprintf(stdout, format, args);
  va_end(args);
  return result;
}
