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

## Runing time test

### cat2.c time
<img width="126" alt="cat2_time" src="https://user-images.githubusercontent.com/16769115/52595974-c9b7cb80-2e14-11e9-9d72-c04e627417b3.png">

### mycat.c time

<img width="126" alt="captura de pantalla 2019-02-11 a la s 11 57 14" src="https://user-images.githubusercontent.com/16769115/52595774-439b8500-2e14-11e9-983d-807f89c92d3c.png">

## GPROF test

### cat2.c test
<img width="735" alt="cat2" src="https://user-images.githubusercontent.com/16769115/52595769-3c747700-2e14-11e9-9ec8-30273f0b92d5.png">

### mycat.c test
<img width="744" alt="mycat" src="https://user-images.githubusercontent.com/16769115/52595658-fc14f900-2e13-11e9-847f-4bd0a91b27bd.png">






