#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "/tmp/echo_fifo1"

int main(void) {
    char messaggio[256];
    int fd;

    printf("Scrivi una riga: ");
    if (fgets(messaggio, sizeof(messaggio), stdin) == NULL) return 1;

    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) { perror("open"); return 1; }
    write(fd, messaggio, strlen(messaggio) + 1);
    close(fd);
    return 0;
}
