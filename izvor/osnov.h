#ifndef OSNOV_H
#define OSNOV_H

#include <GL/glut.h>

/* Opis prozora */
#define PROZ_DIM 550
#define PROZ_POL 50
#define PROZ_BOJA 0.05
#define PROZ_ALPH 0
#define APP_IME "Klikerche"

/* Indikator fullscreen prikaza */
#define SCREEN_FULL 1
int full_screen;

/* Lista za iscrtavanje staze */
#define STAZA 1
GLuint staza;

/* Deklaracije osnovnih fja */
void podesi_biblioteke(int*, char**);
void napravi_prozor(void);
void postavi_svetlo(void);
void napravi_stazu(void);
void postavi_stazu(void);

#endif /* OSNOV_H */
