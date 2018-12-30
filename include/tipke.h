#ifndef TIPKE_H
#define TIPKE_H

#include "main.h"

/* Makro za nekoriscene promenljive */
#define PONISTI(x) (void)x

/* Nealfanumericki aski kodovi */
#define ESC 27 /* eskejp za prekid */
#define SPACE 32 /* spejs za skok */

/* Bafer sa stanjem tipki
 * izrazenim vrednoscu bitova,
 * pocevsi od najmanje tezine */
#define PRAZNO 0 /* sve nule */
#define NAPRED 1 /* jedinica */
#define NAZAD 2 /* 1 << 1 */
#define NAGORE 4 /* 1 << 2 */
#define NADOLE 8 /* 1 << 3 */
#define LEVO 16 /* 1 << 4 */
#define DESNO 32 /* 1 << 5 */
#define RESET 64 /* 1 << 6 */
#define KRENI 128 /* 1 << 7 */
#define VRATI 256 /* 1 << 8 */
/*#define SKOK 512*/ /* 1 << 9 */
/*#define PAUZA 1024*/ /* 1 << 10 */

int tipke;

/* Indikator da li je tipka
 * pritisnuta ili pustena */
enum {DOLE, GORE};

/* Deklaracije kolbek funkcija
 * na dogadjaje tastature */
void na_tipku(unsigned char, int);
void na_tipku_dole(unsigned char, int, int);
void na_tipku_gore(unsigned char, int, int);

#endif /* TIPKE.H */
