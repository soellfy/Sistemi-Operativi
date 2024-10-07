#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>		/* per far si che il padre attenda per la terminazione del figlio e possa ricevere il valore di ritorno */

/* inziio test */

int main(void)	{

	pid_t pid;
	int valore = 0;		/* variabile dove appoggiare il valore di ritorno del figlio */

	pid = fork();		/* creo un nuovo processo che sarà copia di me stesso */

	if(pid < 0){
		fprintf(stderr, "Errore invocazione fork\n");
		exit(1);
	}
	else if(pid == 0){	/* figlio che divernterà u processo nuovo a partire da un programma installato */
		/* invoca la sys-call "exec" con argomento un esefuibile installato */
		execl("/usr/bin/firefox", "firefox", NULL);		/* primo parametro = , secondo parametro è il nome dell'eseguibile,
								 * il terzo paramentro sono dei parametri
								 * aggiuntivi, il quarto è NULL perché non
								 * abbiamo altri paramentri da specificare */

		/* qua sotto è impossibile eseguire perché il processo viene totalmente sovrascritto dall'eseguibile indicato nella "exec" */
	}	
	else{			/* codice del padre che attenderà per la terminazione del figlio e leggerà il valore di ritorno */
		/* io padre attendo per la terminazione del figlio */
		printf("Sono il processo padre e mio figlio ha pid = %d\n", pid);
		printf("Mi metto inattesa per la sua terminazione\n");
		wait(&valore);		/* fa entrare il processo in una coda d'attesa finché non riceve un segnale del figlio e al risveglio,
					 * nella variabile "valore" ci sarà il codice di ritorno del processo figlio */

		/* devo shiftare la variabile a destra di 8 posizioni per spostare il valore di ritorno
		 * negli 8 bit meno significativi ed eliminare il segnale di terminazione 
		 * la variabile ha il formato " valore ritorno|segnale terminazione " */

		valore = valore >> 8;

		/* ora posso stampare la variabile */

		printf("Mio figlio termina con valore %d\n", valore);
	}
	exit(0);
}
