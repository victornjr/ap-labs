Lab 2.4 - Add syslog support to your logger
========================

Logger library in C that will be used for printing the following types of messages.
- `INFO` General information.
- `WARN` Warnings.
- `ERROR` Errors.
- `PANIC` Panics. Non recoverable issues with core dump.

This `logger` library is used instead of `printf` function calls. And the output can change between `stdout` and `syslog`. To change the output just use the function `initLogger(char *logType)` where `logType` is `"stdout"` or `""` for stdout, or `"syslog"` for printing on syslog.

To compile the program just use the Makefile by typing:
```
make
```

Then, to run the test, do the next thing:
```
./testLogger
```
And an example of each type of message will print on the stdout as well as an example for the syslog. You can see the syslog result on `/var/log/syslog`.
