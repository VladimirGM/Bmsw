//
// Created by palsol on 18.11.15.
//

#ifndef SIMPLEEQUATIONSOLVER_SESCHORDSSOLVER_H
#define SIMPLEEQUATIONSOLVER_SESCHORDSSOLVER_H

#include "sesTangetSolver.h"

class sesChordsSolver: public sesTangetSolver
{
public:
    sesChordsSolver();
    sesChordsSolver(double _rangeMin, double _rangeMax, double _precision,
                    std::function< double(double x) > _equation);
    sesChordsSolver(double rangeMin, double rangeMax, double _precision,
                    std::function< double(double x) > _equation,
                    std::function< double(double x) > _equationFirstDerivative,
                    std::function< double(double x) > _equationSecondDerivative);

    virtual void initialization(double _rangeMin, double _rangeMax, double _precision,
                        std::function< double(double x) > _equation,
                        std::function< double(double x) > _equationFirstDerivative,
                        std::function< double(double x) > _equationSecondDerivative);

    virtual void computeRoot();

private:

    std::function< double(double x) > equationSecondDerivative;

};


#endif //SIMPLEEQUATIONSOLVER_SESCHORDSSOLVER_H
