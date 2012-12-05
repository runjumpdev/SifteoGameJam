#include "FlipItGame.h"

void FlipItGame::init(unsigned count, VideoBuffer buffers[])
{
	for (unsigned i = 0; i < count; i++)
	{
		cubes[i] = & flipItCube[i]; 
	}

	BaseGame::init(count, buffers);
	
	randomGen.seed();
}

void FlipItGame::start()
{
    //AudioTracker::play(Music);
	int rand = randomGen.randint(0, 4);

	flipDir = rand;

	lastFoundPlace = 0;
	finishedPieces = 0;

    for (unsigned i = 0; i < CubeCount; i++)
    {
        flipItCube[i].setFlipDir(getFlipDir());
    }

	BaseGame::start();
}

bool FlipItGame::update(TimeDelta timeStep)
{
    for (int i=0; i < CubeCount; i++)
    {
    	if (flipItCube[i].finished && (flipItCube[i].place < 0))
    	{
    		flipItCube[i].SetPlace(lastFoundPlace);
    		lastFoundPlace++;
    		finishedPieces++;
    	}
    }

    if (finishedPieces == CubeCount)
    {
    	return true;
    }
	else
	{
		BaseGame::update(timeStep);
		return false;
	}
}

int FlipItGame::getFlipDir()
{
	return flipDir;
}

