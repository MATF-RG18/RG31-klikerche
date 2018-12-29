#include "../include/staza.h"

void napravi_stazu(void)
{
    /* Pravljenje teksture sanduka i kraja; one se
     * prave pomocu biblioteke SOIL ucitavanjem u
     * podrazumevanom rezimu, a prave im se novi
     * identifikatori, kao i propratne mipmape; ovime
     * SOIL postedjuje rukovanja sa redudantnim
     * fjama poput glGenTextures() i slicnim; same
     * teksture su stock slike sa interneta */
    staza.tekst = SOIL_load_OGL_texture(STAZA_TEKST,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    staza.kraj = SOIL_load_OGL_texture(STAZA_KRAJ,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    
    /* Registrovanje liste za stazu */
    staza.lista = glGenLists(AKTIVNO);
    
    /* Pravljenje liste za stazu */
    glNewList(staza.lista, GL_COMPILE);
    
    /* Refleksija materijala generisane staze;
     * magicni brojevi koji se po zelji mogu
     * menjati; trenutno staza odbija sve svetlo,
     * pa bi bila bela da nema teksture */
    GLfloat refl[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, refl);
    
    /* Ukljucivanje 2D tekstura i vezivanje
     * one namenjene za icrtavanje staze */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, staza.tekst);
    
    /* Iscrtavanje staze; magicni brojevi
     * koji se po potrebi mogu menjati; push
     * i pop su neophodni zbog kretanja tj.
     * inace transformacija klikera, dok se
     * zbog dobrog osvetljenja ne moze bez
     * normalizacije upravnih vektora */
    glEnable(GL_NORMALIZE);
    glPushMatrix();
    
    /* Spustanje staze ispod klikera
     * i pravljenje prve plocice */
    glTranslatef(0, 0, -1.13);
    napravi_plocicu();
    
    /* Pravljenje jos sest plocica
     * duz x ose; produzavanje puta */
    int i;
    for (i = 0; i < 6; i++){
        glTranslatef(-6, 0, 0);
        napravi_plocicu();
    }
    
    /* Pravljenje jos tri plocice
     * duz y ose; malo skretanje */
    for (i = 0; i < 3; i++){
        glTranslatef(0, 6, 0);
        napravi_plocicu();
    }
    
    /* Ukljucivanje teksture za kraj
     * i iscrtavanje zavrsne plocice */
    glBindTexture(GL_TEXTURE_2D, staza.kraj);
    glTranslatef(0, 6, 0);
    napravi_plocicu();
    
    /* Kraj iscrtavanja, a samim tim
     * i potrebe za normalizacijom */
    glPopMatrix();
    glDisable(GL_NORMALIZE);
    
    /* Iskljucivanje 2D tekstura */
    glBindTexture(GL_TEXTURE_2D, NEAKTIVNO);
    glDisable(GL_TEXTURE_2D);
    
    /* Kraj liste za stazu */
    glEndList();
}

void napravi_plocicu(void)
{
    /* Ideja za makroizovano icrtavanje plocica
     * preuzeta je direktno iz implementacije fje
     * glutSolidCube() biblioteke FreeGLUT; doradjena
     * je tako da bude skalirana i teksturirana */
    
    /* Normale i teksture su direktno definisane
     * koordinatama, a temena znakom ispred unapred
     * izracunatih vrednosti koordinata prema skali */
    #define N(a,b,c) glNormal3i(a, b, c)
    #define T(a, b) glTexCoord2i(a, b)
    #define V(a,b,c) glVertex3f(a 3, b 3, c 0.13)
    
    /* Plocice se icrtavaju kao skup kvadrata */
    glBegin(GL_QUADS);
    
    /* Crta se prednja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(1, 0, 0);
    T(0, 1); V(+, -, +);
    T(0, 0); V(+, -, -);
    T(1, 0); V(+, +, -);
    T(1, 1); V(+, +, +);
    
    /* Crta se desna strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, 1, 0);
    T(0, 1); V(+, +, +);
    T(0, 0); V(+, +, -);
    T(1, 0); V(-, +, -);
    T(1, 1); V(-, +, +);
    
    /* Crta se gornja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, 0, 1);
    T(0, 1); V(+, +, +);
    T(0, 0); V(-, +, +);
    T(1, 0); V(-, -, +);
    T(1, 1); V(+, -, +);
    
    /* Crta se zadnja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(-1, 0, 0);
    T(0, 1); V(-, -, +);
    T(0, 0); V(-, +, +);
    T(1, 0); V(-, +, -);
    T(1, 1); V(-, -, -);
    
    /* Crta se leva strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, -1, 0);
    T(0, 1); V(-, -, +);
    T(0, 0); V(-, -, -);
    T(1, 0); V(+, -, -);
    T(1, 1); V(+, -, +);
    
    /* Crta se donja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, 0, -1);
    T(0, 1); V(-, -, -);
    T(0, 0); V(-, +, -);
    T(1, 0); V(+, +, -);
    T(1, 1); V(+, -, -);
    
    /* Kraj iscrtavanja plocica */
    glEnd();
    
    /* Prestanak vazenja makroa */
    #undef V
    #undef T
    #undef N
}

void postavi_stazu(void)
{
    /* Uz odbacivanje postojanja zicanog rezima,
     * odbaceno je i pozivanje liste za iscrtavanje
     * staze prema aktivnosti tog rezima; crtala se
     * popunjena staza inace, a zicana u rezimu */
    /*if (zicani){
        glCallList(staza2);
    } else {
        glCallList(staza1);
    }*/
    
    /* Pozivanje liste za iscrtavanje staze */
    glCallList(staza.lista);
}
