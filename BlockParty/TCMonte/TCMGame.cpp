/*
 * TCMGame.cpp
 *
 *  Created on: Dec 12, 2012
 *      Author: Ben
 */

#include "TCMGame.h"

TCMGame::TCMGame() {
	randomizer.seed();

	BaseGame::BaseGame();
}

void TCMGame::init(unsigned count, VideoBuffer buffers[])
{
	for (unsigned i=0; i < CUBE_COUNT; i++)
	{
		cubes[i] = &tcmCubes[i];
	}
	BaseGame::init(count, buffers);
}

void TCMGame::start()
{
	BaseGame::start();

	keyCube = randomizer.randint(0, CUBE_COUNT-1);

	LOG ("Drawing circle on %d\n", keyCube);

	tcmCubes[keyCube].showKey();

	for (int i=0; i < CUBE_COUNT; i++)
	{
		if (i != keyCube)
		{
			LOG ("Drawing blank on %d\n", i);
			tcmCubes[i].showBlank();
		}
	}

	gameState = 0;
}

// 0 not flipped yet
// 1 flipped, timer counting down
// 2 timer timed out, waiting for user flip
// 3 user flipped, check results
bool TCMGame::update (TimeDelta timeStep)
{
	bool result = false;
	switch (gameState)
	{
	case 0:
		checkStartingFlipState();
		break;
	case 1:
		decrementTime(timeStep);
		break;
	case 2:
		checkEndingFlipState();
		break;
	case 3:
		displayResult();
		result = true;
		break;
	}

	return result;
}

void TCMGame::checkStartingFlipState()
{
	bool allFlipped = true;

	for (int i=0; i < CUBE_COUNT; i++)
	{
		if (!tcmCubes[i].isFlipped())
		{
			allFlipped = false;
			break;
		}
	}

	if (allFlipped)
	{
		LOG ("All flipped over, starting rotation\n");
		// Start playing music

		AudioTracker::play(TCMPlay);
		gameState++;
		timeLeft = ROUND_TIME;
	}
}


void TCMGame::checkEndingFlipState()
{
	for (int i=0; i < CUBE_COUNT; i++)
	{
		if (tcmCubes[i].isUpright())
		{
			LOG ("Reporting that %d is flipped up\n", i);
			if (i == keyCube)
			{
				isWinner = true;
			}
			else
			{
				isWinner = false;
			}

			gameState++;
			break;
		}
	}
}

void TCMGame::decrementTime(TimeDelta timeStep)
{
	timeLeft -= timeStep.seconds();

	if (timeLeft <= 0)
	{
		LOG ("Time's up, ending game\n");

		AudioTracker::stop();
		gameState++;
	}
}

void TCMGame::displayResult()
{
	for (int i=0; i < CUBE_COUNT; i++)
	{
		tcmCubes[i].displayResult (isWinner);
	}
}




