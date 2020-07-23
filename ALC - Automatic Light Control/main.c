#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gpioControl.h"
#include "timeControle.h"
#include "ephemeride.h"

const float compteurTime = 60; //nb sec avant arret automatique lumière

int main(void)
{
        int tZ = 1;
        int tcr = 0;
        int la = 48.9149;
        int lon = 2.2526599999999917;
        int alt = 0;

    while (1)
    {
        //initialisation des variables temps

        int a = localTime("annee");
        int m = localTime("mois");
        int j = localTime("jour");
        int heureLocal = localTime("heure");
        int minuteLocal = localTime("minute");
        float hr_minLocal = (float)heureLocal + ((float)minuteLocal / 60);
        int heureLeveSoleil = lmvSoleil(a, m, j, tZ, tcr, la, lon, alt, 0, 0);
        int minuteLeveSoleil = lmvSoleil(a, m, j, tZ, tcr, la, lon, alt, 0, 1);
        float hr_minLSoleil = (float)heureLeveSoleil + ((float)minuteLeveSoleil / 60);
        int heureCoucheSoleil = lmvSoleil(a, m, j, tZ, tcr, la, lon, alt, 1, 0);
        int minuteCoucheSoleil = lmvSoleil(a, m, j, tZ, tcr, la, lon, alt, 1, 1);
        float hr_minCSoleil = (float)heureCoucheSoleil + ((float)minuteCoucheSoleil / 60); 
        float chronometre = 0;

        //savoir si c jour ou nuit

        if (hr_minLSoleil < hr_minLocal && hr_minLocal > hr_minCSoleil)
        {
            sleep(1); //si c le jour attendre 1sec
        }
        else
        {
            //si nuit
            if (IRSensor() == 1 && lightControl(99) == 0)
            {
                lightControl(1);
            }
            else if (IRSensor() == 1 && lightControl(99) == 1)
            {
                chronometre = 0;
            }
            else if (IRSensor() == 0 && lightControl(99) == 1)
            {
                sleep(0.5);
                chronometre = chronometre + 0.5;

                if (chronometre == compteurTime)
                {
                    lightControl(0);
                }
            }
        }
    }
    return 0;
}