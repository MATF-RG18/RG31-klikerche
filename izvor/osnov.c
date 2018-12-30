#include "../include/osnov.h"

void podesi_biblioteke(int* argc, char** argv)
{
    /* Pokretanje GLUT-a; ovim pozivom se
     * inicijalizuje sve sto je neophodno kako
     * bi jedan graficki program mogao da radi */
    glutInit(argc, argv);
    
    /* Opis: RGB (crvena, zelena, plava) sistem
     * boja, bafer dubine za pravilno postavljanje
     * objekata, dva bafera scene zarad manjeg
     * seckanja prilikom postavljanja nove slike */
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
}

void napravi_prozor(void)
{
    /* Pravljenje prozora: postavljanje
     * dimenzija, polozaja i imena */
    glutInitWindowSize(PROZ_DIM, PROZ_DIM);
    glutInitWindowPosition(PROZ_POL, PROZ_POL);
    glutCreateWindow(APP_IME);
    
    /* Odbaceni pokusaj pravljenja prozora
     * preko GLUT-ove posebne fje za igre;
     * ipak se bolje cini da postoji mogucnost
     * odabira zeljenog: wdwd ili fscr */
    /*glutGameModeString("1366x768:32@60");
    if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)){
        glutEnterGameMode();
    }*/
    
    /* Ulazak u rezim prikaza preko celog ekrana */
    glutFullScreen();
    
    /* Stanje igre je pocetno */
    stanje = POCETAK;
    
    /* Inicijalizacija vremena */
    postavi_vreme();
    
    /* OpenGL inicijalizacija; postavlja se boja
     * koja ce nadalje sluziti za ciscenje prozora;
     * ona se ujedno uzima za zadatu boju pozadine */
    glClearColor(PROZ_BOJA, PROZ_BOJA, PROZ_BOJA, PROZ_ALPHA);
    
    /* Postavljanje svetala, u konkretnom
     * slucaju samo jednog, i to prirodnog,
     * koje osvetljuje celu scenu */
    postavi_svetlo();
}

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
     * oko, kliker, stazu, prepreke */
    glutDisplayFunc(na_prikaz);
    
    /* Na pocetku nema pritisnutih tipki */
    tipke = PRAZNO;
}

void postavi_svetlo(void)
{
    /* Ukljucivanje dubine */
    glEnable(GL_DEPTH_TEST);
    
    /* Ukljucivanje svetla */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    /* Osobine drugog svetla koje osvetljuje scenu;
     * magicni brojevi boje opisuju nesto poput prirodne
     * bele svetlosti, sto je podrazumevano u OpenGL-u,
     * ali samo za prvo/nulto svetlo, pa je za drugo
     * neophodno inicijalizovati nenulte vrednosti */
    GLfloat amb_svetlo[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat dif_svetlo[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat spek_svetlo[] = {0.8f, 0.8f, 0.8f, 1.0f};
    
    /* Postavljanje svojstava svetla */
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb_svetlo);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, dif_svetlo);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spek_svetlo);
    
    /* Odbaceno eksperimentisanje sa dodatnim
     * mogucnostima upravljanja osvetljenjem */
    /*GLfloat amb_scene[] = {0.0f, 0.1f, 0.1f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_scene);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);*/
    
    /* Ukljucivanje dvostranog sencenja */
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void zapocni_igru(void)
{
    /* Igra je sada u toku */
    stanje = U_TOKU;
    
    /* Postavljanje menija, koji sluzi da olaksa
     * upotrebu opcija koje nisu u vezi sa kretanjem
     * (osnovna interkativna komponenta igre), a koje su
     * podrazumevano dostupne preko tipki tastature,
     * posto iz korisnicke tacke gledista i nema mnogo
     * svrhe pamtiti koji taster sta radi */
    postavi_meni();
}

void restartuj_igru(void)
{
    /* Oslobadjanje resursa koji ce
     * ponovo biti inicijalizovani */
    glutDetachMenu(GLUT_RIGHT_BUTTON);
    glutDestroyMenu(meni);
    glDeleteTextures(AKTIVNO, &klik.tekst);
    gluDeleteQuadric(klik.obj);
    
    /* Stanje je pocetno, poruke o
     * cuvanju igre postaju nebitne,
     * a resetuje se i stoperica */
    stanje = POCETAK;
    por.poruka = NEAKTIVNO;
    stopw.starov = NEAKTIVNO;
    stopw.pocetak = vreme.novo;
    vreme.pauza = NEAKTIVNO;
    sprintf(stopw.niska, "00m:00s");
    
    /* Resetovanje parametara oka */
    napravi_oko();
    
    /* Resetovanje parametara klikera */
    napravi_kliker();
}

void napusti_igru(void)
{
    /* Brisanje liste za icrtavanje staze */
    glDeleteLists(scena.lista, AKTIVNO);
    
    /* Otklanjanje veze menija i desnog tastera
     * misa, kao i brisanje samog menija */
    glutDetachMenu(GLUT_RIGHT_BUTTON);
    glutDestroyMenu(meni);
    
    /* Datoteke u koje se upisuju i iz kojih se
     * citaju podaci zatvaraju se odmah po upotrebi */
    /*fclose(...);*/
    
    /* Brisanje quadric objekata, kako ne
     * bi doslo do curenja memorije */
    gluDeleteQuadric(scena.obj);
    gluDeleteQuadric(klik.obj);
    
    /* Oslobadjanje resursa koje koriste
     * napravljene teksture objekata */
    glDeleteTextures(AKTIVNO, &scena.pozt);
    glDeleteTextures(AKTIVNO, &scena.zaklop);
    glDeleteTextures(AKTIVNO, &scena.staza);
    glDeleteTextures(AKTIVNO, &scena.kraj);
    glDeleteTextures(AKTIVNO, &klik.tekst);
    
    /* Izlaz iz programa sa oslobadjanjem
     * ostalih alociranih resursa */
    exit(EXIT_SUCCESS);
}
