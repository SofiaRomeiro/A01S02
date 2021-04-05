#include <stdio.h>

typedef struct Stock {
    char name[10+1];
    float value;
    float percentage;
    float yield;
} Stock;

void readMe(Stock list[], int i) {
    int j, index = 0, value=0, name=0;
    char c;
    list[i].value = 0;
    list[i].percentage = 0;
    list[i].yield = 0;
    printf("name value percentage ?\n");
    
    for (j=0; (c=getchar()) != EOF && c!='\n'; j++) {

        if ((c!=' ' && !name)) {
            list[i].name[index++] = c;
        }
        else if (c==' ' && !value && !name) {
            list[i].name[index] = '\0';
            name = 1;
        }
        else if(c>='0' && c<='9' && !value && name) {
            list[i].value = list[i].value * 10 + (c-'0');
        }
        else if (!value && c==' ' && name){
            value = 1;
        }
        else if (value && c>='0' && c<='9') {
            list[i].percentage = list[i].percentage * 10 + (c-'0');
        }
    }
    list[i].yield = (list[i].value + (list[i].value * (0.01 * list[i].percentage)));
    
}


int main() {

    int n, maxVal, idMax;
    int i=0;
    Stock list[1000];

    printf("Number?\n");
    scanf("%d", &n);
    getchar();

    while (i < n) {       
        readMe(list, i);
        i++;
    }

    for (i=0; i<n; i++) {
        printf("name: %s ; value : %.2f ; percentage : %.2f ; yield : %.2f\n", list[i].name, list[i].value, list[i].percentage, list[i].yield);
    }   

    maxVal = list[0].yield;
    idMax=0;

    for(i=0; i<n; i++) {
        if (maxVal < list[i].yield) {
            maxVal = list[i].yield;
            idMax=i;
        }
    }

    printf("name: %s ; value : %.2f ; percentage : %.2f\n", list[idMax].name, list[idMax].value, list[idMax].percentage);

    return 0;
}