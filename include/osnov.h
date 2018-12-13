#ifndef OSNOV_H
#define OSNOV_H

#include "main.h"

/* Opis prozora */
#define PROZ_DIM 550
#define PROZ_POL 50
#define PROZ_BOJA 0.05
#define PROZ_ALPH 0
#define APP_IME "Klikerche"

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
#define POM_MAX 75
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

#endif /* OSNOV_H */
