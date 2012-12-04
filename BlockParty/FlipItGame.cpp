#include "FlipItGame.h"

void FlipItGame::init()
{
	randomGen.seed();

	//for (unsigned i = 0; i < gNumCubes; i++)
	//{
	//	CurrentGameCube[i] = & flipItCube[i]; 
	//	CurrentGameCube[i]->init(i);
	//}
}

void FlipItGame::start()
{
    //AudioTracker::play(Music);
	int rand = randomGen.randint(0, 4);

	flipDir = rand;

	gameOver = false;
	started = true;

	lastFoundPlace = 0;
	finishedPieces = 0;

    for (unsigned i = 0; i < arraysize(flipItCube); i++)
    {
        flipItCube[i].setFlipDir(getFlipDir());
    }

	BaseGame::start();
}

bool FlipItGame::update(TimeDelta timeStep)
{
//        LOG("update game\n");

    for (int i=0; i < arraysize(flipItCube); i++)
    {
    	if (flipItCube[i].isFinished() && (flipItCube[i].getPlace() < 0))
    	{
    		flipItCube[i].setPlace(lastFoundPlace);
    		lastFoundPlace++;
    		finishedPieces++;
    	}
    }

    if (finishedPieces == arraysize(flipItCube))
    {
    	gameOver = true;
    }

	if (!gameOver)
	{
		BaseGame::update(timeStep);
	}

    return gameOver;
}

int FlipItGame::getFlipDir()
{
	return flipDir;
}

