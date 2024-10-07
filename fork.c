#include <stdio.h>		/* la solita librerie input/output */
#include <sys/types.h> 		/* serve per il pid_t che viene ritornato da fork */
#include <stdlib.h>		/* primitive di tipi exit() */
#include <unistd.h>		/* librerie unix standard che contiene la sys-call fork */

/* inizio codice test per la fork */

int main(void)	{
	/* dichiarasione delle variabili utili per ospitare il pid del processo figlio */
	pid_t pid;

	printf("Io sono il rpocesso originale\n");
	printf("Ho pid = %d\n", getpid());			/* getpid = get pid */
	printf("Mio padre ha pid = %d\n", getppid());		/* getppid = get parent pid */
	
	/* creo un processo figlio che sarà copia identica di me stesso */

	pid = fork();		/* sys-call che duplica il processo in memoria */

	/* ora ho due processi distinti che eseguono a partire da questo punto */

	/* ora voglio distinguere padre e figlio per far fare loro due cose diverse */

	if(pid < 0){
		/* errore nell'esecuzione di "fork()" */
		fprintf(stderr, "Errore nell'invocazione della fork\n");		/* "stderr" serve per distinguere l'output normale dall'output dell'errore */
		exit(1);
	}
	else if(pid == 0){		/* codice che viene eseguito solo dal figio */
		printf("Sono il figlio con pid = %d\n", getpid());
		printf("Mio padre ha pid = %d\n", getppid());
	}
	else{				/* codice eseguito solo dal padre */
		printf("Sono il padre e mio figlio ha pid = %d\n", pid);
	}

	/* questo codice verrà eseguito da entrambi i processi */
	
	printf("Test terminato da parte del processo con pid = %d\n", getpid());
	
	exit(0);	/* termina l'esecuzione senza problemi */
}	
