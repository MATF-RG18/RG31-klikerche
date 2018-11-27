#ifndef OSNOV_H
#define OSNOV_H

#include <GL/glut.h>

// Opis prozora
#define PROZ_DIM 500
#define PROZ_POL 100
#define PROZ_BOJA 0.05
#define PROZ_ALPH 0
#define APP_IME "Klikerche"

// Opis osvetljenja
#define GLATKOST 100

// Deklaracije osnovnih fja
void podesi_biblioteke(int*, char**);
void napravi_prozor(void);
void postavi_svetlo(void);
void postavi_stazu(void);

#endif // OSNOV_H
