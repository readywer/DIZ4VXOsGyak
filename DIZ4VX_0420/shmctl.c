#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 69905L

int main()
{
	int shmid;
	key_t key = SHMKEY;
	int size=512;
	int shmflg;
	int rtn;
	int cmd;
	struct shmid_ds shmid_ds; 

	shmflg = 0;
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	    perror("Shmget() hiba\n");
	    exit(-1);
	}

	do{
		printf("\nParancs:\n");
		printf("0. IPC_STAT (status)\n");
		printf("1. IPC_RMID (torles)\n> ");
		scanf("%d",&cmd);
	} while (cmd < 0 || cmd > 1);

	switch (cmd)
	{
	    case 0:
		rtn = shmctl(shmid, IPC_STAT, &shmid_ds);
		printf("Szegmens merete: %d\n",shmid_ds.shm_segsz);
		printf("Utolso shmop()-os processz pid-je: %d\n",shmid_ds.shm_lpid);
		break;
	    case 1:
		rtn = shmctl(shmid, IPC_RMID, NULL);
		printf("Szegmens torolve. Visszateresi ertek: %d\n", rtn);
	}

	exit(0);

}