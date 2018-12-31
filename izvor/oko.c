#include "../include/oko.h"

void napravi_oko(void)
{
    /* Postavljanje radijusa; za pocetni
     * se bira maksimalan, koji ce se
     * smanjiti u pocetnoj animaciji */
    oko.r = OKO_RAD_MAX;
    
    /* Postavljanje azimuta */
    oko.phi = OKO_PHI;
    
    /* Postavljanje polara */
    oko.theta = OKO_THETA;
    
    /* Postavljanje razlika */
    /*raz.r = RAZ_POC;
    raz.phi = RAZ_POC;
    raz.theta = RAZ_POC;*/
    
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

/* Odbaceni model resetovanja oka koji koristi pomocne
 * promenljive, ima vise racunanja i nije najstabilniji */
/*int oko_reset(void)
{*/
    /* Postepeno vracanje oka u pocetno stanje:
     * za pozitivne razlike to podrazumeva inverzne
     * radnje koje ih smanjuju (napred, levo, dole),
     * a za negativne suprotno (nazad, desno, gore) */
    /*if (raz.r || raz.phi || raz.theta){
        if (raz.r > RAZ_POC){
            oko_napred();
        } else if (raz.r < RAZ_POC){
            oko_nazad();
        }*/
        
        /* Azimutalna razlika u sustini nije znacajna,
         * jer kamera ne treba da se vrati bas u pocetnu
         * tacku; stoga je algoritam postavlja na nulu */
        /*if (raz.phi > RAZ_POC){
            oko_levo();
        } else if (raz.phi < RAZ_POC){
            oko_desno();
        }*/
        /*raz.phi = RAZ_POC;
        
        if (raz.theta > RAZ_POC){
            oko_dole();
        } else if (raz.theta < RAZ_POC){
            oko_gore();
        }*/
    /* 1 ako je vracanje zavrseno */
    /*} else return RES_KRAJ;*/
    
    /* 0 ako vracanje nije zavrseno */
    /*return RES_NIJE;*/
    
    /* Napomena: uvodjenjem delta pomeraja resetovanje
     * je postalo neprecizno u slucaju da brzina racunara
     * osetno fluktuira u toku izvrsavanja; ipak, to je
     * bas redak slucaj, a svakako je i dalje mnogo bolji
     * nacin od prvobitne pesacke ideje kao sto je: */
    /*if (oko.r < OKO_RAD){
        oko_nazad();
    } else if (oko.r > OKO_RAD){
        oko_napred();
    }*/
/*}*/

int oko_reset(void)
{
    /* Novi i precizniji model resetovanja oka;
     * kamera se u sfernom koordinatnom sistemu
     * posmatra kao trojka (r, phi, theta); cilj
     * resetovanja je da tu trojku transformise
     * u (r0, phi, theta0), gde su r0 i theta0
     * pocetne vrednosti poluprecnika i polara;
     * ova tranformacija moze biti najobicnija
     * translacija po vektoru pomeraja (r0-r, 0,
     * theta0-theta) koja lako omogucava efikasno
     * resetovanje uprkos delta pomeraju i bez
     * dodatnog prostora za cuvanje razlika */
    GLdouble t_r = OKO_RAD - oko.r;
    GLdouble t_theta = OKO_THETA - oko.theta;
    
    /* Normalizacija izracunatog vektora
     * deljenjem sa njegovom duzinom i jos
     * mnozenjem sa parametrom reseta */
    double duzina = sqrt(t_r * t_r + t_theta * t_theta)
                    * RES_PAR / vreme.pom;
    t_r /= duzina; t_theta /= duzina;
    
    /* Cuva se povratna vrednost;
     * podrazumevano je kraj resetovanja */
    int vracam = RES_KRAJ;
    
    /* Translacija po izracunatom vektoru,
     * ali samo ako je vrednost pomeraja
     * manja od udaljenosti bitnih tacaka; u
     * tom slucaju jos nije kraj reseta, a
     * u suprotnom se vrednost poluprecnika
     * izjednacava sa pocetnom vrednosti,
     * plus se, radi realnije brzine reseta,
     * polarni pomeraj umanjuje za faktor */
    if (fabs(t_r) < fabs(OKO_RAD - oko.r)){
        oko.r += t_r;
        vracam = RES_NIJE;
    } else {
        oko.r = OKO_RAD;
        t_theta /= RES_THETA;
    }
    
    /* Slicno kao gore, samo za polarni ugao */
    if (fabs(t_theta) < fabs(OKO_THETA - oko.theta)){
        oko.theta += t_theta;
        vracam = RES_NIJE;
    } else {
        oko.theta = OKO_THETA;
    }
    
    /* 1 ako vracanje jeste zavrseno,
     * 0 ako vracanje nije zavrseno */
    return vracam;
}

void oko_levo(void)
{
    /* Svako kretanje kamere
     * zaustavlja resetovanje */
    /*tipke &= ~RESET;*/
    
    /* Okretanjem oka levo
     * smanjuje se azimut */
    oko.phi -= OKO_PHI_D * vreme.pom;
    /*raz.phi--;*/
    
    /* Popravka jer phi = [-pi, pi) */
    if (oko.phi < OKO_PHI_MIN){
        oko.phi += OKO_PHI_POM;
        /*raz.phi = (oko.phi - OKO_PHI) / OKO_PHI_D;*/
    }
}

void oko_desno(void)
{
    /* Svako kretanje kamere
     * zaustavlja resetovanje */
    /*tipke &= ~RESET;*/
    
    /* Okretanjem oka desno povecava
     * se azimut; ukoliko je izazvano
     * stanjem igre, usporava se */
    int kraj = (stanje != U_TOKU) ? OKR_USP : OKR_INC;
    oko.phi += OKO_PHI_D * vreme.pom / kraj;
    /*raz.phi++;*/
    
    /* Popravka jer phi = [-pi, pi) */
    if (oko.phi >= OKO_PHI_MAX){
        oko.phi -= OKO_PHI_POM;
        /*raz.phi = (oko.phi - OKO_PHI) / OKO_PHI_D;*/
    }
}

void oko_gore(void)
{
    /* Svako kretanje kamere
     * zaustavlja resetovanje */
    tipke &= ~RESET;
    
    /* Podizanjem oka se
     * povecava polar */
    oko.theta += OKO_THETA_D * vreme.pom;
    /*raz.theta++;*/
    
    /* Popravka jer theta = [0, pi/2];
     * inace je [-pi/2, pi/2], ali ovako
     * se izbegava odlazak ispod scene */
    /*if (oko.theta > OKO_THETA_MAX){
        oko.theta = OKO_THETA_MAX;
        raz.theta--;
    }*/
    oko.theta = MINIM(oko.theta, OKO_THETA_MAX);
}

void oko_dole(void)
{
    /* Svako kretanje kamere
     * zaustavlja resetovanje */
    tipke &= ~RESET;
    
    /* Spustanjem oka se
     * smanjuje polar */
    oko.theta -= OKO_THETA_D * vreme.pom;
    /*raz.theta--;*/
    
    /* Popravka jer theta = [0, pi/2];
     * inace je [-pi/2, pi/2], ali ovako
     * se izbegava odlazak ispod scene */
    /*if (oko.theta < OKO_THETA_MIN){
        oko.theta = OKO_THETA_MIN;
        raz.theta++;
    }*/
    oko.theta = MAXIM(oko.theta, OKO_THETA_MIN);
}

void oko_napred(void)
{
    /* Svako kretanje kamere
     * zaustavlja resetovanje */
    tipke &= ~RESET;
    
    /* Priblizavanjem oka se
     * smanjuje radijus */
    oko.r -= OKO_RAD_D * vreme.pom;
    /*raz.r--;*/
    
    /* Popravka jer r = [5, 20] */
    /*if (oko.r < OKO_RAD_MIN){
        oko.r = OKO_RAD_MIN;
        raz.r++;
    }*/
    oko.r = MAXIM(oko.r, OKO_RAD_MIN);
}

void oko_nazad(void)
{
    /* Svako kretanje kamere
     * zaustavlja resetovanje */
    tipke &= ~RESET;
    
    /* Udaljavanjem oka se
     * povecava radijus */
    oko.r += OKO_RAD_D * vreme.pom;
    /*raz.r++;*/
    
    /* Popravka jer r = [5, 20] */
    /*if (oko.r > OKO_RAD_MAX){
        oko.r = OKO_RAD_MAX;
        raz.r--;
    }*/
    oko.r = MINIM(oko.r, OKO_RAD_MAX);
}
