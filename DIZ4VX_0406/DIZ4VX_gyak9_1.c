#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //pid_t
#include <signal.h> //signal()
#include <unistd.h> //pause()

void signalHandler(int);

int main(){
	pid_t pid = getpid();
	printf("PID: %d\n", (int)pid);
	printf("Signal kezelo atvetele: %d\n", signal(SIGALRM, signalHandler));
	printf("Waiting...\n");
	pause();
	printf("Not blocked anymore. Terminating...\n");

	return 0;
}

void signalHandler(int sig){
	printf("YD11NL\n");
}