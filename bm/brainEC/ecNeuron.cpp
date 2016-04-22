//
// Created by palsol on 10/31/2015.
//

#include "ecNeuron.h"

double  ecNeuronE(double W, double U, double Z)
{
    return ecR * ecT /  (Z * ecF) * log(U/W);
}

double ecNeuronCalcium(double V, IonConcentration W, IonConcentration U)
{
    double dW_Calcium = 0;

    double a_m = 8.5   /(1 + exp(-1 * (V - 8)  / (12.5)) );
    double a_h = 0.0015/(1 + exp( 1 * (V + 29) / (8)) );
    double b_m = 35    /(1 + exp( 1 * (V + 74) / (14.5)) );
    double b_h = 0.0055/(1 + exp(-1 * (V + 23) / (8)) );

    double Phi = (ecF * V )/ (ecR * ecT);
    double I_CaHVA = 6 * pow(10, -4) * gn_CaHVA * ecF * Phi * (a_m/(a_m + b_m) * a_h/(a_h + b_h))
                     * ( (W.Calcium - U.Calcium * exp(-2*Phi) )/(1 - exp(-2*Phi) ) );
    double I_Capump = pow(10, -2) * Rn_Calcium * ( W.Calcium / ( W.Calcium + 0.0002));
    double I_Caant = -1 * pow(10, -2) * ( gn_NatriumCalcium / pow(12, 4) ) *
                     ( pow(W.Calcium, 3) * U.Calcium * exp(0.5 * Phi) - pow(U.Natrium, 3) * W.Calcium * exp(-0.5 * Phi))
                     / ( 1 + 0.0001 * ( pow(U.Natrium, 3) * W.Calcium + pow(W.Natrium, 3) * U.Calcium ) * (1 + W.Calcium / 0.0069));
    double I_CaNMDA = pow(10, -3) * (4 * Pn_Calcium * ecF * ecF) / (ecR * ecT) * U.Calcium
                      * (72 * U.Glutamate) / ( (72 * U.Glutamate + 6.6) * (1 + 0.028 * exp(-0.062* V) ) )
                      * V * ( (W.Calcium/U.Calcium * exp(2 * Phi) - 1)/ (exp(2 * Phi) - 1) );

    dW_Calcium = ecAn/Z_Calcium * (I_CaHVA + I_Capump + I_Caant + I_CaNMDA);

    return dW_Calcium;
}

double ecNeuronPotassium(double V, IonConcentration W, IonConcentration U)
{

    double dW_Potassium = 0;

    double Phi = (ecF * V )/ (ecR * ecT);
    double PHI = Phi + 176.5 * ecF / ( ecR * ecT);

    double E_Potassium = ecNeuronE(W.Potassium, U.Potassium, Z_Potassium);

    double a_KDR = 0.0047 * (V - 8) / (1 - exp( (V + 12) / 12 ));
    double b_KDR = exp( -1 * (V + 127) / 30 );

    double I_KDR = pow(10, -3) * gn_KDR * (V -  E_Potassium) * pow(a_KDR / (a_KDR + b_KDR), 2) / (1 + exp( (V + 25)/4 ));
    double I_BK = pow(10, -3) * gn_BK * (V - E_Potassium) * ( 250 * W.Calcium / (250 * W.Calcium + 0.1 * exp( -V/12 ) ) );
    double I_Kpump = -1 * pow(10, -2) * Rn_Potassium * pow(U.Potassium / ( U.Potassium + 3.7 ), 2)
                     * pow(W.Natrium / ( W.Natrium + 3.7 ), 3) * ( 0.052 * sinh(PHI) / ( 0.026 * exp(PHI) + 22.5 * exp(-1 * PHI) ));
    double I_Ktrg = pow(10, -3) * gn_trg * (V - (ecR * ecT / ecF)) *
                    log( (pow(U.Natrium / W.Natrium, 3) * (W.Potassium / U.Potassium) * (U.Glutamate / W.Glutamate)) );
    double I_Kexch = pow(10, -3) * gn_PotassiumChlorine * (ecR * ecT / ecF) *
                     log( (W.Potassium / U.Potassium) * (W.Chlorine / U.Chlorine) );
    double I_KNMDA = pow(10, -3) * (Pn_Potassium * pow(ecF, 2) ) / (ecR * ecT) * U.Potassium
                     * (72 * U.Glutamate) / ( (72 * U.Glutamate + 6.6) * (1 + 0.028 * exp(-0.062* V) ) )
                     * V * ( (W.Potassium/U.Potassium * exp(Phi) - 1)/ (exp(Phi) - 1) );

    dW_Potassium = ecAn/Z_Potassium * (I_KDR + I_BK + I_Kpump + I_Ktrg + I_Kexch + I_KNMDA);

    return dW_Potassium;

}

double ecNeuronNatrium(double V, IonConcentration W, IonConcentration U)
{
    double dW_Natrium = 0;

    double E_Natrium = ecNeuronE(W.Natrium, U.Natrium, Z_Natrium);
    double Phi = (ecF * V )/ (ecR * ecT);
    double PHI = Phi + 176.5 * ecF / ( ecR * ecT);

    double a_NaP = 200 / (1 + exp( -1 * ((V - 18) / 16) ) );
    double b_NaP = 25  / (1 + exp( (V + 58) / 8 ) );

    double I_Nap = pow(10, -3) * gn_NaP * a_NaP * (V - E_Natrium) / (a_NaP + b_NaP);
    double I_Napump = -1.5 * pow(10, -2) * Rn_Potassium * pow(U.Potassium / ( U.Potassium + 3.7 ), 2)
                       * pow(W.Natrium / ( W.Natrium + 3.7 ), 3) * ( 0.052 * sinh(PHI) / ( 0.026 * exp(PHI) + 22.5 * exp(-1 * PHI) ));
    double I_Naat = -1.5 * pow(10, -2) * ( gn_NatriumCalcium / pow(12, 4) ) *
                    ( pow(W.Calcium, 3) * U.Calcium * exp(0.5 * Phi) - pow(U.Natrium, 3) * W.Calcium * exp(-0.5 * Phi))
                    / ( 1 + 0.0001 * ( pow(U.Natrium, 3) * W.Calcium + pow(W.Natrium, 3) * U.Calcium ) * (1 + W.Calcium / 0.0069));
    double I_Natrg = -3 *  pow(10, -3) * gn_trg * (V - (ecR * ecT / ecF)) *
                     log( (pow(U.Natrium / W.Natrium, 3) * (W.Potassium / U.Potassium) * (U.Glutamate / W.Glutamate)) );

    double I_NaNMDA = pow(10, -3) * (Pn_Natrium * pow(ecF, 2) ) / (ecR * ecT) * U.Potassium
                      * (72 * U.Glutamate) / ( (72 * U.Glutamate + 6.6) * (1 + 0.028 * exp(-0.062* V) ) )
                      * V * ( (W.Potassium/U.Potassium * exp(Phi) - 1)/ (exp(Phi) - 1) );

    dW_Natrium = ecAn/Z_Natrium * (I_Nap + I_Napump + I_Naat + I_Natrg + I_NaNMDA);

    return dW_Natrium;

}

double ecNeuronChlorine(double V, IonConcentration W, IonConcentration U)
{
    double dW_Chlorine = 0;
    double E_Chlorine = ecNeuronE(W.Chlorine, U.Chlorine, Z_Chlorine);

    double I_stre = -1 * gn_STRE;
    double I_Clpump = -1 * pow(10, -2) * Rn_Chlorine * ( W.Chlorine/ (W.Chlorine + 25) );
    double I_Clexch = -1 *  pow(10, -3) * gn_PotassiumChlorine * (ecR * ecT / ecF) *
                      log( (W.Potassium / U.Potassium) * (W.Chlorine / U.Chlorine) );
    double I_Cldiff = pow(10, -3) * gn_Cldiff * (V - E_Chlorine);

    dW_Chlorine = ecAn/Z_Chlorine * (I_stre + I_Clpump + I_Clexch + I_Cldiff);

    return dW_Chlorine;
}

double ecNeuronGlutamate(double V, IonConcentration W, IonConcentration U)
{
    double dW_Glutamate = 0;
    double E_Glutamate = ecNeuronE(W.Glutamate, U.Glutamate, Z_Glutamate);

    double I_glutrg =  pow(10, -3) * gn_trg * (V - (ecR * ecT / ecF)) *
                       log( (pow(U.Natrium / W.Natrium, 3) * (W.Potassium / U.Potassium) * (U.Glutamate / W.Glutamate)) );

    double I_gludiff = pow(10, -3) * (V - E_Glutamate);


    dW_Glutamate = ecAn/Z_Glutamate * (I_glutrg, I_gludiff);

    return dW_Glutamate;

}

double ecNeuronCharge(double V, IonConcentration W, IonConcentration U)
{
    double charge = ecNeuronCalcium(V, W, U) * Z_Calcium +
                    ecNeuronPotassium(V, W, U) * Z_Potassium +
                    ecNeuronNatrium(V, W, U) * Z_Natrium +
                    ecNeuronChlorine(V, W, U) * Z_Chlorine +
                    ecNeuronGlutamate(V, W, U) * Z_Glutamate;
    return charge;

}