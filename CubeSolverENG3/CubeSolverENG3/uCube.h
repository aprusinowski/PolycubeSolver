/*
* File:   uCube.h
*
* Created on April 8, 2016, 3:21 PM
*/

#include "definitions.h"


#ifndef CUBE_H
#define CUBE_H
class uCube {
	typedef uCube* uCubePtr;

public:
	uCube();
	uCube(long coordinates[]);
	uCube(int, int, int);
	uCube(const uCube& orig);

	long get_x();
	long get_y();
	long get_z();
	inline long& _x() { return x; }
	inline long& _y() { return y; }
	inline long& _z() { return z; }
	void calcIndex();
	long* get_coord();
	unsigned long  get_index();
	void moveCube(int, int, int);
	void offsetCube(long, long, long);



	virtual ~uCube() {};
private:

	long x, y, z;
	long temp_x = 0;
	long temp_y = 0;;
	long temp_z = 0;
	long coordinates[3];
	unsigned long index;
};




#endif /* CUBE_H */
