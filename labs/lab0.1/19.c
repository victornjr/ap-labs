#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
void reverse(char s[]);

int main(void)
{
    char line[MAXLINE]; /* current input line */

    while (get_line(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s\n", line);
    }

    return 0;
}

int getLine(char s[], int lim)
{
    int c, i;

    for (i = 0;i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void reverse(char s[]){
  
}
