#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#define SEMKEY 123456L 

void down (int semid, struct sembuf *sembuf)
{
	int rtn;
	sembuf->sem_num = 0;
	sembuf->sem_op = -1;
	sembuf->sem_flg = SEM_UNDO;
	rtn = semop(semid, sembuf, 1);
	if (rtn < 0) {perror("Down hiba\n"); exit(1);}
	else printf("%d Down\n", getpid());
	
}

void up (int semid, struct sembuf *sembuf)
{
	int rtn;
	sembuf->sem_num = 0;
	sembuf->sem_op = 1;
	sembuf->sem_flg = SEM_UNDO;
	rtn = semop(semid, sembuf, 1);
	if (rtn < 0) {perror("Up hiba\n"); exit(1);}
	else printf("%d Up\n", getpid());
}


int main()
{
	int semid, i;
	struct sembuf sembuf;

	semid = semget (SEMKEY, 0, 00666);
	if (semid < 0 ) {
		perror("Semget hiba\n");
		exit(0);
	} else printf("Semid: %d\n", semid);

	for (i=0;i<3;i++)
	{
		printf("Ciklus: %d --------------\n",i);
		down(semid, &sembuf);
		sleep(10);
		up(semid, &sembuf);

		
	}
}