#include "kolbek.h"

void postavi_kolbek(void)
{
    // Postavljanje kolbek funkcija
    
    /* Funkcija na cekanje obavlja poslove
       u pozadini, dok je program neaktivan
       iz tacke korisnika; ponasa se kao opsti,
       sve vreme aktivan tajmer; ovde proverava
       stanje bafera tipki, te izracunava i
       animira sta treba, sto omogucava glatkost
       i uskladjenost pokreta */
    glutIdleFunc(na_cekanje);
    
    /* Funkcija na tipku dole prima podatke
       o stisnutim tipkama tastature i tu
       informaciju ubacuje u bafer tipki */
    glutKeyboardFunc(na_tipku_dole);
    
    /* Funkcija na tipku gore prima podatke
       o otpustenim tipkama tastature i njih
       izbacuje iz bafera tipki */
    glutKeyboardUpFunc(na_tipku_gore);
    
    /* Funkcija na prozor postavlja pogled
       na scenu, kao i detalje projektivnog
       preslikavanja koje cini taj pogled,
       cime usput resava i problem promene
       dimenzije tj. skaliranja prozora */
    glutReshapeFunc(na_prozor);
    
    /* Funkcija na prikaz jeste glavna fja
       koja upravlja izgledom scene; ovde u
       svakom osvezavanju nanovo postavlja
       oko, loptu, stazu, prepreke */
    glutDisplayFunc(na_prikaz);
    
    // Na pocetku nista nije stisnuto
    tipke = PRAZNO;
}

void na_cekanje(void)
{
    // Resetovanje kamere
    if (tipke & RESET){
        // Kraj animacije resetovanja
        if (resetuj_oko() == RES_KRAJ){
            tipke &= ~RESET;
        }
    }
    
    // Kliker se krece napred
    if (tipke & KRENI){
        kliker_napred();
    }
    
    // Kliker se krece nazad
    if (tipke & VRATI){
        kliker_nazad();
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
    
    /* Kliker se okrece nalevo,
       dakle oko ide desno, osim
       u slucaju istovremenog
       kretanja klikera unazad,
       radi intuitivnijeg pravca */
    if (tipke & LEVO){
        if (tipke & VRATI){
            oko_levo();
        } else oko_desno();
    }
    
    /* Kliker se okrece nadesno,
       dakle oko ide levo, osim
       u slucaju istovremenog
       kretanja klikera unazad,
       radi intuitivnijeg pravca */
    if (tipke & DESNO){
        if (tipke & VRATI){
            oko_desno();
        } else oko_levo();
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
        // Kliker se okrece nalevo
        tipke |= LEVO;
        break;
    
    case 'd':
    case 'D':
        // Kliker se okrece nadesno
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
        // Kliker se krece nazad
        tipke |= VRATI;
        break;
    
    case 'w':
    case 'W':
        // Kliker se krece napred
        tipke |= KRENI;
        break;
    
    case 'x':
    case 'X':
        // Oko se krece dole
        tipke |= DOLE;
        break;
    
    case 'z':
    case 'Z':
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
        /* Inace prekid programa:
           nema exit(), jer ovo
           i ne moze da se desi */
        break;
    
    case 'a':
    case 'A':
        // Kliker se vise ne okrece nalevo
        tipke &= ~LEVO;
        break;
    
    case 'd':
    case 'D':
        // Kliker se vise ne okrece nadesno
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
        /* Resetovanje oka/kamere:
           nema tipke &= ~RESET,
           to radi glutIdleFunc */
        break;
    
    case 's':
    case 'S':
        // Kliker se vise ne krece nazad
        tipke &= ~VRATI;
        break;
    
    case 'w':
    case 'W':
        // Kliker se vise ne krece napred
        tipke &= ~KRENI;
        break;
    
    case 'x':
    case 'X':
        // Oko se vise ne krece dole
        tipke &= ~DOLE;
        break;
    
    case 'z':
    case 'Z':
        // Oko se vise ne krece gore
        tipke &= ~GORE;
        break;
    }
}

void na_prozor(int sirina, int visina)
{
    // Postavljanje pogleda
    glViewport(POGLED, POGLED, sirina, visina);
    
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
    
    /* Polozaj tackastog svetla i njegovo
       postavljanje pre vidnih parametara,
       kako bi ono pratilo kretanje kamere */
    GLint svetlo_pol[] = {0, 0, 0, 1};
    glLightiv(GL_LIGHT0, GL_POSITION, svetlo_pol);
    
    /* Izracunavanje pozicije oka, te
       postavljanje vidnih parametara */
    popravi_oko();
    gluLookAt( oko.x,    oko.y,    oko.z,   // polozaj kamere
              kliker.x, kliker.y, kliker.z, // centar pogleda
               NORM_X,   NORM_Y,   NORM_Z); // vektor normale
    
    // Postavljanje staze tj. terena
    postavi_stazu();
    
    // Crtanje kugle odnosno klikera
    postavi_kliker();
    
    // Zamena bafera tj. prikaz slike na ekranu
    glutSwapBuffers();
}
