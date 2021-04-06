#include <stdio.h>

#define ALUNOS 10
#define DISCIPLINAS 5

/* cada aluno entre [0, 9]
   cada disciplina entre [0,4] */

void readMe(long valores[ALUNOS][DISCIPLINAS]) {

    int j;
    char c;
    int student=0, class=0, v=0, signal=1;
    int st_flag=0, cl_flag=0;

    printf("Aluno(0-9) Disciplina(0-4) Valor de entusiasmo(-100,100)?\n");

    for (j=0; (c=getchar())!= EOF && c!= '\n'; j++) {

        if (c>= '0' && c<='9' && !st_flag && !cl_flag) {
            student = (c-'0');
        }
        else if (c==' ' && !st_flag && !cl_flag) {
            st_flag=1;
        }
        else if (c>= '0' && c<='9' && st_flag && !cl_flag) {
            class = (c-'0');
        }
        else if (c==' ' && st_flag && !cl_flag) {
            cl_flag =1;
        }
        else if (c=='-' && st_flag && cl_flag) {
            signal = -1;
        }
        else if (c>= '0' && c<='9' && st_flag && cl_flag) {
            v = v * 10 + (c-'0');
        }     
    }
    v*= signal;
    valores[student][class] = v;
}


long score_aluno(int aluno, long valores[ALUNOS][DISCIPLINAS]) {

    long score=0;
    int i;

    for (i=0; i<DISCIPLINAS; i++) {
        score += valores[aluno][i];
    }    
    return score;
}

long score_disciplina(int disciplina, long valores[ALUNOS][DISCIPLINAS]) {

    long score=0;
    int i;

    for (i=0; i<DISCIPLINAS; i++) {
        score += valores[i][disciplina];
    }    
    return score;
}


int main () {

    long valores[ALUNOS][DISCIPLINAS];
    int n, i=0, j, k;
    int bestClass=0, bestStud=0; 
    long rateClass=0, rateStud=0;

    for (j=0; j<ALUNOS; j++) {
        for (k=0; k<DISCIPLINAS; k++) {
            valores[j][k] = 0;
        }
    }

    /* input: N A D V  */
    printf("Number of inputs?\n");
    scanf("%d", &n);
    getchar();

    while (i<n) {
        readMe(valores);
        i++;
    }    

    for (i=0; i < DISCIPLINAS; i++) {
        rateClass = score_disciplina(i, valores);
        printf("%ld\n", rateClass);
        if (rateClass>bestClass) {
            bestClass = i;
        }
    }

    for (i=0; i<ALUNOS; i++) {
        rateStud = score_aluno(i, valores);
        if (rateStud>bestStud) {
            bestStud = i;
        }
    }
    
    printf("disciplina mais popular : %d\naluno mais entusiastico : %d", bestClass, bestStud);

    return 0;
}

