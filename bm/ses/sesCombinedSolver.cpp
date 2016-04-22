//
// Created by palsol on 18.11.15.
//

#include "sesCombinedSolver.h"

sesCombinedSolver::sesCombinedSolver()
{
    std::function< double(double x) > equation = [](double x) -> double { return x; };
    initialization(1, 1, 0.01, equation);
}