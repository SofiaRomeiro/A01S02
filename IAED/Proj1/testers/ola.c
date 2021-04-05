#include <string.h>
#include <stdio.h>


int adder(int num, char op) {
    if (op=='y') {
        num++;
        return num;
    }
    else if (op=='n') {
        return num;
    }
    return 0;
}



int main() {
    int i=0, res, quit = 0;
    char c;

    while (!quit) {

        c = getchar();

        switch(c) {
            case 'a':
                res = adder(i, 'y');
                printf("res a : %d\n", res);
                break;
            case 'b':
                res = adder(i,'n');
                printf("res b : %d\n", res);
                break;  
            case 'q':
                quit = 1;
                break;          
        }
    }    

    return 0;
}





