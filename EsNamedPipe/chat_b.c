#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define A_TO_B "/tmp/chat_a_to_b"
#define B_TO_A "/tmp/chat_b_to_a"

int main(void) {
    char testo[256], ricevuto[256];
    int ricevi, invia;

    printf("[B] In attesa di chat_a...\n");
    ricevi = open(A_TO_B, O_RDONLY); /* B apre prima in lettura */
    if (ricevi == -1) { perror("open A_TO_B"); return 1; }
    invia = open(B_TO_A, O_WRONLY);
    if (invia == -1) { perror("open B_TO_A"); return 1; }

    while (1) {
        ssize_t n = read(ricevi, ricevuto, sizeof(ricevuto) - 1);
        if (n <= 0) break;
        ricevuto[n] = '\0';
        printf("A> %s", ricevuto);
        if (strcmp(ricevuto, "EXIT\n") == 0 || strcmp(ricevuto, "EXIT") == 0) break;

        printf("B> ");
        if (fgets(testo, sizeof(testo), stdin) == NULL) break;
        write(invia, testo, strlen(testo) + 1);
        if (strcmp(testo, "EXIT\n") == 0 || strcmp(testo, "EXIT") == 0) break;
    }
    close(ricevi);
    close(invia);
    return 0;
}
