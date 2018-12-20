#ifndef OSNOV_H
#define OSNOV_H

#include "main.h"

/* Opis prozora */
#define PROZ_DIM 550
#define PROZ_POL 50
#define PROZ_BOJA 0.05
#define PROZ_ALPHA 0
#define APP_IME "Klikerche"

/* Zastavica zicanog rezima */
enum {NEAKTIVAN, AKTIVAN};
int zicani;

/* Deklaracije osnovnih fja */
void podesi_biblioteke(int*, char**);
void napravi_prozor(void);
void postavi_kolbek(void);
void postavi_svetlo(void);

#endif /* OSNOV_H */
