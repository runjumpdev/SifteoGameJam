/*
 * HotCubeMPGame.cpp
 *
 *  Created on: Dec 7, 2012
 *      Author: Ben
 */

/**
 * GamePlay:
 *   Chaos Mode
 *
 *   Each cube gets paired with every other cube (up to 4 per)
 *   Players have X seconds to get as many matches as possible
 *     or
 *   Play each round until player gets all matches
 *
 *   Reshuffle
 *
 *   Play until:
 *     X rounds
 *     First to 10
 */

#include "HotCubeMPGame.h"

HotCubeMPGame::HotCubeMPGame() {

	randomizer.seed();

	BaseGame::BaseGame();
}

void HotCubeMPGame::init(unsigned count, VideoBuffer buffers[])
{
	for (unsigned i = 0; i < count; i++)
	{
			cubes[i] = & hotCubes[i];
	}
	BaseGame::init(count, buffers);
}

void HotCubeMPGame::start()
{
	BaseGame::start();

	timeLeft = ROUND_TIME;

	clearAll();

	makePairs();
}

/**
 * If (numCubes == 2)
 *   Pair 1 with 2
 * Else if (numCubes == 3)
 *   Pair 1 with 2
 *   Pair 1 with 3
 *   Pair 2 with 3
 * Else if (numCubes == 4)
 *   Pair 1 with 2, 3, 4
 *   Pair 2 with 3, 4
 *   Pair 3 with 4
 * Else if (numCubes == 5)
 *
 */
void HotCubeMPGame::makePairs()
{
	// If (numCubes == 2)
	//   Pair 1 with 2

	// total Pairs is (number of cubes) * (4 sides) / (2 sides to make a pair)

	LOG ("HotCubeMPGame::MakePairs()\n");

	int totalPairings = CubeCount * 2;

	int maxAllowed = 0;

	int maxStart = 0;

	int leftOnThisLevel = CubeCount;

	unsigned int color = 0;

	unsigned int stamp(0);

	LOG ("makePairs(%d)\n)", CubeCount);
	while (totalPairings > 0)
	{
//		LOG ("START WHILE\n");
		int firstCube = 0;

		// Find the first cube that is not maxed for this level
		while (hotCubes[firstCube].getMatchupsCount() > maxStart && firstCube < CubeCount)
		{
			firstCube++;
		}

//		LOG ("\tfirstCube: %d\n", firstCube);

		if (firstCube == CubeCount)
		{
			// no more left at this level, increment and restart
			leftOnThisLevel = CubeCount;
			maxStart++;

//			LOG ("\tNone Left, (LL:%d, MS:%d, MA:%d)\n", leftOnThisLevel, maxStart, maxAllowed);
			continue;
		}

		int secondCube = randomizer.randint(0, (int)(CubeCount-1));

		// Make sure the two numbers are not the same, and
		// secondCube has the correct number of turns left
		while ((secondCube == firstCube) || hotCubes[secondCube].getMatchupsCount() > maxAllowed)
		{
			if (secondCube < (int)(CubeCount-1))
			{
				secondCube++;
			}
			else
			{
				secondCube = 0;
			}
		}

//		LOG ("\tSecond Cube: %d\n", secondCube);

		makePairing (firstCube, secondCube, color, stamp);

		stamp++;
		if (stamp > 3)
		{
			stamp = 0;
		}

		totalPairings--;

		leftOnThisLevel -= 2;

		if (leftOnThisLevel == 1)
		{
			maxAllowed++;
		}
		else if (leftOnThisLevel == 0)
		{
			maxAllowed++;
			maxStart++;
			leftOnThisLevel = CubeCount;

			color++;

			if (color > 3)
			{
				color = 0;
			}
		}
		else if (leftOnThisLevel == -1)
		{
			// max Allowed was incremented when left was 1
			maxStart++;
			leftOnThisLevel = (CubeCount - 1);

			color++;

			if (color > 3)
			{
				color = 0;
			}

		}

//		LOG ("\tEnd While (LL:%d, MS:%d, MA:%d)\n", leftOnThisLevel, maxStart, maxAllowed);
	}
}

void HotCubeMPGame::makePairing (unsigned int cube1, unsigned int cube2, unsigned int color, unsigned int stamp)
{
	int side1 = 0;
	int side2 = 0;

	while (hotCubes[cube1].isPaired(side1))
	{
		side1++;
	}

	while (hotCubes[cube2].isPaired(side2))
	{
		side2++;
	}

	Matchup matchup;
	matchup.color = color;
	matchup.stamp = stamp;

	matchup.cubeId = cube2;
	matchup.side = side2;

	hotCubes[cube1].setMatchup(matchup, side1);

	matchup.cubeId = cube1;
	matchup.side = side1;

	hotCubes[cube2].setMatchup (matchup, side2);
}

void HotCubeMPGame::clearAll()
{
	for (int i=0; i < CubeCount; i++)
	{
		hotCubes[i].clear();
	}
}

bool HotCubeMPGame::update(TimeDelta timeStep)
{
	bool retval = false;
	timeLeft -= timeStep.seconds();

	if (timeLeft <= 0)
	{
		retval = true;

		for (int i=0; i < CubeCount; i++)
		{
			hotCubes[i].gameFinished (hotCubes[i].getSuccessfulMatchCount());
		}
	}
	else
	{
		for (int i=0; i < CubeCount; i++)
		{
			hotCubes[i].paintCountdown(timeLeft);
		}
	}

	return retval;
}

void HotCubeMPGame::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	BaseGame::onNeighborAdd(firstID, firstSide, secondID, secondSide);
}


