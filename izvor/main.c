#include "../include/main.h"

int main(int argc, char** argv)
{
    /* Pokretanje GLUT-a i osnovno
     * definisanje nacina prikaza */
    podesi_biblioteke(&argc, argv);
    
    /* Pravljenje i postavljanje
     * osobina glavnog prozora */
    napravi_prozor();
    
    /* Postavljanje kolbek fja, koje
     * sluze za obradu dogadjaja, u skladu
     * sa cinjenicom da je OpenGL nosilac
     * event-driven programiranja */
    postavi_kolbek();
    
    /* Postavljanje svetala, u konkretnom
     * slucaju samo jednog i to prirodnog,
     * koje osvetljuje celu scenu */
    postavi_svetlo();
    
    /* Pravljenje oka/kamere; inicijalizacija
     * koja imitira konstruktor u oop */
    napravi_oko();
    
    /* Pravljenje klikera; inicijalizacija
     * koja imitira konstruktor u oop */
    napravi_kliker();
    
    /* Pravljenje staze; postavljanje koda
     * koji generise stazu u listu */
    napravi_stazu();
    
    /* Pokretanje glavne petlje GLUT-a,
     * koja osluskuje dogadjaje */
    glutMainLoop();
    
    /* Kraj programa */
    exit(EXIT_SUCCESS);
}
