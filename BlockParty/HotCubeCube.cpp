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
	matchups[side].isPaired = true;
	matchups[side].color = matchup.color;
	matchups[side].stamp = matchup.stamp;

	lightDisconnected (side);
}

bool HotCubeCube::isPaired (unsigned int side)
{
	return matchups[side].isPaired;
}

bool HotCubeCube::isMatched (unsigned int side)
{
	return matchups[side].isMatched;
}

unsigned int HotCubeCube::getMatchupsCount ()
{
	int total = 0;

	for (int i=0; i < 4; i++)
	{
		total += matchups[i].isPaired;
	}

	return total;
}

unsigned int HotCubeCube::getSuccessfulMatchCount()
{
	return successfulMatches;
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
			lightConnected (firstSide, toCheck->stamp);
		}
	}
	else if (cube == secondID)
	{
		toCheck = &matchups[secondSide];

		toCheck->isMatched = checkMatchup (toCheck, firstID, firstSide);

		if (toCheck->isMatched)
		{
			lightConnected (secondSide, toCheck->stamp);
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

	for (int i=0; i < 3; i++)
	{
		buffer->sprites[i].hide();
	}

	BaseGameCube::cleanUp();
}

void HotCubeCube::lightDisconnected (unsigned int side)
{
	// Image is now drawing red bar at "top"
	if (side == TOP || side == BOTTOM)
	{
		paintEdge (side, HotCubeDiscHoriz[matchups[side].color]);
		paintStamp (side, matchups[side].stamp);
	}
	else
	{
		paintEdge (side, HotCubeDiscVert[matchups[side].color]);
		paintStamp (side, matchups[side].stamp);
	}
}

void HotCubeCube::paintStamp (unsigned int side, unsigned int stampId)
{
	buffer->sprites[side].setImage(HotCubeStamps[stampId]);
	buffer->sprites[side].setHeight(16);

	if (side == TOP)
	{
		buffer->sprites[side].move(56,0);
	}
	else if (side == BOTTOM)
	{
		buffer->sprites[side].move(56,112);
	}
	else if (side == LEFT)
	{
		buffer->sprites[side].move(0,56);
	}
	else if (side == RIGHT)
	{
		buffer->sprites[side].move(112, 56);
	}
}

void HotCubeCube::paintEdge (unsigned int side, const AssetImage& color)
{
	if (side == TOP)
	{
		buffer->bg0.image(vec(3, 0), color);
	}
	else if (side == BOTTOM)
	{
		buffer->bg0.image(vec(3, 14), color);
	}
	else if (side == LEFT)
	{
		buffer->bg0.image(vec(0,3), color);
	}
	else if (side == RIGHT)
	{
		buffer->bg0.image(vec(14, 3), color);
	}
}

void HotCubeCube::clear()
{
	buffer->bg0.image(vec(0,0), White);

	for (int i=0; i < 4; i++)
	{
		buffer->sprites[i].hide();
		matchups[i].isMatched = false;
		matchups[i].isPaired = false;
	}
}

void HotCubeCube::lightConnected (unsigned int side, unsigned int stampId)
{
	LOG ("HotCubeCube::lightConnected (%d)\n", side);
	buffer->sprites[side].hide();

	if (side == TOP || side == BOTTOM)
	{
		paintEdge (side, HotCubeGreen[0]);
	}
	else
	{
		paintEdge (side, HotCubeGreen[1]);
	}

	successfulMatches++;

//	buffer->bg0.image(vec(0,0), HotCubeConn[side]);
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


