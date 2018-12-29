#ifndef PRIKAZ_H
#define PRIKAZ_H

#include "main.h"

/* Opis perspektive */
#define PERSP_UGAO 60
#define PERSP_BLIZ 1
#define PERSP_DALJ 100

/* Opis pogleda; pogled krece
 * od koordinatnog pocetka, a
 * normala je u sustini z osa */
#define POGLED 0
#define NORM_X 0
#define NORM_Y 0
#define NORM_Z 1

/* Opis svetla */
#define S_X 1
#define S_Y -1
#define S_Z 5
#define S_A 0

/* Deklaracije fja prikaza */
void na_prozor(int, int);
void na_prikaz(void);

#endif /* PRIKAZ_H */
