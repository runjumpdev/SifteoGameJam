/*
 * ColorMeGame.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: Ben
 */

#include "ColorMeGame.h"

ColorMeGame::ColorMeGame() {
	randGenerator.seed();
}

void ColorMeGame::init(int numCubes)
{
	actualCubes = numCubes;
	gameRunning = false;
}

void ColorMeGame::start()
{
	startTime = SystemTime::now();
	timeLeft = 5;
	gameIntervalLeft = 5;
	gameRunning = true;
}

bool ColorMeGame::update(TimeDelta timeStep)
{
	bool retval = false;

	if (gameRunning)
	{
		timeLeft -= timeStep.seconds();

		if (timeLeft <= 0)
		{
			int winningValue = randGenerator.randint(0, 5);

			LOG ("Winning Value: %d\n", winningValue);

			for (int i=0; i < actualCubes; i++)
			{
				cubes[i].gameFinished (winningValue);
			}

			gameRunning = false;
		}
	}
	else
	{
		gameIntervalLeft -= timeStep.seconds();

		if (gameIntervalLeft <= 0)
		{
			// Go ahead and let the game end
			retval = true;
		}
	}

	return retval;
}

void ColorMeGame::touched (unsigned id)
{
	if (gameRunning)
	{
		CubeID cube(id);
		if (cube.isTouching())
		{
			cubes[id].touched();
		}
	}
}

void ColorMeGame::setVideoBuffer (VideoBuffer buffers[], int count)
{
	for (int i=0; i < count; i++)
	{
		cubes[i].setVideoBuffer(&buffers[i]);
	}
}




