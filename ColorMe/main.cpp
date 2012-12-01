/*
 * main.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: Ben Gold
 *
 *
 *      Steps:
 *      	1)  Start Game
 *      	2)  While time is still running pick a color
 *      	3)  When time is out pick the winning color
 *      	4)  Declare winners
 */

#include <sifteo.h>
#include "assets.gen.h"
#include "ColorMeGame.h"

using namespace Sifteo;

static const unsigned gNumCubes = 3;

static VideoBuffer cubeVideo[gNumCubes];
static TiltShakeRecognizer motion[gNumCubes];

static Metadata M = Metadata()
		.title("ColorMe")
		.package("com.bmg.sifteo.colorme","1.0")
		.icon(Icon)
		.cubeRange(gNumCubes);

static AssetSlot MainSlot = AssetSlot::allocate().bootstrap(BootstrapAssets);

static void playSfx(const AssetAudio& sfx) {
    static int i=0;
    AudioChannel(i).play(sfx);
    i = 1 - i;
}

static ColorMeGame colorMeGame;

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
		Events::cubeTouch.set(&EventHandler::onTouch, this);
	}

	void onTouch (unsigned id)
	{
		colorMeGame.touched(id);
	}
};

void main()
{

    EventHandler handler;
    handler.init();

    for (int i=0; i < gNumCubes; i++)
    {
    	InitCube (i, i);
    }

    TimeStep ts;
    bool isInitialized = false;
    float startDelay;

    while (1)
    {
        if (!isInitialized)
        {
            colorMeGame.init(gNumCubes);

            colorMeGame.setVideoBuffer(cubeVideo, gNumCubes);

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
                    colorMeGame.start();
                }
            }
            else
            {
            	bool isDone = colorMeGame.update(ts.delta());

            	if (isDone)
            	{
            		isInitialized = false;
            	}
            }
        }
        System::paint();
        ts.next();
    }
}

