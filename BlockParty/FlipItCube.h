#ifndef FLIPITCUBE_H_
#define FLIPITCUBE_H_

#include <sifteo.h>
#include "BaseGameCube.h"
#include "assets.gen.h"

using namespace Sifteo;

class FlipItCube : public BaseGameCube
{
public:
	//Common
	FlipItCube();
	void init (CubeID initCube);
    void start();
	void update(TimeDelta timeStep);
	void onTouch();
	void onAccelChange();

	//Other
	void setFlipDir (int flipDir);
	void setMode (int newMode);

	bool finished = false;
	bool moveSuccess = false;

	// 0 - Left
	// 1 - Right
	// 2 - Up
	// 3 - Down
	// 4 - Flip
	int moveToCheck;

	SystemTime startTime;
	int32_t changeTime;
};

#endif /* FLIPITCUBE_H_ */
