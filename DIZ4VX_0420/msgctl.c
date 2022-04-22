#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 654321L

int main()
{
	int msgid, msgflg,ret;
	key_t key = MSGKEY;

	msgflg = 00666 | IPC_CREAT;

	msgid = msgget(key, msgflg);

	ret = msgctl(msgid, IPC_RMID, NULL);
	printf ("Visszatert: %d\n", ret);

	exit(0);
}