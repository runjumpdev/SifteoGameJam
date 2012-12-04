#include "FlipItCube.h"

FlipItCube::FlipItCube()
{
}

bool FlipItCube::isFinished()
{
	return finished;
}

int FlipItCube::getPlace()
{
	return place;
}

void FlipItCube::setPlace (int newPlace)
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
	}
}

void FlipItCube::update(TimeDelta timeStep)
{
        //LOG("update cube %i\n", (int)cube);
        //cubeVideo[cube].bg0.image(vec(0,0), FlipDown);
	BaseGameCube::update(timeStep);
}

void FlipItCube::setFlipDir (int flipDir)
{
	moveToCheck = flipDir;
}

void FlipItCube::init(CubeID initCube)
{
	cube = initCube;
	place = -1;
}

void FlipItCube::stop()
{
	started = false;
}

void FlipItCube::start()
{
        //AudioTracker::play(Music);
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
		buffer->bg0.image(vec(0,0),FlipUp);
		break;
	case 3:
		buffer->bg0.image(vec(0,0), FlipDown);
		break;
	case 4:
		buffer->bg0.image(vec(0,0), FlipOver);
		break;
	}

	started = true;
	finished = false;
	moveSuccess = false;

}

void FlipItCube::registerListener(CubeID cube)
{

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

void FlipItCube::setMode (int newMode)
{
	moveToCheck = newMode;
}

void FlipItCube::onAccelChange()
{
	if (!started)
	{
		return;
	}

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