#include <stdio.h>

int main(){
  int c, flag;
  flag = 0;
  while((c = getchar()) != EOF){
    if(c == '\b' || c == '\t' || c == '\n'){
      if(!flag){
        flag = 1;
        printf("\n");
      }
    }
    else{
      flag = 0;
      putchar(c);
    }
  }

}
