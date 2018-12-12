#ifndef KOLBEK_H
#define KOLBEK_H

#include <GL/glut.h>
#include "osnov.h"
#include "oko.h"
#include "kliker.h"

/* Nealfanumericki aski kodovi */
#define ESC 27 /* eskejp za prekid */
#define SPACE 32 /* spejs za skok */

/* Makro za nekoriscene promenljive */
#define PONISTI(x) (void)x

/* Opis tajmera */
#define TAJMER 0
#define VREME 50

/* Opis perspektive */
#define PERSP_UGAO 60
#define PERSP_BLIZ 1
#define PERSP_DALJ 100

/* Opis pogleda */
#define POGLED 0
#define NORM_X 0
#define NORM_Y 0
#define NORM_Z 1

/* Bafer sa stanjem tipki */
extern int tipke;

/* Struktura koja enkapsulira oko/kameru
 * sa javnim polozajem (x, y, z) */
extern struct oko oko;

/* Struktura koja enkapsulira kliker
 * sa centrom (x, y, z) i radijusom r */
extern struct kliker kliker;

/* Deklaracije kolbek funkcija */
void postavi_kolbek(void);
void na_tajmer(int);
void na_tipku_dole(unsigned char, int, int);
void na_tipku_gore(unsigned char, int, int);
void na_prozor(int, int);
void na_prikaz(void);

#endif /* KOLBEK_H */
