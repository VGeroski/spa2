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

/* funkcija koja odredjuje broj cvorova u stablu */
int broj(struct cvor *p) {
    if (p == NULL) return 0;
    if (p->levi == NULL && p->desni == NULL) return 1;
    return 1 + broj(p->levi) + broj(p->desni);
}

/* funkcija koja menja mesta levim i desnim podstablima */
void zameni(struct cvor *p) {
    struct cvor *pom;

    if (p != NULL) {
        /* zamena mesta u cvoru */
        pom = p->levi;
        p->levi = p->desni;
        p->desni = pom;

        /* zameni mesto levom i desnom podstablu */
        zameni(p->levi);
        zameni(p->desni);
    }
}

/* funkcija za trazenje cvora u binarnom stablu
 * ukoliko cvor postoji, preko y vracamo roditelja cvora
 */
struct cvor *pronadji(struct cvor *p, int kljuc, struct cvor **y) {
    if (p == NULL) return NULL;

    struct cvor *pom = p;
    *y = NULL;
    while (pom != NULL) {
        if (pom->podatak == kljuc) return pom;

        *y = pom; /* pamtimo roditelja */
        if (kljuc < pom->podatak) pom = pom->levi;
        else pom = pom->desni;
    }

    /* ako izadjemo iz petlje, cvor ne postoji u stablu */
    return NULL;
}

/* funkcija za brisanje cvora iz binarnog stabla za pretrazivanje */
struct cvor *obrisi(struct cvor *p, int kljuc) {
    struct cvor *y = NULL; /* roditelj cvora kojeg brisemo */
    struct cvor *x = pronadji(p, kljuc, &y); /* cvor koji treba obrisati */
    if (x == NULL) return p;

    struct cvor *q = NULL; /* potomak cvora kojeg brisemo */

    /* slucaj ukliko cvor nema potomke */
    if (x->levi == NULL && x->desni == NULL) q = NULL;

    /*slucaj ukoliko cvor ima jednog potomka */
    if (x->desni != NULL && x->levi == NULL) q = x->desni;
    if (x->desni == NULL && x->levi != NULL) q = x->levi;

    /* slucaj ukoliko cvor ima oba potomka */
    if (x->desni != NULL && x->levi != NULL) {
        q = x->levi;
        struct cvor *pom = q;
        while (pom->desni != NULL) pom = pom->desni;
        pom->desni = x->desni;
    }

    if (y != NULL) {
        if (y->levi == x) y->levi = q;
        else y->desni = q;
    } else
        p = q;

    free(x);
    return p;
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
    printf("\nBroj cvorova u stablu: %d\n", broj(koren));

    zameni(koren);
    stampaj_inorder(koren);

    zameni(koren);
    obrisi(koren, 10);
    printf("\n");
    stampaj_inorder(koren);
}