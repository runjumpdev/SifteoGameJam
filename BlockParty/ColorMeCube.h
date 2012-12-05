/*
 * ColorMeCube.h
 *
 *  Created on: Dec 1, 2012
 *      Author: Ben
 */

#ifndef COLORMECUBE_H_
#define COLORMECUBE_H_

#include <sifteo.h>
#include "BaseGameCube.h"
#include "assets.gen.h"

using namespace Sifteo;

class ColorMeCube : public BaseGameCube
{
public:
	ColorMeCube();

	void init(CubeID initCube);
	void start();
	void update(TimeDelta timeStep);
	void onTouch();

	void gameFinished (int winningColor);

private:
	int position = 0;

};

#endif /* COLORMECUBE_H_ */
