#include <stdio.h>
#include <stdlib.h>

/* max value for an identifier = 10000 */
#define IDENTIFIER 10000
/* max username len =  */
#define USERNAME 20
/* max tasks' description len = 50 */
#define DESCFORTASK 50
/* max activities' description len = 20 */
#define DESCFORACTIV 20

/* general functions */
void displayMenu();

/* command reader functions */
int readT(char description[]);
int readL(int ids[]);
int readN();
int readU(char user[]);
int readM(char user[], char activitie[]);
void readD(char activitie[]);
int readA(char activitie[]);

/* type reader functions */
void readSentence(char sentence[], int maxsize);
void readListId(int list[], int maxsize);
int readNum();


/* Execute functions */
void newTask();
void tasksList(int ids[], int id_counter);
void timeAdder(int duration);
void newUser(char user[], int user_exist);
void moveTask(int id, char user[], char activitie[]);
void allTasksList(char activities[]);
void addActivitie(char activitie[], int activ_exist);




int main() {
	/* '+1' means the maximum size plus '\0' */
	int quit = 0, duration = 0, id=0, id_counter=0, user_exist=0, activ_exist=0;
	char command;
	char description[DESCFORTASK + 1];
	int ids[IDENTIFIER+2];
	char user[USERNAME+1];
	char activitie[DESCFORACTIV+1];
	
	while ( !quit ) {
		displayMenu();
		command = getchar();

		switch (command) {
			case 't':
				/* t <duration> <description> */
				duration = readT(description);
				newTask(duration, description);
				break;

			case 'l':
				/* l [<id> <id> ...] */
				id_counter = readL(ids);
				tasksList(ids, id_counter);
				break;

			case 'n':
				/*  n <duração> */
				duration = readN();
				timeAdder(duration);
				break;

			case 'u':
				/*  u [<utilizador>] */
				/* devolve 1 se existir user, 0 se nao existir */
				user_exist = readU(user);
				newUser(user, user_exist);
				break;

			case 'm':
				/* m <id> <utilizador> <atividade> */
				id = readM(user, activitie);
				moveTask(id, user, activitie);
				break;

			case 'd':
				/* d <atividade> */
				readD(activitie);
				allTasksList(activitie);
				break;

			case 'a':
				/* a [<atividade>]*/
				activ_exist = readA(activitie);
				addActivitie(activitie, activ_exist);
				break;
			
			case 'q':
				quit = 1;
				break;
			
			default:
				printf("Error : Command Not Found");
				exit(EXIT_FAILURE);
				break;
		}
	}
	return 0;
}

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

/* Command Read Functions */

int readT(char description[]) {
	/* t <duration> <description> */

	int i, num=0, index=0;
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
			num = num * 10 + (c - '0');
		}
		/* espaco */
		else if (c == ' ' && start_num && !start_description) {
			end_num = 1;	
		}
		/* descricao */		
		else if (end_num && index < DESCFORTASK) {
			description[index++] = c;
			start_description = 1;
		}		
	}
	description[index] = '\0';

	return num;
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

int readU(char user[]) {
	int i, u= 0;
	int start_reading=0, end_reading=0, exist_user=0;
	char c;	
	
	for (i=0; i < USERNAME && ((c=getchar()) != EOF) && c != '\n'; i++) {
		if (c==' ' && !start_reading) {
			continue;
		}
		else if (c != ' ' && !end_reading) {
			user[u++] = c;
			start_reading = 1;
			exist_user=1;
		}
		else if (c == ' ' && start_reading) {
			end_reading = 1;
			continue;
		}
	}	
	user[u] = '\0';
	return exist_user ? 1 : 0;
}

int readM(char user[], char activitie[]) {
	/* m <id> <user> <activitie> */

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
			user[u++] = c;
		}
		/* a ler user e encontro espaco */
		else if (c == ' ' && num_read && !activitie_read && !a_found) {
			reading = 0;
			user_read = 1;
		}
		/* encontro atividade */		
		else if (num_read && user_read && a < DESCFORACTIV) {
			activitie[a++] = c;
			reading = 1;
			a_found = 1;
		}		
	}
	user[u] = '\0';
	activitie[a] = '\0';

	return num;
}

void readD(char activitie[]) {

	int a=0,a_found=0;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {	

		/* encontro espaco */
		if (c == ' ' && !a_found) {
			continue;
		}
		/* encontro atividade */		
		else if (a < DESCFORACTIV) {
			activitie[a++] = c;
			a_found = 1;
		}		
	}
	activitie[a] = '\0';
}

int readA(char activitie[]) {

	int a=0,a_found=0, exist_activitie=0;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {	

		/* encontro espaco */
		if (c == ' ' && !a_found) {
			continue;
		}
		/* encontro atividade */		
		else if (a < DESCFORACTIV) {
			activitie[a++] = c;
			exist_activitie=1;
			a_found = 1;
		}		
	}
	activitie[a] = '\0';

	return exist_activitie ? 1 : 0;



}
/* read-type functions */

int readNum() {
	int num = 0, reading = 0;
	char c;
	while ((c = getchar()) != EOF && c != '\n' && (c != ' ' || reading == 0)) {
		if (c >= '0' && c <= '9') {
			num = num * 10 + (c - '0');
			reading = 1;
		}

		else if (c == ' ' && !reading){
			continue;
		}

		else {
			printf("Please insert a positive number\n");
			exit(EXIT_FAILURE);
		}
	}
	return num;
}

void readSentence(char sentence[], int maxsize) {
	int i, j,n = 0;
	int reading=0;
	char temporary[DESCFORTASK];
	char c;	
	
	for(i=0; i < (maxsize) && (c=getchar()) != EOF && c != '\n'; i++) {
		temporary[i] = c;		
	}

	for (j=0; j < i; j++){
		if (temporary[j] == ' ' && !reading) {
			continue;
		}
		else {
			sentence[n++] = temporary[j];
			reading = 1;
		}
	}
	sentence[n] = '\0';

}

void readListId(int list[], int maxsize) {
	char c;
	int id=0, i, idpos=0, reading=0;
	
	for (i=0; i < maxsize && (c=getchar()) != EOF && c != '\n'; i++) {
		/* se c for ' ' -> passa a frente, adiciona o id ao array e da clean no id*/
		if (c>= '0' && c<= '9') {
			id = id * 10 + (c - '0');
			reading = 1;
		}

		else if ((reading==1) && c == ' ') {
			list[idpos++] = id;
			id = 0;	
			reading = 0;
		}
		else if ((reading==0) && c == ' '){
			reading = 0;			
			continue;
		}			
	}
	list[idpos] = id;
	list[idpos+1] = '\0';	
}

void newTask(int duration, char sentence[]) {

	printf("duration : %d\n", duration);
	printf("sentence: %s\n", sentence);
}

void tasksList(int ids[], int id_counter) {

	int i;
	for (i=0; i < id_counter; i++) {
		printf("id : %d\n", ids[i]);
	}
	printf("number of id's : %d\n", id_counter);
}

void timeAdder(int duration) {
	printf("duration : %d\n", duration);
}

void newUser(char user[], int user_exist) {
	printf("username : %s\n", user);
	printf("%s\n", user_exist ? "user exist" : "user does not exist");
}

void moveTask(int id, char user[], char activitie[]) {
	printf("id :%d\nuser: %s\nactivitie: %s\n", id, user, activitie);
}

void allTasksList(char activitie[]) {
	printf("activitie : %s", activitie);
}

void addActivitie(char activitie[], int activ_exist) {
	printf("activitie : %s\n", activitie);
	printf("%s\n", activ_exist ? "activitie exist" : "activitie does not exist");
}