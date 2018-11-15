#ifndef KLIKER_H
#define KLIKER_H

#include <math.h>
#include <GL/glut.h>

// Struktura koja enkapsulira klikerche
static struct kliker{
    // Koordinate centra
    GLdouble x, y, z;
    
    // Poluprecnik
    GLdouble r;
    
    // Preciznost
    GLdouble prec;
} kliker;

// Deklaracije fja za kliker
void napravi_kliker(void);
void nacrtaj_kliker(void);

#endif // KLIKER_H
