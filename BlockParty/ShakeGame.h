#ifndef SHAKEGAME_H_
#define SHAKEGAME_H_

#include <sifteo.h>
#include "BaseGame.h"
#include "BaseGameCube.h"
#include "ShakeCube.h"
#include "assets.gen.h"

using namespace Sifteo;

class ShakeGame : public BaseGame
{
public:
	//Common
    void init();
	void start();
	bool update(TimeDelta timeStep);

private:
	Random rand;
	
	int whichGame; //0 = x axis shake, 1 = y axis shake

	float timeElapsed = 0;

	float startDelay = 2;
	bool started = false;

	SystemTime startTime;
	
	float howLong = rand.random() * 12 + 2.5;
	
    //AudioTracker::play(Music);

	
	bool gameOver = false;

	int lastFoundPlace = 0;

	int finishedPieces = 0;
	
	int numOut = 0;

	ShakeCube shakeCube[gNumCubes];
};

#endif /* SHAKEGAME_H_ */
