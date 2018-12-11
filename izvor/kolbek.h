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

/* Opis perspektive */
#define PERSP_UGAO 60
#define PERSP_BLIZ 1
#define PERSP_DALJ 100

/* Opis pogleda */
#define POGLED 0
#define NORM_X 0
#define NORM_Y 0
#define NORM_Z 1

/* Bafer sa stanjem tipki
 * izrazenim vrednoscu bitova,
 * pocevsi od najmanje tezine */
#define PRAZNO 0 /* sve nule */
#define NAPRED 1 /* jedinica */
#define NAZAD 2 /* 1 << 1 */
#define GORE 4 /* 1 << 2 */
#define DOLE 8 /* 1 << 3 */
#define LEVO 16 /* 1 << 4 */
#define DESNO 32 /* 1 << 5 */
#define RESET 64 /* 1 << 6 */
#define KRENI 128 /* 1 << 7 */
#define VRATI 256 /* 1 << 8 */
#define SKOK 512 /* 1 << 9 */
#define PAUZA 1024 /* 1 << 10 */

int tipke;

/* Struktura koja enkapsulira oko/kameru
 * sa javnim polozajem (x, y, z) */
extern struct oko oko;

/* Struktura koja enkapsulira kliker
 * sa centrom (x, y, z) i radijusom r */
extern struct kliker kliker;

/* Fja koja postavlja kolbek
 * i fja za fullscreen prikaz */
void postavi_kolbek(void);
void fullscreen(void);

/* Deklaracije kolbek funkcija */
void na_cekanje(void);
void na_tipku_dole(unsigned char, int, int);
void na_tipku_gore(unsigned char, int, int);
void na_prozor(int, int);
void na_prikaz(void);

#endif /* KOLBEK_H */
