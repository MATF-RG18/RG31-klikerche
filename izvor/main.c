#include "osnov.h"
#include "kolbek.h"
#include "oko.h"
#include "kliker.h"

int main(int argc, char** argv)
{
    // Pokretanje Gluta
    podesi_biblioteke(&argc, argv);
    
    // Pravljenje prozora
    napravi_prozor();
    
    // Postavljanje kolbek fja
    postavi_kolbek();
    
    // Postavljanje svetla
    postavi_svetlo();
    
    // Pravljenje oka/kamere
    napravi_oko();
    
    // Pravljenje klikera
    napravi_kliker();
    
    // Glavna petlja Gluta
    glutMainLoop();
    
    // Prekid programa
    exit(EXIT_SUCCESS);
}
