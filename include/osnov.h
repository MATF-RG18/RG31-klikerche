#ifndef OSNOV_H
#define OSNOV_H

#include "main.h"

/* Makroi za minimum i maksimum
 * uporedivih/brojevnih vrednosti */
#define MINIM(A, B) (((A) < (B)) ? (A) : (B))
#define MAXIM(A, B) (((A) > (B)) ? (A) : (B))

/* Opis prozora */
#define PROZ_DIM 512
#define PROZ_POL 50
#define PROZ_BOJA 0.05
#define PROZ_ALPHA 0

/* Ime aplikacije */
#define APP_IME "Klikerche"

/* Enumeracija aktivnosti i zastavica
 * odbacenog ikosaedarskog rezima */
enum {NEAKTIVNO, AKTIVNO};
/*int ikosaedar;*/

/* Deklaracije osnovnih fja */
void podesi_biblioteke(int*, char**);
void napravi_prozor(void);
void postavi_kolbek(void);
void postavi_svetlo(void);
void napusti_igru(void);

#endif /* OSNOV_H */
