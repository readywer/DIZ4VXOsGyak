#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456L 


int main()
{
	int semid,semnum,rtn;
	semid = semget (SEMKEY, 0, 00666);
	if (semid < 0 ) {
		perror(" Semget hiba\n");
		exit(0);
	} else printf("Semid: %d\n",semid);
	
	rtn = semctl(semid,0, IPC_RMID, NULL);
	printf("Megszuntetes visszateres: %d\n",rtn);

}