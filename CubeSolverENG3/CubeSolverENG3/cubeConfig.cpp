
/*
* File:   cubeConfig.cpp* 
*
* Created on April 8, 2016, 2:16 PM
*/

#include "cubeConfig.h"
#include "definitions.h"
#include "puzzlePiece.h"

cubeConfig::cubeConfig()
{
	/*Total number of puzzle pieces. Includes rotations, reflections and moves*/
	puzzlePieceCount = 0;

	//allPieces = allPuzzlePieces();
	//colPieceLookup = colToPieceMap();
	nColumns = CUBEVOLUME;

	/*Identifying number for each of the puzzle pieces used to build a cube. All
	rotations, reflections and moves of a piece will inherit the same identifying
	number so that a piece is not used more than once in the solution*/
	gamePieceIdent = CUBEVOLUME;

	/*Create a 1 to 1 mapping of XYZ coordinates to the 0 to CUBEVOLUME 
	location in the cube*/	
	initIndxMap();
}

cubeConfig::~cubeConfig() {
	/*deletes all puzzlePiece objects created*/
	allPieces.clear();
}

/*Enables adding an original puzzle piece using the index  number 
  0 to CUBEVOLUME*/
void cubeConfig::addPuzzlePieceViaIndex(pieceCubeIndexes* cubeIndexes)
{
	long** xyzCoord = new long*[cubeIndexes->size()];

	long i = 0;
	for (long j : *(cubeIndexes)) {
		xyzCoord[i] = new long[3];
		xyzCoord[i][X] = (indexToXYZ[j])->at(0);
		xyzCoord[i][Y] = (indexToXYZ[j])->at(1);
		xyzCoord[i][Z] = (indexToXYZ[j])->at(2);
		i++;
	}
	addPuzzlePiece(puzzlePieceCount, cubeIndexes->size(), xyzCoord);

}

/*Enables adding an original puzzle piece using XYZ coordinates*/
void cubeConfig::addPuzzlePiece(long ident, long size, long** coordinates) {

	/*Vector of columns in the 0 - CUBEVOLUME index occupied by a puzzle piece*/
	columnVector colsOccupied;
	VECpuzzlePieceVars pieceVariations;
	puzzlePiecePtr tempPiecePntr = new puzzlePiece(size, coordinates);
	pieceVariations = tempPiecePntr->getAllVariations();

	for (puzzlePiecePtr p : pieceVariations) {

		(p->pieceIdent()) = ident;

		/* Necessary for algorithm in order not to select same piece 
		   more than once                                          */
		(p->getPieceLocations()).push_back(gamePieceIdent);
		allPuzzlePieceIndexes.push_back(p->getPieceLocations());
		pIdentNumToPuzzlePiece[puzzlePieceCount] = p;

		/*Use this in destructor to delete all allocated objects*/
		allPieces.push_back(p);
		puzzlePieceCount++;
	}
	gamePieceIdent++;

}

/*Create a 1 to 1 mapping of XYZ coordinates to the 0 to CUBEVOLUME index of *
*every location in the cube                                                 */
void cubeConfig::initIndxMap()
{
	long index = 0;
	xyzVect* tmp;

	for (long y = 0; y < CUBEDIMSIZE; y++) 
		for (long z = 0; z < CUBEDIMSIZE; z++) 
			for (long x = 0; x < CUBEDIMSIZE; x++) {
				tmp = new xyzVect();
				tmp->push_back(x); tmp->push_back(y); tmp->push_back(z);
				indexToXYZ[index] = tmp;
				index++;
			}
}

/*Returns pointer to 1 out puzzlePieceCount possible  puzzlePiece objects*/
puzzlePiecePtr cubeConfig::getPuzzlePieceNum(long pieceNumber)
{
	return pIdentNumToPuzzlePiece[pieceNumber];
}









