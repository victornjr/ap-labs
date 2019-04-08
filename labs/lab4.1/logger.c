#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <syslog.h>
#include <string.h>
#include "logger.h"

time_t currentTime;
struct tm * localT;

int typeOfLogger = 0; //STDOUT as default

int initLogger(char *logType){
  if(strcmp ("stdout", logType) == 0 || strcmp ("", logType) == 0){
    typeOfLogger = 0;
    return 1;
  }
  else if(strcmp ("syslog", logType) == 0){
    typeOfLogger = 1;
    return 1;
  }
  return 0;
}

void getTime(){
  char timeHMS[9];
  time(&currentTime);
  localT = localtime(&currentTime);
  strftime(timeHMS, sizeof(timeHMS), "%H:%M:%S", localT);
  fputs(timeHMS,stdout);
}

int infof(const char *format, ...){
  char start[300] = " INFO: ";
  int result;
  va_list args;
  va_start(args, format);
  strcat(start,format);
  if(typeOfLogger == 0){
    getTime();
    result = vfprintf(stdout, start, args);
  }else{
    vsyslog(LOG_ERR,start, args);
    result = 1;
  }
  va_end(args);

  return result;
}
int warnf(const char *format, ...){
  char start[300] = " WARN: ";
  int result;
  va_list args;
  va_start(args, format);
  strcat(start,format);
  if(typeOfLogger == 0){
    getTime();
    result = vfprintf(stdout, start, args);
  }else{
    vsyslog(LOG_ERR,start, args);
    result = 1;
  }
  va_end(args);

  return result;
}
int errorf(const char *format, ...){
  char start[300] = " ERROR: ";
  int result;
  va_list args;
  va_start(args, format);
  strcat(start,format);
  if(typeOfLogger == 0){
    getTime();
    result = vfprintf(stdout, start, args);
  }else{
    vsyslog(LOG_ERR,start, args);
    result = 1;
  }
  va_end(args);

  return result;
}

int panicf(const char *format, ...){
  char start[300] = " PANIC:";
  int result;
  va_list args;
  va_start(args, format);
  strcat(start,format);
  if(typeOfLogger == 0){
    getTime();
    result = vfprintf(stdout, start, args);
  }else{
    vsyslog(LOG_ERR,start, args);
    result = 1;
  }
  va_end(args);

  return result;
}
