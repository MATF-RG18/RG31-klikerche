#include "../include/kolbek.h"

void postavi_kolbek(void)
{
    /* Funkcija na tajmer tempirano obradjuje
     * oslusane dogadjaje; ovde proverava stanje
     * bafera tipki, te izracunava i animira sta
     * treba, sto omogucava glatkost i uskladjenost
     * pokreta; zakomentarisana je odbacena upotreba
     * fje na cekanje u te svrhe, posto kod nje ne
     * postoji kontrola pozivanja kao kao tajmera */
    /*glutIdleFunc(na_cekanje);*/
    glutTimerFunc(TAJMER, na_tajmer, TAJMER);
    
    /* Funkcija na tipku dole prima podatke
     * o pritisnutim tipkama tastature i tu
     * informaciju ubacuje u bafer tipki */
    glutKeyboardFunc(na_tipku_dole);
    
    /* Funkcija na tipku gore prima podatke
     * o otpustenim tipkama tastature i njih
     * izbacuje iz bafera tipki */
    glutKeyboardUpFunc(na_tipku_gore);
    
    /* Funkcija na prozor postavlja pogled
     * na scenu, kao i detalje projektivnog
     * preslikavanja koje cini taj pogled,
     * cime usput resava i problem promene
     * dimenzije tj. skaliranja prozora */
    glutReshapeFunc(na_prozor);
    
    /* Funkcija na prikaz jeste glavna fja
     * koja upravlja izgledom scene; ovde u
     * svakom osvezavanju nanovo postavlja
     * oko, loptu, stazu, prepreke */
    glutDisplayFunc(na_prikaz);
    
    /* Na pocetku nema pritisnutih tipki */
    tipke = PRAZNO;
}

void na_prozor(int sirina, int visina)
{
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
     * na to posto ne gleda aspect ratio */
    /*glFrustum(-0.75, 0.75, -0.75, 0.75,
              PERSP_BLIZ, PERSP_DALJ);*/
}

void na_prikaz(void)
{
    /* Osvezavanje prozora:
     * ciscenje bafera boje i dubine */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Postavljanje matrice transformacije */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    /* Izracunavanje pozicije oka, te
     * postavljanje vidnih parametara */
    popravi_oko();
    gluLookAt( oko.x,    oko.y,    oko.z,   /* polozaj kamere */
               klik.x,   klik.y,   klik.z,  /* centar pogleda */
               NORM_X,   NORM_Y,   NORM_Z); /* vektor normale */
    
    /* Odbaceni pokusaj ukljucivanja fiksiranog
     * pogleda koji simulira pticju perspektivu koja
     * lici na kosu ili aksonometrijsku projekciju,
     * a bio bi postavljen na tipku "o"; ipak, rezultat
     * je bio vise nego zanimljiv, tako da su vidni
     * parametri zakomentarisani, a celoj situaciji
     * posvecen je bonus gif iz pete sedmice */
    /*gluLookAt(  20,     20,     20, 
               -15,      8,      2,
              NORM_X, NORM_Y, NORM_Z);*/
    
    /* Odbaceni polozaji postavljanje tackastog,
     * a zatim i direkcionog svetla, posto za
     * igricu ovog tipa ipak prirodnije izgleda
     * podrazumevano svetlo, koje podjednako
     * osvetljava svaki deo prikazane scene */
    /*GLint svetlo_pol[] = {1, 1, 1, 0};
    glLightiv(GL_LIGHT0, GL_POSITION, svetlo_pol);*/
    
    /* Postavljanje staze tj. terena */
    postavi_stazu();
    
    /* Crtanje kugle odnosno klikera */
    postavi_kliker();
    
    /* Zamena bafera tj. prikaz slike na ekranu */
    glutSwapBuffers();
}
