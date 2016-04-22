//
// Created by palsol on 10/31/2015.
//

#ifndef BMSMALLWORLD_NEURONEC_H
#define BMSMALLWORLD_NEURONEC_H

#include"ecConstant.h"

double ecNeuronE(double W, double U, double Z);

double ecNeuronCalcium  (double V, IonConcentration W, IonConcentration U);
double ecNeuronPotassium(double V, IonConcentration W, IonConcentration U);
double ecNeuronNatrium  (double V, IonConcentration W, IonConcentration U);
double ecNeuronChlorine (double V, IonConcentration W, IonConcentration U);
double ecNeuronGlutamate(double V, IonConcentration W, IonConcentration U);

double ecNeuronCharge(double V, IonConcentration W, IonConcentration U);

#endif //BMSMALLWORLD_NEURONEC_H
