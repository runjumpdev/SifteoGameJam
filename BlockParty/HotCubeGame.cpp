/*
 * HotCubeGame.cpp
 *
 *  Created on: Dec 5, 2012
 *      Author: Ben
 */

#include "HotCubeGame.h"

HotCubeGame::HotCubeGame() {

	randomizer.seed();

	BaseGame::BaseGame();
}

void HotCubeGame::init(unsigned count, VideoBuffer buffers[])
{
	for (unsigned i = 0; i < count; i++)
	{
			cubes[i] = & hotCubes[i];
	}
	BaseGame::init(count, buffers);
}

void HotCubeGame::start()
{
	BaseGame::start();

	iteration = -1;

	clearAll();

	newIteration();
}

void HotCubeGame::clearAll()
{
	for (int i=0; i < CubeCount; i++)
	{
		hotCubes[i].clear();
	}
}

/**
 * Time loop for game
 */
bool HotCubeGame::update(TimeDelta timeStep)
{
	bool retval = false;

	// After a match there should be a delay before the next round
	// starts.
	if (matched && matchedTimeLeft > 0)
	{
		matchedTimeLeft-= timeStep.seconds();
//		LOG ("Decreased matched time left to %f\n", matchedTimeLeft);
	}
	// This occurs once the delay timer has wound to zero and the next
	// round should start.
	else if (matched)
	{
		matched = false;
		matchedTimeLeft = MATCHED_TIME;
		LOG ("Matched Time ended\n");

		LOG ("Lighting disconnected sides\n");
		clearAll();
		newIteration();
	}
	else
	{
		// This section is when a round is ongoing, there is no match, and the timer
		// has not wound down to 0.
		timeLeft -= timeStep.seconds();

		for (int i=0; i < CubeCount; i++)
		{
			hotCubes[i].paintCountdown (timeLeft);
		}

		if (timeLeft <= 0)
		{
				// GAME OVER
			for (int i=0; i < CubeCount; i++)
			{
				hotCubes[i].gameFinished (iteration);
			}

			retval = true;
		}
	}

	return retval;
}

void HotCubeGame::newIteration()
{
	LOG ("New Iteration\n");
	cube1 = randomizer.randint(0, (int)(CubeCount-1));
	cube2 = randomizer.randint(0, (int)(CubeCount-1));

	unsigned int color = randomizer.randint(0,3);

	while (cube1 == cube2)
	{
		// Make sure it's not the same cube!
		cube2 = randomizer.randint(0, (int)(CubeCount-1));
	}

	side1 = randomizer.randint(0,3);
	side2 = randomizer.randint(0,3);

	LOG ("\tcube1(%d, %d) cube2 (%d, %d), color (%d)\n", cube1, side1, cube2, side2, color);

	Matchup matchup;
	matchup.color = color;

	matchup.cubeId = cube2;
	matchup.side = side2;

	hotCubes[cube1].setMatchup(matchup, side1);

	matchup.cubeId = cube1;
	matchup.side = side1;

	hotCubes[cube2].setMatchup (matchup, side2);

	iteration++;
	timeLeft = START_TIME - (float)(0.5*(float)iteration);
}

void HotCubeGame::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	LOG ("On NeighborAdd (%d, %d, %d, %d)\n", firstID, firstSide, secondID, secondSide);

	BaseGame::onNeighborAdd(firstID, firstSide, secondID, secondSide);

	bool cube1Matched = hotCubes[firstID].isMatched(firstSide);
	bool cube2Matched = hotCubes[secondID].isMatched(secondSide);

	// First could be second and vice versa
	if (cube1Matched && cube2Matched)
	{
		LOG ("\tEverything Matched\n");

		matched = true;
	}
	else
	{
		// TODO:  Penalize wrong connections??
		LOG ("\tEverything did NOT match\n");
	}
}






