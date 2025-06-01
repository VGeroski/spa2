#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cvor {
    int podatak;
    int balans; /* = dubina(desni) - dubina(levi) */
    struct cvor *levi, *desni;
} Cvor;

int dubina(Cvor *p) {
    int dl = 0, dd = 0;

    if (p) {
        if (p->levi) dl = dubina(p->levi);
        if (p->desni) dd = dubina(p->desni);

        if (dl > dd) return ++dl;
        return ++dd;
    }

    return 0;
}

void leva_rotacija(Cvor **t) {
    Cvor *pom_levi = *t;
    Cvor *pom_desni = pom_levi->desni;

    pom_levi->desni = pom_desni->levi;
    pom_desni->desni = pom_levi;

    *t = pom_desni;

    pom_levi->balans = dubina(pom_levi->desni) - dubina(pom_levi->levi);
    pom_desni->balans = dubina(pom_desni->desni) - dubina(pom_desni->levi);
}

void desna_rotacija(Cvor **t) {
    Cvor *pom_desni = *t;
    Cvor *pom_levi = pom_desni->levi;

    pom_desni->levi = pom_levi->desni;
    pom_levi->desni = pom_desni;

    *t = pom_levi;

    pom_levi->balans = dubina(pom_levi->desni) - dubina(pom_levi->levi);
    pom_desni->balans = dubina(pom_desni->desni) - dubina(pom_desni->levi);
}

void dvostruka_leva_rotacija(Cvor **t) {
    desna_rotacija(&(*t)->desni);
    leva_rotacija(t);
}

void dvostruka_desna_desni(Cvor **t) {
    leva_rotacija(&(*t)->levi);
    desna_rotacija(t);
}

Cvor* kreiraj_cvor(int vrednost) {
    Cvor *t = (Cvor *)malloc(sizeof(Cvor));
    if (!t) {
        printf("Greska pri alociranju memorije.\n");
        exit(EXIT_FAILURE);
    }

    t->podatak = vrednost;
    t->balans = 0;
    t->levi = t->desni = NULL;
    return t;
}

int dodaj(Cvor **p, int vrednost) {
    int inkrement = 0, rezultat = 0;

    Cvor *t = *p;

    if (t == NULL) {
        t = kreiraj_cvor(vrednost);
        rezultat = 1; /* znak da smo dodali cvor u stablo */

    } else {

        if (vrednost > t->podatak) inkrement = dodaj(&(t->desni), vrednost);
        else                       inkrement = -dodaj(&(t->levi), vrednost);

        t->balans += inkrement;

        if (inkrement != 0 && t->balans != 0) {

            if (t->balans < -1) {

                if (t->levi->balans > 0) desna_rotacija(&t);
                else                     dvostruka_desna_desni(&t);

            } else if (t->levi->balans > 1) {

                if (t->desni->balans > 0) leva_rotacija(&t);
                else                      dvostruka_leva_rotacija(&t);

            } else
                rezultat = 1;
        }
    }

    *p = t;
    return rezultat;
}

