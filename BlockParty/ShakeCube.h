#ifndef SHAKECUBE_H_
#define SHAKECUBE_H_

#include <sifteo.h>
#include "BaseGameCube.h"
#include "assets.gen.h"

using namespace Sifteo;

class ShakeCube : public BaseGameCube
{
public:
	//Common
	ShakeCube();
	void init (CubeID initCube);
    void start();
	void update(TimeDelta timeStep);

	//Other
	bool isFinished();
	int getPlace();
	void setPlace (int newPlace);
	void stop();

    int whichGame; //0 = x axis shake, 1 = y axis shake

	Int2 lastAccel;

	CubeID cube;
	
	bool started = false;

	bool finished = false;

	int place = -1;

	Float2 text, textTarget;
	
	
private:
	int shakeScore;
	float shakeCounter;
	
	void writeText(const char *str);
	
	void writeScore(int i);
};

#endif /* SHAKECUBE_H_ */

