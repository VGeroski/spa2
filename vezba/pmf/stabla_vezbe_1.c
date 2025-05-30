#include <stdio.h>
#include <stdlib.h>

struct drvo {
    int broj;
    struct drvo *levi, *desni;
};

struct drvo *
novi(int br) {
    struct drvo *x = (struct drvo *) malloc(sizeof(struct drvo));
    x->broj = br;
    x->levi = x->desni = NULL;

    return x;
}

void dodaj(struct drvo **, int);

struct drvo *formiraj();

void ispis(struct drvo *);

int maksimum(struct drvo *);

int zbir(struct drvo *);

int dubina(struct drvo *);

int nadji(struct drvo *, int);

int
main() {
    struct drvo *p;
    int n, m;

    p = formiraj();

    ispis(p);
    printf("\n");

    return 0;
}

/* funkcija ucitava brojeve sa ulaza i ubacuje u binarno stablo */
struct drvo *
formiraj() {
    struct drvo *koren = NULL;
    int k;

    printf("Upisite elemente [0 - kraj]:\n");
    scanf("%d", &k);

    while (k) {
        dodaj(&koren, k);
        scanf("%d", &k);
    }

    return koren;
}

/* funkcija za dodavanje u binarno stablo */
void
dodaj(struct drvo **p, int k) {
    struct drvo *temp = novi(k);
    if (!temp) {
        printf("Greska pri alokaciji memorije.\n");
        exit(EXIT_FAILURE);
    }

    /* ako je stablo prazno, novi cvor je i koren */
    if (!(*p)) *p = temp;
    else {
        struct drvo *pom1 = *p;
        /* pamtimo prethodni cvor */
        struct drvo *pom2 = NULL;

        while (pom1) {
            pom2 = pom1; /* sacuvamo prethodni korak */
            if (k < pom1->broj) pom1 = pom1->levi;
            else pom1 = pom1->desni;
        }

        /* kacimo novi cvor preko pom2, zato sto je pom1 izleteo iz stabla */
        if (k < pom2->broj) pom2->levi = temp;
        else pom2->desni = temp;
    }
}

/* funkcija za ispis stabla - LPD */
void
ispis(struct drvo *p) {
    if (p) {
        ispis(p->levi);
        printf("%5d", p->broj);
        ispis(p->desni);
    }
}

int
maksimum(struct drvo *p) {
    while (p) {
        if (p->desni) p = p->desni;

        return p->broj;
    }
}

int
zbir(struct drvo *p) {
    int s;
    s = p->broj;

    if (p->levi) s += zbir(p->levi);
    if (p->desni) s = zbir(p->desni);

    return s;
}

int
dubina(struct drvo *p) {
    int dl = 0, dd = 0;

    if (p) {
        if (p->levi) dl = dubina(p->levi);
        if (p->desni) dd = dubina(p->desni);

        if (dl > dd) return ++dl;
        return ++dd;
    }

    return 0;
}

int
nadji(struct drvo *p, int kljuc) {
    int dubina = 0;
    struct drvo *pom = p;

    while (pom) {
        dubina++;
        /* ukoliko nadjemo kljuc, odmah vracamo dubinu */
        if (pom->broj == kljuc) return dubina;

        if (kljuc < pom->broj) pom = pom->levi;
        else pom = pom->desni;
    }

    /* ukoliko smo iskocili iz petlje, nismo nasli kljuc */
    return -1;
}



