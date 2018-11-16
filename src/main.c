#include "osnov.h"
#include "oko.h"
#include "kliker.h"

// Struktura koja enkapsulira oko/kameru
// sa javnim koordinatama x, y, z
extern struct oko oko;

// Struktura koja enkapsulira klikerche
// sa javnim koord. centra i radijusom r
extern struct kliker kliker;

// Bafer sa stanjem tipki
// iskazanim vrednoscu bitova:
// NAPRED, NAZAD, GORE, DOLE,
// LEVO, DESNO, RESET
extern int tipke;

// Deklaracije kolbek funkcija
void na_cekanje(void);
void na_tipku_dole(unsigned char, int, int);
void na_tipku_gore(unsigned char, int, int);
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
    
    // Pravljenje klikera
    napravi_kliker();
    
    // Glavna petlja Gluta
    glutMainLoop();
    
    // Prekid programa
    exit(EXIT_SUCCESS);
}

void na_cekanje(void)
{
    // Resetovanje kamere
    if (tipke & RESET){
        if(resetuj_oko()){
            tipke &= ~RESET;
        }
    }
    
    // Oko se krece napred
    if (tipke & NAPRED){
        oko_napred();
    }
    
    // Oko se krece nazad
    if (tipke & NAZAD){
        oko_nazad();
    }
    
    // Oko se krece gore
    if (tipke & GORE){
        oko_gore();
    }
    
    // Oko se krece dole
    if (tipke & DOLE){
        oko_dole();
    }
    
    // Oko se krece levo
    if (tipke & LEVO){
        oko_levo();
    }
    
    // Oko se krece desno
    if (tipke & DESNO){
        oko_desno();
    }
    
    // Osvezavanje prozora
    glutPostRedisplay();
}

void na_tipku_dole(unsigned char tipka, int x, int y)
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
        tipke |= LEVO;
        break;
    
    case 'd':
    case 'D':
        // Oko se krece desno
        tipke |= DESNO;
        break;
    
    case 'e':
    case 'E':
        // Oko se krece napred
        tipke |= NAPRED;
        break;
    
    case 'q':
    case 'Q':
        // Oko se krece nazad
        tipke |= NAZAD;
        break;
    
    case 'r':
    case 'R':
        // Resetovanje oka/kamere
        tipke |= RESET;
        break;
    
    case 's':
    case 'S':
        // Oko se krece dole
        tipke |= DOLE;
        break;
    
    case 'w':
    case 'W':
        // Oko se krece gore
        tipke |= GORE;
        break;
    }
}

void na_tipku_gore(unsigned char tipka, int x, int y)
{
    // Zanemaruje se mesto klika
    PONISTI(x);
    PONISTI(y);
    
    switch (tipka){
    case ESC:
        // Prekid programa
        break;
    
    case 'a':
    case 'A':
        // Oko se vise ne krece levo
        tipke &= ~LEVO;
        break;
    
    case 'd':
    case 'D':
        // Oko se vise ne krece desno
        tipke &= ~DESNO;
        break;
    
    case 'e':
    case 'E':
        // Oko se vise ne krece napred
        tipke &= ~NAPRED;
        break;
    
    case 'q':
    case 'Q':
        // Oko se vise ne krece nazad
        tipke &= ~NAZAD;
        break;
    
    case 'r':
    case 'R':
        // Resetovanje oka/kamere
        // NEMA tipke &= ~RESET;
        // To radi glutIdleFunc
        break;
    
    case 's':
    case 'S':
        // Oko se vise ne krece dole
        tipke &= ~DOLE;
        break;
    
    case 'w':
    case 'W':
        // Oko se vise ne krece gore
        tipke &= ~GORE;
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
    gluLookAt( oko.x,    oko.y,    oko.z,   // polozaj kamere
              kliker.x, kliker.y, kliker.z, // centar pogleda
                 0,        0,        1);    // vektor normale
    
    // Crtanje kugle tj. klikercheta
    nacrtaj_kliker();
    
    // Zamena bafera tj. prikaz slike na ekranu
    glutSwapBuffers();
}
