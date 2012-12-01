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

}

bool ColorMeCube::update(TimeDelta timeStep)
{
	return false;
}

void ColorMeCube::setVideoBuffer(VideoBuffer* newBuffer)
{
	buffer = newBuffer;
	buffer->bg0.image(vec(0,0), First);
}

