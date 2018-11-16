#include "oko.h"

void napravi_oko(void)
{
    // Postavljanje radijusa
    oko.r = OKO_RAD;
    oko.d_r = OKO_RAD_R;
    
    // Postavljanje azimuta
    oko.phi = OKO_PHI;
    oko.d_phi = OKO_PHI_R;
    
    // Postavljanje polara
    oko.theta = OKO_THETA;
    oko.d_theta = OKO_THETA_R;
}

void popravi_oko(void)
{
    // Prevodjenje sfernih koordinata u Dekartove
    oko.x = oko.r * cos(oko.theta) * cos(oko.phi);
    oko.y = oko.r * cos(oko.theta) * sin(oko.phi);
    oko.z = oko.r * sin(oko.theta);
}

int resetuj_oko(void)
{
    // Razlike u odnosu na pocetno stanje
    int r_raz = (oko.r - OKO_RAD) / oko.d_r;
    int phi_raz = (oko.phi - OKO_PHI) / oko.d_phi;
    int theta_raz = (oko.theta - OKO_THETA) / oko.d_theta;
    
    // Postepeno vracanje oka u pocetno stanje
    if (r_raz || phi_raz || theta_raz){
        if (r_raz > 0){
            oko_napred();
            r_raz--;
        } else if (r_raz < 0){
            oko_nazad();
            r_raz++;
        }
        
        if (phi_raz > 0){
            oko_levo();
            phi_raz--;
        } else if (phi_raz < 0){
            oko_desno();
            phi_raz++;
        }
        
        if (theta_raz > 0){
            oko_dole();
            theta_raz--;
        } else if (theta_raz < 0){
            oko_gore();
            theta_raz++;
        }
    // vraca 1 ako je u pocetnom stanju
    } else return 1;
    
    // vraca 0 ako nije u pocetnom stanju
    return 0;
}

void oko_levo(void)
{
    // Oko se krece levo:
    // smanjivanje azimuta
    oko.phi -= oko.d_phi;
    
    // Popravka jer phi = [-pi, pi)
    if (oko.phi < OKO_PHI_MIN){
        oko.phi += OKO_PHI_POM;
    }
}

void oko_desno(void)
{
    // Oko se krece desno:
    // povecavanje azimuta
    oko.phi += oko.d_phi;
    
    // Popravka jer phi = [-pi, pi)
    if (oko.phi >= OKO_PHI_MAX){
        oko.phi -= OKO_PHI_POM;
    }
}

void oko_gore(void)
{
    // Oko se krece gore:
    // povecavanje polara
    oko.theta += oko.d_theta;
    
    // Popravka jer theta = [0, pi/2]
    // Inace je [-pi/2, pi/2], ali ovako
    // se izbegava odlazak ispod scene
    if (oko.theta > OKO_THETA_MAX){
        oko.theta = OKO_THETA_MAX;
    }
}

void oko_dole(void)
{
    // Oko se krece dole:
    // smanjivanje polara
    oko.theta -= oko.d_theta;
    
    // Popravka jer theta = [0, pi/2]
    // Inace je [-pi/2, pi/2], ali ovako
    // se izbegava odlazak ispod scene
    if (oko.theta < OKO_THETA_MIN){
        oko.theta = OKO_THETA_MIN;
    }
}

void oko_napred(void)
{
    // Oko se priblizava:
    // smanjivanje radijusa
    oko.r -= oko.d_r;
    
    // Popravka jer r = [2, 10]
    if (oko.r < OKO_RAD_MIN){
        oko.r = OKO_RAD_MIN;
    }
}

void oko_nazad(void)
{
    // Oko se udaljava:
    // povecavanje radijusa
    oko.r += oko.d_r;
    
    // Popravka jer r = [2, 10]
    if (oko.r > OKO_RAD_MAX){
        oko.r = OKO_RAD_MAX;
    }
}
