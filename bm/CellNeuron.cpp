/*
 * CellNeuron.cpp
 *
 *  Created on: Oct 16, 2015
 *      Author: palsol
 */

#include "CellNeuron.h"

CellNeuron::CellNeuron()
{
    initialization("CellNeuron", NEURON, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10);
}

CellNeuron::CellNeuron(int posX, int posY, int posZ)
{
    initialization("CellNeuron", NEURON, posX, posY, posZ, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10);
}

CellNeuron::~CellNeuron()
{

}

void  CellNeuron::addNeighbor(int neighborId)
{
    srand (time(NULL));
    neighbors.push_back(neighborId);
    if(rand()%2 == 1){ linksTypes.push_back(INHIBITIVE); }
    else{ linksTypes.push_back(EXCITING); }
}

void  CellNeuron::addNeighbor(int neighborId, LinkType linkType)
{
    neighbors.push_back(neighborId);
    linksTypes.push_back(linkType);
}

