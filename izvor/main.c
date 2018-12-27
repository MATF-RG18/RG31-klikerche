#include "../include/main.h"

int main(int argc, char** argv)
{
    /* Pokretanje GLUT-a i osnovno
     * definisanje nacina prikaza */
    podesi_biblioteke(&argc, argv);
    
    /* Pravljenje i postavljanje osobina
     * glavnog prozora; sto ukljucuje i
     * inicijalizaciju vremena i poruka,
     * kao i postavljanje glavnog svetla */
    napravi_prozor();
    
    /* Postavljanje kolbek fja, koje
     * sluze za obradu dogadjaja, u skladu
     * sa cinjenicom da je OpenGL nosilac
     * event-driven programiranja */
    postavi_kolbek();
    
    /* Postavljanje funkcija vezanih za mis,
     * sto je u biti prosirenje kolbeka; ovde
     * sluzi da uvede paralelne komande misa
     * preko vec uvedenih komandi tastature */
    postavi_mis();
    
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
    
    /* Prekid odnosno kraj programa */
    exit(EXIT_SUCCESS);
}
