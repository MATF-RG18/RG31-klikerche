#ifndef KLIKER_H
#define KLIKER_H

#include <math.h>
#include <GL/glut.h>

// Opis klikera
#define KLIK_CENT 0
#define KLIK_RAD 1
#define KLIK_PREC 22

// Struktura koja enkapsulira kliker
struct kliker{
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
