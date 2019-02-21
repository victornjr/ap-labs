#include <stdio.h>

void readDocument(int c);
void getEnd();
void avoidDel(int c);

int main(int argc, char const *argv[]) {
  int character;
  while((character = getchar()) != EOF){
    readDocument(character);
  }
  return 0;
}

void readDocument(int c){
  int nextChar;

  if(c == '/'){
    nextChar = getchar();
    if(nextChar == '*'){
      getEnd();
    }
    else if(nextChar == '/'){
      putchar(c);
      readDocument(nextChar);
    }
    else{
      putchar(c);
      putchar(nextChar);
    }
  }
  else if(c == '"' || c == '\''){
    avoidDel(c);
  }
  else{
    putchar(c);
  }
}

void avoidDel(int startComment){
  int actualChar;
  putchar(startComment);

  while((actualChar = getchar()) != startComment){
    putchar(actualChar);
    if(actualChar == '\\'){
      putchar(getchar());
    }
  }
}

void getEnd(){
  int diag, multSign;

  multSign = getchar();
  diag= getchar();

  while(diag != '/' || multSign != '*'){
    multSign = diag;
    diag = getchar();
  }
}
