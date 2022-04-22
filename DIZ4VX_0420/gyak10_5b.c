#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHMKEY 69922L

int main()
{
	int shmid;
	key_t key = SHMKEY;
	int size=512;
	int shmflg, rtn;
	char c; //valaszto
	struct shmid_ds shmid_ds;
	struct vmi {
		int  hossz;
		char szoveg[size-sizeof(int)];
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

	do{
		printf("1 - Kiolvasas es beiras\n2 - Statusz lekerese\n3 - Szegmens megszuntetese es kilepes\n");
		scanf("%c", &c);
		while(getchar()!='\n');
		switch (c)
		{
	    case '1':
			if (strlen(segm->szoveg) > 0) 
				printf("Regi szoveg: %s (%d hosszon)\n",segm->szoveg,segm->hossz);
 
			printf("Uj szoveg: \n");
			scanf("%[^\n]", segm->szoveg);
			while(getchar()!='\n');
			printf("Az uj szoveg: %s\n",segm->szoveg);
			segm->hossz=strlen(segm->szoveg);
			break;
	    case '2':
			rtn = shmctl(shmid, IPC_STAT, &shmid_ds);
			printf("Szegmens merete: %d\n",shmid_ds.shm_segsz);
			printf("Utolso shmop()-os processz pid-je: %d\n",shmid_ds.shm_lpid);
			break;
		case '3' : break;
		default:
			printf("Ismeretlen karakter\n");
		}
	} while(c!='3');

	
	shmdt(segm);
	rtn = shmctl(shmid, IPC_RMID, NULL);
	printf("Szegmens torolve. Visszateresi ertek: %d\n", rtn);

	exit(0);
}