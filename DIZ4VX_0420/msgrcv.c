#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 654321L

struct msgbuf1 {
	long mtype;
	char mtext[512];
} recvbuf;

struct msqid_ds ds;

int main()
{
	int msgid;		
	key_t key = MSGKEY;
	int mtype, msgflg;
	int ret, msgsz;

	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(key, msgflg);
 	if (msgid == -1) {
                perror("Msgget hiba");
                exit(-1);
        }
	printf("Az msgid: %d\n",msgid);

	msgsz = 20;
	mtype = 0;

	ret = msgctl(msgid, IPC_STAT, &ds);
	printf("Az uzenetek szama az uzenetsorban: %ld\n", ds.msg_qnum);

	while (ds.msg_qnum) {	
		ret = msgrcv(msgid,&recvbuf, msgsz, mtype, msgflg);
		printf("msgrcv() visszaadta: %d, a kapott uzenet: %s\n",ret, recvbuf.mtext);
		ret = msgctl(msgid, IPC_STAT, &ds);
	}

	exit(0);
}