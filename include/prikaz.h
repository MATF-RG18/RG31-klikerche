#ifndef PRIKAZ_H
#define PRIKAZ_H

#include "main.h"

/* Opis perspektive */
#define PERSP_UGAO 60
#define PERSP_BLIZ 1
#define PERSP_DALJ 100

/* Opis pogleda */
#define POGLED 0
#define NORM_X 0
#define NORM_Y 0
#define NORM_Z 1

/* Deklaracije fja prikaza */
void na_prozor(int, int);
void na_prikaz(void);

#endif /* PRIKAZ_H */
