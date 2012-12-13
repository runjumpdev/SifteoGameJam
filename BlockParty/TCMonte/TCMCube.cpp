/*
 * TCMCube.cpp
 *
 *  Created on: Dec 12, 2012
 *      Author: Ben
 */

#include "TCMCube.h"
#include <sifteo/math.h>

TCMCube::TCMCube() {
}

void TCMCube::init(CubeID initCube)
{
	BaseGameCube::init(initCube);

	buffer->bg0.image(vec(0,0), TCMStart);
}

void TCMCube::showKey()
{
	buffer->bg0.image(vec(0,0), TCMBall);
}

void TCMCube::showBlank()
{
	buffer->bg0.image(vec(0,0), White);
}

void TCMCube::displayResult (bool isWinner)
{
	if (isWinner)
	{
		SetPlace (0);
	}
	else
	{
		SetPlace (1);
	}
}

bool TCMCube::isFlipped()
{
	bool retval = false;
	signed int zState = abs(cube.accel().z + 64);

	if (zState < 3)
	{
		retval = true;
	}

	return retval;
}

bool TCMCube::isUpright()
{
	bool retval = false;
	signed int zState = abs(cube.accel().z - 64);

	if (zState < 3)
	{
		retval = true;
	}

	return retval;

}

