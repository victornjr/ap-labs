#include <stdio.h>

#define MAXLINE 1000
#define BIGGEST 80
int getLine(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    printf("Please input a text with a lot of lines, the output wont show blanc lines.\n Press CTRL+D when done.");
    while ((len = getLine(line, MAXLINE)) > 0){}
        if (len > 0 && (line[0] == '\n' || line[0] == '\b' || line[0] == '\t'))  {
            continue;
        }
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
