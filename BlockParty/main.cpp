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

//Game variables
BaseGame* CurrentGame;
static FlipItGame flipItGame;
static ShakeGame shakeGame;
static ColorMeGame colorMeGame;

static void InitCubes()
{
    for (unsigned i = 0; i < arraysize(cubeVideo); i++)
    {
		cubeVideo[i].initMode(BG0_SPR_BG1);
		cubeVideo[i].attach(i);
		motion[i].attach(i);
    }
}

//Event listener
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
		if (CurrentGame->IsStarted)
		{
			CurrentGame->onAccelChange(id);
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
					
					int rand = randomGen.randint(0, 2);
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

					} 
                }
            break;

        }

        System::paint();
        ts.next();
    }
}

