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
    
    /* Na pocetku nije aktivan zicani rezim,
     * a vreme je postavljeno na nulu */
    zicani = NEAKTIVAN;
    vreme.staro = NEAKTIVAN;
    
    /* OpenGL inicijalizacija; postavlja se boja
     * koja ce nadalje sluziti za ciscenje prozora;
     * ona se ujedno uzima za zadatu boju pozadine */
    glClearColor(PROZ_BOJA, PROZ_BOJA, PROZ_BOJA, PROZ_ALPHA);
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
    
    /* Odbacene osobine svetla koje osvetljuje scenu;
     * magicni brojevi boje opisivali su nesto poput
     * prirodne bele svetlosti, sto je podrazumevano
     * u OpenGL-u, tako da su fakticki suvisni, te je
     * jedino neophodno ukljucuti osvetljenje */
    /*GLfloat amb_svetlo[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat dif_svetlo[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat spek_svetlo[] = {1.0f, 1.0f, 1.0f, 1.0f};*/
    
    /* Postavljanje svojstava svetla */
    /*glLightfv(GL_LIGHT0, GL_AMBIENT, amb_svetlo);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_svetlo);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spek_svetlo);*/
    
    /* Odbaceno eksperimentisanje sa dodatnim
     * mogucnostima upravljanja osvetljenjem */
    /*GLfloat amb_scene[] = {0.0f, 0.1f, 0.1f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_scene);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);*/
}
