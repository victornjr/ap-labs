Lab 2.2 - Logger Library
========================

Logger library in C that will be used for printing the following types of messages.
- `INFO` General information.
- `WARN` Warnings.
- `ERROR` Errors.
- `PANIC` Panics. Non recoverable issues with core dump.

This `logger` library is used instead of `printf` function calls.

In order to compile the library with the `testLogger.c` file do the next thing:
```
gcc testLogger.c logger.c -o testLogger
```
By doing this, you will compile the `testLogger.c` file with the `logger.c` file and be able to use the library.

To run the test, do the next thing:
```
./testLogger
```
And an example of each type of message will print on the stdout.
