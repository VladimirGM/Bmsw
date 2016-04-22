//
// Created by palsol on 10/31/2015.
//

#ifndef BMSMALLWORLD_ECCONSTANT_H
#define BMSMALLWORLD_ECCONSTANT_H

#include <cmath>
#include <tgmath.h>
#include <vector>

using namespace std;
//Neurons
const double ze = 1, z[6] = { 0, 2, 1, 1, -1, -1 };


const double ecF = 96.485, ecR = 8.3145, ecT = 310.15, ecvn = 25000, ecsn = 2244.66, ecfn= 0.5;
const double ecAn = ecsn/(ecfn * ecF * ecvn);

const double Z_Calcium = 2,      Z_Potassium = 1,        Z_Natrium = 1,       Z_Chlorine = -1, Z_Glutamate = -1;

const double Rn_Calcium = 5,     Rn_Potassium = 13.632,  Rn_Natrium = 13.632, Rn_Chlorine = 2;
const double Pn_Calcium = 0.126, Pn_Potassium = 0.021,   Pn_Natrium  = 0.021;
const double Pa_Calcium = 0.006, Pa_Potassium = 0.001,   Pa_Natrium  = 0.001;

const double gn_NatriumCalcium = 1.839, gn_trg = 0.038, gn_PotassiumChlorine = 0.231;
const double gn_KDR = 52580, gn_BK = 3.367, gn_NaP = 2.059, gn_CaHVA = 18.342, gn_STRE = 0.05;
const double gn_Cldiff = 5.78, gn_gludiff = 0.008;
const double Vact = -0.04, a0 = 0.0001;

const double Ra_Calcium = 5,     Ra_Potassium = 5.962,  Ra_Natrium = 5.962, Ra_Chlorine = 2;

const double ga_NatriumCalcium = 1.784, ga_trg = 0.049, ga_PotassiumChlorine = 0.719;
const double ga_KDR = 2722.1, ga_BK = 1.979, ga_NaP = 1.922, ga_CaHVA = 165.080, ga_STRE = 0.05, ga_Kir = 5.909;
const double ga_Cldiff = 6.493, ga_gluiff = 0.013;
const double ga_NatriumPotassiumChlorine = 0.016;


const double kAlarm[6] = { 0, 4 * pow(10, - 9), 8 * pow(10, -5), 1 * pow(10, -4), 8 * pow(10, -5), 4 * pow(10, -3) };
const double K_IP3 = 3 * pow(10, -4), K_a = 2 * pow(10, -2), K_i = 0.527, betaAlarm = 20;
const double v_beta = 5 * pow(10, -7), y_ij = 1 * pow(10, -3);
const double K_R = 1.3 * pow(10, -3), K_p = 1 * pow(10, -2), K_pi = 6 * pow(10, -4);


struct IonConcentration
{
    double Calcium;
    double Potassium;
    double Natrium;
    double Chlorine;
    double Glutamate;
};
//start conditions
const struct IonConcentration startNeuronConcentration        = { 6 * pow(10, -4), 130.695, 17.7128, 14.0068, 3};
const struct IonConcentration startAstrocyteConcentration     = { 6 * pow(10, -4), 130.6657, 17.7375, 7.0022, 3};
const struct IonConcentration startIntercellularConcentration = { 2, 5.4125, 139.9705, 149.382, 0.001};
const double startVn = -53.3, startVa = -73.3;
#endif //BMSMALLWORLD_ECCONSTANT_H




