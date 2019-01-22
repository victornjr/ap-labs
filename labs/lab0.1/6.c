#include <stdio.h>

int main(){
  //Exercise 6
  printf("\nExercise 6:\n");
  printf("\nInput a character or press CTRL + D to continue\n");
  int c;
  c = (getchar() != EOF);
  printf("value of c: %d\n",c);
}
