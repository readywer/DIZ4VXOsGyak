#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char **argv){
	int pid;
    if (argc != 2){
        perror("No valid argument.\n");
        exit(1);
    }
    pid=atoi(argv[1]);
    kill(pid,SIGALRM);
	return 0;
}
