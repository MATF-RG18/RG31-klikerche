#ifndef KOLBEK_H
#define KOLBEK_H

#include <GL/glut.h>
#include "osnov.h"
#include "oko.h"
#include "kliker.h"

// Aski kod eskejp karaktera
#define ESC 27

// Makro za nekoriscene promenljive
#define PONISTI(x) (void)x

// Opis perspektive
#define PERSP_UGAO 60
#define PERSP_BLIZ 1
#define PERSP_DALJ 100

// Opis pogleda
#define POGLED 0
#define NORM_X 0
#define NORM_Y 0
#define NORM_Z 1

/* Bafer sa stanjem tipki
   izrazenim vrednoscu bitova,
   pocevsi od najmanje tezine */
#define PRAZNO 0
#define NAPRED 1
#define NAZAD 1<<1
#define GORE 1<<2
#define DOLE 1<<3
#define LEVO 1<<4
#define DESNO 1<<5
#define RESET 1<<6
#define KRENI 1<<7
#define VRATI 1<<8

int tipke;

/* Struktura koja enkapsulira oko/kameru
   sa javnim koordinatama x, y, z */
extern struct oko oko;

/* Struktura koja enkapsulira kliker
   sa centrom x, y, z i radijusom r */
extern struct kliker kliker;

// Deklaracije kolbek funkcija
void postavi_kolbek(void);
void na_cekanje(void);
void na_tipku_dole(unsigned char, int, int);
void na_tipku_gore(unsigned char, int, int);
void na_prozor(int, int);
void na_prikaz(void);

#endif // KOLBEK_H
