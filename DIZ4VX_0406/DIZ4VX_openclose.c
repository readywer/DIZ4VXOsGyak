#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>



int main(){
	int fd, bytes;
    char buf[64] = "Dobai Attila, mernokinformatikus, DIZ4VX";

    fd = open("DIZ4VX.txt", O_RDWR);
    if (fd == -1) {
        perror("Open error\n");
        exit(-1);
    }

    bytes = read(fd, buf, 64);
    printf("Called read, %d bytes were read: %s\n", bytes, buf);

    lseek(fd, 0, SEEK_SET);
    int result = lseek(fd, 0, SEEK_SET);
    printf("lseek() : %d is the new file cursor.\n", result);

    strcpy(buf, "DIZ4VX\n");

    bytes=write(fd, buf, strlen(buf));
    printf("Called write, %d bytes were written.\n", bytes);

    bytes = write(STDOUT_FILENO, buf, strlen(buf));
    printf("Called write, %d bytes were written.\n", bytes);


    close(fd);
    return 0;

}