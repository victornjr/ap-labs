#include <stdio.h>

int main(){
  //Exercise 4
  printf("\nExercise 4:\n");
  float fahr, celsius;
  int lower, upper, step;
  
  lower = -10;
  upper = 150;
  step = 20;
  celsius = lower;
  printf("Celsius to Fahrenheit table\nCelsius\tFahrenheit\n");
  while (celsius <= upper){
    fahr = (celsius * 9.0/5.0) + 32.0;
    printf("%3.0f\t%6.1f\n",celsius,fahr);
    celsius = celsius + step;
  }
}
