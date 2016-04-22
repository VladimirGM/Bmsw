//
// Created by palsol on 18.11.15.
//

#ifndef SIMPLEEQUATIONSOLVER_SESTANGETSOLVER_H
#define SIMPLEEQUATIONSOLVER_SESTANGETSOLVER_H

#include "sesSolver.h"

class sesTangetSolver: public sesSolver
{
public:

    sesTangetSolver();
    sesTangetSolver(double _rangeMin, double _rangeMax, double _precision,
                    std::function< double(double x) > _equation);
    sesTangetSolver(double _rangeMin, double _rangeMax, double _precision,
                    std::function< double(double x) > _equation,
                    std::function< double(double x) > _equationFirstDerivative);

    virtual void initialization(double _rangeMin, double _rangeMax, double _precision,
                        std::function< double(double x) > _equation,
                        std::function< double(double x) > _equationFirstDerivative);

    virtual void computeRoot();

protected:

    std::function< double(double x) > equationFirstDerivative;
};


#endif //SIMPLEEQUATIONSOLVER_SESTANGETSOLVER_H
