/*
 * HotCubeMPGame.h
 *
 *  Created on: Dec 7, 2012
 *      Author: Ben
 */

#ifndef HOTCUBEMPGAME_H_
#define HOTCUBEMPGAME_H_

#include "BaseGame.h"
#include "HotCubeCube.h"

#define ROUND_TIME 10.0

class HotCubeMPGame: public BaseGame {
public:
	HotCubeMPGame();

	void init (unsigned count, VideoBuffer buffers[]);
	void start();
	bool update (TimeDelta timeStep);

	void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide);

private:

	void clearAll();
	void newIteration();
	void makePairs();

	void makePairing (unsigned int cube1, unsigned int cube2, unsigned int color, unsigned int stamp);

	HotCubeCube hotCubes[CUBE_ALLOCATION];

	float timeLeft;

	int iteration;

	Random randomizer;

	int playerScore[CUBE_ALLOCATION];

};

#endif /* HOTCUBEMPGAME_H_ */
