#include "../include/oko.h"

void napravi_oko(void)
{
    /* Postavljanje radijusa */
    oko.r = OKO_RAD;
    
    /* Postavljanje azimuta */
    oko.phi = OKO_PHI;
    
    /* Postavljanje polara */
    oko.theta = OKO_THETA;
    
    /* Postavljanje razlika */
    raz.r = RAZ_POC;
    raz.phi = RAZ_POC;
    raz.theta = RAZ_POC;
    
    /* Dekartove koordinate se ne
     * inicijalizuju, vec se kasnije
     * racunaju preko sfernih */
}

void popravi_oko(void)
{
    /* Prevodjenje sfernih koordinata u Dekartove */
    oko.x = klik.x + oko.r * cos(oko.theta) * cos(oko.phi);
    oko.y = klik.y + oko.r * cos(oko.theta) * sin(oko.phi);
    oko.z = klik.z + oko.r * sin(oko.theta);
}

int oko_reset(void)
{
    /* Postepeno vracanje oka u pocetno stanje:
     * za pozitivne razlike to podrazumeva inverzne
     * radnje koje ih smanjuju (napred, levo, dole),
     * a za negativne suprotno (nazad, desno, gore) */
    if (raz.r || raz.phi || raz.theta){
        if (raz.r > RAZ_POC){
            oko_napred();
        } else if (raz.r < RAZ_POC){
            oko_nazad();
        }
        
        /* Azimutalna razlika u sustini nije znacajna,
         * jer kamera ne treba da se vrati bas u pocetnu
         * tacku; stoga je algoritam postavlja na nulu */
        /*if (raz.phi > RAZ_POC){
            oko_levo();
        } else if (raz.phi < RAZ_POC){
            oko_desno();
        }*/
        raz.phi = RAZ_POC;
        
        if (raz.theta > RAZ_POC){
            oko_dole();
        } else if (raz.theta < RAZ_POC){
            oko_gore();
        }
    /* 1 ako je vracanje zavrseno */
    } else return RES_KRAJ;
    
    /* 0 ako vracanje nije zavrseno */
    return RES_NIJE;
}

void oko_levo(void)
{
    /* Okretanjem oka levo
     * smanjuje se azimut */
    oko.phi -= OKO_PHI_D * vreme.pom;
    raz.phi--;
    
    /* Popravka jer phi = [-pi, pi) */
    if (oko.phi < OKO_PHI_MIN){
        oko.phi += OKO_PHI_POM;
        raz.phi = (oko.phi - OKO_PHI) / OKO_PHI_D;
    }
}

void oko_desno(void)
{
    /* Okretanjem oka desno
     * povecava se azimut */
    oko.phi += OKO_PHI_D * vreme.pom;
    raz.phi++;
    
    /* Popravka jer phi = [-pi, pi) */
    if (oko.phi >= OKO_PHI_MAX){
        oko.phi -= OKO_PHI_POM;
        raz.phi = (oko.phi - OKO_PHI) / OKO_PHI_D;
    }
}

void oko_gore(void)
{
    /* Podizanjem oka se
     * povecava polar */
    oko.theta += OKO_THETA_D * vreme.pom;
    raz.theta++;
    
    /* Popravka jer theta = [0, pi/2];
     * inace je [-pi/2, pi/2], ali ovako
     * se izbegava odlazak ispod scene */
    if (oko.theta > OKO_THETA_MAX){
        oko.theta = OKO_THETA_MAX;
        raz.theta--;
    }
}

void oko_dole(void)
{
    /* Spustanjem oka se
     * smanjuje polar */
    oko.theta -= OKO_THETA_D * vreme.pom;
    raz.theta--;
    
    /* Popravka jer theta = [0, pi/2];
     * inace je [-pi/2, pi/2], ali ovako
     * se izbegava odlazak ispod scene */
    if (oko.theta < OKO_THETA_MIN){
        oko.theta = OKO_THETA_MIN;
        raz.theta++;
    }
}

void oko_napred(void)
{
    /* Priblizavanjem oka se
     * smanjuje radijus */
    oko.r -= OKO_RAD_D * vreme.pom;
    raz.r--;
    
    /* Popravka jer r = [5, 20] */
    if (oko.r < OKO_RAD_MIN){
        oko.r = OKO_RAD_MIN;
        raz.r++;
    }
}

void oko_nazad(void)
{
    /* Udaljavanjem oka se
     * povecava radijus */
    oko.r += OKO_RAD_D * vreme.pom;
    raz.r++;
    
    /* Popravka jer r = [5, 20] */
    if (oko.r > OKO_RAD_MAX){
        oko.r = OKO_RAD_MAX;
        raz.r--;
    }
}
