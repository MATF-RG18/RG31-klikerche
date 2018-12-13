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

/* Deklaracije kolbek funkcija
 * prikaza i fje koja postavlja
 * sve kolbek funkcije */
void postavi_kolbek(void);
void na_prozor(int, int);
void na_prikaz(void);

#endif /* KOLBEK_H */
