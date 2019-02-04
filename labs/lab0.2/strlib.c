int strlen(char *str){
  if(str == '\0'){
    return 0;
  }

  int counter = 0;
  while(*str){
    counter++;
    str++;
  }

  return counter;
}

char* stradd(char *origin, char *addition){
  char *cat = (char *)malloc(strlen(origin) + strlen(addition) + 1);
  char *temp;
  temp = cat;

  while(*origin){
    *temp = *origin;
    temp++;
    origin++;
  }
  while(*addition){
    *temp = *addition;
    temp++;
    addition++;
  }
  *temp = '\0';

  return cat;
}

int strfind(char *origin, char *substr){
  char *tempO;
  char *tempS;
  tempO = origin;
  tempS = substr;

  if(substr == '\0'){
    return 1;
  }

  while(*tempO){
    if(*tempO == *tempS){
      tempS++;
      if(*tempS == '\0'){
        return 1;
      }
    }
    else{
      tempS = substr;
    }
    tempO++;
  }

  return 0;
}
