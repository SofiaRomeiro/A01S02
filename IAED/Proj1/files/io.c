#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./io.h"
#include "./define.h"
#include "./usecases.h"

/* Command Read Functions */

void displayMenu() {
	printf("\nComando \t Acao\n");
	printf("\n");	
	printf(" t \t Adiciona uma nova tarefa ao sistema\n");
	printf(" l \t Lista as tarefas\n");
	printf(" n \t Avanca o tempo do sistema\n");
	printf(" u \t Adiciona um utilizador ou lista todos os utilizadores\n");
	printf(" m \t Move uma tarefa de uma atividade para outra\n");
	printf(" d \t Lista todas as tarefas que estejam numa dada atividade\n");
	printf(" a \t Adiciona uma atividade ou lista todas as atividades\n");
	printf(" q \t Termina o programa\n");
	printf("\n");
}

int readT(char newdescription[]) {
	/* t <duration> <description> */

	int i, duration=0, index=0;
	int start_description=0;
	int start_num=0, end_num=0;
	char c;
	
	for (i=0; (c=getchar()) != EOF && c != '\n'; i++) {		
		/* espaco antes do numero */
		if (c == ' ' && !start_num && !start_description) {
			continue;
		}
		/* numero */
		else if (c>='0' && c <= '9' && !end_num) {
			start_num = 1;
			duration = duration * 10 + (c - '0');
		}
		/* espaco */
		else if (c == ' ' && start_num && !start_description) {
			end_num = 1;	
		}
		/* descricao */		
		else if (end_num && index < DESCFORTASK) {
			newdescription[index++] = c;
			start_description = 1;
		}		
	}
	newdescription[index] = '\0';

	return duration;
}

int readL(int ids[]) {
	char c;
	int id=0, i, idpos=0, reading=0, exist_id=0;
	/* conta espacos para ver se se inseriu ids */
	
	for (i=0; (c=getchar()) != EOF && c != '\n'; i++) {

		/* se c for numero, continua a ler e construir numero ate encontrar espaco */
		if (c>= '0' && c<= '9') {
			id = id * 10 + (c - '0');
			reading = 1;
			exist_id = 1;
		}

		/* se c for ' ' -> passa a frente, adiciona o id ao array e da clean no id*/
		else if (reading && c == ' ') {
			ids[idpos++] = id;
			id = 0;	
			reading = 0;
		}

		else if (!reading && c == ' '){			
			continue;
		}			
	}
	ids[idpos++] = id;
	return  exist_id ? idpos : 0;
}

int readN() {
	int num = 0, reading = 0, end = 0, failed = 0;
	char c;
	while ((c = getchar()) != EOF && c != '\n') {
		
		/* caracteres inseridos nao validos */
		if ((c > '0' && c < '9') && c != ' ' && c == '-') {
			printf("Please insert a positive number\n");
			failed = 1;
		}

		/* comeca a ler o numero */
		else if (c >= '0' && c <= '9' && !end) {
			num = num * 10 + (c - '0');
			reading = 1;
		}

		/* ainda nao encontrou nenhum numero e nao esta a ler */
		else if (c == ' ' && !reading && !end){
			continue;
		}

		/* ja encontrou o numero e ja leu 1 numero */
		else if (c == ' ') {
			reading = 0;
			end = 1;
		}
		
	}
	return !failed ? num : -1;
}

int readU(char newuser[]) {
	int i, u= 0;
	int start_reading=0, end_reading=0, exist_user=0;
	char c;	
	
	for (i=0; i < USERNAME && ((c=getchar()) != EOF) && c != '\n'; i++) {
		if (c==' ' && !start_reading) {
			continue;
		}
		else if (c != ' ' && !end_reading) {
			newuser[u++] = c;
			start_reading = 1;
			exist_user=1;
		}
		else if (c == ' ' && start_reading) {
			end_reading = 1;
			continue;
		}
	}	
	newuser[u] = '\0';
	return exist_user ? 1 : 0;
}

int readM(char newuser[], char newactivity[]) {
	/* m <id> <user> <activity> */

	int num=0, u=0, a=0, reading=0, a_found=0;	
	int num_read=0;
	int user_read=0;
	int activitie_read=0;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {		
		/* espaco antes do numero */
		if (c == ' ' && !num_read && !user_read && !activitie_read && !reading) {
			continue;
		}
		/* encontrei numero */
		else if (c>='0' && c <= '9' && !num_read && !user_read && !activitie_read) {
			reading = 1;
			num = num * 10 + (c - '0');
		}
		/* a ler numero e encontro espaco */
		else if (c == ' ' && reading && !num_read && !user_read && !activitie_read) {
			reading = 0;
			num_read = 1;	
		}
		/* encontro user */
		else if (c != ' ' && num_read && !user_read && u < USERNAME && !activitie_read) {
			reading = 1;
			newuser[u++] = c;
		}
		/* a ler user e encontro espaco */
		else if (c == ' ' && num_read && !activitie_read && !a_found) {
			reading = 0;
			user_read = 1;
		}
		/* encontro atividade */		
		else if (num_read && user_read && a < DESCFORACTIV) {
			newactivity[a++] = c;
			reading = 1;
			a_found = 1;
		}		
	}
	newuser[u] = '\0';
	newactivity[a] = '\0';

	return num;
}

void readD(char newactivity[]) {

	int a=0,a_found=0;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {	

		/* encontro espaco */
		if (c == ' ' && !a_found) {
			continue;
		}
		/* encontro atividade */		
		else if (a < DESCFORACTIV) {
			newactivity[a++] = c;
			a_found = 1;
		}		
	}
	newactivity[a] = '\0';
}

int readA(char newactivity[]) {

	int a=0,a_found=0, exist_activitie=0;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {	

		/* encontro espaco */
		if (c == ' ' && !a_found) {
			continue;
		}
		/* encontro atividade */		
		else if (a < DESCFORACTIV) {
			if (c>= 'a' && c <= 'z') {
				newactivity[a++] = (c - ('a' - 'A'));
			}
			else if ((c>= 'A' && c <= 'Z') || c == ' ' || c == '\t') {
				newactivity[a++] = c;
			}
			exist_activitie=1;
			a_found = 1;
		}		
	}
	newactivity[a] = '\0';

	return exist_activitie ? 1 : 0;
}
