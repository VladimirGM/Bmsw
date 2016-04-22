//
// Created by palsol on 18.11.15.
//Simple Equation Solver
//

#ifndef SIMPLEEQUATIONSOLVER_SESSOLVER_H
#define SIMPLEEQUATIONSOLVER_SESSOLVER_H

#include <cmath>
#include <functional>
#include <iostream>
using namespace std;

class sesSolver
{
public:

    sesSolver();
    sesSolver(double _rangeMin, double _rangeMax, double _precision,
              std::function< double(double x) > _equation);

    virtual void initialization(double _rangeMin, double _rangeMax, double _precision,
                                std::function< double(double x) > _equation);

    void setRange(double _rangeMin, double _rangeMax);
    void setPrecision(double _precision);
    double getRoot();

    virtual void computeRoot();

protected:

    double rangeMin, rangeMax;
    double precision;
    double root;

    std::function< double(double x) > equation;
    /*std::function< double > _equationFirstDerivative;
    std::function< double > _equationSecondDerivative;*/
};


#endif //SIMPLEEQUATIONSOLVER_SESSOLVER_H
