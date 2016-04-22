//
// Created by palsol on 18.11.15.
//

#include "sesChordsSolver.h"

sesChordsSolver::sesChordsSolver()
{
    precision = 0.01;

    std::function< double(double x) > _equation = [](double x) -> double { return x; };

    std::function< double(double x) >  _equationFirstDerivative
            = [this](double x)
            {
                return ( equation( x + precision) - equation( x - precision) ) / ( 2 * precision );
            };

    std::function< double(double x) >  _equationSecondDerivative
            = [this](double x)
            {
                return ( equationFirstDerivative( x + precision) - equationFirstDerivative( x - precision) ) / ( 2 * precision );
            };

    initialization(1, -1, precision, _equation, _equationFirstDerivative, _equationSecondDerivative);
}

sesChordsSolver::sesChordsSolver(double _rangeMin, double _rangeMax, double _precision,
                std::function< double(double x) > _equation)
{
    std::function< double(double x) >  _equationFirstDerivative
            = [this](double x)
            {
                return equation( x + precision) - equation( x - precision) / ( 2 * precision );
            };

    std::function< double(double x) >  _equationSecondDerivative
            = [this](double x)
            {
                return ( equationFirstDerivative( x + precision) - equationFirstDerivative( x - precision) ) / ( 2 * precision );
            };

    initialization(_rangeMin, _rangeMax, _precision, _equation, _equationFirstDerivative, _equationSecondDerivative);
}

sesChordsSolver::sesChordsSolver(double rangeMin, double rangeMax, double precision,
                std::function< double(double x) > equation,
                std::function< double(double x) > equationFirstDerivative,
                std::function< double(double x) > equationSecondDerivative)
{
    initialization(rangeMin, rangeMax, precision, equation, equationFirstDerivative, equationSecondDerivative);
}

void sesChordsSolver::initialization(double _rangeMin, double _rangeMax, double _precision,
                    std::function< double(double x) > _equation,
                    std::function< double(double x) > _equationFirstDerivative,
                    std::function< double(double x) > _equationSecondDerivative)
{
    equationSecondDerivative = _equationSecondDerivative;
    sesTangetSolver::initialization(_rangeMin, _rangeMax, _precision, _equation, _equationFirstDerivative);
}

void sesChordsSolver::computeRoot()
{
    double x_n1 = 0, x_n = 0, a = 0, fa = 0;

    if(rangeMin * rangeMax > 0)
    {
        cout<< "error: function does not intersect X axis" << endl;
        root = 999999;
    }

    else
    {
        if(equationSecondDerivative(rangeMax) < 0)
        {
            x_n1 = rangeMax -  equation(rangeMax) * ( rangeMax - rangeMin )
                                / ( equation(rangeMax) - equation(rangeMin) );

            a = rangeMin;
        }
        else
        {
            x_n1 = rangeMin -  equation(rangeMin) * ( rangeMin - rangeMax )
                                / ( equation(rangeMin) - equation(rangeMax) );

            a = rangeMax;
        }

        fa = equation(a);
        while(abs(x_n1 - x_n) > precision )
        {
            x_n = x_n1;
            x_n1 = x_n -  equation(x_n) * ( x_n - a ) / ( equation(x_n) - fa );

            // cout << "x_n+1 = " << x_n1 << " " << "x_n = " << x_n << "\n" << endl;
            // cout << "f(x_n) = " << _equation(x_n) << " " << "f'(x_n) = " << _equationFirstDerivative(x_n) << "\n" << endl;

        }

        root = x_n;
    }

}

