#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];

    int numeri[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t ritorno_fork = fork();

    if (ritorno_fork == -1) {
        perror("fork");
        exit(1);
    }

    // Processo Figlio
    if (!ritorno_fork) {
        close(fd[0]);

        int somma_pari = 0;

        for (int i = 0; i < 10; i++) {
            if (numeri[i] % 2 == 0) {
                somma_pari += numeri[i];
            }
        }

        write(fd[1], &somma_pari, sizeof(somma_pari));

        close(fd[1]);
        exit(0);
    }

    // Processo Padre
    close(fd[1]);

    int somma_dispari = 0;
    int somma_pari;

    for (int i = 0; i < 10; i++) {
        if (numeri[i] % 2 != 0) {
            somma_dispari += numeri[i];
        }
    }

    read(fd[0], &somma_pari, sizeof(somma_pari));

    close(fd[0]);

    wait(NULL);

    printf("Somma pari: %d\n", somma_pari);
    printf("Somma dispari: %d\n", somma_dispari);
    printf("Somma totale: %d\n", somma_pari + somma_dispari);

    return 0;
}