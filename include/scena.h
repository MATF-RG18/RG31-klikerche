#ifndef SCENA_H
#define SCENA_H

#include "main.h"

/* Teksture scene */
#define SCENA_POZT "ostalo/pozadina.png"
#define SCENA_ZAKL "ostalo/plavetnilo.png"
#define STAZA_TEKST "ostalo/sanduk.png"
#define STAZA_KRAJ "ostalo/kraj.png"

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
    
    /* Tekstura sanduka */
    GLuint staza;
    
    /* Tekstura za kraj */
    GLuint kraj;
} scena;

/* Deklaracije fja za stazu */
void napravi_scenu(void);
void napravi_pozadinu(void);
void napravi_stazu(void);
void napravi_plocicu(void);
void postavi_scenu(void);

#endif /* SCENA_H */
