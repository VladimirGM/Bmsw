/*
 * Cell.h
 *
 *  Created on: Oct 16, 2015
 *      Author: palsol
 */

#ifndef CELL_H_
#define CELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "brainEC/ecConstant.h"

enum TypeCell { EMPTY, NEURON, ASTROCYTE };

using namespace std;

struct cellVec3
{
	int x, y, z;
};

class Cell
{

public:

	Cell();
	Cell(int posX, int posY, int posZ);
	Cell(cellVec3 pos);

	virtual ~Cell();

	void initialization(string _name, TypeCell _type, int posX, int posY, int posZ,
						double _inConcentrationCa2, double _outConcentrationCa2,
						double _inConcentrationK,   double _outConcentrationK,
						double _inConcentrationNa,  double _outConcentrationNa,
						double _inConcentrationCl,  double _outConcentrationCl,
						double _inConcentrationGlu, double _outConcentrationGlu,
						double _ATP, double numStoredDiffusionSteps);


	virtual void addNeighbor(int neighborId);
	virtual void printState();


	string name;
    TypeCell type;
	cellVec3 pos;

	vector < int > neighbors;
	IonConcentration W, oldW;
	IonConcentration U, oldU;
    double V, oldV;

	int numStoredSteps;
	int lifeTime;
    vector < IonConcentration > F;

	double ATP;

};


#endif /* CELL_H_ */
