#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_PING "/tmp/fifo_ping"
#define FIFO_PONG "/tmp/fifo_pong"

int main(void) {
    char messaggio[100];
    int lettura, scrittura;

    printf("[PONG] Attendo PING...\n");
    lettura = open(FIFO_PING, O_RDONLY); /* Prima: pong apre in lettura */
    if (lettura == -1) { perror("open fifo_ping"); return 1; }
    read(lettura, messaggio, sizeof(messaggio) - 1);
    messaggio[sizeof(messaggio) - 1] = '\0';
    close(lettura);
    printf("[PONG] Ricevuto: %s\n", messaggio);

    scrittura = open(FIFO_PONG, O_WRONLY);
    if (scrittura == -1) { perror("open fifo_pong"); return 1; }
    write(scrittura, "PONG", 5);
    close(scrittura);
    return 0;
}
