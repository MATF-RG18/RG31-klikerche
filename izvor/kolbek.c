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

void na_tajmer(int id)
{
    /* Nema potrebe proveravati da li
     * je pozvan pravi tajmer, posto je
     * samo jedan i sam sebe poziva */
    /*if (id != TAJMER){
          return;
    }*/
    PONISTI(id);
    
    /* Svakim pozivom fje na tajmer
     * azurira se vremenski pomeraj;
     * iako se ocekuje da bude jednak
     * trajanju tajmera (VREME), ipak
     * valja preduprediti talasanje */
    popravi_vreme();
    
    /* Pauzirana igra znaci da se
     * nista ne desava na tajmer */
    if (tipke & PAUZA){
        return;
    }
    
    /* Kliker skace */
    if (tipke & SKOK){
        /* Kraj animacije skoka */
        if (kliker_skok() == SKOK_KRAJ){
            tipke &= ~SKOK;
        }
    }
    
    /* Resetovanje pogleda */
    if (tipke & RESET){
        /* Kraj animacije resetovanja */
        if (oko_reset() == RES_KRAJ){
            tipke &= ~RESET;
        }
    }
    
    /* Kliker se krece napred */
    if (tipke & KRENI){
        kliker_napred();
    }
    
    /* Kliker se krece nazad */
    if (tipke & VRATI){
        kliker_nazad();
    }
    
    /* Oko se priblizava */
    if (tipke & NAPRED){
        oko_napred();
    }
    
    /* Oko se udaljava */
    if (tipke & NAZAD){
        oko_nazad();
    }
    
    /* Oko se penje */
    if (tipke & GORE){
        oko_gore();
    }
    
    /* Oko se spusta */
    if (tipke & DOLE){
        oko_dole();
    }
    
    /* Kliker se okrece nalevo,
     * dakle oko ide desno, osim
     * u slucaju istovremenog
     * kretanja klikera unazad,
     * radi intuitivnijeg pravca */
    if (tipke & LEVO){
        if (tipke & VRATI){
            oko_levo();
        } else oko_desno();
    }
    
    /* Kliker se okrece nadesno,
     * dakle oko ide levo, osim
     * u slucaju istovremenog
     * kretanja klikera unazad,
     * radi intuitivnijeg pravca */
    if (tipke & DESNO){
        if (tipke & VRATI){
            oko_desno();
        } else oko_levo();
    }
    
    /* Osvezavanje prozora */
    glutPostRedisplay();
    
    /* Ponovno postavljanje tajmera */
    glutTimerFunc(VREME, na_tajmer, TAJMER);
}

void na_tipku_dole(unsigned char tipka, int x, int y)
{
    /* Zanemaruje se mesto klika */
    PONISTI(x);
    PONISTI(y);
    
    switch (tipka){
    case ESC:
        /* Prekid programa */
        exit(EXIT_SUCCESS);
    
    case SPACE:
        /* Kliker krece u skok, ali
         * samo ako je igra u toku */
        if (!(tipke & PAUZA)){
            tipke |= SKOK;
        }
        break;
    
    case 'a':
    case 'A':
        /* Kliker se okrece nalevo */
        tipke |= LEVO;
        break;
    
    case 'd':
    case 'D':
        /* Kliker se okrece nadesno */
        tipke |= DESNO;
        break;
    
    case 'e':
    case 'E':
        /* Oko se priblizava */
        tipke |= NAPRED;
        break;
    
    case 'f':
    case 'F':
        /* Promena rezima prikaza */
        fullscreen();
        break;
    
    case 'g':
    case 'G':
        /* Promena debag rezima;
         * AKT. u PAS. i obrnuto */
        debag = !debag;
        break;
    
    case 'k':
    case 'K':
        /* Cuvanje trenutne igre */
        sacuvaj_igru();
        break;
    
    case 'l':
    case 'L':
        /* Citanje sacuvane igre */
        ucitaj_igru();
        break;
    
    case 'p':
    case 'P':
        /* Pauzira se igra ili nastavlja
         * ako je prethodno pauzirana */
        tipke ^= PAUZA;
        
        /* Ponovo se postavlja tajmer ako
         * je igra nastavljena nakon pauze,
         * a usput se i resetuje vreme */
        if (!(tipke & PAUZA)){
            vreme.staro = glutGet(GLUT_ELAPSED_TIME);
            glutTimerFunc(TAJMER, na_tajmer, TAJMER);
        }
        
        /* Zaustavlja se animacija
         * ako je uopste u toku */
        tipke &= ~RESET;
        break;
    
    case 'q':
    case 'Q':
        /* Oko se udaljava */
        tipke |= NAZAD;
        break;
    
    case 'r':
    case 'R':
        /* Resetovanje pogleda, ali
         * samo ako je igra u toku */
        if (!(tipke & PAUZA)){
            tipke |= RESET;
        }
        break;
    
    case 's':
    case 'S':
        /* Kliker se krece nazad */
        tipke |= VRATI;
        break;
    
    case 'w':
    case 'W':
        /* Kliker se krece napred */
        tipke |= KRENI;
        break;
    
    case 'x':
    case 'X':
        /* Oko se spusta */
        tipke |= DOLE;
        break;
    
    case 'z':
    case 'Z':
        /* Oko se podize */
        tipke |= GORE;
        break;
    }
}

void na_tipku_gore(unsigned char tipka, int x, int y)
{
    /* Zanemaruje se mesto klika */
    PONISTI(x);
    PONISTI(y);
    
    switch (tipka){
    case ESC:
        /* Do prekida programa dolazi
         * po pritiskanju ESC tipke;
         * otpustanje nije bitno */
        break;
    
    case SPACE:
        /* Skok je uglavnom animacija;
         * otpustanje tipke nije bitno */
        break;
    
    case 'a':
    case 'A':
        /* Kliker se vise ne okrece nalevo */
        tipke &= ~LEVO;
        break;
    
    case 'd':
    case 'D':
        /* Kliker se vise ne okrece nadesno */
        tipke &= ~DESNO;
        break;
    
    case 'e':
    case 'E':
        /* Oko se vise ne priblizava */
        tipke &= ~NAPRED;
        break;
    
    case 'f':
    case 'F':
        /* Fullscreen je opcija tipa toggle;
         * otpustanje tipke nije bitno */
        break;
    
    case 'g':
    case 'G':
        /* Debag je opcija tipa toggle;
         * otpustanje tipke nije bitno */
        break;
    
    case 'k':
    case 'K':
        /* Cuvanje igre ima trenutni efekat;
         * otpustanje tipke nije bitno */
        break;
    
    case 'l':
    case 'L':
        /* Citanje igre ima trenutni efekat;
         * otpustanje tipke nije bitno */
        break;
    
    case 'p':
    case 'P':
        /* Pauza je opcija tipa toggle;
         * otpustanje tipke nije bitno */
        break;
    
    case 'q':
    case 'Q':
        /* Oko se vise ne udaljava */
        tipke &= ~NAZAD;
        break;
    
    case 'r':
    case 'R':
        /* Resetovanje pogleda je animacija;
         * otpustanje tipke nije bitno */
        break;
    
    case 's':
    case 'S':
        /* Kliker se vise ne krece nazad */
        tipke &= ~VRATI;
        break;
    
    case 'w':
    case 'W':
        /* Kliker se vise ne krece napred */
        tipke &= ~KRENI;
        break;
    
    case 'x':
    case 'X':
        /* Oko se vise ne spusta */
        tipke &= ~DOLE;
        break;
    
    case 'z':
    case 'Z':
        /* Oko se vise ne podize */
        tipke &= ~GORE;
        break;
    }
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
    
    /* Odbaceni polozaj tackastog svetla, posto
     * za igricu ovog tipa prirodnije izgleda
     * podrazumevano svetlo, koje podjednako
     * osvetljava svaki deo iscrtane scene */
    /*GLint svetlo_pol[] = {1, 1, 1, 0};
    glLightiv(GL_LIGHT0, GL_POSITION, svetlo_pol);*/
    
    /* Postavljanje staze tj. terena */
    postavi_stazu();
    
    /* Crtanje kugle odnosno klikera */
    postavi_kliker();
    
    /* Zamena bafera tj. prikaz slike na ekranu */
    glutSwapBuffers();
}
