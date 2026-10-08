#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int fd[2];

    if (pipe(fd) == -1) {
        fprintf(stderr, "Error pipe\n");
        exit(-1);
    }

    pid_t ritorno = fork();
    if (ritorno == -1) {
        fprintf(stderr, "Error fork\n");
        exit(-2);
    }

    if (ritorno == 0) {
        // Processo FIGLIO: calcola la somma dei numeri pari
        close(fd[0]);

        int somma_pari = 0;
        for (int i = 0; i < 10; i++) {
            if (array[i] % 2 == 0) {
                somma_pari += array[i];
            }
        }


        write(fd[1], &somma_pari, sizeof(somma_pari));
        close(fd[1]);
        exit(0);
    } else {
        // Processo PADRE: calcola la somma dei numeri dispari
        close(fd[1]);

        int somma_dispari = 0;
        for (int i = 0; i < 10; i++) {
            if (array[i] % 2 != 0) {
                somma_dispari += array[i];
            }
        }

        int somma_pari_ricevuta = 0;
        read(fd[0], &somma_pari_ricevuta, sizeof(somma_pari_ricevuta));
        close(fd[0]);

        wait(NULL);

        int somma_totale = somma_pari_ricevuta + somma_dispari;

        printf("Somma numeri pari (figlio): %d\n", somma_pari_ricevuta);
        printf("Somma numeri dispari (padre): %d\n", somma_dispari);
        printf("Somma totale complessiva: %d\n", somma_totale);
    }

    return 0;
}
