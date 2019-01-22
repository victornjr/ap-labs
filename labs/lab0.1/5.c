#include <stdio.h>

int main(){
  //Exercise 5
  float fahr;
  printf("\nExercise 5:\n");
  printf("Fahrenheit to Celsius table (backwards)\nFahrenheit\tCelsius\n");
  for(fahr = 300; fahr >=0; fahr = fahr - 20)
    printf("%3.0f\t%6.1f\n",fahr,(5.0/9.0) * (fahr-32.0));
}
