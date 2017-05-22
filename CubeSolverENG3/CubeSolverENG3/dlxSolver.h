
/*
* File:   dlxSolver.h
*
* Created on April 25, 2016, 6:23 PM
*/

#include "definitions.h" 
#include "Node.h"

using namespace std;
#ifndef DLXSOLVER_H
#define DLXSOLVER_H

typedef vector<Node>  nodesVec;
typedef vector<Node*> nodePtrVec;
typedef std::vector<long>    puzzlePieceIdent;
typedef vector<vector<long> > allPuzzlePieceConfigs;
typedef Node* node_Ptr;
#define FOUND_SOLUTION true

class dlxSolver {
public:

	dlxSolver(long,allPuzzlePieceConfigs*);
	bool findSolutions() { return dlxStart(); }
	puzzlePieceIdent* getSolution(long);

private:

	Node*rootNode;
	long colCount;;
	long rowCount;
	long solutionsRequested;	
	long solutionsFound;
	long iteration = 0;

	nodesVec columHeads;//cols
	vector<nodesVec> allRows;//rows
	nodesVec uniquePieceNodes;	
	nodesVec* newRow;
	allPuzzlePieceConfigs* allConfigs;
	PieceConfigSets allSolutionsFound;
	puzzlePieceIdent solution;

	void linkLR(node_Ptr, nodesVec*, long&, long);
	void setupColHeads(nodePtrVec&);
	void addRows(nodePtrVec&);

	bool dlxStart();
	node_Ptr newRoot(node_Ptr);
	void CoverColumn(node_Ptr);
	void unCoverColumn(node_Ptr);

	
	

};

#endif /* DLXSOLVER_H */