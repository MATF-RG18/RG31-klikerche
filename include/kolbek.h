#ifndef KOLBEK_H
#define KOLBEK_H

#include "main.h"

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

/* Deklaracije kolbek funkcija
 * prikaza i fje koja postavlja
 * sve kolbek funkcije */
void postavi_kolbek(void);
void na_prozor(int, int);
void na_prikaz(void);

#endif /* KOLBEK_H */
