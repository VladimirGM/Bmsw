/*
 * CellAstrocyte.h
 *
 *  Created on: Oct 16, 2015
 *      Author: palsol
 */

#ifndef CELLASTROCYTE_H_
#define CELLASTROCYTE_H_

#include "Cell.h"

class CellAstrocyte: public Cell
{
public:

	CellAstrocyte();
	CellAstrocyte(int posX, int posY, int posZ);
	virtual ~CellAstrocyte();

};

#endif /* CELLASTROCYTE_H_ */
