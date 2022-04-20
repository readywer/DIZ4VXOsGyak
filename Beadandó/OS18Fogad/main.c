#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
struct mesg_buffer {
    long mesg_type;
    int a;
    int b;
    int c;
    int state;
} message;

int main()
{
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("progfile", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);


    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    int a=message.a;
    int b=message.b;
    int c=message.c;
    int state=message.state;

    // display the message
    printf("Data Received is : %d %d %d %d\n",a,b,c,state);



    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

        FILE *fp2;
    fp2=fopen("OSOUT.txt","w");
    if (!fp2) {
        printf("Error: cannot open file."); return 0; }
    fprintf(fp2,"%d %d %d %d",a,b,c,state);
    fclose(fp2);

    return 0;
}
