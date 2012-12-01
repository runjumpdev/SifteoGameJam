/*
 * main.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: Ben Gold
 *
 *
 *      Steps:
 *        Register for tilt events, verify cubes are flat
 *        at (second 0) display "3"
 *        at (second 1) display "2"
 *        at (second 2) display "1"
 *        at (second 3) show random symbol
 *        Verify cube movement, record time
 *        Compare all times
 *        For Winner Show "winner"
 *        For All Others Show "loser"
 */

#include <sifteo.h>
#include <sifteo/math.h>

#include "assets.gen.h"
using namespace Sifteo;

static Metadata M = Metadata()
		.title("FlipIt")
		.package("com.bmg.sifteo.flipit","1.0")
		.icon(Icon)
		.cubeRange(1);

static VideoBuffer vid;

static AssetSlot MainSlot = AssetSlot::allocate().bootstrap(BootstrapAssets);

static TiltShakeRecognizer motion;

class CubeTracker
{
public:

	bool moveSuccess = false;

	// 0 - Left
	// 1 - Right
	// 2 - Up
	// 3 - Down
	// 4 - Flip
	int moveToCheck;

	Random randomGen;

	SystemTime startTime;
	int32_t changeTime;

	CubeTracker()
	{
		randomGen.seed();
	}

	void init ()
	{
		int rand = randomGen.randint(0, 4);

		LOG ("Rand: %i\n", rand);

		switch (rand)
		{
		case 0:
			vid.bg0.image(vec(0,0), FlipLeft);
			break;
		case 1:
			vid.bg0.image(vec(0,0), FlipRight);
			break;
		case 2:
			vid.bg0.image(vec(0,0),FlipUp);
			break;
		case 3:
			vid.bg0.image(vec(0,0), FlipDown);
			break;
		case 4:
			vid.bg0.image(vec(0,0), FlipOver);
			break;
		}

		moveToCheck = rand;

		startTime = SystemTime::now();
	}

	void registerListener(CubeID cube)
	{
		Events::cubeAccelChange.set(&CubeTracker::cubeMoved, this);
		Events::cubeTouch.set(&CubeTracker::touched, this);
	}

	void touched (unsigned id)
	{
		LOG ("touched\n");
		CubeID cube(0);
		if (moveSuccess == true)
		{
			moveSuccess = false;
			init();
		}
	}

	void setMode (int newMode)
	{
		moveToCheck = newMode;
	}

	void cubeMoved(unsigned id)
	{
		LOG ("Cube Moved\n");

		SystemTime nowTime = SystemTime::now();

		CubeID cube(0);

		unsigned changeFlags = motion.update();

		auto tilt = motion.tilt;

		auto accel = cube.accel();

		LOG ("Accel.x %d Accel.y: %d Accel.z %d\n", (signed int)accel.x, (signed int)accel.y, (signed int)accel.z);

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
		if (move < 3)
		{
			moveSuccess = true;
			LOG ("MOVE SUCCESS %d\n", move);
			vid.bg0.image(vec(0,0), Green);

			TimeDelta delta = nowTime - startTime;
			changeTime = delta.milliseconds();

			LOG ("DELTA TIME: %d\n", changeTime);
		}

	}
};

void main()
{
	vid.initMode(BG0_SPR_BG1);
	vid.attach(0);

	static CubeTracker tracker;
	tracker.registerListener(0);

	tracker.init();

	motion.attach(0);

	while (1)
	{
		System::paint();
	}

}
