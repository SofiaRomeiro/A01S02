#include <stdio.h>

void displaymenu();

int main() {

	int quit = 0;
	char command;

	while ( !quit ) {
		displaymenu();
		command = getchar();

		switch (command) {
			case 't':
				/* New Task */
				newtask();
				break;

			case 'l':
				/* tasks list */
				taskslist();
				break;

			case 'n':
				/* time adder */
				timeadder();
				break;

			case 'u':
				/* add new user or new list of users */
				newuser();
				break;

			case 'm':
				/* move task from one activitie to another*/
				movetask();
				break;

			case 'd':
				/* lists all tasks in one activitie */
				alltaskslist();
				break;

			case 'a':
				/* add new activitie or list all activities */
				addactivitie();
				break;
			
			case 'q':
				quit = 1;
				break;
			
			default:
				printf("Error : Command Not Found");
				break;
		}
	}



	return 0;
}

void DisplayMenu() {
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