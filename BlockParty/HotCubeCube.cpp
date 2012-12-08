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
	BaseGameCube::init(initCube);

	buffer->bg0.image(vec(0,0), HotCubeStart);
	buffer->bg1.eraseMask();

}

void HotCubeCube::start()
{
	BaseGameCube::start();

	Float2 panning;
	panning.set(0, 0);
	buffer->bg1.setMask(BG1Mask::filled(vec(4,7), vec(8,2)));
	buffer->bg1.text(vec(4,7), BlackFont, "          ");
	buffer->bg1.setPanning(panning);
}

void HotCubeCube::stop()
{
	BaseGameCube::stop();
}

void HotCubeCube::setMatchup (Matchup matchup, unsigned int side)
{
	matchups[side].cubeId = matchup.cubeId;
	matchups[side].side = matchup.side;
	matchups[side].isMatched = false;

	lightDisconnected (side);
}

bool HotCubeCube::isMatched (unsigned int side)
{
	return matchups[side].isMatched;
}

/**
 * Check for a match of the neighbor to what is being watched for
 */
void HotCubeCube::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	bool matchFound = false;

	Matchup* toCheck;

	if (cube == firstID)
	{
		toCheck = &matchups[firstSide];
		toCheck->isMatched = checkMatchup (toCheck, secondID, secondSide);

		if (toCheck->isMatched)
		{
			lightConnected (firstSide);
		}
	}
	else if (cube == secondID)
	{
		toCheck = &matchups[secondSide];

		toCheck->isMatched = checkMatchup (toCheck, firstID, firstSide);

		if (toCheck->isMatched)
		{
			lightConnected (secondSide);
		}
	}
}

bool HotCubeCube::checkMatchup (Matchup* matchup, unsigned ID, unsigned side)
{
	bool matchFound = false;
	if (matchup->cubeId == ID && matchup->side == side)
	{
		matchFound = true;
	}

	return matchFound;
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
	clear();

	String<16> time;

	time << "TOTAL:" << Fixed(totalIterations, 2, true);

	buffer->bg1.text(vec(4,7), BlackFont, time);
}


