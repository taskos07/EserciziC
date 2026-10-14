#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        // Figlio
        for (int i = 1; i <= 5; i++) {
            printf("[Figlio] %d\n", i);
            sleep(1);
        }

        exit(0);

    } else {

        // Padre
        wait(NULL);

        for (int i = 6; i <= 10; i++) {
            printf("[Padre] %d\n", i);
        }
    }

    return 0;
}