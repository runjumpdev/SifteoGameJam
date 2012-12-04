/*
 * ColorMeGame.h
 *
 *  Created on: Dec 1, 2012
 *      Author: Ben
 */

#ifndef COLORMEGAME_H_
#define COLORMEGAME_H_

#include <sifteo.h>
#include "assets.gen.h"
#include "ColorMeCube.h"

using namespace Sifteo;

class ColorMeGame {
public:
	ColorMeGame();

	void init(int numCubes);
	void start();
	bool update(TimeDelta timestep);

	void touched (unsigned id);

	void setVideoBuffer (VideoBuffer buffers[], int count);
private:

	ColorMeCube cubes[10];
	int actualCubes = 0;
	SystemTime startTime;

	float timeLeft;

	float gameIntervalLeft;

	bool gameRunning;

	Random randGenerator;
};

#endif /* COLORMEGAME_H_ */
