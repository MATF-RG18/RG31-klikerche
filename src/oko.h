#ifndef OKO_H
#define OKO_H

#include <math.h>
#include <GL/glut.h>

// Struktura koja enkapsulira oko/kameru,
// predstavljeno sfernim koordinatama
struct oko{
    // Poluprecnik i promena
    GLdouble r, d_r;
    
    // Azimutni ugao i promena
    GLdouble phi, d_phi;
    
    // Polarni ugao i promena
    GLdouble theta, d_theta;
    
    // Dekartove koordinate
    GLdouble x, y, z;
} oko;

// Deklaracije fja za oko/kameru
void napravi_oko(void);
void popravi_oko(void);
void oko_levo(void);
void oko_desno(void);
void oko_gore(void);
void oko_dole(void);
void oko_napred(void);
void oko_nazad(void);

#endif // OKO_H
