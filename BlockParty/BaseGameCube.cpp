#include "BaseGameCube.h"

void BaseGameCube::setVideoBuffer(VideoBuffer* newBuffer)
{
	buffer = newBuffer;
}

void BaseGameCube::setTiltShakeRecognizer(TiltShakeRecognizer* newMotion)
{
	motion = newMotion;
}
