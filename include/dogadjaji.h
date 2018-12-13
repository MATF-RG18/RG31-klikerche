#ifndef DOGADJAJI_H
#define DOGADJAJI_H

#include "main.h"

/* Nealfanumericki aski kodovi */
#define ESC 27 /* eskejp za prekid */
#define SPACE 32 /* spejs za skok */

/* Deklaracije kolbek funkcija
 * na dogadjaje tastature */
void na_tipku_dole(unsigned char, int, int);
void na_tipku_gore(unsigned char, int, int);

#endif /* DOGADJAJI.H */
