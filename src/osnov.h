#ifndef OSNOV_H
#define OSNOV_H

#include <math.h>
#include <GL/glut.h>

// Opis prozora
#define PROZ_DIM 500
#define PROZ_POL 100
#define APP_IME "Klikerche"

// Opis perspektive
#define PERSP_UGAO 60
#define PERSP_BLIZ 1
#define PERSP_DALJ 10

// Aski kod eskejp karaktera
#define ESC 27

// Makro za nekoriscene promenljive
#define PONISTI(x) (void)x

// Deklaracije kolbek funkcija
extern void na_tipku(unsigned char, int, int);
extern void na_prozor(int, int);
extern void na_prikaz(void);

// Deklaracije sablonskih funkcija
void podesi_biblioteke(int, char**);
void napravi_prozor(void);
void postavi_kolbek(void);
void postavi_svetlo(void);

#endif // OSNOV_H
