#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Esercizio 1
void es1_saluto(void)
{
    char nome[50];
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);

    nome[strcspn(nome, "\n")] = '\0';

    printf("Ciao, %s! Benvenuto in C.\n", nome);
}

//Esercizio 2
void es2_pari_dispari(void)
{
    int n;
    printf("Inserisci un numero: ");
    scanf("%d", &n);

    if (n % 2 == 0)
        printf("%d e' pari.\n", n);
    else
        printf("%d e' dispari.\n", n);
}

//Esercizio 3
void es3_tabellina(void)
{
    int n;
    printf("Quale tabellina? ");
    scanf("%d", &n);

    for (int i = 1; i <= 10; i++)
        printf("%d x %d = %d\n", n, i, n * i);
}

//Esercizio 4
void es4_somma_media(void)
{
    int quanti;
    int somma = 0;

    printf("Quanti numeri? ");
    scanf("%d", &quanti);

    for (int i = 1; i <= quanti; i++)
    {
        int num;
        printf("Numero %d: ", i);
        scanf("%d", &num);
        somma += num;
    }

    printf("\nSomma: %d\n", somma);
    printf("Media: %.2f\n", (float)somma / quanti);
}

//Esercizio 5
void es5_max_min(void)
{
    int v[5];
    printf("Inserisci 5 numeri:\n");
    for (int i = 0; i < 5; i++)
        scanf("%d", &v[i]);

    int max = v[0], min = v[0];
    for (int i = 1; i < 5; i++)
    {
        if (v[i] > max) max = v[i];
        if (v[i] < min) min = v[i];
    }

    printf("\nMassimo: %d\n", max);
    printf("Minimo: %d\n", min);
}

//Esercizio 6
void es6_conta_vocali(void)
{
    char s[100];
    int conta = 0, i = 0;

    printf("Inserisci una stringa: ");
    scanf("%99s", s);

    while (s[i] != '\0')
    {
        char c = s[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            conta++;
        i++;
    }

    printf("Vocali trovate: %d\n", conta);
}

//Esercizio 7
void es7_inverti_stringa(void)
{
    char s[100];
    printf("Inserisci una stringa: ");
    scanf("%99s", s);

    int len = 0;
    while (s[len] != '\0')
        len++;

    printf("Stringa invertita: ");
    for (int i = len - 1; i >= 0; i--)
        putchar(s[i]);
    printf("\n");
}

//Esercizio 8
void es8_indovina_numero(void)
{
    srand((unsigned int)time(NULL));
    int segreto = rand() % 100 + 1;
    int tentativi = 7;
    int trovato = 0;

    printf("Ho pensato un numero tra 1 e 100. Hai %d tentativi.\n", tentativi);

    for (int t = 1; t <= tentativi; t++)
    {
        int prova;
        printf("Tentativo %d: ", t);
        scanf("%d", &prova);

        if (prova == segreto)
        {
            printf("  -> ESATTO! Trovato in %d tentativi.\n", t);
            trovato = 1;
            break;
        }
        else if (prova < segreto)
            printf("  -> troppo basso\n");
        else
            printf("  -> troppo alto\n");
    }

    if (!trovato)
        printf("Tentativi esauriti. Il numero era %d.\n", segreto);
}

//Esercizio 9
double es9_somma(double a, double b) { return a + b; }
double es9_sottrai(double a, double b) { return a - b; }
double es9_moltiplica(double a, double b) { return a * b; }

void es9_calcolatrice(void)
{
    double a, b;
    char op;

    printf("Primo numero: ");
    scanf("%lf", &a);
    printf("Operatore (+ - * /): ");
    scanf(" %c", &op);
    printf("Secondo numero: ");
    scanf("%lf", &b);

    switch (op)
    {
        case '+':
            printf("Risultato: %.2f\n", es9_somma(a, b));
            break;
        case '-':
            printf("Risultato: %.2f\n", es9_sottrai(a, b));
            break;
        case '*':
            printf("Risultato: %.2f\n", es9_moltiplica(a, b));
            break;
        case '/':
            if (b == 0)
                printf("Errore: divisione per zero.\n");
            else
                printf("Risultato: %.2f\n", a / b);
            break;
        default:
            printf("Operatore non valido.\n");
    }
}

//Esercizio 10
void es10_triangolo(void)
{
    int altezza;
    printf("Altezza: ");
    scanf("%d", &altezza);

    for (int riga = 1; riga <= altezza; riga++)
    {
        for (int col = 1; col <= riga; col++)
            putchar('*');
        printf("\n");
    }
}

//Esercizio 11
void es11_validatore_input(void)
{
    int valore;
    int letto;

    printf("Inserisci un numero (1-100): ");
    letto = scanf("%d", &valore);

    while (letto != 1 || valore < 1 || valore > 100)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (letto != 1)
            fprintf(stderr, "  -> input non valido, riprova: ");
        else
            fprintf(stderr, "  -> fuori range, riprova: ");

        letto = scanf("%d", &valore);
    }

    printf("Valore accettato: %d\n", valore);
}

//Esercizio 12
int es12_fattoriale(int n)
{
    printf("  livello %d: n vive a %p\n", n, (void *)&n);

    if (n <= 1)
        return 1;
    return n * es12_fattoriale(n - 1);
}

void es12_esegui(void)
{
    int n;
    printf("Calcola fattoriale di: ");
    scanf("%d", &n);

    printf("fattoriale(%d):\n", n);
    int risultato = es12_fattoriale(n);
    printf("Risultato: %d\n", risultato);
}

//Esercizio 13
void es13_leggi_file(void)
{
    char nomefile[200];
    printf("Nome del file da leggere: ");
    scanf("%199s", nomefile);

    FILE *f = fopen(nomefile, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Errore: impossibile aprire il file '%s'\n", nomefile);
        return;
    }

    char riga[256];
    int numero = 1;
    while (fgets(riga, sizeof(riga), f) != NULL)
    {
        printf("%d: %s", numero, riga);
        numero++;
    }

    fclose(f);
}

//Esercizio 14
void es14_stdout_stderr(void)
{
    int n;
    int positivi = 0, negativi = 0;

    printf("Inserisci numeri interi, termina con 0:\n");
    while (scanf("%d", &n) == 1 && n != 0)
    {
        if (n > 0)
        {
            printf("Quadrato di %d: %d\n", n, n * n);
            positivi++;
        }
        else
        {
            fprintf(stderr, "Attenzione: valore non positivo (%d)\n", n);
            negativi++;
        }
    }

    printf("Numeri positivi: %d\n", positivi);
    printf("Numeri negativi: %d\n", negativi);
}

//Esercizio 15
void es15_stampa_colonna(int altezza, int max, int riga)
{
    if (altezza >= (max - riga + 1))
        printf("# ");
    else
        printf("  ");
}

void es15_istogramma(void)
{
    int v[5];
    printf("Inserisci 5 valori (0-10): ");
    for (int i = 0; i < 5; i++)
        scanf("%d", &v[i]);

    int max = v[0];
    for (int i = 1; i < 5; i++)
        if (v[i] > max) max = v[i];

    for (int riga = 1; riga <= max; riga++)
    {
        for (int i = 0; i < 5; i++)
            es15_stampa_colonna(v[i], max, riga);
        printf("\n");
    }

    for (int i = 0; i < 5; i++) printf("---");
    printf("\n");
    for (int i = 0; i < 5; i++)
        printf("%d  ", v[i]);
    printf("\n");
}

//Menu principale
int main(void)
{
    int scelta;

    do
    {
        printf("\nEsercizi base\n");
        printf(" 1  Saluto personalizzato\n");
        printf(" 2  Pari o dispari\n");
        printf(" 3  Tabellina\n");
        printf(" 4  Somma di N numeri\n");
        printf(" 5  Massimo e minimo\n");
        printf(" 6  Conta le vocali\n");
        printf(" 7  Inverti una stringa\n");
        printf(" 8  Indovina il numero\n");
        printf(" 9  Calcolatrice semplice\n");
        printf("10  Triangolo di asterischi\n");
        printf("11  Validatore di input robusto\n");
        printf("12  Fattoriale ricorsivo\n");
        printf("13  Leggi un file riga per riga\n");
        printf("14  Stdout vs stderr\n");
        printf("15  Istogramma verticale\n");
        printf(" 0  Esci\n");
        printf("Scegli un esercizio: ");
        scanf("%d", &scelta);

        switch (scelta)
        {
            case 1:  es1_saluto(); break;
            case 2:  es2_pari_dispari(); break;
            case 3:  es3_tabellina(); break;
            case 4:  es4_somma_media(); break;
            case 5:  es5_max_min(); break;
            case 6:  es6_conta_vocali(); break;
            case 7:  es7_inverti_stringa(); break;
            case 8:  es8_indovina_numero(); break;
            case 9:  es9_calcolatrice(); break;
            case 10: es10_triangolo(); break;
            case 11: es11_validatore_input(); break;
            case 12: es12_esegui(); break;
            case 13: es13_leggi_file(); break;
            case 14: es14_stdout_stderr(); break;
            case 15: es15_istogramma(); break;
            case 0:  printf("Uscita\n"); break;
            default: printf("Scelta non valida.\n");
        }

    } while (scelta != 0);

    return 0;
}