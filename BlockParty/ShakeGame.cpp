#include "ShakeGame.h"

void ShakeGame::init()
{
    rand.seed();

	whichGame = rand.randrange(0,1);

	for (unsigned i = 0; i < gNumCubes; i++)
	{
		shakeCube[i].init(i);
		shakeCube[i].whichGame = whichGame;
	}		
}

void ShakeGame::start()
{
    AudioTracker::play(Music);
	startTime = SystemTime::now();

	gameOver = false;
	started = true;

	lastFoundPlace = 0;
	finishedPieces = 0;
}

bool ShakeGame::update(TimeDelta timeStep)
{
//        LOG("update game\n");

	timeElapsed += timeStep;
	if (timeElapsed < howLong)
	{
		// for (unsigned i = 0; i < arraysize(instances); i++)
		// {
				// instances[i].update(ts.delta(), whichGame, started);
				// if (instances[i].isOut && instances[i].rank == 0)
				// {
					
					// numOut++;
					// instances[i].rank = numOut;
				// }
		// }
	}
	else
	{
		AudioTracker::stop();
	}

    for (int i=0; i < arraysize(shakeCube); i++)
    {
    	if (shakeCube[i].isFinished() && (shakeCube[i].getPlace() < 0))
    	{
    		shakeCube[i].setPlace(lastFoundPlace);
    		lastFoundPlace++;
    		finishedPieces++;
    	}
    }

    if (finishedPieces == arraysize(shakeCube))
    {
    	gameOver = true;
    }

    return gameOver;
}