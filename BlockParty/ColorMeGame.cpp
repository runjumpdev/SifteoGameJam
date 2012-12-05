/*
 * ColorMeGame.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: Ben
 */

#include "ColorMeGame.h"

ColorMeGame::ColorMeGame()
{
	randGenerator.seed();
}

void ColorMeGame::init(unsigned count, VideoBuffer buffers[])
{
	for (unsigned i = 0; i < count; i++)
	{
		cubes[i] = & colorMeCube[i];
	}

	BaseGame::init(count, buffers);
}

void ColorMeGame::start()
{
	AudioTracker::play(Music);
	startTime = SystemTime::now();
	timeLeft = 5;
	
	BaseGame::start();
}

bool ColorMeGame::update(TimeDelta timeStep)
{
	bool retval = false;

	timeLeft -= timeStep.seconds();

	if (timeLeft <= 0)
	{
		int winningValue = randGenerator.randint(0, 5);

		LOG ("Winning Value: %d\n", winningValue);

		for (int i=0; i < CubeCount; i++)
		{
			colorMeCube[i].gameFinished (winningValue);
		}

		retval = true;
		
		AudioTracker::stop();
	}

	return retval;
}

void ColorMeGame::onTouch (unsigned id)
{
	CubeID cube(id);
	if (cube.isTouching())
	{
		colorMeCube[id].onTouch();
	}
}
