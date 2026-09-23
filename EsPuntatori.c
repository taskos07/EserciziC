#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Esercizio 1
void es1_indirizzi_valori(void)
{
    int x = 42;
    int *ptr = &x;

    printf("Valore di x: %d\n", x);
    printf("Indirizzo di x: %p\n", (void *)&x);
    printf("Valore puntato da ptr: %d\n", *ptr);

    *ptr = 100;
    printf("\nDopo la modifica tramite puntatore:\n");
    printf("Nuovo valore di x: %d\n", x);
}

//Esercizio 2
void scambia(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void es2_scambio(void)
{
    int x = 10, y = 20;
    printf("Prima dello scambio: x = %d, y = %d\n", x, y);

    scambia(&x, &y);

    printf("Dopo lo scambio: x = %d, y = %d\n", x, y);
}

//Esercizio 3
void es3_malloc_singolo(void)
{
    float *p = (float *) malloc(sizeof(float));
    if (p == NULL)
    {
        printf("Errore malloc\n");
        return;
    }

    printf("Inserisci un numero decimale: ");
    scanf("%f", p);

    *p = *p * 1.20f;
    printf("Valore inserito aumentato del 20%%: %.2f\n", *p);

    free(p);
}

//Esercizio 4
void es4_array_dinamico(void)
{
    int n;
    printf("Quanti numeri vuoi inserire? ");
    scanf("%d", &n);

    int *v = (int *) malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Errore malloc\n");
        return;
    }

    int somma = 0;
    for (int i = 0; i < n; i++)
    {
        printf("Numero %d: ", i + 1);
        scanf("%d", &v[i]);
        somma += v[i];
    }

    printf("Somma totale: %d\n", somma);

    free(v);
}

//Esercizio 5
void es5_puntatori_array(void)
{
    int arr[5] = {10, 20, 30, 40, 50};
    int *p;

    printf("Array: [");
    for (int i = 0; i < 5; i++)
        printf("%d%s", arr[i], (i < 4) ? ", " : "");
    printf("]\n");

    printf("\nElementi dell'array stampati tramite puntatore:\n");
    int i = 0;
    for (p = arr; p < arr + 5; p++)
    {
        printf("Elemento %d: %d\n", i, *p);
        i++;
    }
}

//Esercizio 6
void inverti_array(int *v, int n)
{
    int *inizio = v;
    int *fine = v + n - 1;

    while (inizio < fine)
    {
        scambia(inizio, fine);
        inizio++;
        fine--;
    }
}

void es6_inverti_array_dinamico(void)
{
    int n;
    printf("N: ");
    scanf("%d", &n);

    int *v = (int *) malloc(n * sizeof(int));
    if (v == NULL) { printf("Errore malloc\n"); return; }

    printf("Inserisci %d numeri:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    printf("Array originale: ");
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");

    inverti_array(v, n);

    printf("Array invertito: ");
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");

    free(v);
}

//Esercizio 7
char *duplica_stringa(const char *s)
{
    int len = (int) strlen(s);
    char *nuova = (char *) malloc((len + 1) * sizeof(char));
    if (nuova == NULL)
        return NULL;

    for (int i = 0; i <= len; i++)
        nuova[i] = s[i];

    return nuova;
}

void es7_duplica_stringa(void)
{
    char originale[200];
    printf("Stringa da duplicare: ");
    scanf(" %199[^\n]", originale);

    char *copia = duplica_stringa(originale);
    if (copia == NULL) { printf("Errore malloc\n"); return; }

    printf("Originale: %s\n", originale);
    printf("Copia: %s\n", copia);

    free(copia);
}

//Esercizio 8
int *trova_massimo(int *array, int dimensione)
{
    int *max = array;
    for (int i = 1; i < dimensione; i++)
        if (array[i] > *max)
            max = &array[i];
    return max;
}

void es8_trova_massimo(void)
{
    int n;
    printf("Quanti elementi? ");
    scanf("%d", &n);

    int *v = malloc(n * sizeof(int));
    if (v == NULL) { printf("Errore malloc\n"); return; }

    printf("Array: [");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < n; i++)
        printf("%d%s", v[i], (i < n - 1) ? ", " : "");
    printf("]\n");

    int *pmax = trova_massimo(v, n);

    printf("\nMassimo: %d\n", *pmax);
    printf("Posizione (indice): %ld\n", (long)(pmax - v));

    free(v);
}

//Esercizio 5
void es9_array_stringhe(void)
{
    int n;
    printf("Quante parole vuoi inserire? ");
    scanf("%d", &n);

    char **parole = (char **) malloc(n * sizeof(char *));
    if (parole == NULL) { printf("Errore malloc\n"); return; }

    char buffer[100];
    for (int i = 0; i < n; i++)
    {
        printf("Parola %d: ", i + 1);
        scanf("%99s", buffer);

        parole[i] = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(parole[i], buffer);
    }

    printf("\nParole in ordine inverso:\n");
    for (int i = n - 1; i >= 0; i--)
        printf("%s\n", parole[i]);

    for (int i = 0; i < n; i++)
        free(parole[i]);
    free(parole);
}

//Esercizio 10
void es10_vettore_espande(void)
{
    int capacita = 2;
    int dimensione = 0;
    int *v = (int *) malloc(capacita * sizeof(int));
    if (v == NULL) { printf("Errore malloc\n"); return; }

    printf("Inserisci numeri (0 per terminare):\n");

    int num;
    scanf("%d", &num);
    while (num != 0)
    {
        if (dimensione == capacita)
        {
            capacita *= 2;
            v = (int *) realloc(v, capacita * sizeof(int));
            if (v == NULL) { printf("Errore realloc\n"); return; }
            printf("(Espansione a %d elementi)\n", capacita);
        }

        v[dimensione] = num;
        dimensione++;

        scanf("%d", &num);
    }

    printf("\nNumeri inseriti:\n");
    for (int i = 0; i < dimensione; i++)
        printf("%d ", v[i]);
    printf("\n");

    free(v);
}

//Menu principale
int main(void)
{
    int scelta;

    do
    {
        printf("\nEsercizi puntatori e allocazione dinamica\n");
        printf("Indirizzi e valori\n");
        printf("Scambio di variabili (swap)\n");
        printf("Allocazione singola con malloc\n");
        printf("Array dinamico semplice\n");
        printf("Puntatori e array\n");
        printf("Inversione di un array dinamico\n");
        printf("Copia di stringa dinamica\n");
        printf("Ricerca del massimo in un array\n");
        printf("Array di stringhe dinamico\n");
        printf("Vettore che si espande (realloc)\n");
        printf("Esci\n");
        printf("Scegli un esercizio: ");
        scanf("%d", &scelta);

        switch (scelta)
        {
            case 1:  es1_indirizzi_valori(); break;
            case 2:  es2_scambio(); break;
            case 3:  es3_malloc_singolo(); break;
            case 4:  es4_array_dinamico(); break;
            case 5:  es5_puntatori_array(); break;
            case 6:  es6_inverti_array_dinamico(); break;
            case 7:  es7_duplica_stringa(); break;
            case 8:  es8_trova_massimo(); break;
            case 9:  es9_array_stringhe(); break;
            case 10: es10_vettore_espande(); break;
            case 0:  printf("Uscita\n"); break;
            default: printf("Scelta non valida\n");
        }

    } while (scelta != 0);

    return 0;
}