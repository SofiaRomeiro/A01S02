#include <stdio.h>

void DisplayMenu();

int main() {

	int quit = 0;
	char command;

	while ( !quit ) {
		DisplayMenu();
		command = getchar();

		switch (command) {
			case 't':
				/* code */
				break;

			case 'l':
				/* code */
				break;

			case 'n':
				/* code */
				break;

			case 'u':
				/* code */
				break;

			case 'm':
				/* code */
				break;

			case 'd':
				/* code */
				break;

			case 'a':
				/* code */
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