#include "kliker.h"

void napravi_kliker(void)
{
    // Postavljanje centra sfere
    kliker.x = KLIK_CENT;
    kliker.y = KLIK_CENT;
    kliker.z = KLIK_CENT;
    
    // Postavljanje radijusa sfere
    kliker.r = KLIK_RAD;
    
    // Postavljanje preciznosti sfere
    kliker.prec = KLIK_PREC;
}

void postavi_kliker(void)
{
    /* Ambijentalna, difuzna i spekularna
       refleksija materijala igracevog klikera,
       magicni brojevi koji se po zelji mogu
       menjati u cilju promene boje sfere */
    GLfloat amb_ref[] = {0.3f, 0.7f, 0.3f, 1.0f};
    GLfloat dif_ref[] = {0.2f, 1.0f, 0.2f, 1.0f};
    GLfloat spek_ref[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    // Postavljanje svojstava klikera
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb_ref);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_ref);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spek_ref);
    glMateriali(GL_FRONT, GL_SHININESS, GLATKOST);
    
    // Pomeranje u centar sfere
    glTranslated(kliker.x, kliker.y, kliker.z);
    
    // Crtanje popunjene sfere
    glutSolidSphere(kliker.r, kliker.prec, kliker.prec);
}

void kliker_napred(void)
{
    /* Pomeraj je projekcija vektora koji
       razapinju centar oka i centar klikera
       na xy ravan, tako da se starim koord.
       klikera dodaje razlika vrednosti */
    float duzina = sqrt((kliker.x - oko.x) * (kliker.x - oko.x)
                 +  (kliker.y - oko.y) * (kliker.y - oko.y))
                 * POMERAJ; // normalizacija pomeraja
    kliker.x += (kliker.x - oko.x)/duzina;
    kliker.y += (kliker.y - oko.y)/duzina;
}

void kliker_nazad(void)
{
    /* Pomeraj je projekcija vektora koji
       razapinju centar klikera i centar oka
       na xy ravan, tako da se starim koord.
       klikera dodaje razlika vrednosti */
    float duzina = sqrt((oko.x - kliker.x) * (oko.x - kliker.x)
                 +  (oko.y - kliker.y) * (oko.y - kliker.y))
                 * POMERAJ; // normalizacija pomeraja
    kliker.x += (oko.x - kliker.x)/duzina;
    kliker.y += (oko.y - kliker.y)/duzina;
}
