int initLogger(char *logType);
int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main(int argc, char** argv){
    infof("Printing on STDOUT\n");
    infof("This is an example of %s in %s\n","INFO","STDOUT");
    warnf("This is an example of %s in %s\n","WARNING","STDOUT");
    errorf("This is an example of %s in %s\n","ERROR","STDOUT");
    panicf("This is an example of %s in %s\n","PANIC","STDOUT");

    infof("Printing on SYSLOG (/var/log/syslog)\n");
    initLogger("syslog");

    infof("This is an example of %s in %s\n","INFO","SYSLOG");
    warnf("This is an example of %s in %s\n","WARNING","SYSLOG");
    errorf("This is an example of %s in %s\n","ERROR","SYSLOG");
    panicf("This is an example of %s in %s\n","PANIC","SYSLOG");
    return 0;
}
