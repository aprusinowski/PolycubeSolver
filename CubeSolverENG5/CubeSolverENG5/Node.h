
/*
* File:   DLXNode.h
* Created on April 25, 2016, 6:22 PM
*/
using namespace std;
#ifndef NODE_H
#define NODE_H



class Node {
	typedef Node* node_Ptr;
public:
	Node(long);
	node_Ptr u;
	node_Ptr d;
	node_Ptr l;
	node_Ptr r;
	node_Ptr cHead;
	long nodeCount;
	long pieceIdent;
	void coverRow();
	void coverCol();
	void unCoverRow();
	void unCoverCol();
private:
	
};

#endif /* NODE_H */

