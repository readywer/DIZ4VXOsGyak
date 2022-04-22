#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHMKEY 69905L

int main()
{
	int shmid;
	key_t key = SHMKEY;
	int size=512;
	int shmflg;
	struct vmi {
		int  hossz;
		char szoveg[size-sizeof(int)]; /* az egesz merete 512, ezert a hossz valtozot levonjuk a tombbol */
	} *segm;
	

	shmflg = 0;	

	if ((shmid=shmget(key, size, shmflg)) < 0) {
	    perror("Shmget hiba\n");
	    exit(-1);
	}


	shmflg = 00666 | SHM_RND;
	segm = (struct vmi *)shmat(shmid, NULL, shmflg);

	if (segm == (void *)-1) {
		perror("Shmat hiba\n");
		exit(-1);
	}

	if (strlen(segm->szoveg) > 0) 
		printf("Regi szoveg: %s (%d hosszon)\n",segm->szoveg,segm->hossz);
 
	printf("Uj szoveg: \n");
	scanf("%[^\n]", segm->szoveg);
	printf("Az uj szoveg: %s\n",segm->szoveg);
	segm->hossz=strlen(segm->szoveg);
	
	shmdt(segm);

	exit(0);
}