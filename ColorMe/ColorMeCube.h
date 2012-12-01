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

private:
	VideoBuffer* buffer;
	TiltShakeRecognizer motion;

};

#endif /* COLORMECUBE_H_ */
