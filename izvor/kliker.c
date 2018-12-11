#include "kliker.h"

void napravi_kliker(void)
{
    /* Postavljanje centra sfere */
    kliker.x = KLIK_CENT;
    kliker.y = KLIK_CENT;
    kliker.z = KLIK_CENT;
    
    /* Postavljanje radijusa sfere */
    kliker.r = KLIK_RAD;
    
    /* Postavljanje parametra skoka */
    kliker.s = SKOK_MIN;
    
    /* Postavljanje ugla rotacije */
    rot.u = UGAO_POC;
}

void postavi_kliker(void)
{
    /* Ambijentalna, difuzna i spekularna
     * refleksija materijala igracevog klikera;
     * magicni brojevi koji se po zelji mogu
     * menjati u cilju promene boje sfere */
    GLfloat amb_ref[] = {0.3f, 0.7f, 0.3f, 1.0f};
    GLfloat dif_ref[] = {0.2f, 1.0f, 0.2f, 1.0f};
    GLfloat spek_ref[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    /* Postavljanje svojstava klikera */
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb_ref);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_ref);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spek_ref);
    glMateriali(GL_FRONT, GL_SHININESS, GLATKOST);
    
    /* Pomeranje u centar sfere */
    glTranslated(kliker.x, kliker.y, kliker.z);
    
    /* Izracunavanje vektora rotacije */
    napravi_vektor();
    
    /* Rotacija radi realisticnijeg kretanja
     * klikera; zapravo simulacija kotrljanja */
    glRotated(rot.u, rot.a, rot.b, rot.c);
    
    /* Crtanje zicane sfere */
    glutWireSphere(kliker.r, KLIK_PREC, KLIK_PREC);
    
    /* Nema poziva glPushMatrix() i glPushMatrix()
     * posto je postavljanje klikera poslednja u nizu
     * transformacija, nakon koje se prozor brise */
}

void kliker_napred(void)
{
    /* Pomeraj je projekcija vektora koji
     * razapinju centar oka i centar klikera
     * na xy ravan, tako da se starim koord.
     * klikera dodaje razlika vrednosti */
    float duzina = sqrt((kliker.x - oko.x) * (kliker.x - oko.x)
                 +  (kliker.y - oko.y) * (kliker.y - oko.y))
                 * POMERAJ; /* normalizacija pomeraja */
    kliker.x += (kliker.x - oko.x)/duzina;
    kliker.y += (kliker.y - oko.y)/duzina;
    
    /* Kretanjem napred povecava
     * se ugao rotacije */
    rot.u += UGAO_POM;
}

void kliker_nazad(void)
{
    /* Pomeraj je projekcija vektora koji
     * razapinju centar klikera i centar oka
     * na xy ravan, tako da se starim koord.
     * klikera dodaje razlika vrednosti */
    float duzina = sqrt((oko.x - kliker.x) * (oko.x - kliker.x)
                 +  (oko.y - kliker.y) * (oko.y - kliker.y))
                 * POMERAJ; /* normalizacija pomeraja */
    kliker.x += (oko.x - kliker.x)/duzina;
    kliker.y += (oko.y - kliker.y)/duzina;
    
    /* Kretanjem nazad smanjuje
     * se ugao rotacije */
    rot.u -= UGAO_POM;
}

int kliker_skok(void)
{
    /* Cuva se povratna vrednost;
     * podrazumevano nije kraj skoka */
    int vracam = SKOK_NIJE;
    
    /* Povecavanje parametra skoka */
    kliker.s++;
    
    /* Ako je parametar dostigao maksimum,
     * resetuje se, sto oznacava kraj skoka */
    if (kliker.s >= SKOK_MAX){
        kliker.s = SKOK_MIN;
        vracam = SKOK_KRAJ;
    }
    
    /* Skok se modeluje sinusoidnom funkcijom;
     * kao argument se forsira vrednost od nula
     * do pi, tako da sinus vraca vrednosti koje
     * rastu od nule do jedinice, a zatim opet
     * opadaju do nule; mnozenje sa ocekivanom
     * visinom skoka daje z koordinatu klikera */
    kliker.z = SKOK_VIS * sin(kliker.s * M_PI / SKOK_MAX);
    
    /* 0 ako nije kraj, 1 ako jeste */
    return vracam;
}

void napravi_vektor(void)
{
    /* Vektor oko kog kliker rotira zapravo je
     * normala ravni koju razapinju koordinate
     * oka (ox, oy, oz), centar klikera (kx, ky,
     * kz) i treca tacka poput (kx, ky, 5) */
    
    /* Trebalo bi da ga je lako pronaci pomocu
     * algoritma za odredjivanje ravni kroz tri
     * tacke, ali taj kod, usled malo vremena, ipak
     * ostaje za narednu sedmicu; trenutne dummy
     * vrednosti tacne su ukoliko se kliker krece
     * paralelno x osi, u negativnom smeru, sto znaci
     * napred ili nazad iz pocetne pozicije */
    rot.a = 0;
    rot.b = -1;
    rot.c = 0;
}
