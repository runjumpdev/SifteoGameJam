#ifndef BASEGAME_H_
#define BASEGAME_H_

#include <sifteo.h>
#include "BaseGameCube.h"
using namespace Sifteo;

class BaseGame
{
public:
    virtual void init();
    virtual void start();
    virtual bool update(TimeDelta timeStep);
    virtual void setVideoBuffer (VideoBuffer buffers[], int count);
	virtual void setTiltShakeRecognizer (TiltShakeRecognizer motions[], int count);
    virtual void onTouch(unsigned id);
	virtual void onAccelChange(unsigned id);

protected:
	BaseGameCube cubes[10];
};

#endif /* BASEGAME_H_ */