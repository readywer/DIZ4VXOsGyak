#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(){
	char command[20];
	int status;

	printf("Adja meg a parancsot: ");
	scanf("%s", command);
	do{
		status=system(command);
		if(WIFEXITED(status)) printf("Normalis befejezodes, visszaadott ertek: %d\n", WEXITSTATUS(status));
		printf("Adja meg a parancsot (kilepeshez q/Q): ");
		scanf("%s", command);
	} while(strcmp(command, "q") !=0 && strcmp(command, "Q") !=0);
	exit(0);
}
 
