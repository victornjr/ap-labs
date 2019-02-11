#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/* fileRead: reads every line of the file and writes it */
void fileRead(int ifp)
{
    char line[1];
    while(read(ifp,line,1) == 1){
      write(1,line,strlen(line));
    }

}

/* cat:  concatenate files, version 2 */
int main(int argc, char *argv[])
{
    int fp;
    void fileRead(int);
    char *prog = argv[0];   /* program name for errors */

    if (argc == 1)  /* no args; copy standard input */
        fileRead('\0');
    else
        while (--argc > 0)
            if ((fp = open(*++argv, O_RDONLY)) < 0) {
                write(1,prog,strlen(prog));
                write(1,": can′t open ",16);
                write(1,*argv,strlen(*argv));
                write(1,"\n",1);
                return 1;
            } else {
                fileRead(fp);
                close(fp);
            }

    return 0;
}
