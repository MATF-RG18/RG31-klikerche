#ifndef TAJMER_H
#define TAJMER_H

#include "main.h"

/* Opis tajmera; ispitati trajanje
 * (VREME); renderovanje je glatko
 * samo ukoliko nema odlaganja novog
 * postavljanja tajmera, ali to onda
 * zahteva previse procesorskog rada,
 * te vrlo neodrzivih 1000 FPS (slika
 * po sekundi), plus bi bilo neophodno
 * dodati sinhronizaciju niti zbog
 * prebrzog azuriranja promenljivih */
#define TAJMER 0
#define VREME 35

/* Deklaracija tajmera */
void na_tajmer(int);

#endif /* TAJMER.H */
