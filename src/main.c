#include "osnov.h"
#include "oko.h"
#include "kliker.h"

// Struktura koja enkapsulira oko/kameru
// sa javnim koordinatama x, y, z
extern struct oko oko;

// Struktura koja enkapsulira klikerche
// sa javnim koord. centra i radijusom r
extern struct kliker kliker;

// Deklaracije kolbek funkcija
void na_tipku(unsigned char, int, int);
void na_prozor(int, int);
void na_prikaz(void);

int main(int arg_br, char** arg_niz)
{
    // Pokretanje Gluta
    podesi_biblioteke(arg_br, arg_niz);
    
    // Pravljenje prozora
    napravi_prozor();
    
    // Postavljanje kolbek funkcija
    postavi_kolbek();
    
    // Postavljanje svetla i materijala
    postavi_svetlo();
    
    // Pravljenje oka/kamere
    napravi_oko();
    
    // Pravljenje klikercheta
    napravi_kliker();
    
    // Glavna petlja Gluta
    glutMainLoop();
    
    // Prekid programa
    exit(EXIT_SUCCESS);
}

void na_tipku(unsigned char tipka, int x, int y)
{
    // Zanemaruje se mesto klika
    PONISTI(x);
    PONISTI(y);
    
    switch (tipka){
    case ESC:
        // Prekid programa
        exit(EXIT_SUCCESS);
    
    case 'a':
    case 'A':
        // Oko se krece levo
        oko_levo();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'd':
    case 'D':
        // Oko se krece desno
        oko_desno();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'e':
    case 'E':
        // Oko se krece napred
        oko_napred();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'q':
    case 'Q':
        // Oko se krece nazad
        oko_nazad();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'r':
    case 'R':
        // Resetovanje oka/kamere
        napravi_oko();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 's':
    case 'S':
        // Oko se krece dole
        oko_dole();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'w':
    case 'W':
        // Oko se krece gore
        oko_gore();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    }
}

void na_prozor(int sirina, int visina)
{
    // Postavljanje pogleda
    glViewport(0, 0, sirina, visina);
    
    // Podesavanje projekcije
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(PERSP_UGAO, (float)sirina/visina,
                   PERSP_BLIZ, PERSP_DALJ);
}

void na_prikaz(void)
{
    // Osvezavanje prozora
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Postavljanje matrice transformacije
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Polozaj tackastog svetla i njegovo
    // postavljanje pre vidnih parametara,
    // kako bi ono pratilo kretanje kamere
    GLfloat svetlo_pol[] = {0, 0, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, svetlo_pol);
    
    // Postavljanje vidnih parametara
    popravi_oko();
    gluLookAt( oko.x,    oko.y,    oko.z,   // centar oka/kamere
              kliker.x, kliker.y, kliker.z, // centar pogleda
                 0,        0,        1);    // vektor normale
    
    // Crtanje kugle tj. klikercheta
    nacrtaj_kliker();
    
    // Zamena bafera tj. prikaz slike na ekranu
    glutSwapBuffers();
}
