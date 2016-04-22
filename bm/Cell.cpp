/*
 * Cell.cpp
 *
 *  Created on: Oct 16, 2015
 *      Author: palsol
 */

#include "Cell.h"

Cell::Cell()
{
	initialization("Cell", EMPTY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10);
}

Cell::Cell(int posX, int posY, int posZ)
{
	initialization("Cell", EMPTY, posX, posY, posZ, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10);
}

Cell::Cell(cellVec3 pos)
{
	initialization("Cell", EMPTY, pos.x, pos.y, pos.z, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10);
}

Cell::~Cell()
{

}

void Cell::initialization(string _name, TypeCell _type, int posX, int posY, int posZ,
						  double _inConcentrationCa2, double _outConcentrationCa2,
						  double _inConcentrationK,   double _outConcentrationK,
						  double _inConcentrationNa,  double _outConcentrationNa,
						  double _inConcentrationCl,  double _outConcentrationCl,
						  double _inConcentrationGlu, double _outConcentrationGlu,
						  double _ATP, double numStoredDiffusionSteps)
{
	name = _name;
	type = _type;
	pos.x = posX;
	pos.y = posY;
	pos.z = posZ;

	W.Calcium   = _inConcentrationCa2;
	W.Potassium = _inConcentrationK;
	W.Natrium   = _inConcentrationNa;
	W.Chlorine  = _inConcentrationCl;
	W.Glutamate = _inConcentrationGlu;

	U.Calcium   = _outConcentrationCa2;
	U.Potassium = _outConcentrationK;
	U.Natrium   = _outConcentrationNa;
	U.Chlorine  = _outConcentrationCl;
	U.Glutamate = _outConcentrationGlu;

	ATP = _ATP;

	lifeTime = 0;
	numStoredSteps = numStoredDiffusionSteps;
	F.resize(numStoredSteps);
}

void Cell::addNeighbor(int neighborId)
{
    neighbors.push_back(neighborId);
}

void Cell::printState()
{
	std::cout
	<< "x: " << pos.x << " y: " << pos.y << " z: " << pos.z
	<<" name: " << name << "\n"
	<<" type: " << type  << "\n" << "\n"
	<<" concentration: " << "\n"
	<<"  Ca2+: " << W.Calcium
	<<" K+: "    << W.Potassium
	<<" Na+: "   << W.Natrium
	<<" Cl-: "   << W.Chlorine
	<<" glu: "   << W.Glutamate << "\n" << "\n"
    <<" neighbors: "
    << std::endl;

    for(int i = 0; i < neighbors.size(); i++)
    {
       std::cout
       << "  id: "  <<  i
       << "\n  smId: " <<  neighbors[i]  << std::endl;

    }

}
