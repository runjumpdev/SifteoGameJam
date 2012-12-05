#ifndef BASEGAME_H_
#define BASEGAME_H_

#include <sifteo.h>
#include "BaseGameCube.h"
using namespace Sifteo;

class BaseGame
{
public:
    virtual void init(unsigned CubeCount, VideoBuffer buffers[]);
    virtual void start();
	virtual void stop();
    virtual bool update(TimeDelta timeStep);
	virtual void setTiltShakeRecognizer(TiltShakeRecognizer motions[], int count);
    virtual void onTouch(unsigned id);
	virtual void onAccelChange(unsigned id);

	bool IsStarted = false;	

protected:
	BaseGameCube* cubes[10];
	unsigned CubeCount;
};

#endif /* BASEGAME_H_ */