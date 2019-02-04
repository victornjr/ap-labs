#include <stdio.h>

int strlen(char*);
char* stradd(char*,char*);
int strfind(char*, char*);

int main(int argc, char** argv){

  printf("Initial Lenght\t: %d\n",strlen(argv[1]));

  char *newString = stradd(argv[1],argv[2]);
  printf("New String\t: %s\n", newString);

  if(strfind(newString,argv[3])){
    printf("SubString was found\t: yes\n");
  }
  else{
    printf("SubString was found\t: no\n");
  }

  free(newString);
  return 0;
}
