#include "ShakeCube.h"

ShakeCube::ShakeCube()
{
}

void ShakeCube::init (CubeID initCube)
{
	cube = initCube;
	place = -1;

	shakeScore = 0;
	shakeCounter = 0;

    // Our background is 18x18 to match BG0, and it seamlessly tiles
	if (whichGame == 0)
	{
		buffer->bg0.image(vec(0,0), BackgroundX);
	}
	else if (whichGame == 1)
	{
		buffer->bg0.image(vec(0,0), BackgroundY);
	}

    // Allocate 16x2 tiles on BG1 for text at the bottom of the screen
    buffer->bg1.setMask(BG1Mask::filled(vec(0,12), vec(16,4)));
}

void ShakeCube::start()
{
	started = true;
	finished = false;

}

void ShakeCube::update(TimeDelta timeStep)
{
	//LOG("Update");
	if (whichGame == 0)
	{
		buffer->bg0.image(vec(0,0), BackgroundXTwo);
	}
	else if (whichGame == 1)
	{
		buffer->bg0.image(vec(0,0), BackgroundYTwo);
	}
	
	writeScore(shakeScore);

	Int2 accel = buffer->physicalAccel().xy();
	float delta;
	
	if (whichGame == 0)
	{
		delta = accel.x - lastAccel.x;
	}
	else if (whichGame == 1)
	{
		delta = accel.y - lastAccel.y;
	}
    
	delta = Sifteo::abs(delta);
	
	shakeCounter += delta;
	
	if (shakeCounter > 1000)
	{
		shakeCounter -= 1000;
		shakeScore++;
	}
			
	lastAccel = accel;
    
    buffer->bg1.setPanning(text.round());
}

bool ShakeCube::isFinished()
{
	return finished;
}

int ShakeCube::getPlace()
{
	return place;
}

void ShakeCube::setPlace (int newPlace)
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

void ShakeCube::stop()
{
	started = false;
}


void ShakeCube::writeText(const char *str)
{
    // Text on BG1, in the 16x2 area we allocated
    buffer->bg1.text(vec(0,12), Font2, str);
}

void ShakeCube::writeScore(int i)
{
	int maskWidth = 2;
	
	buffer->bg1.setMask(BG1Mask::filled(vec(0,12), vec(maskWidth * 2, 4)));
	text.set(-64 + maskWidth * 6, 52);
	
	String<3> bTest;
	bTest << Fixed(i, maskWidth, true);
	
	textTarget = text;
	writeText(bTest.c_str());
}
