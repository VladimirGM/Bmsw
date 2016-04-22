/*
 * CellAstrocyte.cpp
 *
 *  Created on: Oct 16, 2015
 *      Author: palsol
 */

#include "CellAstrocyte.h"

CellAstrocyte::CellAstrocyte()
{
    initialization("CellAstrocyte", ASTROCYTE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10);
}

CellAstrocyte::CellAstrocyte(int posX, int posY, int posZ)
{
    initialization("CellAstrocyte", ASTROCYTE, posX, posY, posZ, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10);
}

CellAstrocyte::~CellAstrocyte()
{

}

