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
#include "BaseGame.h"
#include "BaseGameCube.h"
#include "ColorMeCube.h"

using namespace Sifteo;

class ColorMeGame : public BaseGame
{
public:
	ColorMeGame();

	void init(unsigned count, VideoBuffer buffers[]);
	void start();
	bool update(TimeDelta timestep);

	void onTouch (unsigned id);

private:

	ColorMeCube colorMeCube[10];
	SystemTime startTime;

	float timeLeft;

	Random randGenerator;
};

#endif /* COLORMEGAME_H_ */
