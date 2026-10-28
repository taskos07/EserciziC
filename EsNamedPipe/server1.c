#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define FIFO_PATH "/tmp/echo_fifo1"

int main(void) {
    char messaggio[256] = {0};
    int fd;

    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }
    printf("[SERVER] In attesa del client...\n");
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) { perror("open"); unlink(FIFO_PATH); return 1; }
    read(fd, messaggio, sizeof(messaggio) - 1);
    close(fd);
    printf("[SERVER] %s", messaggio);
    unlink(FIFO_PATH);
    return 0;
}
