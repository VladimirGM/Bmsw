//
// Created by gryaznov on 05.11.15.
//

#ifndef BMSMALLWORLD_ECASTROCYTE_H
#define BMSMALLWORLD_ECASTROCYTE_H

#include"ecConstant.h"

double ecAstrocyteE(double W, double U, double Z)
{
    return ecR * ecT /  (Z * ecF) * log(U/W);
}

double ecAstrocyteCalcium  (double V, IonConcentration W, IonConcentration U, double q_1, double q_2, double q_3);
double ecAstrocytePotassium(double V, IonConcentration W, IonConcentration U);
double ecAstrocyteNatrium  (double V, IonConcentration W, IonConcentration U);
double ecAstrocyteChlorine (double V, IonConcentration W, IonConcentration U);
double ecAstrocyteGlutamate(double V, IonConcentration W, IonConcentration U);
double ecAstrocyteIP3(double q1, vector < double > neighborsq1, IonConcentration W, IonConcentration U);
double ecAstrocyteCaER(double q1, double q2, double q3, IonConcentration W, IonConcentration U);
double ecAstrocyteR(double q1, double q2, double q3, IonConcentration W, IonConcentration U);

#endif //BMSMALLWORLD_ECASTROCYTE_H

