#include "../include/prikaz.h"

void na_prozor(int sirina, int visina)
{
    /* Sprecavanje da prozor postane vertikalno
     * deformisan u odnosu na pocetni kvadrat;
     * visina veca od sirine postaje iste
     * duzine kao i sirina prozora */
    if (visina > sirina){
        glutReshapeWindow(sirina, sirina);
        return;
    
    /* Sprecavanje da sirina, a samim tim i ceo
     * prozor bude manji od pocetnog kvadrata;
     * i sirina i visina postaju pocetne duzine */
    } else if (sirina < PROZ_DIM){
        glutReshapeWindow(PROZ_DIM, PROZ_DIM);
        return;
    
    /* Popravka visine, za slucaj da je ona manja
     * od minimalne dimenzije, a sirina nije;
     * visina postaje pocetne duzine */
    } else if (visina < PROZ_DIM){
        glutReshapeWindow(sirina, PROZ_DIM);
        return;
    }
    
    /* Postavljanje oblasti prikaza;
     * ona se krece od koord. (0, 0)
     * prozora do (sirina, visina) */
    glViewport(POGLED, POGLED, sirina, visina);
    
    /* Podesavanje perpektive: ugao pogleda,
     * odnos oblasti prikaza (aspect ratio),
     * prednja i zadnja ravan odsecanja */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(PERSP_UGAO, (float)sirina/visina,
                   PERSP_BLIZ, PERSP_DALJ);
    
    /* Odbaceni pokusaj podesavanja perspektive
     * preko fje glFrustum(); prozor slobodno
     * menja velicinu, a ova fja nije otporna
     * na to posto ne razmatra aspect ratio */
    /*glFrustum(-0.75, 0.75, -0.75, 0.75,
              PERSP_BLIZ, PERSP_DALJ);*/
}

void na_prikaz(void)
{
    /* Ciscenje prozora: ciscenje bafera boje i dubine;
     * prothodni sadrzaj prozora brise se tako sto se boja
     * svih piksela postavlja na zadatu boju pozadine */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Postavljanje matrice transformacije;
     * ucitava se jedinicna matrica koja se
     * kasnije mnozi matricama odgovarajucih
     * geometrijskih transformacija */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    /* Ukoliko igra nije u toku, oko tj.
     * kamera se blago okrece nadesno */
    if (stanje != U_TOKU &&
        stanje != GAME_OVER){
        oko_desno();
    }
    
    /* Izracunavanje pozicije oka; ukoliko
     * nije neuspesan kraj igre, racuna se
     * klasicno; u suprotnom, postavlja se
     * iznad klikera koji pada u ambis */
    if (stanje != GAME_OVER){
        popravi_oko();
    } else if (oko.iznad) {
        oko_iznad();
    }
    
    /* Vidni parametri; scena se tranformise tako
     * da se oko nadje ispred, a kliker na centru
     * scene, cime se simulira sinteticka kamera */
    gluLookAt( oko.x,  oko.y,  oko.z,  /* polozaj kamere */
              klik.x, klik.y, klik.z,  /* centar pogleda */
              norm.x, norm.y, norm.z); /* vektor normale */
    
    /* Odbaceni pokusaj ukljucivanja fiksiranog
     * pogleda koji simulira pticju perspektivu koja
     * lici na kosu ili aksonometrijsku projekciju,
     * a bio bi postavljen na tipku 'o'; ipak, rezultat
     * je bio vise nego zanimljiv, tako da su vidni
     * parametri zakomentarisani, a celoj situaciji
     * posvecen je bonus gif iz pete sedmice */
    /*gluLookAt( 20,     20,     20, 
                -15,      8,      2,
                NORM_X, NORM_Y, NORM_Z);*/
    
    /* Postavljanje dva usmerena tj, direkciona
     * svetla, koja poput svojevrsnih sunaca odnosno
     * jakih reflektora obasjavaju scenu */
    GLint svetlo_pol[] = {S_X, S_Y, S_Z, S_A};
    glLightiv(GL_LIGHT0, GL_POSITION, svetlo_pol);
    svetlo_pol[0] = S_Y; svetlo_pol[1] = S_X;
    glLightiv(GL_LIGHT1, GL_POSITION, svetlo_pol);
    
    /* Postavljanje scene i staze */
    postavi_scenu();
    
    /* Crtanje kugle odnosno klikera */
    postavi_kliker();
    
    /* Ispis aktivnih poruka na ekran */
    ispisi_poruke();
    
    /* Zamena bafera tj. prikaz novonacrtane
     * slike na ekranu umesto prethodne */
    glutSwapBuffers();
}
