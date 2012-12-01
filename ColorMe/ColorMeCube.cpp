/*
 * ColorMeCube.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: Ben
 */

#include "ColorMeCube.h"

ColorMeCube::ColorMeCube() {
}

void ColorMeCube::init()
{

}

void ColorMeCube::start()
{
	position = 0;
}

bool ColorMeCube::update(TimeDelta timeStep)
{
	return false;
}

void ColorMeCube::setVideoBuffer(VideoBuffer* newBuffer)
{
	buffer = newBuffer;
	buffer->bg0.image(vec(0,0), Pick);
}

void ColorMeCube::touched()
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

		// Winner!
		buffer->bg0.image(vec(0,0), FinishFirst);
	}
	else
	{
		// Loser :(
		buffer->bg0.image(vec(0,0), FinishSecond);
	}
}

