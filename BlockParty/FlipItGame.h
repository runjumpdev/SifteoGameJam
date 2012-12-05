#ifndef FLIPITGAME_H_
#define FLIPITGAME_H_

#include <sifteo.h>
#include "BaseGame.h"
#include "BaseGameCube.h"
#include "FlipItCube.h"
#include "assets.gen.h"

using namespace Sifteo;

class FlipItGame : public BaseGame
{
public:
	//Common
    void init(unsigned count, VideoBuffer buffers[]);
	void start();
	bool update(TimeDelta timeStep);

	//Other
	int getFlipDir();

private:
	Random randomGen;

	int flipDir;

	int lastFoundPlace = 0;

	int finishedPieces = 0;

	FlipItCube flipItCube[10];
};

#endif /* FLIPITGAME_H_ */
