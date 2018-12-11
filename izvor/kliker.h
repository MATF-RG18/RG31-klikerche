#ifndef KLIKER_H
#define KLIKER_H

#include <GL/glut.h>
#include <math.h>
#include "oko.h"

/* ANSI standard zabranjuje standardnoj
 * biblioteci da optereti glavni imenski
 * prostor nerezervisanim imenima, tako
 * da M_PI iz math.h nije dostupan */
#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif

/* Opis klikera */
#define KLIK_CENT 0
#define KLIK_RAD 1
#define KLIK_PREC 22
#define GLATKOST 100
#define POMERAJ 20

/* Opis skoka */
#define SKOK_MIN 0
#define SKOK_MAX 180
#define SKOK_VIS 2.5
enum {SKOK_NIJE, SKOK_KRAJ};

/* Opis rotacije */
#define UGAO_POC 0
#define UGAO_POM 0.4

/* Struktura koja enkapsulira oko/kameru
 * sa javnim polozajem (x, y, z) */
extern struct oko oko;

/* Struktura koja enkapsulira kliker */
struct kliker{
    /* Koordinate centra */
    GLdouble x, y, z;
    
    /* Poluprecnik */
    GLdouble r;
    
    /* Parametar skoka */
    int s;
} kliker;

/* Struktura koja enkapsulira rotaciju */
struct rotacija{
    /* Ugao rotacije */
    GLdouble u;
    
    /* Vektor rotacije */
    GLdouble a, b, c;
} rot;

/* Deklaracije fja za kliker */
void napravi_kliker(void);
void postavi_kliker(void);
void kliker_napred(void);
void kliker_nazad(void);
int kliker_skok(void);
void napravi_vektor(void);

#endif /* KLIKER_H */
