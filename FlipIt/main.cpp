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


class FlipItCube
{
public:
    void init(CubeID initcube)
    {
	cube = initcube;

        cubeVideo[cube].bg0.image(vec(0,0), FlipLeft);

        // Allocate 16x2 tiles on BG1 for text at the bottom of the screen
        //vid.bg1.setMask(BG1Mask::filled(vec(0,14), vec(16,2)));
    }

    void start()
    {
    }
    
    void update(TimeDelta timeStep)
    {
        //LOG("update cube %i\n", (int)cube);
        cubeVideo[cube].bg0.image(vec(0,0), FlipDown);
    }

private:       
    CubeID cube;
};


class FlipItGame
{
public:
    void init()
    {
    }
    
    void start()
    {
        //AudioTracker::play(Music);
    }
    
    void update(TimeDelta timeStep)
    {
        //LOG("update game\n");
    }

private:

};

static FlipItCube flipItCube[gNumCubes];
static FlipItGame flipItGame;


static void InitCube(int CubeIndex, CubeID cube)
{
    cubeVideo[CubeIndex].initMode(BG0_SPR_BG1);
    cubeVideo[CubeIndex].attach(cube);
}


void main()
{
    for (unsigned i = 0; i < arraysize(cubeVideo); i++)
    {
        InitCube(i, i);
    }

    TimeStep ts;
    bool isInitialized = false;
    float startDelay;

    while (1)
    {
        if (!isInitialized)
        {
            flipItGame.init();
            for (unsigned i = 0; i < arraysize(flipItCube); i++)
            {
                flipItCube[i].init(i);
            }
            startDelay = 3;
            isInitialized = true;
	    playSfx (CountSound);
        }
        else
        {
            if (startDelay > 0)
            {
                startDelay -= float(ts.delta());

                if (startDelay <= 0)
                {
                    flipItGame.start();
                    for (unsigned i = 0; i < arraysize(flipItCube); i++)
                    {
                        flipItCube[i].start();
                    }
                }
            }
            else
            {
                flipItGame.update(ts.delta());
                for (unsigned i = 0; i < arraysize(flipItCube); i++)
                {
                    flipItCube[i].update(ts.delta());
                }
            }
        }
        System::paint();
        ts.next();
    }
}





