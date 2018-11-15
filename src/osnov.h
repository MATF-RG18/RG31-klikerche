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

// Bafer sa stanjem tipki
// izrazenim sa sest bitova:
// prvi = napred, drugi = nazad,
// treci = gore, cetvrti = dole,
// peti = levo, sesti = desno
#define NAPRED 1
#define NAZAD 2
#define GORE 4
#define DOLE 8
#define LEVO 16
#define DESNO 32

int tipke;

// Deklaracije kolbek funkcija
extern void na_cekanje(void);
extern void na_tipku_dole(unsigned char, int, int);
extern void na_tipku_gore(unsigned char, int, int);
extern void na_prozor(int, int);
extern void na_prikaz(void);

// Deklaracije sablonskih funkcija
void podesi_biblioteke(int, char**);
void napravi_prozor(void);
void postavi_kolbek(void);
void postavi_svetlo(void);

#endif // OSNOV_H
