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

void nacrtaj_kliker(void)
{
    // Crtanje mrezaste sfere
    glutWireSphere(kliker.r, kliker.prec, kliker.prec);
}
