/*
 * TCMGame.h
 *
 *  Created on: Dec 12, 2012
 *      Author: Ben
 *
 *      Overview:
 *        Display a ball in random cube
 *        Make all cubes be flipped over
 *        Play music for 10 seconds
 *        Wait for one flip
 *        If flip is right
 *          Winner
 *        Else
 *          Loser
 */

#ifndef TCMGAME_H_
#define TCMGAME_H_

#include <sifteo.h>
#include "BaseGame.h"
#include "TCMCube.h"

using namespace Sifteo;

#define CUBE_COUNT 3

#define ROUND_TIME 10.0

class TCMGame: public BaseGame {
public:
	TCMGame();

	void init (unsigned CubeCount, VideoBuffer buffers[]);
	void start();
//	void stop();
//	void cleanUp();
	bool update (TimeDelta timeStep);

private:

	void checkStartingFlipState();
	void checkEndingFlipState();
	void decrementTime(TimeDelta timeStep);
	void displayResult();

	Random randomizer;

	unsigned int keyCube;

	float timeLeft;

	// 0 not flipped yet
	// 1 flipped, timer counting down
	// 2 timer timed out, waiting for user flip
	// 3 user flipped, check results
	int gameState;

	bool isWinner;

	TCMCube tcmCubes[CUBE_COUNT];
};

#endif /* TCMGAME_H_ */
