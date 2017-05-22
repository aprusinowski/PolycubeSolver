
/*
* File:   DLXNode.cpp
*
* Created on April 25, 2016, 6:22 PM
*/
#include "Node.h"

Node::Node(long id)
{	
	pieceIdent = id;
	nodeCount = 0;
}
void Node::coverRow() {
	r->l = l;
	l->r = r;	
}

void Node::coverCol() {
	u->d = d;
	d->u = u;
	cHead->nodeCount--;
}

void Node::unCoverRow() {
	r->l = this;
	l->r = this;	
}

void Node::unCoverCol() {
	u->d = this;
	d->u = this;
	cHead->nodeCount++;
}