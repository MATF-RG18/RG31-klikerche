#ifndef STAZA_H
#define STAZA_H

#include "main.h"

/* Teksture staze */
#define STAZA_TEKST "ostalo/sanduk.png"
#define STAZA_KRAJ "ostalo/kraj.png"

/* Struktura koja enkapsulira
 * stazu i njeno iscrtavanje */
struct staza{
    /* Lista za iscrtavanje */
    GLuint lista;
    
    /* Tekstura sanduka */
    GLuint tekst;
    
    /* Tekstura za kraj */
    GLuint kraj;
} staza;

/* Deklaracije fja za stazu */
void napravi_stazu(void);
void napravi_plocicu(void);
void postavi_stazu(void);

#endif /* STAZA_H */
