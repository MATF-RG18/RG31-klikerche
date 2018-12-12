#include "../include/osnov.h"
#include "../include/kolbek.h"
#include "../include/oko.h"
#include "../include/kliker.h"

int main(int argc, char** argv)
{
    /* Pokretanje GLUT-a */
    podesi_biblioteke(&argc, argv);
    
    /* Pravljenje prozora */
    napravi_prozor();
    
    /* Postavljanje kolbek fja */
    postavi_kolbek();
    
    /* Postavljanje svetla */
    postavi_svetlo();
    
    /* Pravljenje oka/kamere */
    napravi_oko();
    
    /* Pravljenje klikera */
    napravi_kliker();
    
    /* Pravljenje staze */
    napravi_stazu();
    
    /* Glavna petlja GLUT-a */
    glutMainLoop();
    
    /* Kraj programa */
    exit(EXIT_SUCCESS);
}
