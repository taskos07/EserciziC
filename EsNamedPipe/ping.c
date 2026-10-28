#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define FIFO_PING "/tmp/fifo_ping"
#define FIFO_PONG "/tmp/fifo_pong"

static int crea_fifo(const char *percorso) {
    if (mkfifo(percorso, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return -1;
    }
    return 0;
}

int main(void) {
    char risposta[100];
    int scrittura, lettura;

    if (crea_fifo(FIFO_PING) == -1 || crea_fifo(FIFO_PONG) == -1)
        return 1;

    printf("[PING] Attendo PONG...\n");
    scrittura = open(FIFO_PING, O_WRONLY); /* Prima: ping apre in scrittura */
    if (scrittura == -1) { perror("open fifo_ping"); return 1; }
    write(scrittura, "PING", 5);
    close(scrittura);

    lettura = open(FIFO_PONG, O_RDONLY);
    if (lettura == -1) { perror("open fifo_pong"); return 1; }
    read(lettura, risposta, sizeof(risposta) - 1);
    risposta[sizeof(risposta) - 1] = '\0';
    close(lettura);
    printf("[PING] Risposta: %s\n", risposta);

    unlink(FIFO_PING);
    unlink(FIFO_PONG);
    return 0;
}