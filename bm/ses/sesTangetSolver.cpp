//
// Created by palsol on 18.11.15.
//

#include "sesTangetSolver.h"

sesTangetSolver::sesTangetSolver()
{
    precision = 0.001;

    std::function< double(double x) > _equation = [](double x) -> double { return pow(x, 3) + 4; };
    std::function< double(double x) >  _equationFirstDerivative
            = [this](double x)
            {
                return ( equation( x + precision) - equation( x - precision) ) / ( 2 * precision );
            };

    initialization(-10, 10, precision, _equation, _equationFirstDerivative);
}

sesTangetSolver::sesTangetSolver(double _rangeMin, double _rangeMax, double _precision,
                std::function< double(double x) > _equation)
{
    std::function< double(double x) >  _equationFirstDerivative
            = [this](double x)
            {
                return equation( x + precision) - equation( x - precision) / ( 2 * precision );
            };


    initialization(_rangeMin, _rangeMax, _precision, _equation, _equationFirstDerivative);
}

sesTangetSolver::sesTangetSolver(double _rangeMin, double _rangeMax, double _precision,
                std::function< double(double x) > _equation,
                std::function< double(double x) > _equationFirstDerivative)
{
    initialization(_rangeMin, _rangeMax, _precision, _equation, _equationFirstDerivative);
}

void sesTangetSolver::initialization(double _rangeMin, double _rangeMax, double _precision,
                                     std::function< double(double x) > _equation,
                                     std::function< double(double x) > _equationFirstDerivative)
{
    equationFirstDerivative = _equationFirstDerivative;
    sesSolver::initialization(_rangeMin, _rangeMax, _precision, _equation);
}

void sesTangetSolver::computeRoot()
{
    double x_n1 = 0, x_n = 0;

    if(rangeMin * rangeMax > 0)
    {
        cout<< "error: function does not intersect X axis" << endl;
        root = 999999;
    }

    else
    {
        if(equationFirstDerivative(rangeMax) < 0)
        {
            x_n1 = rangeMin;
        }
        else
        {
            x_n1 = rangeMax;
        }

        while(abs(x_n1 - x_n) > precision )
        {
            x_n = x_n1;
            x_n1 = x_n - equation(x_n)/equationFirstDerivative(x_n);

           // cout << "x_n+1 = " << x_n1 << " " << "x_n = " << x_n << "\n" << endl;
           // cout << "f(x_n) = " << _equation(x_n) << " " << "f'(x_n) = " << _equationFirstDerivative(x_n) << "\n" << endl;

        }

        root = x_n;
    }

}