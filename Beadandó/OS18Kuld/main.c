#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 10

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
    int a;
    int b;
    int c;
    int state=0;
    FILE *fp;
    fp=fopen("OS.txt","rt");
    if (!fp) {
        printf("Error: cannot open file."); return 0; }
    fscanf(fp, "%d %d %d", &a,&b,&c);
    printf("Az A oldal: %d \n A B oldal: %d \n A C oldal: %d \n",a,b,c);
    fclose(fp);
    if(a+b>c && a+c>b && b+c>a){
        state=1;
    }
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("progfile", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;

    //printf("Write Data : ");
    //fgets(message.mesg_text,MAX,stdin);

    message.a=a;
    message.b=b;
    message.c=c;
    message.state=state;

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);

    // display the message

    printf("A haromszog szerkesztheto:%d \n",state);
    /*
    FILE *fp2;
    fp2=fopen("OSOUT.txt","w");
    if (!fp2) {
        printf("Error: cannot open file."); return 0; }
    fprintf(fp2,"%d %d %d %d",a,b,c,state);
    fclose(fp2);
*/
    return 0;
}
