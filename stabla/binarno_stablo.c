/* Binarna stabla za ptragu - Predavanje */

#include <stdio.h>
#include <stdlib.h>

/* struktura kojom predstavljamo cvor */
struct cvor {
    int podatak;
    struct cvor *levi, *desni; /* pokazivaci na levo i desno podstablo */
};

/* funkcija za dodavanje novog cvora u binarno stablo */
struct cvor *dodaj(struct cvor *p, int vrednost) {
    /* kreiranje novog cvora */
    struct cvor *novi = (struct cvor *)malloc(sizeof(struct cvor));
    if (novi == NULL) {
        printf("Greska pri alociranju memorije\n");
        exit(1);
    }
    novi->podatak = vrednost;
    novi->levi = novi->desni = NULL;

    /* dodavanje cvora u prazno stablo */
    if (p == NULL) {
        p = novi;

    /* dodavanje cvora u popunjeno stablo */
    } else {
        /* prolazimo kroz stablo da nadjemo za koji cvor da zakacimo novi cvor */
        struct cvor *pom1 = p;
        struct cvor *pom2 = NULL;
        while (pom1 != NULL) {
            /* pamtimo roditeljski cvor */
            pom2 = pom1;
            if (vrednost <= pom1->podatak) pom1 = pom1->levi;
            else                           pom1 = pom1->desni;
        }

        /* kacimo novi cvor preko pom2 */
        if (vrednost <= pom2->podatak) pom2->levi = novi;
        else                           pom2->desni = novi;
    }

    return p;
}

/* funkcija za stampanje binarnog stabla u inorder redosledu */
void stampaj_inorder(struct cvor *p) {
    if (p != NULL) {
        stampaj_inorder(p->levi);
        printf("%d\t", p->podatak);
        stampaj_inorder(p->desni);
    }
}

int main(void) {
    struct cvor *koren = NULL;
    int n, x;

    printf("Unesite broj cvorova:\n");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Unesite vrednost:\n");
        scanf("%d", &x);
        koren = dodaj(koren, x);
    }

    stampaj_inorder(koren);
}