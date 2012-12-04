#include "BaseGameCube.h"
#include "BaseGame.h"

void BaseGame::setVideoBuffer (VideoBuffer buffers[], int count)
{
	for (int i=0; i < count; i++)
	{
		cubes[i].setVideoBuffer(&buffers[i]);
	}
}

void BaseGame::setTiltShakeRecognizer (TiltShakeRecognizer motions[], int count)
{
	for (int i=0; i < count; i++)
	{
		cubes[i].setTiltShakeRecognizer(&motions[i]);
	}
}

void BaseGame::start()
{
	for (unsigned i = 0; i < gNumCubes; i++)
	{
		cubes[i].start();
	}
}

bool BaseGame::update(TimeDelta timeStep)
{
	for (unsigned i = 0; i < gNumCubes; i++)
	{
		cubes[i].update(timeStep);
	}

	return false;
}

void BaseGame::onAccelChange(unsigned id)
{
	cubes[id].onAccelChange();
}

void BaseGame::onTouch (unsigned id)
{
	cubes[id].onTouch();
}