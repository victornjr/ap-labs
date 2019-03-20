Lab 3.1 - File/Directory Monitor
================================

A program that logs all file creations, deletions, and renames under the directory named in its command-line argument.
The program should monitor events in all of the subdirectories under the specified directory.
When a new subdirectory is added under the tree or a directory is deleted, the set of monitored subdirectories should be updated accordingly.

To compile the program just use the Makefile:
```
make
```
And to run the program just run it as a normal one and add the path of the directory you would like to monitor:
```
./monitor pathname...
```
