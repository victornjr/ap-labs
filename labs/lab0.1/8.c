#include <stdio.h>

int main(){
  //Exercise 8
  printf("\nExercise 8:\n");
  int c,blanc, tabs, newline;
  blanc = 0;
  tabs = 0;
  newline = 0;
  printf("\nInput some words and press CTRL + D to continue (use blanc spaces, tabs and newlines)\n");
  while((c = getchar()) != EOF){
    if(c == '\b'){
      ++blanc;
    }
    else if(c == '\t'){
      ++tabs;
    }
    else if(c == '\n'){
      ++newline;
    }
  }
  printf("There were %d blanc spaces, %d tabs and %d newlines in the text.\n",blanc, tabs,newline);

}
