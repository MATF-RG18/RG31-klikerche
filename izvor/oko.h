#ifndef OKO_H
#define OKO_H

#include <GL/glut.h>
#include <math.h>
#include "kliker.h"

/* Opis kamere */
/* Pocetni sferni parametri */
#define OKO_RAD 15
#define OKO_PHI 0
#define OKO_THETA 0.52359877559829887308 /* M_PI/6 */

/* Promena parametara */
#define OKO_RAD_D 0.03
#define OKO_PHI_D 0.0069813170079773183077 /* M_PI/450 */
#define OKO_THETA_D 0.0069813170079773183077 /* M_PI/450 */

/* Minimum parametara */
#define OKO_RAD_MIN 5
#define OKO_PHI_MIN -3.14159265358979323846 /* -M_PI */
#define OKO_THETA_MIN 0

/* Maksimum parametara */
#define OKO_RAD_MAX 20
#define OKO_PHI_MAX 3.14159265358979323846 /* M_PI */
#define OKO_THETA_MAX 1.5638150097869193009 /* M_PI/2-M_PI/450 */

/* Pun krug za azimut */
#define OKO_PHI_POM 6.2831853071795864769 /* 2*M_PI */

/* Pocetne razlike */
#define RAZ_POC 0

/* Enumeracija za resetovanje */
enum {RES_NIJE, RES_KRAJ};

/* Struktura koja enkapsulira kliker
 * sa centrom (x, y, z) i radijusom r */
extern struct kliker kliker;

/* Struktura koja enkapsulira oko/kameru,
 * predstavljeno sfernim koordinatama */
struct oko{
    /* Poluprecnik */
    GLdouble r;
    
    /* Azimutni ugao */
    GLdouble phi;
    
    /* Polarni ugao */
    GLdouble theta;
    
    /* Dekartove koordinate,
     * tzv. tacka pogleda */
    GLdouble x, y, z;
} oko;

/* Struktura koja enkapsulira razlike
 * izmedju pocetnog i trenutnog stanja oka */
struct razlika{
    int r, phi, theta;
} razlika;

/* Deklaracije fja za oko/kameru */
void napravi_oko(void);
void popravi_oko(void);
int oko_reset(void);
void oko_levo(void);
void oko_desno(void);
void oko_gore(void);
void oko_dole(void);
void oko_napred(void);
void oko_nazad(void);

#endif /* OKO_H */
