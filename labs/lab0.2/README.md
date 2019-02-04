This program was implemented to do string manipulation, and could be used as a library for these actions: get the lenght of a string, concatenate two strings, and find a substring inside a string.

All these functions are inside the strlib.c file, and in order to use this library you need to compile the program this way:

		gcc -c str-main.c -o str-main.o
		gcc -c strlib.c -o strlib.o
		gcc str-main.o strlib.o -o str-final.o

Once it's compiled, the main program (str-main.c) needs to run this way:

		./str-final.o stringForLenght stringToConcatenate substringToSearch

For example, the next input:

		./str-final.o originalVeryLongString Addition Add

Should give these results:

		Initial Lenght      : 22
		New String          : originalVeryLongStringAddition
		SubString was found : yes
