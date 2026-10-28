#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(void) {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    srand(time(NULL));

    // Creazione processo B
    pid_t pidB = fork();

    if (pidB == -1) {
        perror("fork");
        exit(1);
    }

    if (!pidB) {
        // Processo B
        close(pipe1[1]);
        close(pipe2[0]);

        int numero;

        while (read(pipe1[0], &numero, sizeof(numero)) > 0) {
            if (numero >= 50) {
                int quadrato = numero * numero;

                write(pipe2[1], &quadrato, sizeof(quadrato));
            }
        }

        close(pipe1[0]);
        close(pipe2[1]);

        exit(0);
    }

    // Creazione processo C
    pid_t pidC = fork();

    if (pidC == -1) {
        perror("fork");
        exit(1);
    }

    if (!pidC) {
        // Processo C
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);

        int numero;
        int somma = 0;
        int contatore = 0;

        while (read(pipe2[0], &numero, sizeof(numero)) > 0) {
            printf("Quadrato ricevuto: %d\n", numero);

            somma += numero;
            contatore++;
        }

        close(pipe2[0]);

        if (contatore > 0) {
            printf("Media: %.2f\n", (float)somma / contatore);
        } else {
            printf("Nessun numero ricevuto.\n");
        }

        exit(0);
    }

    // Processo A (Padre)
    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe2[1]);

    for (int i = 0; i < 20; i++) {
        int numero = rand() % 100 + 1;

        printf("Numero generato: %d\n", numero);

        write(pipe1[1], &numero, sizeof(numero));
    }

    close(pipe1[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}