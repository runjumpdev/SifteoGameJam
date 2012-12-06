#include "BaseGameCube.h"

void BaseGameCube::init(CubeID initcube)
{
	cube = initcube;
	place = -1;
}

void BaseGameCube::setVideoBuffer(VideoBuffer* newBuffer)
{
	buffer = newBuffer;
}

void BaseGameCube::setTiltShakeRecognizer(TiltShakeRecognizer* newMotion)
{
	motion = newMotion;
}

void BaseGameCube::start()
{
	IsStarted = true;
}

void BaseGameCube::stop()
{
	IsStarted = false;
}

void BaseGameCube::cleanUp()
{

}

void BaseGameCube::update(TimeDelta timeStep)
{
}

void BaseGameCube::onTouch()
{
}

void BaseGameCube::onAccelChange()
{
}

void BaseGameCube::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{

}


void BaseGameCube::SetPlace (int newPlace)
{
	LOG ("Cube %d finished %d\n", (int)cube, newPlace);

	place = newPlace;

	switch (newPlace)
	{
		case 0:
			buffer->bg0.image(vec(0,0), First);
			break;
		case 1:
			buffer->bg0.image(vec(0,0), Second);
			break;
		case 2:
			buffer->bg0.image(vec(0,0), Third);
			break;
		default:
			//todo change for sorry
			buffer->bg0.image(vec(0,0), Third);
			break;
	}
}
