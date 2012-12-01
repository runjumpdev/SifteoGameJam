/*
 * ColorMeCube.h
 *
 *  Created on: Dec 1, 2012
 *      Author: Ben
 */

#ifndef COLORMECUBE_H_
#define COLORMECUBE_H_

#include <sifteo.h>
#include "assets.gen.h"

using namespace Sifteo;

class ColorMeCube {
public:
	ColorMeCube();

	void init();
	void start();
	bool update (TimeDelta timeStep);
	void setVideoBuffer (VideoBuffer* buffer);
	void touched();

	void gameFinished (int winningColor);

private:
	VideoBuffer* buffer;
	TiltShakeRecognizer motion;

	int position = 0;

};

#endif /* COLORMECUBE_H_ */
