#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26
#define MAKS_DUZINA 100

typedef struct drvo {
    char c;

    struct drvo *sledeci[26];
} Drvo;

Drvo* kreirajCvor(char c) {
    Drvo *novi = malloc(sizeof(Drvo));
    novi->c = c;

    for (int i = 0; i < ALPHABET; i++)
        novi->sledeci[i] = NULL;

    return novi;
}

int mesto(char c) {
    return c - 'a'; // c - 97
}

void kreirajDigitalnoStablo(Drvo *koren) {

    char rec[MAKS_DUZINA];
    Drvo *tmp = koren;

    printf("Unesite rec: ");
    scanf("%s", rec);
    const int n = strlen(rec);

    for (int i = 0; i < n; i++) {
        if (rec[i] < 'A' && rec[i] > 'z') {
            printf("Uneli ste pogresan karakter [%c]\n", rec[i]);
            exit(1);
        }

        const int indeks = mesto(rec[i]);
        if (tmp->sledeci[indeks] == NULL) {
            tmp->sledeci[indeks] = kreirajCvor(rec[i]);
        }

        tmp = tmp->sledeci[indeks];
    }
}

int recPostoji(Drvo *koren, char *rec) {

    Drvo* tmp = koren;
    for (int i = 0; i < strlen(rec); i++) {
        const int indeks = mesto(rec[i]);

        if (tmp->sledeci[indeks] == NULL) return 0;
        tmp = tmp->sledeci[indeks];
    }

    return 1;
}

void oslobodi_memoriju(Drvo *koren) {
    if (koren == NULL) return;

    for (int i = 0; i < ALPHABET; i++) {
        if (koren->sledeci[i] != NULL) {
            oslobodi_memoriju(koren->sledeci[i]);
        }
    }

    free(koren);
}

int main() {
    Drvo *koren = kreirajCvor(' ');

    printf("Unesite broj reci: ");
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        kreirajDigitalnoStablo(koren);
    }

    printf("Unesite rec za pretragu? ");
    char rec[MAKS_DUZINA];
    scanf("%s", rec);

    if (recPostoji(koren, rec))
        printf("\nUneta rec postoji\n");
    else
        printf("Rec ne postoji\n");

    oslobodi_memoriju(koren);

    return 0;
}