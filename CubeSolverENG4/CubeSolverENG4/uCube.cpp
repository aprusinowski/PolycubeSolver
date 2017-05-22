/*
* File:   uCube.cpp
* 
*
* Created on April 8, 2016, 3:22 PM
*/

#include "uCube.h"
uCube::uCube()
{
	x = 0;
	y = 0;
	z = 0;
	index = 0;
	coordinates[0] = 0;
	coordinates[1] = 0;
	coordinates[2] = 0;

}

uCube::uCube(long coordinates[])
{
	x = coordinates[0];
	y = coordinates[1];
	z = coordinates[2];
	this->coordinates[0] = x;
	this->coordinates[1] = y;
	this->coordinates[2] = z;

	calcIndex();
}

uCube::uCube(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	coordinates[0] = x;
	coordinates[1] = y;
	coordinates[2] = z;

	calcIndex();
}
uCube::uCube(const uCube& orig)
{
	x = orig.x;
	y = orig.y;
	z = orig.z;
	coordinates[0] = orig.coordinates[0];
	coordinates[1] = orig.coordinates[1];
	coordinates[2] = orig.coordinates[2];
	index = orig.index;
}

void uCube::moveCube(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	coordinates[0] = this->x;
	coordinates[1] = this->y;
	coordinates[2] = this->z;
	calcIndex();
}

void uCube::offsetCube(long x_offst, long y_offst, long z_offst)
{
	x = x - x_offst;
	y = y - y_offst;
	z = z - z_offst;
	coordinates[0] = x;
	coordinates[1] = y;
	coordinates[2] = z;
	calcIndex();
}

long uCube::get_x()
{
	return x;
}

long uCube::get_y()
{
	return y;
}

long uCube::get_z()
{
	return z;
}



long* uCube::get_coord()
{
	coordinates[0] = this->x;
	coordinates[1] = this->y;
	coordinates[2] = this->z;
	return coordinates;
}

unsigned long uCube::get_index()
{
	return index;
}

void uCube::calcIndex()
{
	index = (y*CUBELEVELSIZE) + (z*CUBEDIMSIZE) + x;
}





