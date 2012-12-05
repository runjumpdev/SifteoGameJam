#ifndef BASEGAMECUBE_H_
#define BASEGAMECUBE_H_

#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;

class BaseGameCube
{
public:
    virtual void init(CubeID initcube);
	virtual void setVideoBuffer (VideoBuffer* buffer);
	virtual void setTiltShakeRecognizer (TiltShakeRecognizer* motion);
    virtual void start();
	virtual void stop();
    virtual void update(TimeDelta timeStep);
    virtual void onTouch();
	virtual void onAccelChange();
	virtual void SetPlace (int newPlace);
	
	bool IsStarted = false;
	CubeID cube;
	int place = -1;
	
protected:
	VideoBuffer* buffer;
    TiltShakeRecognizer* motion;
};

#endif /* BASEGAMECUBE_H_ */
