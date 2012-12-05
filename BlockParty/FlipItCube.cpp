#include "FlipItCube.h"

FlipItCube::FlipItCube()
{
}

void FlipItCube::init(CubeID initCube)
{
	BaseGameCube::init(initCube);
	
	buffer->bg0.image(vec(0,0), FlipStart);
}

void FlipItCube::start()
{
	startTime = SystemTime::now();

	switch (moveToCheck)
	{
	case 0:
		buffer->bg0.image(vec(0,0), FlipLeft);
		break;
	case 1:
		buffer->bg0.image(vec(0,0), FlipRight);
		break;
	case 2:
		buffer->bg0.image(vec(0,0), FlipUp);
		break;
	case 3:
		buffer->bg0.image(vec(0,0), FlipDown);
		break;
	case 4:
		buffer->bg0.image(vec(0,0), FlipOver);
		break;
	}

	finished = false;
	moveSuccess = false;
}

void FlipItCube::update(TimeDelta timeStep)
{
    //LOG("update cube %i\n", (int)cube);
	BaseGameCube::update(timeStep);
}

void FlipItCube::onTouch ()
{
	LOG ("touched\n");
	/*
	if (moveSuccess == true)
	{
		moveSuccess = false;
	}
	*/
}

void FlipItCube::onAccelChange()
{
	SystemTime nowTime = SystemTime::now();

	unsigned changeFlags = motion->update();

	auto tilt = motion->tilt;

	auto accel = cube.accel();

//		LOG ("Accel.x %d Accel.y: %d Accel.z %d\n", (signed int)accel.x, (signed int)accel.y, (signed int)accel.z);

	signed int move;

	switch (moveToCheck)
	{
	case 0: // left
		move = accel.x + 64;
		break;
	case 1: // right
		move = accel.x - 64;
		break;
	case 2: // up
		move = accel.y + 64;
		break;
	case 3:
		move = accel.y - 64;
		break;
	case 4:
		move = accel.z + 64;
		break;
	}

	move = abs(move);

	// Cube Face Up, Fip To the "Left" is -X axis
	if (move < 3 && !moveSuccess)
	{
		moveSuccess = true;
		LOG ("MOVE SUCCESS %d\n", move);

		TimeDelta delta = nowTime - startTime;
		changeTime = delta.milliseconds();

		LOG ("DELTA TIME: %d\n", changeTime);
		finished = true;
	}

}

void FlipItCube::setFlipDir (int flipDir)
{
	moveToCheck = flipDir;
}

void FlipItCube::setMode (int newMode)
{
	moveToCheck = newMode;
}