#include "../include/kliker.h"

void napravi_kliker(void)
{
    /* Postavljanje centra sfere */
    klik.x = KLIK_CENT;
    klik.y = KLIK_CENT;
    klik.z = KLIK_CENT;
    
    /* Pravljenje teksture mermera; ona se pravi
     * pomocu biblioteke SOIL tako sto se ucitava
     * u podrazumevanom rezimu, a prave joj se novi
     * identifikator, kao i propratna mipmapa; ovime
     * SOIL postedjuje rukovanja sa redudantnim
     * fjama poput glGenTextures() i slicnim; sama
     * tekstura je stock slika sa interneta */
    klik.tekst = SOIL_load_OGL_texture(KLIK_TEKST,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    
    /* Iscrtavanje klikera resava se preko
     * GLU-ovog quadric objekta, posto on
     * ima ugradjenu podrsku za teksture;
     * pravi se novi quadric i sugerise mu
     * se da prihvati aktivnu teksturu */
    klik.obj = gluNewQuadric();
    gluQuadricTexture(klik.obj, GLU_TRUE);
    
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
     * trenutnom obliku kliker je sedefaste
     * boje nastale kombinacijom ambijentalne
     * i difuzne komponente, dok su mu glatkost
     * (shininess), presijavanje (specular),
     * i isijavanje (emmision) reda nula */
    GLfloat refl[] = {0.7f, 0.9f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, refl);
    
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
    
    /* Odbaceno crtanje GLUT-ove sfere inace, a
     * ikosaedra u ikosaedarskom (debag) rezimu */
    /*if (ikosaedar){
        glutSolidIcosahedron();
    } else {
        glutSolidSphere(KLIK_RAD, KLIK_PREC, KLIK_PREC);
    }*/
    
    /* Ukljucivanje 2D tekstura i vezivanje
     * one namenjene za iscrtavanje klikera */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, klik.tekst);
    
    /* Odbaceno parametrizovano iscrtavanje klikera
     * zasnovano  na iscrtavanju sferne trake trouglova;
     * bilo je potpuno isto kao parametrizacija oka, ali
     * ipak nije lako zalepiti teksturu u tom slucaju */
    /*GLfloat theta = -M_PI/2, phi = -M_PI;
    GLfloat pomeraj = M_PI/klik.prec;
    for ( ; theta < M_PI/2; theta += pomeraj){
        glBegin(GL_TRIANGLE_STRIP);
        for ( ; phi <= M_PI + M_PI/klik.prec; phi += pomeraj){*/
            /* Postavljaju se normala i koordinate
             * jedne obicne tacke sfernog klikera */
            /*glTexCoord2f(0, 0);
            glNormal3f(
                KLIK_RAD * cos(theta) * cos(phi),
                KLIK_RAD * cos(theta) * sin(phi),
                KLIK_RAD * sin(theta)
                );
            glVertex3f(
                KLIK_RAD * cos(theta) * cos(phi),
                KLIK_RAD * cos(theta) * sin(phi),
                KLIK_RAD * sin(theta)
                );*/
            
            /* Postavljaju se normala i koordinate
             * jedne "vise" tacke sfernog klikera */
            /*glTexCoord2f(0, 1);
            glNormal3f(
                KLIK_RAD * cos(theta + pomeraj) * cos(phi),
                KLIK_RAD * cos(theta + pomeraj) * sin(phi),
                KLIK_RAD * sin(theta + pomeraj)
                );
             glVertex3f(
                KLIK_RAD * cos(theta + pomeraj) * cos(phi),
                KLIK_RAD * cos(theta + pomeraj) * sin(phi),
                KLIK_RAD * sin(theta + pomeraj)
                );
        }
    glEnd();*/
    
    /* Reinicijalizacija azimuta */
    /*phi = -M_PI;
    }*/
    
    /* Iscrtavanje klikera kao quadrica */
    gluSphere(klik.obj, KLIK_RAD, KLIK_PREC, KLIK_PREC);
    
    /* Iskljucivanje 2D tekstura */
    glBindTexture(GL_TEXTURE_2D, NEAKTIVNO);
    glDisable(GL_TEXTURE_2D);
    
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

void kliker_skok(void)
{
    /* Odbaceno cuvanje povratne vrednosti;
     * podrazumevano nije bio kraj skoka */
    /*int vracam = SKOK_NIJE;*/
    
    /* Povecavanje parametra skoka */
    klik.s += UGAO_PAR * vreme.pom;
    
    /* Ako je parametar dostigao maksimum,
     * resetuje se, sto oznacava kraj skoka */
    if (klik.s >= UGAO_EXT){
        klik.s = UGAO_POC;
        /*vracam = SKOK_KRAJ;*/
    }
    
    /* Skok se modeluje sinusoidnom funkcijom;
     * kao argument se forsira vrednost od nula
     * do pi, tako da sinus vraca vrednosti koje
     * rastu od nule do jedinice, a zatim opet
     * opadaju do nule; mnozenje sa ocekivanom
     * visinom skoka daje z koordinatu klikera */
    klik.z = SKOK_VIS * sin(klik.s * M_PI / UGAO_EXT);
    
    /* 0 ako nije kraj, 1 ako jeste */
    /*return vracam;*/
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
    GLdouble ugao = smer * UGAO_PAR * vreme.pom;
    glRotated(ugao, rot.x, rot.y, ROT_Z);
    
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
