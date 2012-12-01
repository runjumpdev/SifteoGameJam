/*
 * ColorMeGame.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: Ben
 */

#include "ColorMeGame.h"

ColorMeGame::ColorMeGame() {
}

void ColorMeGame::init(int numCubes)
{
	actualCubes = numCubes;
}

void ColorMeGame::start()
{

}

bool ColorMeGame::update(TimeDelta timeStep)
{
	return false;
}

void ColorMeGame::touched (unsigned id)
{

}

void ColorMeGame::setVideoBuffer (VideoBuffer buffers[], int count)
{
	for (int i=0; i < count; i++)
	{
		cubes[i].setVideoBuffer(&buffers[i]);
	}
}




