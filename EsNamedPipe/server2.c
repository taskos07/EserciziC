#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define FIFO_PATH "/tmp/echo_fifo2"

int main(void) {
    char messaggio[256];
    int fd;

    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }
    printf("[SERVER] In attesa del client...\n");
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) { perror("open"); unlink(FIFO_PATH); return 1; }

    while (1) {
        ssize_t n = read(fd, messaggio, sizeof(messaggio) - 1);
        if (n <= 0) break;
        messaggio[n] = '\0';
        if (strcmp(messaggio, "QUIT\n") == 0 || strcmp(messaggio, "QUIT") == 0) {
            printf("[SERVER] Client disconnesso. Ciao!\n");
            break;
        }
        printf("[SERVER] %s", messaggio);
    }
    close(fd);
    unlink(FIFO_PATH);
    return 0;
}