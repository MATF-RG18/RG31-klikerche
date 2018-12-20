#ifndef VREME_H
#define VREME_H

#include "main.h"

/* Opis tajmera */
#define TAJMER 0
#define VREME 35

/* Struktura koja enkapsulira proteklo
 * vreme u programu; tip int obicno ima
 * cetiri bajta, sto je dovoljno da
 * program bez prekoracenja radi skoro
 * pa punih dvadeset i pet dana */
#define POM_MAX 75
struct vreme{
    int staro;
    int novo;
    int pom;
} vreme;

/* Deklaracija tajmera */
void na_tajmer(int);
void popravi_vreme(void);

#endif /* VREME.H */
