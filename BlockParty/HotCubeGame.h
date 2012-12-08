/*
 * HotCubeGame.h
 *
 *  Created on: Dec 5, 2012
 *      Author: Ben G
 *
 *  Start with a cube
 *    In X Seconds, connect on of four cube sides to a different cube
 *      and side
 *    Repeat
 */

#ifndef HOTCUBEGAME_H_
#define HOTCUBEGAME_H_

#include <sifteo.h>
#include "HotCubeCube.h"
#include "BaseGame.h"
#include "BaseGameCube.h"

using namespace Sifteo;

#define START_TIME 6.0
#define MATCHED_TIME 1.5

class HotCubeGame : public BaseGame {
public:
	HotCubeGame();

	void init(unsigned count, VideoBuffer buffers[]);
	void start();
	bool update (TimeDelta timeStep);


	void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide);

private:

	void clearAll();
	void newIteration();

	HotCubeCube hotCubes[CUBE_ALLOCATION];
	HotCubeCube* activeCube;

	float timeLeft;

	int iteration;

	Random randomizer;

	unsigned cube1;
	unsigned cube2;
	unsigned side1;
	unsigned side2;

	bool matched = false;

	float matchedTimeLeft = MATCHED_TIME;
};

#endif /* HOTCUBEGAME_H_ */
