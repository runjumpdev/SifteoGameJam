#ifndef BASEGAMECUBE_H_
#define BASEGAMECUBE_H_

#include <sifteo.h>
using namespace Sifteo;

class BaseGameCube
{
public:
    virtual void init(CubeID initcube);
	virtual void setVideoBuffer (VideoBuffer* buffer);
	virtual void setTiltShakeRecognizer (TiltShakeRecognizer* motion);
    virtual void start();
    virtual void update(TimeDelta timeStep);
    virtual void onTouch();
	virtual void onAccelChange();

protected:
	VideoBuffer* buffer;
    TiltShakeRecognizer* motion;
};

static const unsigned gNumCubes = 3;

#endif /* BASEGAMECUBE_H_ */
