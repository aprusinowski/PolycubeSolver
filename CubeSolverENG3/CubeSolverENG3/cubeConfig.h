
/*
* File:   cubeConfig.h

* Created on April 8, 2016, 2:16 PM
*/

#ifndef CUBECONFIG_H
#define CUBECONFIG_H
#include "definitions.h"

class cubeConfig {
	typedef std::vector<puzzlePiecePtr>              allPuzzlePieces;
	typedef puzzlePiece*                             puzzlePiecePtr;
	typedef std::unordered_map<long, xyzVect*>       indexToCoordMap;
	typedef std::unordered_map<long, puzzlePiecePtr> p_identToPuzzlePMAP;
	typedef vector<vector<long>>                     PieceConfigSets;	

public:
	cubeConfig();

	/*Enables adding an original puzzle piece using XYZ coordinates*/
	void addPuzzlePiece(long, long, long**);

	/*Enables adding an original puzzle piece using the index  number 
	  0 to CUBEVOLUME*/
	void addPuzzlePieceViaIndex(pieceCubeIndexes*);

	PieceConfigSets& getAllBitSets() { return allPuzzlePieceIndexes; }
	puzzlePiecePtr   getPuzzlePieceNum(long);	
	long getPieceCount() { return puzzlePieceCount; }
	virtual ~cubeConfig();
private:

	long nColumns;
	long nRows;
	allPuzzlePieces      allPieces;
	pieceCubeIndexes     cubeIndexes;
	indexToCoordMap      indexToXYZ;
	PieceConfigSets      allPuzzlePieceIndexes;
	p_identToPuzzlePMAP  pIdentNumToPuzzlePiece;


	/*Total number of puzzle pieces. Includes rotations,
	  reflections and moves*/
	long puzzlePieceCount;

	/*Identifying number for each of the puzzle pieces 
      used to build a cube. All rotations, reflections 
	  and moves of a piece will inherit the same identifying
	  number so that a piece is not used more than once in 
	  the solution                                         */
	long gamePieceIdent;

	/*Create a 1 to 1 mapping of XYZ coordinates to the 0      
	  to CUBEVOLUME index of every location in the cube        */
	void initIndxMap();


};

#endif /* CUBECONFIG_H */

