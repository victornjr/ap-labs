Lab 3.2 - Progress Notifier with Signals
========================================
A program for encoding and decoding files by using the `Base64` [algorithm](https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64). This program has the addition of giving the progress of encoding and decoding by using signals like `SIGINFO` and `SIGINT`.

In order to compile the program just use the `Makefile`:
```
make
```
Then after compilation you may use the encoder or decoder.

Encoder
--------
```
./base64 --encode fileName
```
The program will generate a new `encoded.txt` file with the result.

Decoder
--------
```
./base64 --decode encoded.txt
```
The program will generate a `decoded.txt` file with the result.

How to test?
------------
To test the program, while it is running you can do the next in a new terminal.
- Get process ID
```
ps aux | grep base64
```
With the process ID then do the next:
- Send the signals
```
kill -SIGINT <PID>
kill -SIGINFO <PID>
```


Test files
----------
You may use these files to test it:

- [vgilante.txt](http://textfiles.com/stories/vgilante.txt)
- [sick-kid.txt](http://textfiles.com/stories/sick-kid.txt)
- [aesop11.txt](http://textfiles.com/stories/aesop11.txt)
