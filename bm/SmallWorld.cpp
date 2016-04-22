/*
 * SmallWorld.cpp
 *
 *  Created on: Oct 16, 2015
 *      Author: palsol
 */


#include "SmallWorld.h"


using namespace voro;

//#define DEBUGPPRIT

SmallWorld::SmallWorld()
{
	initialization(0, 0, 0);
}

SmallWorld::SmallWorld(int sizeX, int sizeY, int sizeZ)
{
	initialization(sizeX, sizeY, sizeZ);
}

SmallWorld::~SmallWorld()
{

}

unsigned long SmallWorld::getSize()
{
	return cells.size();
}

Cell* SmallWorld::getCell(int i)
{
	return cells[i].get();
}

Cell* SmallWorld::getCell(int posX, int posY, int posZ)
{
	return cells[posX * sizeY * sizeZ + posY * sizeY + posZ].get();
}


void SmallWorld::initialization(int _sizeX, int _sizeY, int _sizeZ)
{
	sizeX = _sizeX;
	sizeY = _sizeY;
	sizeZ = _sizeZ;

	srand (time(NULL));
	int random = 0;

	for(int i = 0; i < sizeX; i++){
		for(int j = 0; j < sizeY; j++){
			for(int k = 0; k < sizeZ; k++)
			{
				random = rand()%100;

				if(random > 66)
				{
					cells.push_back( unique_ptr<Cell> (new CellAstrocyte(i, j, k)));
				}

				else if ( random < 66 && random > 33)
				{
					cells.push_back( unique_ptr<Cell> (new CellNeuron(i, j, k)));
				}

				else
				{
					cells.push_back( unique_ptr<Cell> (new Cell(i, j, k)));
				}
			}
		}
	}

}

bool SmallWorld::initAstrocyteLinks()
{
	int id = 0;
	int nx, ny, nz;
	double x, y, z;

	vector < cellVec3 > astrocytePositions;
	cellVec3 astrocytePosition = {0, 0, 0};

	voronoicell_neighbor voroniCell;
	Cell* cell;

	pre_container precon(0, sizeX, 0, sizeY, 0, sizeZ, false, false, false);

	for(int i = 0; i < cells.size(); i++)
	{
		cell = cells[i].get();

		if(cell->type == ASTROCYTE)
		{
			x = cell->pos.x;
			y = cell->pos.y;
			z = cell->pos.z;

			precon.put(id, x, y, z);

#ifdef DEBUGPPRIT
			cout << " id : " << id << "\n"
				 << " x : " << x
				 << " y : " << y
				 << " z : " << z
			     << " type : " << cell->getType() << endl;
#endif

			astrocytePosition.x = x;
			astrocytePosition.y = y;
			astrocytePosition.z = z;
			astrocytePositions.push_back(astrocytePosition);

			id++;
		}
	}

	precon.guess_optimal(nx, ny, nz);
	container con(0, sizeX, 0, sizeY, 0, sizeZ, nx, ny, nz, false, false, false, 8);
	precon.setup(con);

#ifdef DEBUGPPRIT
	double cvol=(_sizeX-0)*(_sizeY-0)*(_sizeZ-0);
	double vvol = con.sum_cell_volumes();

	cout
	<< "\n Container volume :" << cvol
	<< "\n Voronoi volume : " <<  vvol
	<< "\n Difference : " <<  vvol - cvol << "\n"
	<< endl;
#endif


	vector<int> neighbors;
	c_loop_all clo(con);
	if(clo.start()) do if(con.compute_cell(voroniCell, clo))
			{
				voroniCell.neighbors(neighbors);
				clo.pos(x, y, z);
				cell = cells[x * sizeY * sizeZ + y * sizeY + z].get();

#ifdef DEBUGPPRIT
				cout
				<< "cell  id  :" << clo.pid() << "\n"
				<< " x : " <<  x
				<< " y : " <<  y
				<< " z : " <<  z <<	"\n"
				<< endl;
#endif

				cell->neighbors.clear();

				for(int i = 0; i < neighbors.size(); i++)
				{
					if(neighbors[i] >= 0)
					{
						cell->addNeighbor(astrocytePositions[neighbors[i]].x * sizeY * sizeZ +
										  astrocytePositions[neighbors[i]].y * sizeY +
										  astrocytePositions[neighbors[i]].z);
					}
#ifdef DEBUGPPRIT
                    cout << "neighbor id : " << neighbors[i] << "\n" << endl;
#endif
				}

#ifdef DEBUGPPRIT
				printf("--------------------- \n");
#endif

			} while (clo.inc());

}

double SmallWorld::LinksInd(vector<int> &vlink, int i)
{


	Cell* cell;
	cell = cells[vlink[i]].get();

	return (double) cell->neighbors.size();
}

vector<double> SmallWorld::Possibilites(vector<double> &line, int suml, int ID)
{
	vector<double> pos;
	pos.resize(ID);
	double sum = 0;
	for(int i = 0;  i < pos.size(); i++)
	{
		pos[i] = 100*(line[i]/ suml);
		sum = sum + pos[i];
	}
	//cout << "sum" << sum << endl;
	return pos;
}

bool SmallWorld::initNeuronLinks()
{
	int id = 0;
	Cell *cell;
	Cell * celld;
	vector<int> Nlink(0);
	//cout << 1 << endl;
	for (int i = 0; i < getSize(); i++)
	{
		cell = getCell(i);
		//cout << cell->type << endl;
		if (cell->type == NEURON)
		{
			Nlink.push_back(i);
			cout << i <<"and"<< Nlink[Nlink.size()-1] << endl;
			id++;
		};
	}
	cout << Nlink.size() << endl;
	//vector<vector<int>> NLINK;
	int ran = 0;
	double randomize;
	long int linkSum = 0;//?????????? ?????? ? ???????
//	cout << 2 << endl;
	for (int i = 0; i < 4; i++)
	{
		cell = cells[Nlink[i]].get();

		if (i == 0) { ran = 1; }

		for (int j = 0; j < ran; j++)
		{
			int randomiz = rand() % 3 + 4;//? ???? ??????????????
			while (randomiz == i) { randomiz = rand() % 7 + 1; }

			cell->addNeighbor(Nlink[randomiz]);
			celld = cells[Nlink[randomiz]].get();
			celld->addNeighbor(Nlink[i]);

		}

		linkSum =linkSum + 2*ran;
		ran = rand() % (int)(linkSum/2) + 1;
		//cout<<ran << " " << linkSum<<endl;// ? ????? ??????????? ??????
		// ?????????? ????????? ???????
	}

	//cout << 3 << endl;
	vector<double> Individ;
	for (int i = 0; i < Nlink.size(); i++)
	{
		Individ.push_back(LinksInd(Nlink, i));
	}

	vector<double> POS;
	vector<int> NoPair(id);

	for (int i = 1; i < NoPair.size(); i++)
	{
		NoPair[i] = 0;
	}
	//cout << 4 << endl;
	for (int i = 8; i < id; i++)
	{
		double svyaz = 0;

		cell = cells[Nlink[i]].get();
		//cout << 5 << endl;
		NoPair[0] = 1;
		ran = rand() % (int)(linkSum/8)+1;
		//cout << ran << endl;

		POS = Possibilites(Individ, (int)linkSum, id);
		//cout << "!!!!" << POS[0] << endl;
		#pragma omp  parallel for num_threads(4)
		for (int K = 0; K < ran; K++)
		{
			double ost = 100 - POS[0];
			//int bouran= rand()%15;
			randomize = (double)rand()/RAND_MAX*(100-0);
			//cout << randomize << endl;
			double trrand = rand()%5+5;
			bool Tr = false;

			if(randomize > 100.0 - POS[0] && POS[0] > rand())
			{
				if(NoPair[0] != 0)
				{
					celld = cells[Nlink[0]].get();
					celld->addNeighbor(Nlink[i]);
					cell->addNeighbor(Nlink[0]);


					Tr = true;
					//
					svyaz++;
					NoPair[0] = 0;
				}
				else
				{
					randomize = (double) rand()/RAND_MAX*(ost - 0);
				}
			}

			if(K == ran - 1){ NoPair[0] = 1; Tr = false; }

			double PB = 100.0 - POS[0];

			for(int j = 1; j < id && j != i; j++)
			{
				if(Tr == true){break;}
				ost = ost - POS[j];


				if (randomize > PB - POS[j] && randomize < PB && POS[j] > trrand ) //&& POS[j] > bouran)
				{
					if(NoPair[j] != j) {

						cell->addNeighbor(Nlink[j]);
						celld = cells[Nlink[j]].get();
						celld->addNeighbor(Nlink[i]);
						NoPair[j] = j;
						Tr = true;
						svyaz++;
					}


						else
						{
							randomize = (double) rand() / RAND_MAX * (ost - 0);
						}
				}

				if(K == ran-1){NoPair[j] = 0; Tr = false;}
				PB = PB - POS[j];
			}
			//cout << i << endl;
		}
		//POS.clear();
		//NoPair.clear();
		linkSum += 2*svyaz;
		//cells[Nlink[i]]->printState();
		Individ.clear();
		for (int u = 0; u < Nlink.size(); u++)
		{
			Individ.push_back(LinksInd(Nlink, u));
		}

		//cout << id << endl << endl;
	}

	cout << linkSum << endl;
}


void SmallWorld::computeAdditionalNeuronLinksCurrent(int id)
{
	CellNeuron* cell =  (CellNeuron*)cells[id].get();
	Cell* neighborCell;
	double aLink = 0;

	if(cell -> type == NEURON)
	{
		IonConcentration additionalCurrent;

		for(int i = 0; i < cell->neighbors.size(); i++)
		{
			if(neighborCell->oldV < Vact){ aLink = 0;}
			else if(cell->linksTypes[i] == INHIBITIVE){ aLink = (-1) * a0; }
			else if(cell->linksTypes[i] == EXCITING){ aLink = a0; }

			neighborCell = cells[ cell->neighbors[i] ].get();
			additionalCurrent.Calcium += aLink * ecNeuronCalcium(neighborCell->oldV, cell->oldW, cell->oldU) * neighborCell->oldV ;
		}
	}

}

