#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void do_nothing();
void handleSignals(int sig);

int main() {

    printf("PID: %d\n", getpid());

    signal(SIGINT, handleSignals);
    signal(SIGQUIT, handleSignals);
    signal(SIGALRM, do_nothing);
    unsigned sec=10;

    while (1) {
        alarm(sec);
        printf("Waiting...\n");
        pause();
    }
    return 0;
}

void do_nothing(){ ;}

void handleSignals(int sig) {
    if (sig == SIGQUIT) {
        printf("SIGQUIT lett megadva  -  %d\n", sig);
    }

    else if (sig == SIGINT) {
        printf("SIGINT lett megadva  -  %d\n", sig);
        signal(SIGINT, SIG_DFL);
    }
}