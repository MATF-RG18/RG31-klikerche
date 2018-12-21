#include "../include/kliker.h"

void napravi_kliker(void)
{
    /* Postavljanje centra sfere */
    klik.x = KLIK_CENT;
    klik.y = KLIK_CENT;
    klik.z = KLIK_CENT;
    
    /* Postavljanje parametra skoka */
    klik.s = UGAO_POC;
    
    /* Postavljanje ugla rotacije */
    rot.u = UGAO_POC;
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
    
    /* Izracunavanje vektora rotacije */
    napravi_vektor();
    
    /* Rotacija radi realisticnijeg kretanja
     * klikera; zapravo simulacija kotrljanja */
    glRotated(rot.u, rot.x, rot.y, ROT_Z);
    
    /* Crtanje popunjene sfere inace,
     * a zicane u zicanom rezimu */
    if (zicani){
        glutWireSphere(KLIK_RAD, KLIK_PREC, KLIK_PREC);
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
     * kretanju napred */
    rot_napred();
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
     * kretanju nazad */
    rot_nazad();
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
     * proizvod jednak je (oy-ky, kx-ox, 0) */
    rot.x = oko.y - klik.y;
    rot.y = klik.x - oko.x;
}

void rot_napred(void)
{
    /* Kretanjem napred povecava
     * se ugao rotacije */
    rot.u += UGAO_PAR * vreme.pom;
    
    /* Popravka jer u = [-pi, pi) */
    if (rot.u >= UGAO_EXT){
        rot.u -= UGAO_POM;
    }
}

void rot_nazad(void)
{
    /* Kretanjem nazad smanjuje
     * se ugao rotacije */
    rot.u -= UGAO_PAR * vreme.pom;
    
    /* Popravka jer u = [-pi, pi) */
    if (rot.u < -UGAO_EXT){
        rot.u += UGAO_POM;
    }
}
