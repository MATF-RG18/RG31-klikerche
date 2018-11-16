#ifndef OKO_H
#define OKO_H

#include <math.h>
#include <GL/glut.h>

// Opis kamere
#define OKO_RAD 5
#define OKO_PHI 0
#define OKO_THETA M_PI/6

#define OKO_RAD_R 0.03
#define OKO_PHI_R M_PI/450
#define OKO_THETA_R M_PI/450

#define OKO_RAD_MIN 2
#define OKO_PHI_MIN -M_PI
#define OKO_THETA_MIN 0

#define OKO_RAD_MAX 10
#define OKO_PHI_MAX M_PI
#define OKO_THETA_MAX M_PI/2

#define OKO_PHI_POM 2*M_PI

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
int resetuj_oko(void);
void oko_levo(void);
void oko_desno(void);
void oko_gore(void);
void oko_dole(void);
void oko_napred(void);
void oko_nazad(void);

#endif // OKO_H
