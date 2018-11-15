#include "oko.h"

void napravi_oko(void)
{
    // Postavljanje radijusa
    oko.r = 5;
    oko.d_r = 0.03;
    
    // Postavljanje azimuta
    oko.phi = 0;
    oko.d_phi = M_PI/450;
    
    // Postavljanje polara
    oko.theta = M_PI/6;
    oko.d_theta = M_PI/450;
}

void popravi_oko(void)
{
    // Prevodjenje sfernih koordinata u Dekartove
    oko.x = oko.r * cos(oko.theta) * cos(oko.phi);
    oko.y = oko.r * cos(oko.theta) * sin(oko.phi);
    oko.z = oko.r * sin(oko.theta);
}

void oko_levo(void)
{
    // Oko se krece levo:
    // smanjivanje azimuta
    oko.phi -= oko.d_phi;
    
    // Popravka jer phi = [0, 2pi)
    if (oko.phi < 0){
        oko.phi += 2*M_PI;
    }
}

void oko_desno(void)
{
    // Oko se krece desno:
    // povecavanje azimuta
    oko.phi += oko.d_phi;
    
    // Popravka jer phi = [0, 2pi)
    if (oko.phi >= 2*M_PI){
        oko.phi -= 2*M_PI;
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
    if (oko.theta > M_PI/2){
        oko.theta = M_PI/2;
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
    if (oko.theta < 0){
        oko.theta = 0;
    }
}

void oko_napred(void)
{
    // Oko se priblizava:
    // smanjivanje radijusa
    oko.r -= oko.d_r;
    
    // Popravka jer r = [2, 10]
    if (oko.r < 2){
        oko.r = 2;
    }
}

void oko_nazad(void)
{
    // Oko se udaljava:
    // povecavanje radijusa
    oko.r += oko.d_r;
    
    // Popravka jer r = [2, 10]
    if (oko.r > 10){
        oko.r = 10;
    }
}
