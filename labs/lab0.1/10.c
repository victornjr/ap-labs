#include <stdio.h>

int main(){
  //Exercise 10
  printf("\nExercise 10:\n");
  int c,flag;
  flag = 0;
  printf("\nInput some text with many blanc spaces, tabs and backslash, then press CTRL+D\n");
  while((c = getchar()) != EOF){
    if(c == '\b'){
        printf("\\b");
    }
    else if(c == '\t'){
      printf("\\t");
    }
    else if(c == '\\'){
      printf("\\\\");
    }
    else{
      putchar(c);
    }
  }
}
