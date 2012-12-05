#ifndef SHAKEGAME_H_
#define SHAKEGAME_H_

#include <sifteo.h>
#include "BaseGame.h"
#include "BaseGameCube.h"
#include "ShakeCube.h"
#include "assets.gen.h"

using namespace Sifteo;

class ShakeGame : public BaseGame
{
public:
	//Common
    void init(unsigned count, VideoBuffer buffers[]);
	void start();
	bool update(TimeDelta timeStep);

private:
	void CalcPlaces();
	
	Random rand;
	
	int whichGame; //0 = x axis shake, 1 = y axis shake

	float timeElapsed = 0;
	
	float howLong;
	
	ShakeCube shakeCube[10];
};

#endif /* SHAKEGAME_H_ */
