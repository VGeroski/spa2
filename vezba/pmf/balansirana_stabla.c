/*
 * Napisati program koji formira balansirano uredjeno binarno stablo celih brojeva.
 * AVL - stabla
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct drvo {
    int broj;
    int balans;
    struct drvo *levi, *desni;
} Drvo;

int max(int a, int b) {
    return a > b ? a : b;
}

Drvo* kreirajCvor(int podatak) {
    Drvo *novi = (Drvo *)malloc(sizeof(Drvo));
    novi->broj = podatak;
    novi->balans = 0;
    novi->levi = novi->desni = NULL;

    return novi;
}

int dubina(Drvo *p) {
    if(!p) return 0;

    int leva_dubina = dubina(p->levi);
    int desna_dubina = dubina(p->desni);

    return 1 + max(leva_dubina, desna_dubina);
}

void leva_rot(Drvo **d) {
    Drvo *poml = *d;
    Drvo *pomd = poml->desni;

    poml->desni = pomd->levi;
    pomd->levi = poml;

    *d = pomd;

    poml->balans = dubina(poml->desni) - dubina(poml->levi);
    pomd->balans = dubina(pomd->desni) - dubina(pomd->levi);
}

void desna_rot(Drvo **d) {
    Drvo *pomd = *d;
    Drvo *poml = pomd->levi;

    pomd->levi = poml->desni;
    poml->desni = pomd;

    *d = poml;

    poml->balans = dubina(poml->desni) - dubina(poml->levi);
    pomd->balans = dubina(pomd->desni) - dubina(pomd->levi);
}

int dodaj(Drvo **p, int vrednost) {
    int inkrement = 0, rezultat = 0;
    Drvo *t = *p;

    if (!t) {
        t = kreirajCvor(vrednost);
        rezultat = 1;

    } else {
        if (vrednost > t->broj)
            inkrement = dodaj(&(t->desni), vrednost);
        else
            inkrement = -dodaj(&(t->levi), vrednost);

        t->balans += inkrement;

        if (inkrement != 0 && t->balans != 0) {

            if (t->balans < -1) {
                if (t->levi->balans < 0) desna_rot(&t);
                else {
                    leva_rot(&(t->levi));
                    desna_rot(&t);
                }

            } else if (t->balans > 1) {

                if (t->desni->balans > 0) leva_rot(&t);
                else {
                    desna_rot(&(t->desni));
                    leva_rot(&t);
                }

            } else
                rezultat = 1;
        }
    }

    *p = t;
    return rezultat;
}

Drvo* formiraj(){
    Drvo *koren;
    int k;
    koren = NULL;
    scanf("%d",&k);
    while(k) {
        dodaj(&koren,k);
        scanf("%d",&k);
    }
    return koren;
}

void ispis(Drvo *p) {
    if (p) {
        ispis(p->levi);
        printf("%5d", p->broj);
        ispis(p->desni);
    }
}

void oslobodi_memoriju(Drvo *drvo) {
    if (drvo == NULL) return;

    oslobodi_memoriju(drvo->levi);
    oslobodi_memoriju(drvo->desni);

    free(drvo);
}

int main() {
    Drvo *p = formiraj();
    ispis(p);
    printf("\n");
    printf("Dubina je %d\n", dubina(p));

    oslobodi_memoriju(p);
}

