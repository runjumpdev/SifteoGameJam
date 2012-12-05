#include "ShakeGame.h"

void ShakeGame::init(unsigned count, VideoBuffer buffers[])
{
	for (unsigned i = 0; i < count; i++)
	{
		cubes[i] = & shakeCube[i]; 
	}

	BaseGame::init(count, buffers);
	
    rand.seed();

	whichGame = rand.randrange(0,1);

	for (unsigned i = 0; i < CubeCount; i++)
	{
		shakeCube[i].whichGame = whichGame;
	}
}

void ShakeGame::start()
{
    AudioTracker::play(Music);
	
	howLong = rand.random() * 12 + 2.5;
	timeElapsed = 0;
	LOG("Delay %f\n", howLong);

	BaseGame::start();
}

bool ShakeGame::update(TimeDelta timeStep)
{
	timeElapsed += timeStep.seconds();
	if (timeElapsed <= howLong)
	{
		BaseGame::update(timeStep);
		return false;
	}
	else
	{
		LOG("Elapsed %f\n", timeElapsed);
		CalcPlaces();
		AudioTracker::stop();
		return true;
	}
}

void ShakeGame::CalcPlaces()
{
	unsigned lastpos = 0;
	int topscore;

	do
	{
		topscore = -1;

		//Find top score
		for (unsigned i = 0; i < CubeCount; i++)
		{
			if ((shakeCube[i].place == -1) && (shakeCube[i].shakeScore > topscore))
			{	
				topscore = shakeCube[i].shakeScore;
			}
		}
		
		//Assign place to people that have high score
		if (topscore != -1)
		{
			for (unsigned i = 0; i < CubeCount; i++)
			{
				if ((shakeCube[i].place == -1) && (shakeCube[i].shakeScore == topscore))
				{	
					shakeCube[i].SetPlace(lastpos);
				}
			}
			lastpos++;
		}
	} while (topscore != -1);
}