/*
This code receives a txt file when running and prints on the console all the words in order
and with a couple of numbers that show the lines in which you can find this word.

This code was made by using the next repo as reference:
https://github.com/wreckage/k-r/blob/master/ch6/6-03.c
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define WORDSIZE 100
#define BUFFER 100
#define SIZE_OF_NOISE (sizeof(noiseWords) / sizeof(*noiseWords))

int nlines = 0;
char buf[BUFFER];
int bufp = 0;
FILE *fptr;
char *noiseWords[] = {"an","and","are","as","at","be","but","by","for","from","if","in",
                      "is","it","no","not","of","on","or","so","that","the","this","to","was","were","with","yes"};


int formWord(char *, int);
int isAWord(char *word);
int getNextChar();
void goBackChar(int c);

struct wordNode *addNode(struct wordNode *, char *);
void printWords(struct wordNode *);
char *wordMAllocation(char *);
int locateWord(char *, char **, int);

struct wordNode {
    char *word;
    int numberOfLine[10000];
    int countLine;
    struct wordNode *leftNode;
    struct wordNode *rightNode;
};

int main(int argc, char **argv)
{
    struct wordNode *newWord = NULL;
    char word[WORDSIZE];

    fptr = fopen(argv[1], "r");
    while (formWord(word, WORDSIZE) != EOF){
      if (isAWord(word)){
        newWord = addNode(newWord, word);
      }
    }

    printf("   Words\tLines\n");
    printf("===========================\n");
    printWords(newWord);
    fclose(fptr);
    return 0;
}

int isAWord(char *word){
  int resultBinSearch = (locateWord(word, noiseWords, SIZE_OF_NOISE)) == -1;
  if(resultBinSearch && strlen(word)>1){
    return 1;
  }
  return 0;
}

char *wordMAllocation(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int formWord(char *word, int lim){

    int c;
    char *w = word;

    while (isspace(c = getNextChar())){
        if (c == '\n'){
            nlines++;
        }
    }

    if (c != EOF) {
        *w++ = c;
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++){
        if (!isalnum(*w = getNextChar())) {
            goBackChar(*w);
            break;
        }
    }

    *w = '\0';
    return *word;
}

int getNextChar(){
    return (bufp > 0) ? buf[--bufp] : tolower(getc(fptr));
}

void goBackChar(int c){
    if (bufp >= BUFFER){
      printf("Only one character at a time\n");
    }
    else{
        buf[bufp++] = c;
    }
}

struct wordNode *addNode(struct wordNode *p, char *w){
    int cond;

    if (p == NULL) {
        p = (struct wordNode *)malloc(sizeof(struct wordNode));
        p->word = wordMAllocation(w);
        p->countLine = 0;
        p->numberOfLine[p->countLine++] = nlines;
        p->leftNode = p->rightNode = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0){
      p->numberOfLine[p->countLine++] = nlines;
    }
    else if (cond < 0){
      p->leftNode = addNode(p->leftNode, w);
    }
    else{
      p->rightNode = addNode(p->rightNode, w);
    }
    return p;
}

void printWords(struct wordNode *p){
    int i;
    if (p != NULL) {
        printWords(p->leftNode);
        printf("%10s\t", p->word);
        for (i = 0; i < p->countLine-1; i++){
          printf("%d,", p->numberOfLine[i] + 1);
        }
        printf("%d\n",p->numberOfLine[p->countLine-1] + 1);
        printWords(p->rightNode);
    }
}

int locateWord(char *word, char *list[], int n){
    int cond;
    int low, mid, high;
    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low+high)/2;
        if ((cond = strcmp(word, list[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
