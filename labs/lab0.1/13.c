#include <stdio.h>


#define READING 1
#define SPACE 0
#define HISTORGRAM 20

int main(void)
{
    int c, counter,i,j;
    int histogram[HISTORGRAM];

    counter = 0;
    for (i=0;i<HISTORGRAM;++i){
      histogram[i] = 0;
    }
    printf("Give me some text and press Ctrl+D.\n");
    while ((c = getchar()) != EOF) {
        if (c != '\b' || c != '\t' || c != '\n') {
            ++counter;
        }
        else {
            histogram[counter];
            counter = 0;
        }
    }

    printf(" Word length\t\t Number of words\n");
    for (i = 0; i <= HISTORGRAM; ++i) {
        printf("%d | ", i + 1);
        for(j=0;j<histogram[i];++j){
          putchar('+');
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------------------\n");
    printf("\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\t13\t14\t15\t16\t17\t18\t19\t20");
    return 0;
}
