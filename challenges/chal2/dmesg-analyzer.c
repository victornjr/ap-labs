#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define REPORT_FILE "report.txt"

void analizeLog(char *logFile, char *report);
void fileRead(int);

int main(int argc, char **argv) {

    if (argc < 2) {
    	printf("Usage:./dmesg-analizer.o logfile.txt\n");
    	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void fileRead(int id){

}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    int fileR;
    char element[1];
    int fileW;

    if((fileR = open(logFile, O_RDONLY )) < 0){
      printf("Can't open log file\n");
    }
    else{
      if((fileW = creat(report, S_IRUSR | S_IWUSR)) < 0){
        printf("Can't create the reportfile\n");
      }

      while(read(fileR,element,1) == 1){
          write(fileW,element,strlen(element));
      }
      close(fileR);
      close(fileW);
    }


    printf("Report is generated at: [%s]\n", report);
}
