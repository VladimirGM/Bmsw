//============================================================================
// Name        : brainSmallWorld_noomp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "bm/SmallWorld.h"
#include "bm/ses/sesChordsSolver.h"

double equationFunc(double x)
{
    double y = x + 10;
    return y;
}

int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	SmallWorld* brain = new SmallWorld(20, 20, 20);
	brain->initAstrocyteLinks();
	brain->initNeuronLinks();

	Cell* testCell = brain->getCell(1, 1, 3);
	testCell->printState();


    std::function< double(double x) > equation = [](double x) -> double { return sin(3.14 * x) + pow(x, 2) - 2; };
    //std::function< double(double x) > equation = equationFunc;
	sesChordsSolver equation0 = *(new sesChordsSolver(100, -100, 0.000001, equation));

	equation0.computeRoot();

	cout << equation0.getRoot() << endl;



	return 0;
}
