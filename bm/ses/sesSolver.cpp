//
// Created by palsol on 18.11.15.
//

#include "sesSolver.h"

sesSolver::sesSolver()
{
    std::function< double(double x) > _equation = [](double x) -> double { return x; };
    initialization(-1, 1, 0.01, _equation);
}

sesSolver::sesSolver(double _rangeMin, double _rangeMax, double _precision,
                     std::function< double(double x) > _equation)
{
    initialization(_rangeMin, _rangeMax, _precision, _equation);
}

void sesSolver::initialization(double _rangeMin, double _rangeMax, double _precision,
                    std::function< double(double x) > _equation)
{
    precision = _precision;
    if(_rangeMin < _rangeMax) { rangeMin = _rangeMin; rangeMax = _rangeMax; }
    else { rangeMin = _rangeMax; rangeMax = _rangeMin; }

    equation = _equation;
}

void sesSolver::setRange(double _rangeMin, double _rangeMax)
{
    rangeMin = _rangeMin;
    rangeMax = _rangeMax;
}

void sesSolver::setPrecision(double _precision)
{
    precision = _precision;
}

double sesSolver::getRoot()
{
    return root;
}

void sesSolver::computeRoot()
{
    root = 1234567;
}