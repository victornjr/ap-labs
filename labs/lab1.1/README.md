Lab 1.1 - mycat
===============
This lab is about the performance of two programs. The first one is cat2.c, which is a representation of the cat function used to concatenate. This program uses functions from a library amd the comparison is between it and the mycat.c program which uses system calls instead of the functions.

Each program ran with the KJBible.txt file, which is big enough to see both performances.
The way to compile them is:
		gcc mycat.c -o mycat

After compilation to run the program do the next:
		./mycat KJBible.txt

If you would like to concatenate more files, just add them after the execute program:
		./mycat KJBible.txt hola.txt example.txt


The next are some images that show the performance of both programs using GPROF, that is included in the gcc compiler. Also a time test was made to see which one rean faster.




