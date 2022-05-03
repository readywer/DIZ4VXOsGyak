#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456L 

int main()
{
	int semid, nsems, semnum, rtn;
	union semun {
        int              val;    
        struct semid_ds *buf;
        unsigned short  *array; 
        struct seminfo  *__buf; 
    } arg;

    printf ("Kerem a szemaforok szamat!\n");
	scanf("%d",&nsems);
	semid = semget (SEMKEY, nsems, 00666 | IPC_CREAT);
	if (semid < 0 ) {
		perror("Semget hiba\n");
		exit(0);
	} else printf("Semid: %d\n",semid);
	
	arg.val=0;
	for(semnum=0; semnum<nsems; semnum++){
		rtn = semctl(semid, semnum , SETVAL, arg);
		printf("Set  visszateres: %d , %d. szemafor erteke: %d\n", rtn, semnum+1, arg.val);
	}

}