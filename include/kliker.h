#ifndef KLIKER_H
#define KLIKER_H

#include <GL/glut.h>
#include <math.h>
#include "osnov.h"
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
#define KLIK_POM 60
#define GLATKOST 100

/* Opis skoka i rotacije */
#define UGAO_POC 0
#define UGAO_EXT 180
#define UGAO_POM 360
#define UGAO_PAR 0.3
#define ROT_Z 0
#define SKOK_VIS 2.75
enum {SKOK_NIJE, SKOK_KRAJ};

/* Indikator debag rezima */
extern int debag;

/* Struktura koja enkapsulira
 * proteklo vreme u programu */
extern struct vreme vreme;

/* Struktura koja enkapsulira oko/kameru
 * sa javnim polozajem (x, y, z) */
extern struct oko oko;

/* Struktura koja enkapsulira kliker */
struct kliker{
    /* Koordinate centra */
    GLdouble x, y, z;
    
    /* Parametar skoka */
    GLdouble s;
} klik;

/* Struktura koja enkapsulira rotaciju */
struct rotacija{
    /* Ugao rotacije */
    GLdouble u;
    
    /* Vektor rotacije */
    GLdouble x, y;
} rot;

/* Deklaracije fja za kliker */
void napravi_kliker(void);
void postavi_kliker(void);
void kliker_napred(void);
void kliker_nazad(void);
int kliker_skok(void);
void napravi_vektor(void);
void rot_napred(void);
void rot_nazad(void);

#endif /* KLIKER_H */
