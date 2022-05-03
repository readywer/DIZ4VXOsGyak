#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456L  



int main()
{
	int semid,semnum,rtn;
	struct sembuf sembuf;

	semid = semget (SEMKEY, 0, 00666);
	if (semid < 0 ) {
		perror(" Semget hiba\n");
		exit(0);
	} else printf("Semid: %d\n",semid);
	
	for(semnum=0; (rtn=semctl(semid, semnum , GETVAL, NULL))!=-1; semnum++){
		sembuf.sem_num = semnum;
		sembuf.sem_op = 1;
		sembuf.sem_flg = 0666;
		rtn = semop(semid, &sembuf, 1);
		printf("Semop visszateres: %d\n",rtn);
	}

}