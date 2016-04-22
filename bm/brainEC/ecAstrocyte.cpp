//
// Created by gryaznov on 05.11.15.
//

#include "ecAstrocyte.h"



double ecAstrocyteCalcium  (double V, IonConcentration W, IonConcentration U, double q_1, double q_2, double q_3)
{
    double dW_Calcium = 0;

    double a_m = 8.5   /(1 + exp(-1 * (V - 8)  / (12.5)) );
    double a_h = 0.0015/(1 + exp( 1 * (V + 29) / (8)) );
    double b_m = 35    /(1 + exp( 1 * (V + 74) / (14.5)) );
    double b_h = 0.0055/(1 + exp(-1 * (V + 23) / (8)) );

    double Phi = (ecF * V )/ (ecR * ecT);
    double I_CaHVA = 6 * pow(10, -4) * ga_CaHVA * ecF * Phi * (a_m/(a_m + b_m) * a_h/(a_h + b_h))
                     * ( (W.Calcium - U.Calcium * exp(-2*Phi) )/(1 - exp(-2*Phi) ) );
    double I_Capump = pow(10, -2) * Rn_Calcium * ( W.Calcium / ( W.Calcium + 0.0002));
    double I_Caant = -1 * pow(10, -2) * ( ga_NatriumCalcium / pow(12, 4) ) *
                     ( pow(W.Calcium, 3) * U.Calcium * exp(-0.5 * Phi) - pow(U.Natrium, 3) * W.Calcium * exp(-0.5 * Phi))
                     / ( 1 + 0.0001 * ( pow(U.Natrium, 3) * W.Calcium + pow(W.Natrium, 3) * U.Calcium ) * (1 + W.Calcium / 0.0069));
    double I_CaAMPA = pow(10, -3) * (Pa_Potassium * pow(ecF, 2) / (ecR * ecT)) * U.Calcium
                      * ( 1100 * U.Glutamate ) / ( 1100 * U.Glutamate + 190 ) * V
                      * ( ( W.Calcium / U.Calcium ) * exp(Phi) - 1 ) / exp(Phi);
    double I_ER = kAlarm[1] - kAlarm[3] * W.Calcium
                  + ( kAlarm[2] * q_3 * pow(W.Calcium, 2) * pow(q_1, 2) * (q_2 - W.Calcium) )
                    / ( ( pow(K_a, 2) + pow(W.Calcium, 2) ) * ( pow(K_IP3, 2) + pow(q_1, 2) ) );

    dW_Calcium = ecAn/Z_Calcium * (I_CaHVA + I_Capump + I_Caant + I_CaAMPA) + I_ER;

    return dW_Calcium;
}

double ecAstrocytePotassium(double V, IonConcentration W, IonConcentration U)
{
    double dW_Potassium = 0;

    double Phi = (ecF * V )/ (ecR * ecT);
    double PHI = Phi + 176.5 * ecF / ( ecR * ecT);

    double E_Potassium = ecAstrocyteE(W.Potassium, U.Potassium, Z_Potassium);

    double a_KDR = 0.0047 * (V - 8) / (1 - exp( (V + 12) / 12 ));
    double b_KDR = exp( -1 * (V + 127) / 30 );

    double I_KDR = pow(10, -3) * ga_KDR * (V -  E_Potassium) * pow(a_KDR / (a_KDR + b_KDR), 2) / (1 + exp( (V + 25)/4 ));
    double I_BK = pow(10, -3) * ga_BK * (V - E_Potassium) * ( 250 * W.Calcium / (250 * W.Calcium + 0.1 * exp( -V/12 ) ) );
    double I_Kpump = -1 * pow(10, -2) * Rn_Potassium * pow(U.Potassium / ( U.Potassium + 3.7 ), 2)
                     * pow(W.Natrium / ( W.Natrium + 3.7 ), 3) * ( 0.052 * sinh(PHI) / ( 0.026 * exp(PHI) + 22.5 * exp(-1 * PHI) ));
    double I_Ktrg = pow(10, -3) * ga_trg * (V - (ecR * ecT / ecF)) *
                    log( (pow(U.Natrium / W.Natrium, 3) * (W.Potassium / U.Potassium) * (U.Glutamate / W.Glutamate)) );
    double I_Kexch = pow(10, -3) * ga_PotassiumChlorine * (ecR * ecT / ecF) *
                     log( (W.Potassium / U.Potassium) * (W.Chlorine / U.Chlorine) );

    double I_kastro = -1 * pow(10, -3) * ga_NatriumPotassiumChlorine * ecR * ecT / ecF
                      * log( ( pow(( U.Natrium / W.Natrium ), 3) * ( W.Potassium / U.Potassium ) * ( W.Chlorine / U.Chlorine ) ) );

    double I_KAMPA = pow(10, -3) * (Pa_Potassium * pow(ecF, 2) / (ecR * ecT)) * U.Calcium
                     * ( 1100 * U.Glutamate ) / ( 1100 * U.Glutamate + 190 ) * V
                     * ( ( W.Potassium / U.Potassium ) * exp(Phi) - 1 ) / exp(Phi);

    double I_Kir = pow(10, -3) * ga_Kir * ( V - E_Potassium ) * 1 / ( 2 + exp(1.62*ecF/( ecR*ecT )*( V - E_Potassium)) )
                   * U.Potassium/( U.Potassium + 13 );

    dW_Potassium = ecAn/Z_Potassium * (I_KDR + I_BK + I_Kpump + I_Ktrg + I_Kexch + I_kastro + I_KAMPA + I_Kir);

    return dW_Potassium;
}


double ecAstrocyteNatrium  (double V, IonConcentration W, IonConcentration U)
{
    double dW_Natrium = 0;

    double E_Natrium = ecAstrocyteE(W.Natrium, U.Natrium, Z_Natrium);
    double Phi = (ecF * V )/ (ecR * ecT);
    double PHI = Phi + 176.5 * ecF / ( ecR * ecT);

    double a_NaP = 200 / (1 + exp( -1 * ((V - 18) / 16) ) );
    double b_NaP = 25  / (1 + exp( (V + 58) / 8 ) );

    double I_Nap = pow(10, -3) * gn_NaP * a_NaP * (V - E_Natrium) / (a_NaP + b_NaP);
    double I_Napump =  1.5 * pow(10, -2) * Rn_Potassium * pow(U.Potassium / ( U.Potassium + 3.7 ), 2)
                       * pow(W.Natrium / ( W.Natrium + 3.7 ), 3) * ( 0.052 * sinh(PHI) / ( 0.026 * exp(PHI) + 22.5 * exp(-1 * PHI) ));
    double I_Naat = 1.5 * pow(10, -2) * ( gn_NatriumCalcium / pow(12, 4) ) *
                    ( pow(W.Calcium, 3) * U.Calcium * exp(-0.5 * Phi) - pow(U.Natrium, 3) * W.Calcium * exp(-0.5 * Phi))
                    / ( 1 + 0.0001 * ( pow(U.Natrium, 3) * W.Calcium + pow(W.Natrium, 3) * U.Calcium ) * (1 + W.Calcium / 0.0069));
    double I_Natrg = -3 *  pow(10, -3) * gn_trg * (V - (ecR * ecT / ecF)) *
                     log( (pow(U.Natrium / W.Natrium, 3) * (W.Potassium / U.Potassium) * (U.Glutamate / W.Glutamate)) );

    double I_NaAMPA = pow(10, -3) * (Pa_Natrium * pow(ecF, 2) / (ecR * ecT)) * U.Calcium
                      * ( 1100 * U.Glutamate ) / ( 1100 * U.Glutamate + 190 ) * V
                      * ( ( W.Natrium / U.Natrium ) * exp(Phi) - 1 ) / exp(Phi);

    dW_Natrium = ecAn/Z_Natrium * (I_Nap + I_Napump + I_Naat + I_Natrg + I_NaAMPA);

    return dW_Natrium;
}




double ecAstrocyteChlorine (double V, IonConcentration W, IonConcentration U)
{
    double dW_Chlorine = 0;

    double E_Chlorine = ecAstrocyteE(W.Chlorine, U.Chlorine, Z_Chlorine);
    double Phi = (ecF * V )/ (ecR * ecT);
    double PHI = Phi + 176.5 * ecF / ( ecR * ecT);

    double I_stre = ga_STRE;
    double I_Clpump = pow(-10, -2) * Ra_Chlorine * ( W.Chlorine/ (W.Chlorine + 25));
    double I_Clexch =  (-1) * pow(10, -3) * ga_PotassiumChlorine * (ecR * ecT / ecF) *
                              log( (W.Potassium / U.Potassium) * (W.Chlorine / U.Chlorine) );
    double I_Clastro = 2 * pow(10, -3) * ga_NatriumPotassiumChlorine * ecR * ecT / ecF
                       * log( ( pow(( U.Natrium / W.Natrium ), 3) * ( W.Potassium / U.Potassium ) * ( W.Chlorine / U.Chlorine ) ) );
    double I_Cldiff = pow(10, -3) * ga_Cldiff * ( V - E_Chlorine );

    dW_Chlorine = ecAn/Z_Chlorine * (I_stre + I_Clpump + I_Clexch + I_Clastro + I_Cldiff);

    return dW_Chlorine;
}

double ecAstrocyteGlutamate(double V, IonConcentration W, IonConcentration U)
{
    double dW_Glutamate = 0;

    double E_Glutamate = ecAstrocyteE(W.Glutamate, U.Glutamate, Z_Glutamate);

    double I_glutrg = pow(10, -3) * ga_trg * (V - (ecR * ecT / ecF)) *
                      log( (pow(U.Natrium / W.Natrium, 3) * (W.Potassium / U.Potassium) * (U.Glutamate / W.Glutamate)) );
    double I_gludiff = pow(10, -30) * ga_gluiff * ( V - E_Glutamate );

    dW_Glutamate = ecAn/Z_Glutamate * (I_glutrg + I_gludiff);

    return dW_Glutamate;
}

double ecAstrocyteIP3(double q1, vector < double > neighborsq1, IonConcentration W, IonConcentration U)
{
    double dq_1 = 0;

    dq_1 = v_beta * pow( U.Glutamate, 0.7) - kAlarm[4] * q1;

    for(int i = 0; i < neighborsq1.size(); i++)
    {
        dq_1 += y_ij*(neighborsq1[i] - q1);
    }

    return dq_1;
}
double ecAstrocyteCaER(double q1, double q2, double q3, IonConcentration W, IonConcentration U)
{
    double dq_2 = 0;

    dq_2 = (-1) * betaAlarm *
           ( (q2 - W.Calcium) * ( kAlarm[1] + kAlarm[2] * q3 * pow(W.Calcium, 2) * pow(q1, 2) )/
           ( ( pow(K_a, 2) + pow(W.Calcium, 2) ) * ( pow(K_IP3, 2) + pow(q1, 2) ) )  - kAlarm[3] * W.Calcium);

    return dq_2;
}

double ecAstrocyteR(double q1, double q2, double q3, IonConcentration W, IonConcentration U)
{
    double dq_3 = 0;

    dq_3 = kAlarm[5] * ( pow(K_i, 2) / ( pow(K_i, 2) + pow(W.Calcium, 2) ) - q3);

    return dq_3;
}