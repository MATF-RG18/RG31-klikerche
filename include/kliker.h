#ifndef KLIKER_H
#define KLIKER_H

#include "main.h"

/* ANSI standard zabranjuje standardnoj
 * biblioteci da optereti glavni imenski
 * prostor nerezervisanim imenima, tako
 * da M_PI iz <math.h> nije dostupan */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Opis klikera */
#define KLIK_CENT 0
#define KLIK_RAD 1
#define KLIK_PREC 22
#define KLIK_POM 60
#define KLIK_TEKST "ostalo/mermer.png"

/* Uglovi skoka i rotacije */
#define UGAO_POC 0
#define UGAO_EXT 180
/*#define UGAO_POM 360*/
#define UGAO_PAR 0.333333

/* Dodatni opis rotacije; posebna
 * enumeracija predstavlja znak ugla
 * to jest smer u kom se rotira */
#define MAT_DIM 16
#define ROT_Z 0
enum {UNAPRED = 1, UNAZAD = -1};

/* Struktura koja enkapsulira kliker */
struct kliker{
    /* Koordinate centra */
    GLdouble x, y, z;
    
    /* Koordinate na stazi */
    int sx, sy, sz;
    
    /* Trenutni pomeraj */
    GLdouble px, py;
    
    /* Tekstura mermera */
    GLuint tekst;
    
    /* GLU-ov quadric objekat */
    GLUquadricObj* obj;
    
    /* Parametar skoka */
    GLdouble s;
    
    /* Indikatori pada i visina
     * do koje treba pasti */
    int pad, kret;
    double padv;
} klik;

/* Struktura koja enkapsulira rotaciju */
struct rotacija{
    /* Ugao rotacije; vazan za
     * prvi model kotrljanja */
    /*GLdouble u;*/
    
    /* Vektor rotacije */
    GLdouble x, y;
    
    /* Matrica rotacije; vazna
     * za novi model kotrljanja */
    GLdouble mat[MAT_DIM];
} rot;

/* Deklaracije fja za kliker */
void napravi_kliker(void);
void postavi_kliker(void);
void kliker_napred(void);
void kliker_nazad(void);
void napravi_vektor(void);
/*void rot_napred(void);
void rot_nazad(void);*/
void kotrljaj(int);

#endif /* KLIKER_H */
