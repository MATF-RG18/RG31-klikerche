#ifndef SCENA_H
#define SCENA_H

#include "main.h"

/* Teksture scene */
#define SCENA_POZT "ostalo/pozadina.png"
#define SCENA_ZAKL "ostalo/zaklop.png"

/* Opis pozadine */
#define POZ_DIM 100
#define POZ_VIS 150
#define POZ_PREC 20

/* Struktura koja enkapsulira
 * scenu i njeno iscrtavanje */
struct scena{
    /* GLU-ov quadric objekat */
    GLUquadricObj* obj;
    
    /* Lista za iscrtavanje */
    GLuint lista;
    
    /* Tekstura pozadine */
    GLuint pozt;
    
    /* Tekstura zaklopa */
    GLuint zaklop;
} scena;

/* Deklaracije fja za scenu */
void napravi_scenu(void);
void napravi_pozadinu(void);
void postavi_scenu(void);

#endif /* SCENA_H */
