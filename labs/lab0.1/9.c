#include <stdio.h>

int main(){
  //Exercise 9
  printf("\nExercise 9:\n");
  int c,flag;
  flag = 0;
  printf("\nInput some text with many blanc spaces, then press CTRL+D\n");
  while((c = getchar()) != EOF){
    if(c == '\b'){
      if(!flag){
        flag = 1;
        putchar(c);
      }
    }
    else{
      flag = 0;
      putchar(c);
    }
  }
}
