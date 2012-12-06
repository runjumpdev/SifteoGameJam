/*
 * HotCubeCube.h
 *
 *  Created on: Dec 5, 2012
 *      Author: Ben
 */

#ifndef HOTCUBECUBE_H_
#define HOTCUBECUBE_H_

#include <sifteo.h>
#include "assets.gen.h"
#include "BaseGameCube.h"

using namespace Sifteo;

class HotCubeCube : public BaseGameCube
{
public:
	HotCubeCube();

	void init (CubeID initcube);
	void start();
	void stop();

	void cleanUp();

	void lightDisconnected (unsigned int side);
	void lightConnected (unsigned int side);

	void paintCountdown (float timeLeft);

	void gameFinished (int totalIterations);

	void clear();

private:
	void setImageRotation (unsigned int side);
	void writeText (const char* str);
};

#endif /* HOTCUBECUBE_H_ */
