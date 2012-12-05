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
	void SetPlace (int newPlace);

	//Other
    int whichGame; //0 = x axis shake, 1 = y axis shake

	Int2 lastAccel;

	Float2 text, textTarget;
	
	int shakeScore;
	
private:
	float shakeCounter;
	
	void writeText(const char *str);
	
	void writeScore(int i);
};

#endif /* SHAKECUBE_H_ */

