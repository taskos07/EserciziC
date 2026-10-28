#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define FIFO_PATH "/tmp/echo_fifo2"

int main(void) {
    char messaggio[256];
    int fd;

    signal(SIGPIPE, SIG_IGN);
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) { perror("open: avvia prima il server"); return 1; }

    while (1) {
        printf("Messaggio (QUIT per terminare): ");
        if (fgets(messaggio, sizeof(messaggio), stdin) == NULL) break;
        if (write(fd, messaggio, strlen(messaggio)) == -1) {
            perror("write: server non disponibile");
            close(fd);
            return 1;
        }
        if (strcmp(messaggio, "QUIT\n") == 0 || strcmp(messaggio, "QUIT") == 0)
            break;
    }
    close(fd);
    return 0;
}
