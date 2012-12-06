#include "BaseGame.h"

void BaseGame::init(unsigned count, VideoBuffer buffers[])
{
	CubeCount = count;
	
	for (int i=0; i < count; i++)
	{
		cubes[i]->setVideoBuffer(&buffers[i]);
		cubes[i]->init(i);
	}	
}

void BaseGame::start()
{
	for (unsigned i = 0; i < CubeCount; i++)
	{
		cubes[i]->start();
	}
	
	IsStarted = true;
}

void BaseGame::stop()
{
	for (unsigned i = 0; i < CubeCount; i++)
	{
		cubes[i]->stop();
	}
	
	IsStarted = false;
}

void BaseGame::cleanUp()
{
	for (unsigned i=0; i < CubeCount; i++)
	{
		cubes[i]->cleanUp();
	}
}

bool BaseGame::update(TimeDelta timeStep)
{
	for (unsigned i = 0; i < CubeCount; i++)
	{
		cubes[i]->update(timeStep);
	}

	return false;
}

void BaseGame::setTiltShakeRecognizer (TiltShakeRecognizer motions[], int count)
{
	for (int i=0; i < count; i++)
	{
		cubes[i]->setTiltShakeRecognizer(&motions[i]);
	}
}

void BaseGame::onTouch (unsigned id)
{
	cubes[id]->onTouch();
}

void BaseGame::onAccelChange(unsigned id)
{
	cubes[id]->onAccelChange();
}

void BaseGame::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	cubes[firstID]->onNeighborAdd(firstID, firstSide, secondID, secondSide);
	cubes[secondID]->onNeighborAdd(firstID, firstSide, secondID, secondSide);
}


