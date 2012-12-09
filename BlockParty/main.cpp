#include <sifteo.h>
#include "assets.gen.h"
#include "BaseGameCube.h"
#include "BaseGame.h"
#include "FlipItCube.h"
#include "FlipItGame.h"
#include "ShakeCube.h"
#include "ShakeGame.h"
#include "ColorMeCube.h"
#include "ColorMeGame.h"
#include "HotCubeGame.h"
#include "HotCubeMP/HotCubeMPGame.h"

using namespace Sifteo;

// TODO: Change this to a runtime number?
//  Sensors shows CubeSet::connected() event to determine connected cubes
//  and use const to declare *maximum* supported cubes
static unsigned gNumCubes = 3;
static VideoBuffer cubeVideo[CUBE_ALLOCATION];
static TiltShakeRecognizer motion[CUBE_ALLOCATION];

static Metadata M = Metadata()
		.title("Block Party")
		.package("com.rjd.sifteo.blockparty","1.1")
		.icon(Icon)
		.cubeRange(1, CUBE_ALLOCATION);

static AssetSlot MainSlot = AssetSlot::allocate().bootstrap(BootstrapAssets);
static AssetSlot HotCubeSlot = AssetSlot::allocate().bootstrap(HotCubeAssets);

static void playSfx(const AssetAudio& sfx) {
    static int i=0;
    AudioChannel(i).play(sfx);
    i = 1 - i;
}

//Game variables
BaseGame* CurrentGame;
static FlipItGame flipItGame;
static ShakeGame shakeGame;
static ColorMeGame colorMeGame;
static HotCubeGame hotCubeGame;
static HotCubeMPGame hotCubeMPGame;

static void InitCubes()
{
	LOG ("InitCubes\n");
	int i=0;
	for (CubeID cube : CubeSet::connected())
	{
		cubeVideo[i].initMode(BG0_SPR_BG1);
		cubeVideo[i].attach(i);
		motion[i].attach(i);

		i++;
	}

	LOG ("\tCubes Found: %d\n", gNumCubes);

	gNumCubes = i;
}

//Event listener
class EventHandler
{
public:
	void init()
	{
		Events::cubeAccelChange.set(&EventHandler::onAccelChange, this);
		Events::neighborAdd.set(&EventHandler::onNeighborAdd, this);
		Events::cubeTouch.set(&EventHandler::onTouch, this);
		Events::cubeConnect.set(&EventHandler::onConnect, this);
	}

	void onConnect (unsigned id)
	{
		LOG ("onConnect (%d)\n", id);
		CubeID cube (id);
		cubeVideo[id].initMode(BG0_SPR_BG1);
		cubeVideo[id].attach(id);
		motion[id].attach (id);

		gNumCubes++;
	}

	void onAccelChange(unsigned id)
	{
		if (CurrentGame->IsStarted)
		{
			CurrentGame->onAccelChange(id);
		}
	}

	void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
	{
		if (CurrentGame->IsStarted)
		{
			CurrentGame->onNeighborAdd(firstID, firstSide, secondID, secondSide);
		}
	}

	void onTouch (unsigned id)
	{
		if (CurrentGame->IsStarted)
		{
			CurrentGame->onTouch(id);
		}
	}
};

//Meta game states
enum GameState
{
  StateInit,
  StateStart,
  StatePlay,
  StateResults
};

void main()
{
    GameState state = StateResults;
	Random randomGen;
  	randomGen.seed();

	InitCubes();
	
    EventHandler handler;
    handler.init();

    TimeStep ts;
    float Delay;
    bool isDone;

    while (1)
    {
        switch (state)
        {
            case StateInit:
				CurrentGame->init(gNumCubes, cubeVideo);
				CurrentGame->setTiltShakeRecognizer(motion, gNumCubes);
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
                    LOG ("Start Done\n");
		            state = StatePlay;
                }
            break;

            case StatePlay:
				isDone = CurrentGame->update(ts.delta());

				if (isDone)
				{
					LOG ("Game Done\n");
					CurrentGame->stop();
					state = StateResults;
					Delay = 3;
					playSfx (CheersSound);
				}

            break;

            case StateResults:
                Delay -= float(ts.delta());

                if (Delay <= 0)
                {
					state = StateInit;
					LOG ("Results Done\n");
					
					if (CurrentGame != NULL)
						CurrentGame->cleanUp();

					int rand = randomGen.randint(0, 4);
					switch (rand)
					{
					    case 0:
							LOG ("Playing Flip It\n");
							CurrentGame = &flipItGame;
							break;
						
						case 1:
							LOG ("Playing Color Me\n");
							CurrentGame = &colorMeGame;
							break;

						case 2:
							LOG ("Playing Shake\n");
							CurrentGame = &shakeGame;
							break;

						case 3:
							LOG ("Playing Hot Cube\n");
							CurrentGame = &hotCubeGame;
							break;

						case 4:
							LOG ("Playing Hot Cube MP\n");
							CurrentGame = &hotCubeMPGame;
							break;

					} 
                }
            break;

        }

        System::paint();
        ts.next();
    }
}

