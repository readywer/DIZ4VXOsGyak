
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 69922L

int main()
{
	int shmid;
	key_t key = SHMKEY;
	int size=512;
	int shmflg;	

	shmflg = 0;
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	   shmflg = 00666 | IPC_CREAT;
	   if ((shmid=shmget(key, size, shmflg)) < 0) {
	      perror("Shmget() hiba\n");
	      exit(-1);
	   }
	   printf("A szegmens elkeszult\n");
	} else printf("A szegmens mar letezik\n");

	printf("\nAz shm szegmens azonositoja %d: \n", shmid);

	exit(0);
}
