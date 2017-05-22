/*
* File:   puzzlePiece.cpp
*
* Created on April 8, 2016, 2:15 PM
*/


#include "puzzlePiece.h"

using namespace std;

/******************************************************************************
*                                                                             *
* Constructor                                                                 *
*                                                                             *
*                                                                             *
******************************************************************************/
puzzlePiece::puzzlePiece(long size, long** coordinates)
{
	long level;
	long index;
	this->size = size;

	validVariations = 0;
	thisPieceIndex = BITSET_Cube();

	/*Stores the bitset pattern for each piece. 
	 Used for comparing all variations*/
	cubesIndexBITSET = VECPuzzleVarsBTS();

	/*Stores Index numbers of all unit cubes making up this puzzle piece*/
	cubePositions = VECPuzVarIndx();

	/*Stores pointers to variations of original puzzle piece.
	  Only used in original*/
	pieceVariations = std::vector<puzzlePiecePtr>();

	for (long i = 0; i < size; i++)
		tempCubes[i] = new uCube(coordinates[i]);

	normalize(tempCubes);

	for (long i = 0; i < size; i++) {
		index = tempCubes[i]->get_index();
		level = tempCubes[i]->get_y();
		allCubes.push_back(new uCube(*tempCubes[i]));
		thisPieceIndex.set(index, TRUE);
		addCubeToIndex(index);
	}

	addVar(this);
	createValidMoves(this);
	createVariations();
}


/******************************************************************************
*Constructor for variations. Does not call createVariations                   *
*otherwise we would get an infinite loop                                      *
*                                                                             *
*                                                                             *
******************************************************************************/

puzzlePiece::puzzlePiece(long size, uCubePtr cubes[MAXPIECESIZE])
{
	long index;
	long level;
	this->size = size;

	for (long i = 0; i < size; i++) {
		index = cubes[i]->get_index();
		allCubes.push_back(cubes[i]);
		addCubeToIndex(index);
		level = allCubes.at(i)->get_y();
	}
}

/******************************************************************************

******************************************************************************/
puzzlePiece::~puzzlePiece() {

	allCubes.clear();
	pieceVariations.clear();
	cubesIndexBITSET.clear();
	cubePositions.clear();

}

/******************************************************************************

******************************************************************************/
void puzzlePiece::createVariations()
{
	long count = 0;
	for (long i = 0; i < NUM_POSSIBLE_VARS; i++) {

		for (long j = 0; j < size; j++)
			tempCubes[j] = new uCube(allCubes.at(j)->get_coord());

		rotatePiece(tempCubes, i);
		normalize(tempCubes);

		if (isUniqueVar(tempCubes)) {
			addVar(new puzzlePiece(size, tempCubes));
			(*(pieceVariations.back())).createValidMoves(this);
			count++;
		}
	}
}

/******************************************************************************

******************************************************************************/
void puzzlePiece::addVar(puzzlePiecePtr newPiece) {
	pieceVariations.push_back(newPiece);
	cubesIndexBITSET.push_back(newPiece->getbitIndex());
	validVariations++;
}
/******************************************************************************

******************************************************************************/
bool puzzlePiece::isUniqueVar(uCubePtr cubes[MAXPIECESIZE])
{
	BITSET_Cube tmpBitset;

	for (long i = 0; i < size; i++)
		tmpBitset.set(cubes[i]->get_index());

	for (long i = 0; i < validVariations; i++)
		if ((tmpBitset ^ cubesIndexBITSET.at(i)).none()) 
			return false;

	return true;
}
/******************************************************************************

******************************************************************************/
void puzzlePiece::addCubeToIndex(unsigned long cubeIndex) {
	/*sets the bit number equal to this cube's index position
	 (0 - CUBEVOLUME)                                      */
	thisPieceIndex.set(cubeIndex, TRUE);

	/*Store location of this unit cube*/
	cubePositions.push_back(cubeIndex);
}
/******************************************************************************

******************************************************************************/
void puzzlePiece::rotatePiece(uCubePtr  c[MAXPIECESIZE], long vr)
{
	for (long i = 0; i < size; i++) {
		transformFunction[vr](c[i]->_x(), c[i]->_y(), c[i]->_z());
		c[i]->calcIndex();
	}
}

/******************************************************************************

******************************************************************************/
void puzzlePiece::normalize(uCubePtr cubes[MAXPIECESIZE])
{
	min_xyz[X] = cubes[0]->get_x();
	min_xyz[Y] = cubes[0]->get_y();
	min_xyz[Z] = cubes[0]->get_z();

	for (long i = 1; i < size; i++)
	{
		long x = cubes[i]->get_x();
		long y = cubes[i]->get_y();
		long z = cubes[i]->get_z();
		
		if (x < min_xyz[X])
			min_xyz[X] = x;	

		if (y < min_xyz[Y]) 
			min_xyz[Y] = y;
		
		if (z < min_xyz[Z]) 
			min_xyz[Z] = z;
	}

	//move all cubes of this piece by the calculated offsets
	if (min_xyz[X] || min_xyz[Y] || min_xyz[Z])
		for (long i = 0; i < size; i++) 
			cubes[i]->offsetCube(min_xyz[X], min_xyz[Y], min_xyz[Z]);
}

/******************************************************************************

******************************************************************************/

void puzzlePiece::calcMoveBounds()
{
	long x;
	long y;
	long z;
	numXmvsAllowed = 0;
	numYmvsAllowed = 0;
	numZmvsAllowed = 0;
	max_xyz[X] = allCubes[0]->get_x();
	max_xyz[Y] = allCubes[0]->get_y();
	max_xyz[Z] = allCubes[0]->get_z();

	for (long i = 1; i < size; i++)
	{
		x = allCubes[i]->get_x();
		y = allCubes[i]->get_y();
		z = allCubes[i]->get_z();

		if (x > max_xyz[X])
			max_xyz[X] = x;

		if (y > max_xyz[Y])
			max_xyz[Y] = y;

		if (z > max_xyz[Z])
			max_xyz[Z] = z;
	}
	numXmvsAllowed = (CUBEDIMSIZE - max_xyz[X]);
	numYmvsAllowed = (CUBEDIMSIZE - max_xyz[Y]);
	numZmvsAllowed = (CUBEDIMSIZE - max_xyz[Z]);

}


/******************************************************************************

******************************************************************************/
void puzzlePiece::createValidMoves(puzzlePiecePtr originalPiece)
{
	calcMoveBounds();
	for (long x = 0; x < numXmvsAllowed; x++)
		for (long z = 0; z < numZmvsAllowed; z++)
			for (long y = 0; y < numYmvsAllowed; y++) {

				if (x || z || y) {
					originalPiece->addVar(shiftXYZpos(x, y, z));


				}
			}
}

/******************************************************************************

******************************************************************************/
puzzlePiecePtr puzzlePiece::shiftXYZpos(long x, long y, long z)
{
	long* newXYZ;
	for (long i = 0; i < size; i++) {
		newXYZ = (allCubes.at(i))->get_coord();
		tempCubes[i] = new uCube(newXYZ[X] + x, newXYZ[Y] + y, newXYZ[Z] + z);
		//thisPieceIndex.set((tempCubes[i])->get_index());         
	}

	return (new puzzlePiece(size, tempCubes));

}

void puzzlePiece::printPuzzlePiece()
{	
	cout << pieceIdentifier << endl;
	cout << size << endl;
	for (long i = 0; i< size; i++)
	{
		cout << cubePositions[i] << endl;
	}

}


puzzlePiece::transform puzzlePiece::transformFunction[] = {

	&puzzlePiece::transform0,
	&puzzlePiece::transform1,
	&puzzlePiece::transform2,
	&puzzlePiece::transform3,
	&puzzlePiece::transform4,
	&puzzlePiece::transform5,
	&puzzlePiece::transform6,
	&puzzlePiece::transform7,
	&puzzlePiece::transform8,
	&puzzlePiece::transform9,
	&puzzlePiece::transform10,
	&puzzlePiece::transform11,
	&puzzlePiece::transform12,
	&puzzlePiece::transform13,
	&puzzlePiece::transform14,
	&puzzlePiece::transform15,
	&puzzlePiece::transform16,
	&puzzlePiece::transform17,
	&puzzlePiece::transform18,
	&puzzlePiece::transform19,
	&puzzlePiece::transform20,
	&puzzlePiece::transform21,
	&puzzlePiece::transform22,
	&puzzlePiece::transform23
};




