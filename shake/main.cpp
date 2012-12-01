/*
 * Sifteo SDK Example.
 */

#include <sifteo.h>
#include <sifteo/string.h>
#include "assets.gen.h"

using namespace Sifteo;

static const unsigned gNumCubes = 3;
Random gRandom;

static AssetSlot MainSlot = AssetSlot::allocate()
    .bootstrap(GameAssets);

static Metadata M = Metadata()
    .title("shake")
    .package("empty", "1.0")
    .icon(Icon)
    .cubeRange(gNumCubes);


class StarDemo {
public:

    static const unsigned numStars = 1;
    
	public : bool isOut;
	Int2 lastAccel;
	public : int rank;
    static const float textSpeed = 0.2f;
    static const float bgScrollSpeed = 10.0f;
    static const float bgTiltSpeed = 1.0f;
    static const float starEmitSpeed = 60.0f;
    static const float starTiltSpeed = 3.0f;
	
	static CubeSet outCubes; //cubes that have lost

    void init(CubeID cube, int wG)
    {
        frame = 0;
	
        bg.x = 0;
        bg.y = 0;
		rank = 0;
		
		shakeScore = 0;
		shakeCounter = 0;
		
        vid.initMode(BG0_SPR_BG1);
        vid.attach(cube);
        
        for (unsigned i = 0; i < numStars; i++)
            initStar(i);

        // Our background is 18x18 to match BG0, and it seamlessly tiles
		if (wG == 0)
		{
			vid.bg0.image(vec(0,0), BackgroundX);
		}
		else if (wG == 1)
		{
			vid.bg0.image(vec(0,0), BackgroundY);
		}

        // Allocate 16x2 tiles on BG1 for text at the bottom of the screen
        vid.bg1.setMask(BG1Mask::filled(vec(0,12), vec(16,4)));
    }
    
    void update(TimeDelta timeStep, int wG, bool b)
    {
	if (!b)
	{
		writeText("                                 ");
		return;
	}
	if (wG == 0)
		{
			vid.bg0.image(vec(0,0), BackgroundXTwo);
		}
		else if (wG == 1)
		{
			vid.bg0.image(vec(0,0), BackgroundYTwo);
		}
		
		writeScore(shakeScore);

		Int2 accel = vid.physicalAccel().xy();
		float delta;
		
		if (wG == 0)
		{
			delta = accel.x - lastAccel.x;
		}
		else if (wG == 1)
		{
			delta = accel.y - lastAccel.y;
		}
        
		delta = Sifteo::abs(delta);
		
        //Float2 tilt = accel * starTiltSpeed;
        
		//float x = accel.x - lastAccel.x;
		//float y = accel.y - lastAccel.y;
		//float z = accel.z - lastAccel.z;
		
		//float deltaSquared = x * x + y * y; 
		
		//shakeCounter += deltaSquared;
		shakeCounter += delta;
		
		if (shakeCounter > 1000)
		{
			shakeCounter -= 1000;
			shakeScore++;
		}
		
		// if (shakeCounter > 512000)
		// {
			// shakeCounter -= 512000;
			// shakeScore++;
		// }
		
		lastAccel = accel;
        
        // for (unsigned i = 0; i < numStars; i++) 
		// {
            // const Float2 center = { 64 - 16.0f, 64 - 16.0f };
            // vid.sprites[i].setImage(Star, frame % Star.numFrames());
            // vid.sprites[i].move(stars[i].pos + center);
        // }
		
        //Float2 bgVelocity = bgTiltSpeed + vec(0.0f, -1.0f) * bgScrollSpeed;
        //bg += float(timeStep) * bgVelocity;
        //vid.bg0.setPanning(bg.round());
		
        vid.bg1.setPanning(text.round());
    }

private:   
    struct {
        Float2 pos, velocity;
    } stars[numStars];
    
    VideoBuffer vid;
    unsigned frame;
	
    Float2 bg, text, textTarget;
    float fpsTimespan;
	int shakeScore;
	float shakeCounter;

    void writeText(const char *str)
    {
        // Text on BG1, in the 16x2 area we allocated
        vid.bg1.text(vec(0,12), Font, str);
    }
	
	void writeScore(int i)
	{
		int maskWidth = 2;
		
		vid.bg1.setMask(BG1Mask::filled(vec(0,12), vec(maskWidth * 2, 4)));
		text.set(-64 + maskWidth * 6, 52);
		
		String<3> bTest;
		bTest << Fixed(i, maskWidth, true);
		
		textTarget = text;
		writeText(bTest.c_str());
	}

    void initStar(int id)
    {
        float angle = gRandom.uniform(0, 2 * M_PI);
        float speed = gRandom.uniform(starEmitSpeed * 0.5f, starEmitSpeed);    
        stars[id].pos.set(0, 0);
        stars[id].velocity.setPolar(angle, speed);
    }
};


void main()
{
    static StarDemo instances[gNumCubes];

	Random rand;
	rand.seed();
	
	int whichGame; //0 = x axis shake, 1 = y axis shake
	whichGame = rand.randrange(0,2);
	
	float timeElapsed = 0;
	
	float startDelay = 2;
	bool started = false;
	
	float howLong = rand.random() * 12 + 2.5;
	
    AudioTracker::play(Music);

    for (unsigned i = 0; i < arraysize(instances); i++)
        instances[i].init(i, whichGame);
    int numOut = 0;
    TimeStep ts;
    while (1) 
	{
	startDelay -= ts.delta();
	if (startDelay <= 0)
	{
		
		started = true;
	}
	if (started)
	{
		timeElapsed += ts.delta();
	}
		if (timeElapsed < howLong)
		{
			for (unsigned i = 0; i < arraysize(instances); i++)
			{
					instances[i].update(ts.delta(), whichGame, started);
					if (instances[i].isOut && instances[i].rank == 0)
					{
						
						numOut++;
						instances[i].rank = numOut;
					}
			}
		}
		else
		{
			AudioTracker::stop();
		}
		System::paint();
			ts.next();   
    }
}