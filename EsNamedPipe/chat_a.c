#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define A_TO_B "/tmp/chat_a_to_b"
#define B_TO_A "/tmp/chat_b_to_a"

int main(void) {
    char testo[256], risposta[256];
    int invia, ricevi;

    if (mkfifo(A_TO_B, 0666) == -1 && errno != EEXIST) { perror("mkfifo"); return 1; }
    if (mkfifo(B_TO_A, 0666) == -1 && errno != EEXIST) { perror("mkfifo"); return 1; }

    printf("[A] Avvia ora chat_b in un secondo terminale.\n");
    invia = open(A_TO_B, O_WRONLY); /* A apre prima in scrittura */
    if (invia == -1) { perror("open A_TO_B"); return 1; }
    ricevi = open(B_TO_A, O_RDONLY);
    if (ricevi == -1) { perror("open B_TO_A"); return 1; }

    while (1) {
        printf("A> ");
        if (fgets(testo, sizeof(testo), stdin) == NULL) break;
        write(invia, testo, strlen(testo) + 1);
        if (strcmp(testo, "EXIT\n") == 0 || strcmp(testo, "EXIT") == 0) break;

        ssize_t n = read(ricevi, risposta, sizeof(risposta) - 1);
        if (n <= 0) break;
        risposta[n] = '\0';
        printf("B> %s", risposta);
        if (strcmp(risposta, "EXIT\n") == 0 || strcmp(risposta, "EXIT") == 0) break;
    }
    close(invia);
    close(ricevi);
    unlink(A_TO_B);
    unlink(B_TO_A);
    return 0;
}