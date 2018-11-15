#include "kliker.h"

void napravi_kliker(void)
{
    // Postavljanje centra sfere
    kliker.x = 0;
    kliker.y = 0;
    kliker.z = 0;
    
    // Postavljanje radijusa sfere
    kliker.r = 1;
    
    // Postavljanje preciznosti sfere
    kliker.prec = 22;
}

void nacrtaj_kliker(void)
{
    // Crtanje mrezaste sfere
    glutWireSphere(kliker.r, kliker.prec, kliker.prec);
}
