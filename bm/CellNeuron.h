/*
 * CellNeuron.h
 *
 *  Created on: Oct 16, 2015
 *      Author: palsol
 */

#ifndef CELLNEURON_H_
#define CELLNEURON_H_

#include <memory>
#include <time.h>
#include "Cell.h"
#include "brainEC/ecNeuron.h"

enum LinkType { INHIBITIVE, EXCITING };

class CellNeuron: public Cell
{

public:

	CellNeuron();
	CellNeuron(int posX, int posY, int posZ);
	virtual ~CellNeuron();

	void  addNeighbor(int neighborId);
	void  addNeighbor(int neighborId, LinkType linkType);


    IonConcentration additionalLinksCurrent;
	vector < LinkType > linksTypes;

};

#endif /* CELLNEURON_H_ */
