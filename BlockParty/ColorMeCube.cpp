/*
 * ColorMeCube.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: Ben
 */

#include "ColorMeCube.h"

ColorMeCube::ColorMeCube()
{
}

void ColorMeCube::init(CubeID initCube)
{
	BaseGameCube::init(initCube);
	
	buffer->bg0.image(vec(0,0), ColorMeStart);
}

void ColorMeCube::start()
{
	position = 0;
	buffer->bg0.image(vec(0,0), Colors[position]);
}

void ColorMeCube::update(TimeDelta timeStep)
{

}

void ColorMeCube::onTouch()
{
	position++;
	if (position >= arraysize(Colors))
	{
		position = 0;
	}

	buffer->bg0.image(vec(0,0), Colors[position]);
}

void ColorMeCube::gameFinished(int winningColor)
{
	LOG ("game Finished %d\n", winningColor);
	if (position == winningColor)
	{
		//Winner
		SetPlace(0);
	}
	else
	{
		// Loser :(
		SetPlace(1);
	}
}

