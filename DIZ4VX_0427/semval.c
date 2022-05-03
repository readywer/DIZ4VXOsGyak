#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456L


int main()
{
	int semid,rtn, semnum;

	union semun {
        	int              val; 
        	struct semid_ds *buf;   
        	unsigned short  *array;  
        	struct seminfo  *__buf;
    	} arg;

	semid = semget (SEMKEY, 0, 00666); //csak azonositunk, lehet 0
	if (semid < 0 ) {
		perror("Semget hiba\n");
		exit(0);
	} else printf("Semid: %d\n",semid);

	for(semnum=0; (rtn=semctl(semid, semnum , GETVAL, NULL))!=-1; semnum++){
		printf("%d. szemafor erteke: %d\n", semnum+1, rtn);
	}

}