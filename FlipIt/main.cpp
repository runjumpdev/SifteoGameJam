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
#include "assets.gen.h"
using namespace Sifteo;

static const unsigned gNumCubes = 3;

static VideoBuffer cubeVideo[gNumCubes];
static TiltShakeRecognizer motion[gNumCubes];

static Metadata M = Metadata()
		.title("FlipIt")
		.package("com.bmg.sifteo.flipit","1.0")
		.icon(Icon)
		.cubeRange(gNumCubes);

static AssetSlot MainSlot = AssetSlot::allocate().bootstrap(BootstrapAssets);

static void playSfx(const AssetAudio& sfx) {
    static int i=0;
    AudioChannel(i).play(sfx);
    i = 1 - i;
}

class BaseGameCube
{
public:
    virtual void init(CubeID initcube);
    virtual void start();
    virtual void update(TimeDelta timeStep);
};

class BaseGame
{
public:
    virtual void init();
    virtual void start();
    virtual bool update(TimeDelta timeStep);
};

BaseGame* CurrentGame;
BaseGameCube* CurrentGameCube[gNumCubes];

class FlipItcube : public BaseGameCube
{
public:

	bool moveSuccess = false;

	// 0 - Left
	// 1 - Right
	// 2 - Up
	// 3 - Down
	// 4 - Flip
	int moveToCheck;

	SystemTime startTime;
	int32_t changeTime;

	CubeID cube;

	bool started = false;

	bool finished = false;

	int place = -1;

	FlipItcube()
	{
	}

	bool isFinished()
	{
		return finished;
	}

	int getPlace()
	{
		return place;
	}

	void setPlace (int newPlace)
	{
		LOG ("Cube %d finished %d\n", (int)cube, newPlace);

		place = newPlace;

		switch (newPlace)
		{
		case 0:
			cubeVideo[cube].bg0.image(vec(0,0), First);
			break;
		case 1:
			cubeVideo[cube].bg0.image(vec(0,0), Second);
			break;
		case 2:
			cubeVideo[cube].bg0.image(vec(0,0), Third);
			break;
		}
	}

	void update(TimeDelta timeStep)
	{
	        //LOG("update cube %i\n", (int)cube);
	        //cubeVideo[cube].bg0.image(vec(0,0), FlipDown);
	}

	void setFlipDir (int flipDir)
	{
		moveToCheck = flipDir;
	}

	void init (CubeID initCube)
	{
		cube = initCube;
		place = -1;
	}

	void stop()
	{
		started = false;
	}

	void start()
	{
	        //AudioTracker::play(Music);
		startTime = SystemTime::now();

		switch (moveToCheck)
		{
		case 0:
			 cubeVideo[cube].bg0.image(vec(0,0), FlipLeft);
			break;
		case 1:
			cubeVideo[cube].bg0.image(vec(0,0), FlipRight);
			break;
		case 2:
			 cubeVideo[cube].bg0.image(vec(0,0),FlipUp);
			break;
		case 3:
			 cubeVideo[cube].bg0.image(vec(0,0), FlipDown);
			break;
		case 4:
			 cubeVideo[cube].bg0.image(vec(0,0), FlipOver);
			break;
		}

		started = true;
		finished = false;
		moveSuccess = false;

	}

	void registerListener(CubeID cube)
	{

	}

	void touched ()
	{
		LOG ("touched\n");
		/*
		if (moveSuccess == true)
		{
			moveSuccess = false;
		}
		*/
	}

	void setMode (int newMode)
	{
		moveToCheck = newMode;
	}

	void cubeMoved()
	{
		if (!started)
		{
			return;
		}

		SystemTime nowTime = SystemTime::now();

		unsigned changeFlags = motion[cube].update();

		auto tilt = motion[cube].tilt;

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
};

static FlipItcube flipItCube[gNumCubes];

class FlipItGame : public BaseGame
{
	Random randomGen;

	int flipDir;

	bool gameOver = false;

	bool started = false;

	int lastFoundPlace = 0;

	int finishedPieces = 0;

public:
    void init()
    {
    	randomGen.seed();

		for (unsigned i = 0; i < gNumCubes; i++)
		{
			CurrentGameCube[i] = & flipItCube[i]; 
			CurrentGameCube[i]->init(i);
		}		
    }

    void start()
    {
        //AudioTracker::play(Music);
    	int rand = randomGen.randint(0, 4);

    	flipDir = rand;

    	gameOver = false;
    	started = true;

    	lastFoundPlace = 0;
    	finishedPieces = 0;

                    for (unsigned i = 0; i < arraysize(flipItCube); i++)
                    {
                        flipItCube[i].setFlipDir(getFlipDir());
                    }

    }

    bool update(TimeDelta timeStep)
    {
//        LOG("update game\n");

        for (int i=0; i < arraysize(flipItCube); i++)
        {
        	if (flipItCube[i].isFinished() && (flipItCube[i].getPlace() < 0))
        	{
        		flipItCube[i].setPlace(lastFoundPlace);
        		lastFoundPlace++;
        		finishedPieces++;
        	}
        }

        if (finishedPieces == arraysize(flipItCube))
        {
        	gameOver = true;
        }

        return gameOver;
    }

    int getFlipDir()
    {
    	return flipDir;
    }

private:

};

static FlipItGame flipItGame;

static void InitCube(int CubeIndex, CubeID cube)
{
    cubeVideo[CubeIndex].initMode(BG0_SPR_BG1);
    cubeVideo[CubeIndex].attach(cube);
    motion[CubeIndex].attach(CubeIndex);
}

class EventHandler
{
public:
	void init()
	{
		Events::cubeAccelChange.set(&EventHandler::onAccelChange, this);
		Events::cubeTouch.set(&EventHandler::onTouch, this);
	}

	void onAccelChange(unsigned id)
	{
		flipItCube[id].cubeMoved();
	}

	void onTouch (unsigned id)
	{
		flipItCube[id].touched();
	}
};

enum GameState
{
  StateInit,
  StateStart,
  StatePlay,
  StateResults
};

void main()
{
    GameState state = StateInit;

    for (unsigned i = 0; i < arraysize(cubeVideo); i++)
    {
        InitCube(i, i);
    }

    EventHandler handler;
    handler.init();

    TimeStep ts;
    float Delay;
    bool isDone;

    CurrentGame = &flipItGame;

    while (1)
    {
        switch (state)
        {
            case StateInit:
				CurrentGame->init();
				Delay = 3;
				playSfx (CountSound);
				LOG ("Init\n");
				state = StateStart;
            break;

            case StateStart:
                Delay -= float(ts.delta());

                if (Delay <= 0)
                {
                    CurrentGame->start();
                    for (unsigned i = 0; i < gNumCubes; i++)
                    {
                        CurrentGameCube[i]->start();
                    }
                    LOG ("Start Done\n");
		            state = StatePlay;
                }
            break;

            case StatePlay:
				isDone = CurrentGame->update(ts.delta());

				if (isDone)
				{
					LOG ("Game Done\n");
					state = StateResults;
					Delay = 3;
					playSfx (CheersSound);
				}
				else
				{
					for (unsigned i = 0; i < gNumCubes; i++)
					{
						CurrentGameCube[i]->update(ts.delta());
					}
				}
            break;

            case StateResults:
                Delay -= float(ts.delta());

                if (Delay <= 0)
                {
					state = StateInit;
					LOG ("Results Done\n");
                }
            break;

        }

        System::paint();
        ts.next();
    }
}

