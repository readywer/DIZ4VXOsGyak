#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSGKEY 654321L

struct msgbuf1 {
	long mtype;
	char mtext[512];
} sendbuf;

int main()
{
	int msgid;		
	key_t key = MSGKEY;	
	int msgflg= 00666 | IPC_CREAT;		
	int ret, msgsz;
	char str[100];

	
	msgid = msgget(key, msgflg);
 	if (msgid == -1) {
                perror("Msgget hiba");
                exit(-1);
        }
	printf("Az msgid letrejott: %d, %x\n", msgid,msgid);

	sendbuf.mtype = 1;
	printf("Irja be az uzenetet (kilepeshez exit)!\n");
	scanf("%[^\n]", str);
	while(strcmp(str, "exit")){
		while(getchar()!='\n');
		strcpy(sendbuf.mtext, str);
		msgsz = strlen(sendbuf.mtext) + 1;
    	ret = msgsnd(msgid, &sendbuf, msgsz, 0);
    	printf("A msgsnd() visszaadott: %d\n", ret);
		printf("A kikuldott uzenet: %s\n", sendbuf.mtext);
		printf("Irja be az uzenetet (kilepeshez: exit)!\n");
		scanf("%[^\n]", str);
	}

	exit(0);
}