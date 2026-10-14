#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

struct Messaggio {
    char testo[100];
    int vocali;
};

int main(void) {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
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
        close(pipe1[1]);
        close(pipe2[0]);

        char testo[100];
        struct Messaggio messaggio;

        read(pipe1[0], testo, sizeof(testo));

        close(pipe1[0]);

        strcpy(messaggio.testo, testo);
        messaggio.vocali = 0;

        for (int i = 0; messaggio.testo[i] != '\0'; i++) {
            messaggio.testo[i] = toupper(messaggio.testo[i]);

            if (messaggio.testo[i] == 'A' ||
                messaggio.testo[i] == 'E' ||
                messaggio.testo[i] == 'I' ||
                messaggio.testo[i] == 'O' ||
                messaggio.testo[i] == 'U') {
                messaggio.vocali++;
                }
        }

        write(pipe2[1], &messaggio, sizeof(messaggio));

        close(pipe2[1]);
        exit(0);
    }

    // Processo Padre
    close(pipe1[0]);
    close(pipe2[1]);

    char testo[100];
    struct Messaggio messaggio;

    printf("Inserisci una frase: ");
    fgets(testo, sizeof(testo), stdin);

    write(pipe1[1], testo, sizeof(testo));

    close(pipe1[1]);

    read(pipe2[0], &messaggio, sizeof(messaggio));

    close(pipe2[0]);

    wait(NULL);

    printf("Testo maiuscolo: %s", messaggio.testo);
    printf("Numero di vocali: %d\n", messaggio.vocali);

    return 0;
}