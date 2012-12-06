/*
 * HotCubeCube.cpp
 *
 *  Created on: Dec 5, 2012
 *      Author: Ben
 */

#include "HotCubeCube.h"
#include <sifteo/string.h>

HotCubeCube::HotCubeCube() {}

void HotCubeCube::init(CubeID initCube)
{
	LOG ("HotCubeCube::init()\n");
	BaseGameCube::init(initCube);

	buffer->bg0.image(vec(0,0), HotCubeStart);
	buffer->bg1.eraseMask();

}

void HotCubeCube::start()
{
	LOG ("HotCubeCube::start()\n");
	BaseGameCube::start();

	Float2 panning;
	panning.set(0, 0);
	buffer->bg1.setMask(BG1Mask::filled(vec(4,7), vec(8,2)));
	buffer->bg1.text(vec(4,7), BlackFont, "          ");
	buffer->bg1.setPanning(panning);
}

void HotCubeCube::stop()
{
	LOG ("HotCubeCube::stop\n");

	BaseGameCube::stop();
}

void HotCubeCube::cleanUp()
{
	buffer->bg1.eraseMask();

	BaseGameCube::cleanUp();
}

void HotCubeCube::lightDisconnected (unsigned int side)
{
	// Image is now drawing red bar at "top"

	buffer->bg0.image(vec(0,0), HotCubeDisc[side]);

}

void HotCubeCube::clear()
{
	buffer->bg0.image(vec(0,0), White);
}

void HotCubeCube::lightConnected (unsigned int side)
{
	buffer->bg0.image(vec(0,0), HotCubeConn[side]);
}

void HotCubeCube::setImageRotation(unsigned int side)
{
	switch (side)
		{
		case BOTTOM:
			// flip 180
			buffer->setRotation(ROT_180);
			break;
		case LEFT:
			buffer->setRotation(ROT_LEFT_90);
			break;
		case RIGHT:
			buffer->setRotation(ROT_RIGHT_90);
			break;
		}
}

void HotCubeCube::paintCountdown (float timeLeft)
{
	String<16> time;
	time << (int)timeLeft << "." << Fixed((int)(timeLeft * 100) % 100, 2, true);

	writeText (time);
}

void HotCubeCube::writeText (const char* str)
{
	buffer->bg1.text(vec(5,7), BlackFont, str);

}

void HotCubeCube::gameFinished (int totalIterations)
{

	LOG ("HotCubeCube::gameFinished %d\n", totalIterations);
	clear();

	String<16> time;

	time << "TOTAL:" << Fixed(totalIterations, 2, true);

	buffer->bg1.text(vec(4,7), BlackFont, time);
}


