#ifndef OSNOV_H
#define OSNOV_H

#include <GL/glut.h>
#include <stdio.h>
#include "oko.h"
#include "kliker.h"

/* Opis prozora */
#define PROZ_DIM 550
#define PROZ_POL 50
#define PROZ_BOJA 0.05
#define PROZ_ALPH 0
#define APP_IME "Klikerche"

/* Ime sacuvane igre */
#define SAVEGAME "savegame.txt"

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

/* Zastavica fullscreen
 * i debag rezima */
enum {PASIVAN, AKTIVAN};
int fulskrin;
int debag;

/* Liste za iscrtavanje staze */
#define STAZA 1
GLuint staza1, staza2;

/* Struktura koja enkapsulira
 * proteklo vreme u programu */
#define POM_MAX 200
struct vreme{
    int staro;
    int novo;
    int pom;
} vreme;

/* Deklaracije osnovnih fja */
void podesi_biblioteke(int*, char**);
void napravi_prozor(void);
void postavi_svetlo(void);
void napravi_stazu(void);
void postavi_stazu(void);

/* Deklaracije funkcija koje
 * pozicaju kolbek funkcije */
void fullscreen(void);
void popravi_vreme(void);
void sacuvaj_igru(void);
void ucitaj_igru(void);

#endif /* OSNOV_H */
