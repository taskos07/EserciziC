#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        // Processo Padre
        printf("[Padre] Creo il nipote.\n");

        pid_t pid2 = fork();

        if (pid2 == 0) {

            // Nipote
            printf("[Nipote] Sono il nipote.\n");
            sleep(1);
            printf("[Nipote] Termino.\n");

            exit(0);

        } else {

            wait(NULL);

            printf("[Padre] Il nipote è terminato. Termino anche io.\n");

            exit(0);
        }

    } else {

        wait(NULL);

        printf("[Nonno] Il padre è terminato. Termino anche io.\n");
    }

    return 0;
}