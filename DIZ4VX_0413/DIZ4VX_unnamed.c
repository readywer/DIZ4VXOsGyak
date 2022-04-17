#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
     int pipefd[2];
     pid_t pid;
     char buf;
     char szoveg[32];
     int ret;

     if (pipe(pipefd) == -1) {
	   perror("Pipe error");
	   exit(-1);
     }

     printf("%d: olvaso descriptor: %d, iro descriptor: %d\n",getpid(),pipefd[0],pipefd[1]);

     pid = fork();
     if (pid == -1) {
	   perror("Fork error");
	   exit(-1);
     }

     if (pid != 0) {   
	   printf("%d: a szulo PID-je\n",getpid());
	   close(pipefd[1]);   

	   printf("%d: Varakozas a cso kiolvasasara\n%d: ",getpid(), getpid());
	   while (read(pipefd[0], &buf, 1) > 0) {
		 printf("%c",buf);
	   }
	   printf("\n%d: Lezarodott a cso\n",getpid());

	   close(pipefd[0]);

   	   exit(0);

     } else {
	   printf("%d: a gyerek PID-je\n",getpid());

   	   close(pipefd[0]);  

	   strcpy(szoveg,"Dobai Attila - DIZ4VX");  
	   printf("%d: Szoveg kuldese...: %s\n",getpid(),szoveg);
	   write(pipefd[1], szoveg, strlen(szoveg));

	   close(pipefd[1]);

	   exit(0);
     }
}