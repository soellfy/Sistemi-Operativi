#include <stdio.h>
#include <stdlib.h>

int main(void)	{

	int *variable,
	     n;
	
	n = 1000;

	while(1)
		variable = (int *)malloc(n * sizeof(int));

	return(0);
}
