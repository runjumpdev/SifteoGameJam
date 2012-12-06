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

	newIteration();

	lightDisconnectedSides();

}

void HotCubeGame::lightDisconnectedSides()
{
	for (int i=0; i < CubeCount; i++)
	{
		if (i == cube1)
		{
			hotCubes[cube1].lightDisconnected (side1);
		}
		else if (i == cube2)
		{
			hotCubes[cube2].lightDisconnected (side2);
		}
		else
		{
			hotCubes[i].clear();
		}
	}
}

bool HotCubeGame::update(TimeDelta timeStep)
{
	bool retval = false;

	if (matched && matchedTimeLeft > 0)
	{
		matchedTimeLeft-= timeStep.seconds();
//		LOG ("Decreased matched time left to %f\n", matchedTimeLeft);
	}
	else if (matched)
	{
		matched = false;
		matchedTimeLeft = MATCHED_TIME;
		LOG ("Matched Time ended\n");

		LOG ("Lighting disconnected sides\n");
		lightDisconnectedSides();
	}
	else
	{

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

	while (cube1 == cube2)
	{
		// Make sure it's not the same cube!
		cube2 = randomizer.randint(0, (int)(CubeCount-1));
	}

	side1 = randomizer.randint(0,3);
	side2 = randomizer.randint(0,3);

	LOG ("\tcube1(%d, %d) cube2 (%d, %d)\n", cube1, side1, cube2, side2);

	iteration++;
	timeLeft = START_TIME - (float)(0.5*(float)iteration);
}

void HotCubeGame::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	LOG ("On NeighborAdd (%d, %d, %d, %d)\n", firstID, firstSide, secondID, secondSide);

	// First could be second and vice versa
	if ((firstID == cube1 && firstSide == side1 &&
		secondID == cube2 && secondSide == side2) ||
		(firstID == cube2 && firstSide == side2 &&
		 secondID == cube1 && secondSide == side1))
	{
		LOG ("\tEverything Matched\n");
		LOG ("\tLighting Cube1 Side1 (%d,%d)\n", cube2, side1);
		LOG ("\tLighting Cube2 Side2 (%d,%d)\n", cube2, side2);
		hotCubes[firstID].lightConnected (firstSide);
		hotCubes[secondID].lightConnected (secondSide);

		newIteration();

		matched = true;
	}
	else
	{
		// TODO:  Penalize wrong connections??
		LOG ("\tEverything did NOT match\n");
	}
}






