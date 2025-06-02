#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct drvo {
    union {
        int broj;
        char oper;
    } sadrzaj;

    struct drvo *levi, *desni;
} Drvo;

typedef struct stek {
    Drvo *drvo;
    struct stek *sledeci;
} Stek;

Drvo *kreirajDrvoCvor() {
    Drvo *noviCvor = (Drvo *) malloc(sizeof(Drvo));
    if (!noviCvor) {
        printf("Greska pri alociranju memorije.\n");
        exit(EXIT_FAILURE);
    }

    noviCvor->levi = noviCvor->desni = NULL;

    return noviCvor;
}

Stek *kreirajStekCvor(Drvo *drvoCvor) {
    Stek *noviCvor = (Stek *) malloc(sizeof(Stek));
    if (!noviCvor) {
        printf("Greska pri alociranju memorije.\n");
        exit(EXIT_FAILURE);
    }

    noviCvor->drvo = drvoCvor;
    noviCvor->sledeci = NULL;

    return noviCvor;
}

void gurniNaStek(Stek **s, Drvo *d) {
    Stek *tmp = kreirajStekCvor(d);

    tmp->sledeci = *s;
    *s = tmp;
}

Drvo *skiniSaSteka(Stek **s) {
    /* prazan stek */
    if (*s == NULL) return NULL;

    Drvo *cvorZaVracanje = (*s)->drvo;

    /* prevezujemo cvor da bi oslobodili memoriju */
    Stek *tmp = *s;
    *s = (*s)->sledeci;

    free(tmp);

    return cvorZaVracanje;
}

int daLiJeOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

Drvo *kreirajStablo() {
    char token[50], ch;
    int brojac = 0;

    Drvo *tmp, *levi, *desni, *operator;
    Stek *stek = NULL;

    while ((ch = getchar()) != '\n') {
        if (ch == '(' || ch == ' ') continue;

        if (isdigit(ch)) {
            /* ukoliko broj nije jednocifren, 
             * izlacimo sve cifre pre konverzije */
            while (isdigit(ch)) {
                token[brojac++] = ch;
                ch = getchar();
            }

            token[brojac] = '\0';
            brojac = 0; /* restartujemo brojac za novi broj koji naidje */

            tmp = kreirajDrvoCvor();
            tmp->sadrzaj.broj = atoi(token);

            gurniNaStek(&stek, tmp);
        }

        if (daLiJeOperator(ch)) {
            tmp = kreirajDrvoCvor();
            tmp->sadrzaj.oper = ch;

            gurniNaStek(&stek, tmp);
        }

        if (ch == ')') {
            desni = skiniSaSteka(&stek);
            operator = skiniSaSteka(&stek);
            levi = skiniSaSteka(&stek);

            operator->levi = levi;
            operator->desni = desni;

            gurniNaStek(&stek, operator);
        }
    }

    return skiniSaSteka(&stek);
}

int vrednost(Drvo *drvo) {
    if (drvo == NULL) return 0;

    int levi = vrednost(drvo->levi);
    int desni = vrednost(drvo->desni);

    if (daLiJeOperator(drvo->sadrzaj.oper)) {
        int vrednost = 0;

        switch (drvo->sadrzaj.oper) {
            case '+':
                vrednost = levi + desni;
                break;
            case '-':
                vrednost = levi - desni;
                break;
            case '*':
                vrednost = levi * desni;
                break;
            case '/':
                vrednost = levi / desni;
                break;
            default:
                break;
        }

        return vrednost;
    }

    return drvo->sadrzaj.broj;
}

void ispis(struct drvo *p) {
    if (p->levi && p->desni) {
        printf("(");
        ispis(p->levi);
        printf(" %c ", p->sadrzaj.oper);
        ispis(p->desni);
        printf(")");
    } else printf("%d", p->sadrzaj.broj);
}

void oslobodi_memoriju(Drvo *drvo) {
    if (drvo == NULL) return;

    oslobodi_memoriju(drvo->levi);
    oslobodi_memoriju(drvo->desni);

    free(drvo);
}

int main() {
    Drvo *izraz = kreirajStablo();
    ispis(izraz);

    printf("\nVrednost je %d\n", vrednost(izraz));
    oslobodi_memoriju(izraz);
    return 0;
}
