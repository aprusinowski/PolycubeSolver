/*
* File:   dlxSolver.cpp
* 
*
* Created on April 25, 2016, 6:23 PM
*/

#include "dlxSolver.h"
#include "Node.h"
#define HEADNODE -1
using namespace std;

/*************************************************************************
                     SETUP THE NODES
**************************************************************************/
dlxSolver::dlxSolver(long solutionsRequested,allPuzzlePieceConfigs* allConfigs){

	nodePtrVec tempRowNodes;
	nodesVec::iterator nodeIter;

	solutionsFound = 0;
	rowCount = (*allConfigs).size();	
	this->allConfigs = allConfigs;
	this->solutionsRequested = solutionsRequested;
	colCount = NUMGAMEPIECES + CUBEVOLUME;	

	for (long c = 0; c <= colCount; c++)
		columHeads.push_back(Node(HEADNODE));

	setupColHeads(tempRowNodes);	
	addRows(tempRowNodes);
	
	/*Link up bottom row with column headers*/
	nodeIter = columHeads.begin();
	for (Node* nodePtr : tempRowNodes) {
		nodePtr->d = nodeIter._Ptr;
		(nodeIter++)->u = nodePtr;		
	}
}

/* add links the circular two way linked list rows*/
void dlxSolver::linkLR(node_Ptr nodePtr, nodesVec* vect, long& pos, long size)
{
	nodePtr->l = &(vect->at((pos + size - 1) % size));
	nodePtr->r = &(vect->at(((pos++) + 1) % size));
}

/* Sets up the column head nodes circular two way linked list*/
void dlxSolver::setupColHeads(nodePtrVec& tempNodeVec)
{
	long index = 0;
	nodesVec::iterator colIter = columHeads.begin();
	rootNode = (columHeads.end())._Ptr;
	rootNode->r = colIter._Ptr;
	rootNode->l = ((columHeads.end() - 1))._Ptr;

	for (; colIter != columHeads.end(); colIter++) {
		linkLR(colIter._Ptr, &columHeads, index, colCount);
		tempNodeVec.push_back(colIter._Ptr);
	}
	(columHeads.at(0)).l = rootNode;
	(columHeads.at(colCount - 1)).r = rootNode;

}


void dlxSolver::addRows(nodePtrVec& tempRowNodes)
{
	long pieceSize;
	long ucube = 0;
	long pieceNum = 0;
	nodesVec::iterator nodeIter;
	pieceCubeIndexes::iterator nextUnitCubePos;

	/*Iterate through all piece configurations*/
	for (pieceCubeIndexes uniquePiececeCfg : (*allConfigs)) {
		pieceSize = uniquePiececeCfg.size();
		nextUnitCubePos = uniquePiececeCfg.begin();
		newRow = new nodesVec();

		/*add enough nodes to this row for each unit Cube making up
		the puzzlepiece + 1 for the piece ident*/
		for (long pieceIndex : uniquePiececeCfg)
			newRow->push_back(*(new Node(pieceNum)));
		ucube = 0;
		for (nodeIter = (*newRow).begin(); nodeIter != (*newRow).end(); nodeIter++) {
			linkLR(nodeIter._Ptr, newRow, ucube, pieceSize);
			nodeIter->u = tempRowNodes.at(*nextUnitCubePos);
			nodeIter->cHead = &columHeads.at(*nextUnitCubePos);
			tempRowNodes.at(*nextUnitCubePos)->d = nodeIter._Ptr;
			tempRowNodes.at(*nextUnitCubePos) = tempRowNodes.at(*nextUnitCubePos)->d;
			columHeads.at(*nextUnitCubePos++).nodeCount++;
			allRows.push_back((*newRow));
		}
		pieceNum++;
	}


}

/*************************************************************************
                       SOLVE THE CUBE   
**************************************************************************/

bool dlxSolver::dlxStart() {
	iteration++;
	node_Ptr rowStart, rowCol;	

	/*When no columns left a solution is found*/
	if (rootNode == rootNode->l) {
		solutionsFound++;
		allSolutionsFound.push_back(solution);
		return FOUND_SOLUTION;
	}

	/*Find column with fewest 1s*/
	node_Ptr column = newRoot(rootNode);
	CoverColumn(column);

	
	/*Go down the column untill it wraps around back to the column node */
	for (rowStart = column->d; rowStart != column; rowStart = rowStart->d) {

		/*Adding first row to solution. pieceIdent identifies a specific  
		  piece in one specific configuration*/
		solution.push_back(rowStart->pieceIdent);

		/*The columns occupied by this row need to be removed from 
		  solution space*/
		for (rowCol = rowStart->r; rowCol != rowStart; rowCol = rowCol->r)
			CoverColumn(rowCol->cHead);

		/*attempt to solve the reduced problem*/
		dlxStart();
		
		/*If found number of requested solutions return*/
		if (allSolutionsFound.size() == solutionsRequested)
			return FOUND_SOLUTION;

		/*If reached this point, previous call to dlxSolve() picked a 
		  column with no rows or algorithm is looking for more solutions. 
		  The last row added to the solution needs to be removed 
		  and its columns uncovered          */
		solution.pop_back();

		/*Uncover columns belonging to row removed from possible solution in 
		  reverse*/
		for (rowCol = rowStart->l; rowCol != rowStart; rowCol = rowCol->l)
			unCoverColumn(rowCol->cHead);

	}

	/*Previous call to CoverColumn() covered a column with no nodes. 
	Column needs to be uncovered          */
	unCoverColumn(column);


}

/*Finds column with fewest 1s(Nodes attached)*/
node_Ptr dlxSolver::newRoot(node_Ptr r) {

	Node *nodej;
	Node *lowest = rootNode->r;
	long count = 0;
	for (nodej = rootNode->r; nodej != rootNode; nodej = nodej->r) {

		if (lowest->nodeCount > nodej->nodeCount) {
			lowest = nodej;
			count++;
		}
	}

	return lowest;
}



void dlxSolver::CoverColumn(node_Ptr column) {
	node_Ptr rowStart, rowCol;	
	column->coverRow();
	for (rowStart = column->d;rowStart!= column;rowStart=rowStart->d) 
		for (rowCol=rowStart->r;rowCol!=rowStart;rowCol=rowCol->r) 			
			rowCol->coverCol();	
}




void dlxSolver::unCoverColumn(node_Ptr column) {
	node_Ptr rowStart, rowCol;
	for (rowStart=column->u;rowStart!= column;rowStart=rowStart->u) 
		for (rowCol = rowStart->l;rowCol!=rowStart;rowCol=rowCol->l)
			rowCol->unCoverCol();
	column->unCoverRow();
}



puzzlePieceIdent* dlxSolver::getSolution(long solutionNumber)
{
	if(solutionNumber <= solutionsFound)
	return &(allSolutionsFound.at(solutionNumber-1));
}




