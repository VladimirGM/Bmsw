/*
 * SmallWorld.h
 *
 *  Created on: Oct 16, 2015
 *      Author: palsol
 */

#ifndef SMALLWORLD_H_
#define SMALLWORLD_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <memory>
#include <time.h>
#include <iostream>

using namespace std;

#include "Cell.h"
#include "CellNeuron.h"
#include "CellAstrocyte.h"

#include "voro++/voro++.hh"


class SmallWorld
{

public:

	SmallWorld();
	SmallWorld(int sizeX, int sizeY, int sizeZ);
	~SmallWorld();


	void initialization(int _sizeX, int _sizeY, int _sizeZ);
	bool initAstrocyteLinks();
	bool initNeuronLinks();

	double LinksInd(vector<int> &vlink, int i);
	vector<double> Possibilites(vector<double> &line, int suml, int ID);

	void computeAdditionalNeuronLinksCurrent(int id);

	unsigned long getSize();
	Cell* getCell(int i);
	Cell* getCell(int posX, int posY, int posZ);

private:

	int sizeX, sizeY, sizeZ;
	std::vector< unique_ptr<Cell> > cells;

};

#endif /* SMALLWORLD_H_ */
