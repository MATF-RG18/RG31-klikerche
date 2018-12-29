#ifndef MISH_H
#define MISH_H

#include "main.h"

/* Definisanje smera srednjeg
 * tastera misa u slucaju da
 * vec nije definisan */
#ifndef GLUT_WHEEL_UP
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#endif

/* Struktura koja enkapsulira mis
 * predstavljen tekucim relativnim
 * koordinatama pokazivaca */
struct mis{
    int x;
    int y;
} mis;

/* Enumeracija koja opisuje
 * odrednice menija */
enum {RESETUJ, FULLSCREEN, /*IKOSAEDAR,*/
      SACUVAJ, UCITAJ, PAUZIRAJ, NAPUSTI};

/* Identifikator menija */
int meni;

/* Deklaracije fja za mis */
void postavi_mis(void);
void na_mis(int, int, int, int);
void na_pomeraj(int, int);

/* Deklaracije fja za meni */
void postavi_meni(void);
void na_meni(int);

#endif /* MISH_H */
