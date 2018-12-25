#include "../include/kliker.h"

void napravi_kliker(void)
{
    /* Postavljanje centra sfere */
    klik.x = KLIK_CENT;
    klik.y = KLIK_CENT;
    klik.z = KLIK_CENT;
    
    /* Postavljanje parametra skoka */
    klik.s = UGAO_POC;
    
    /* Postavljanje ugla rotacije; nije
     * vazno u novom modelu kotrljanja */
    /*rot.u = UGAO_POC;*/
    
    /* Postavljanje matrice rotacije
     * na jedinicnu (identitet) */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetDoublev(GL_MODELVIEW_MATRIX, rot.mat);
}

void postavi_kliker(void)
{
    /* Refleksija materijala igracevog klikera;
     * magicni brojevi koji se po zelji mogu
     * menjati u cilju promene boje sfere; u
     * trenutnom obliku kliker je zelenkaste
     * boje nastale kombinacijom ambijentalne
     * i difuzne komponente, dok su mu glatkost
     * (shininess), presijavanje (specular),
     * i isijavanje (emmision) reda nula */
    GLfloat amb_ref[] = {0.3f, 0.7f, 0.3f, 1.0f};
    GLfloat dif_ref[] = {0.2f, 1.0f, 0.2f, 1.0f};
    
    /* Postavljanje svojstava klikera */
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb_ref);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_ref);
    
    /* Pomeranje u centar sfere */
    glTranslated(klik.x, klik.y, klik.z);
    
    /* Izracunavanje vektora rotacije;
     * premesteno u novom modelu kotrljanja */
    /*napravi_vektor();*/
    
    /* Rotacija radi realisticnijeg kretanja
     * klikera; zapravo simulacija kotrljanja;
     * u starom modelu izvodi se rotacijom oko
     * izracunatog vektora, a u novom mnozenjem
     * tekuce matrice tranformacije modela i
     * pogleda (modelview) sa izracunatom */
    /*glRotated(rot.u, rot.x, rot.y, ROT_Z);*/
    glMultMatrixd(rot.mat);
    
    /* Crtanje sfere inace, a ikosaedra
     * u ikosaedarskom (debag) rezimu */
    if (ikosaedar){
        glutSolidIcosahedron();
    } else {
        glutSolidSphere(KLIK_RAD, KLIK_PREC, KLIK_PREC);
    }
    
    /* Nema poziva glPushMatrix() i glPopMatrix()
     * posto je postavljanje klikera poslednja u nizu
     * transformacija, nakon koje se prozor cisti */
}

void kliker_napred(void)
{
    /* Pomeraj je projekcija vektora koji
     * razapinju centar oka i centar klikera
     * na xy ravan, tako da se starim koord.
     * klikera dodaje razlika vrednosti */
    double duzina = sqrt((klik.x - oko.x) * (klik.x - oko.x)
                    + (klik.y - oko.y) * (klik.y - oko.y))
                    * KLIK_POM / vreme.pom; /* normalizacija */
    klik.x += (klik.x - oko.x) / duzina;
    klik.y += (klik.y - oko.y) / duzina;
    
    /* Rotacija koja odgovara
     * kretanju unapred */
    /*rot_napred();*/
    kotrljaj(UNAPRED);
}

void kliker_nazad(void)
{
    /* Pomeraj je projekcija vektora koji
     * razapinju centar klikera i centar oka
     * na xy ravan, tako da se starim koord.
     * klikera dodaje razlika vrednosti */
    double duzina = sqrt((oko.x - klik.x) * (oko.x - klik.x)
                    + (oko.y - klik.y) * (oko.y - klik.y))
                    * KLIK_POM / vreme.pom; /* normalizacija */
    klik.x += (oko.x - klik.x) / duzina;
    klik.y += (oko.y - klik.y) / duzina;
    
    /* Rotacija koja odgovara
     * kretanju unazad */
    /*rot_nazad();*/
    kotrljaj(UNAZAD);
}

int kliker_skok(void)
{
    /* Cuva se povratna vrednost;
     * podrazumevano nije kraj skoka */
    int vracam = SKOK_NIJE;
    
    /* Povecavanje parametra skoka */
    klik.s += UGAO_PAR * vreme.pom;
    
    /* Ako je parametar dostigao maksimum,
     * resetuje se, sto oznacava kraj skoka */
    if (klik.s >= UGAO_EXT){
        klik.s = UGAO_POC;
        vracam = SKOK_KRAJ;
    }
    
    /* Skok se modeluje sinusoidnom funkcijom;
     * kao argument se forsira vrednost od nula
     * do pi, tako da sinus vraca vrednosti koje
     * rastu od nule do jedinice, a zatim opet
     * opadaju do nule; mnozenje sa ocekivanom
     * visinom skoka daje z koordinatu klikera */
    klik.z = SKOK_VIS * sin(klik.s * M_PI / UGAO_EXT);
    
    /* 0 ako nije kraj, 1 ako jeste */
    return vracam;
}

void napravi_vektor(void)
{
    /* Vektor oko kog kliker rotira normalan je
     * na vektore koje razapinju koordinate oka
     * (ox, oy, oz), centar klikera (kx, ky, kz)
     * i treca tacka cija je xy projekcija na istoj
     * pravoj kao projekcije prve dve tacke, kao
     * npr. (kx, ky, oz) za pravougli trougao;
     * racun se pojednostavljuje ako se visinske
     * koordinate postave na nule i jedinice, a
     * kliker translira u koordinatni pocetak, cime
     * se problem svodi na racunanje vektorskog
     * proizvoda (normalnog vektora) trojki kao
     * sto su (ox-kx, oy-ky, 0) za oko, (0, 0, 0)
     * za kliker i (0, 0, 1) za trecu tacku; taj
     * proizvod jednak je (oy-ky, kx-ox, 0), koji je
     * inace jednakog smera, ali suprotnog pravca od
     * vektora nadesno sintetickog modela kamere,
     * kako bi rotacija bila u odgovarajucem smeru */
    rot.x = oko.y - klik.y;
    rot.y = klik.x - oko.x;
}

/* Odbaceni model kotrljanja u kome se cuva
 * ugao rotacije; kako se rotacija obavljala
 * u odnosu na trenutni vektor nadesno, kliker
 * se okretao zajedno sa okom, sto mozda i nije
 * najocekivanije ponasanje kada se uzme u
 * obzir cinjenica da je u pitanju objekat koji
 * nema jasno izdvojeno nesto poput ociju, pa da
 * mora da "gleda" u pravcu kretanja */
/*void rot_napred(void)
{*/
    /* Kretanjem napred povecava
     * se ugao rotacije */
    /*rot.u += UGAO_PAR * vreme.pom;*/
    
    /* Popravka jer u = [-pi, pi) */
    /*if (rot.u >= UGAO_EXT){
        rot.u -= UGAO_POM;
    }*/
/*}*/

/* Druga funkcija starog modela kotrljanja */
/*void rot_nazad(void)
{*/
    /* Kretanjem nazad smanjuje
     * se ugao rotacije */
    /*rot.u -= UGAO_PAR * vreme.pom;*/
    
    /* Popravka jer u = [-pi, pi) */
    /*if (rot.u < -UGAO_EXT){
        rot.u += UGAO_POM;
    }*/
/*}*/

void kotrljaj(int smer)
{
    /* Odabir matrice transformacije modela
     * i pogleda kao trenutne; bez ovoga bi
     * doslo do problema ako se u toku kretanja
     * menja velicina prozora, jer u tom trenutku
     * postaje aktivna matrica projekcije */
    glMatrixMode(GL_MODELVIEW);
    
    /* Kopiranje tekuce matrice */
    glPushMatrix();
    
    /* Ucitavanje jedinicne matrice */
    glLoadIdentity();
    
    /* Izracunavanje vektora rotacije */
    napravi_vektor();
    
    /* Dodavanje nove rotacije oko izracunatog
     * vektora na sve prethodne sacuvane */
    rot.u = smer * UGAO_PAR * vreme.pom;
    glRotated(rot.u, rot.x, rot.y, ROT_Z);
    
    /* Mnozenje sacuvanom matricom rotacije,
     * cime se izvode zapamcene rotacije; ovime
     * novi model kotrljanja, uz cinjenicu da je
     * izracunavanje nezavisno od iscrtavanja,
     * cini kotrljanje klikera prirodnijim i
     * nezavisnim od polozaja kamere */
    glMultMatrixd(rot.mat);
    
    /* Cuvanje nove matrice rotacije */
    glGetDoublev(GL_MODELVIEW_MATRIX, rot.mat);
    
    /* Vracanje kopirane matrice */
    glPopMatrix();
}
