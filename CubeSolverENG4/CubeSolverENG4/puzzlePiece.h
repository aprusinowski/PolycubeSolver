/*
* File:   puzzlePiece.h
*
*
* Created on April 8, 2016, 2:15 PM
*/


#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H

#include "definitions.h"
#include "uCube.h"

class puzzlePiece {
	typedef uCube*                       cubePtr;
	typedef puzzlePiece*                puzzlePiecePtr;
	//typedef std::bitset<CUBELEVELSIZE>  BITSET_Clevel;
	typedef std::bitset<CUBEVOLUME>     BITSET_Cube;

	/*Vector of CUBEVOLUME sized bitset objects. Each bitset represents a specific
	*valid configuration of original puzzle piece. Vector stores all configs.*/
	typedef std::vector<BITSET_Cube>    VECPuzzleVarsBTS;

	/*Vector of indexes of all variations of this puzzle piece*/
	typedef std::vector<long>           VECPuzVarIndx;

	/*Vector of pointers to objects of type puzzlePiece that are variations on this  *
	*puzzlePiece object                                                             */
	typedef vector<puzzlePiecePtr>      VECpuzzlePieceVars;

	/*Transform function pointers*/
	typedef void(*transform)(long&, long&, long&);

public:
	/******************************************************************
	* Constructor for original puzzle piece.                          *
	*Arguments:                                                       *
	*    long   -  size of puzzle piece (Number of unit cube objects) *
	*    long** -  pointer to XYZ coordinate arrays for each unit cube*
	*******************************************************************/
	puzzlePiece(long, long**);

	/******************************************************************
	* Constructor for variations of original puzzle piece             *
	*Arguments:                                                       *
	*    long   -  size of puzzle piece (Number of unit cube objects) *
	*    cubePtr[] - array of unitCube objects                        *
	******************************************************************/
	puzzlePiece(long, cubePtr[MAXPIECESIZE]);

	/********************************************************************************
	* Return a reference to an indentifier for this puzzlePiece                     *
	********************************************************************************/
	long&    pieceIdent() { return pieceIdentifier; }	

	/********************************************************************************
	* Return a Vector of index positions for all variations of the original         *
	* puzzle piece                                                                  *
	*********************************************************************************/
	VECPuzVarIndx&   getPieceLocations() { return cubePositions; }

	/********************************************************************************
	* Return a reference to a Vector of pointers to objects of type puzzlePiece     *
	* which are variations on the original puzzlePiece object                       *
	*********************************************************************************/
	VECpuzzlePieceVars& getAllVariations() { return pieceVariations; }

	/********************************************************************************
	* REturn number of unique variations on the original puzzlePiece object         *
	*                              NOT USED AT THIS TIME                            *
	********************************************************************************/
	long     getNumVars() { return validVariations; }


	/********************************************************************************
	* Outputs XYZ Coordinates for all unitCubes in this puzzlePiece to STDOUT      *
	********************************************************************************/
	void     printPuzzlePiece();

	/********************************************************************************
	* Destructor                                                                    *
	*********************************************************************************/
	virtual ~puzzlePiece();

	static transform transformFunction[NUM_POSSIBLE_VARS];

private:

	void calcMoveBounds();
	void createValidMoves(puzzlePiecePtr);
	puzzlePiecePtr shiftXYZpos(long, long, long);
	void createVariations();
	void addCubeToIndex(unsigned long cubeIndex);
	void rotatePiece(cubePtr[MAXPIECESIZE], long);
	void normalize(cubePtr[MAXPIECESIZE]);
	bool isUniqueVar(cubePtr[MAXPIECESIZE]);
	void addVar(puzzlePiecePtr);

	/********************************************************************************
	* Return a BITSET_Cube object for a single puzzle piece variation               *
	* puzzle piece. Used for checking uniqueness when rotating transforming         *
	*********************************************************************************/
	BITSET_Cube getbitIndex() { return thisPieceIndex; }


	long size;
	long pieceIdentifier;	
	long min_xyz[3];
	long max_xyz[3];
	long numXmvsAllowed;
	long numYmvsAllowed;
	long numZmvsAllowed;
	unsigned long validVariations = 0;
	vector<cubePtr>       allCubes;	
	BITSET_Cube           thisPieceIndex;
	puzzlePiecePtr        tempPiece;
	cubePtr               tempCubes[MAXPIECESIZE];	

	/*Vector of pointers to objects of type puzzlePiece that are variations on this  *
	*puzzlePiece object                                                             */
	VECpuzzlePieceVars    pieceVariations;
	/*Vector of CUBEVOLUME sized bitset objects. Each bitset represents a specific
	*valid configuration of original puzzle piece. Vector stores all configs.*/
	VECPuzzleVarsBTS      cubesIndexBITSET;
	/*Vector of indexes of all variations of this puzzle piece*/
	VECPuzVarIndx         cubePositions;

#define XYZSAVE  long t_x,t_y,t_z; t_x =x;t_y =y;t_z=z;
	static void transform0(long&x, long&y, long&z) { XYZSAVE x = t_x; y = t_y; z = t_z; }
	static void transform1(long&x, long&y, long&z) { XYZSAVE x = t_y; y = t_z; z = t_x; }
	static void transform2(long&x, long&y, long&z) { XYZSAVE x = t_z; y = t_x; z = t_y; }
	static void transform3(long&x, long&y, long&z) { XYZSAVE x = -t_y; y = t_x; z = t_z; }
	static void transform4(long&x, long&y, long&z) { XYZSAVE x = -t_z; y = t_y; z = t_x; }
	static void transform5(long&x, long&y, long&z) { XYZSAVE x = -t_x; y = t_z; z = t_y; }
	static void transform6(long&x, long&y, long&z) { XYZSAVE x = -t_x; y = -t_y; z = t_z; }
	static void transform7(long&x, long&y, long&z) { XYZSAVE x = -t_y; y = -t_z; z = t_x; }
	static void transform8(long&x, long&y, long&z) { XYZSAVE x = -t_z; y = -t_x; z = t_y; }
	static void transform9(long&x, long&y, long&z) { XYZSAVE x = t_y; y = -t_x; z = t_z; }
	static void transform10(long&x, long&y, long&z) { XYZSAVE x = t_z; y = -t_y; z = t_x; }
	static void transform11(long&x, long&y, long&z) { XYZSAVE x = t_x; y = -t_z; z = t_y; }
	static void transform12(long&x, long&y, long&z) { XYZSAVE x = t_x; y = t_z; z = -t_y; }
	static void transform13(long&x, long&y, long&z) { XYZSAVE x = t_y; y = t_x; z = -t_z; }
	static void transform14(long&x, long&y, long&z) { XYZSAVE x = t_z; y = t_y; z = -t_x; }
	static void transform15(long&x, long&y, long&z) { XYZSAVE x = -t_z; y = t_x; z = -t_y; }
	static void transform16(long&x, long&y, long&z) { XYZSAVE x = -t_x; y = t_y; z = -t_z; }
	static void transform17(long&x, long&y, long&z) { XYZSAVE x = -t_y; y = t_z; z = -t_x; }
	static void transform18(long&x, long&y, long&z) { XYZSAVE x = -t_x; y = -t_z; z = -t_y; }
	static void transform19(long&x, long&y, long&z) { XYZSAVE x = -t_z; y = -t_y; z = -t_x; }
	static void transform20(long&x, long&y, long&z) { XYZSAVE x = -t_y; y = -t_x; z = -t_z; }
	static void transform21(long&x, long&y, long&z) { XYZSAVE x = t_z; y = -t_x; z = -t_y; }
	static void transform22(long&x, long&y, long&z) { XYZSAVE x = t_y; y = -t_z; z = -t_x; }
	static void transform23(long&x, long&y, long&z) { XYZSAVE x = t_x; y = -t_y; z = -t_z; }

};

#endif /* PUZZLEPIECE_H */

