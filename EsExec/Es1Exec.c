#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char comando[50];

    while (1) {
        printf("mini-shell> ");
        fflush(stdout);

        if (fgets(comando, sizeof(comando), stdin) == NULL) {
            continue;
        }

        for (int i = 0; comando[i] != '\0'; i++) {
            if (comando[i] == '\n') {
                comando[i] = '\0';
                break;
            }
        }

        if (strcmp(comando, "exit") == 0) {
            break;
        }

        if (comando[0] == '\0') {
            continue;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Errore nella fork");
        }
        else if (pid == 0) {
            char *args[] = {comando, NULL};

            execvp(args[0], args);

            printf("Errore: comando '%s' non trovato\n", comando);
            exit(1);
        }
        else {
            wait(NULL);
        }
    }

    printf("Uscita dalla mini shell.\n");
    return 0;
}
