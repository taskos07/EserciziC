#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define FIFO_PATH "/tmp/fifo_test"

int main(void) {
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        if (errno == EEXIST) {
            printf("La FIFO esiste gia': %s\n", FIFO_PATH);
        } else {
            perror("mkfifo");
            return 1;
        }
    } else {
        printf("FIFO creata: %s\n", FIFO_PATH);
    }

    printf("Controllala con ls -l mentre aspetto 10 secondi.\n");
    sleep(10);

    if (unlink(FIFO_PATH) == -1) {
        perror("unlink");
        return 1;
    }
    printf("FIFO rimossa.\n");
    return 0;
}
