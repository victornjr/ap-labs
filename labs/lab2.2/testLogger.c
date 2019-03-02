int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main(int argc, char** argv){
    infof("This is an example of %s number %d\n","INFO",1);
    warnf("This is an example of %s number %d\n","WARNING",2);
    errorf("This is an example of %s number %d\n","ERROR",3);
    panicf("This is an example of %s number %d\n","PANIC",4);
    return 0;
}
