/*
 * Sifteo SDK Example.
 */

#include <sifteo.h>
#include <sifteo/string.h>
#include <sifteo/math.h>
#include "assets.gen.h"

using namespace Sifteo;

static const unsigned gNumCubes = 3;
Random gRandom;

static AssetSlot MainSlot = AssetSlot::allocate()
    .bootstrap(GameAssets);

static Metadata M = Metadata()
    .title("R U Game")
    .package("empty", "1.0")
    .icon(Icon)
    .cubeRange(gNumCubes);


class StarDemo {
public:

    static const unsigned numStars = 4;
    
	public : bool isOut;
	Int2 lastAccel;
	public : int rank;
    static const float textSpeed = 0.2f;
    static const float bgScrollSpeed = 10.0f;
    static const float bgTiltSpeed = 1.0f;
    static const float starEmitSpeed = 60.0f;
    static const float starTiltSpeed = 3.0f;
	
	static CubeSet outCubes; //cubes that have lost

    void init(CubeID cube)
    {
        frame = 0;
		timeElapsed = 0;
        bg.x = 0;
        bg.y = 0;
		rank = 0;
		isOut = false;
		
        vid.initMode(BG0_SPR_BG1);
        vid.attach(cube);
        
        for (unsigned i = 0; i < numStars; i++)
            initStar(i);

        // Our background is 18x18 to match BG0, and it seamlessly tiles
        vid.bg0.image(vec(0,0), Background);

        // Allocate 16x2 tiles on BG1 for text at the bottom of the screen
        vid.bg1.setMask(BG1Mask::filled(vec(0,12), vec(16,4)));
    }
    
    void update(TimeDelta timeStep, bool b, float tE)
    {
		
		if (!b)
		{
		for (unsigned i = 0; i < numStars; i++) 
		{
            const Float2 center = {52, 64 - 16.0f };
            vid.sprites[i].setImage(Star, frame % Star.numFrames());
            vid.sprites[i].move(stars[i].pos + center);
        }
		
			writeScore(Sifteo::round(tE));
			vid.bg0.setPanning(bg.round());
			vid.bg1.setPanning(text.round());
			 
			return;
		}
		else
		{
			if (!isOut)
			{
				vid.bg1.setMask(BG1Mask::filled(vec(0,0), vec(0,0)));
			}
			else
			{
				vid.bg1.setMask(BG1Mask::filled(vec(0,12), vec(12,4)));
				text.set(-16,82);
				textTarget = text;
				writeText("U looz");
			}
		}

		if (isOut)
		{
			frame = 7;
			//text.set(0, 8);
			//textTarget = text;
		}
		else
		{
			timeElapsed += timeStep;
			if (timeElapsed > .5)
			{
				frame++;
				timeElapsed -= .5;
			}
		}
		
        Int2 accel = vid.physicalAccel().xy();
        //Float2 tilt = accel * starTiltSpeed;
        
		float x = accel.x - lastAccel.x;
		float y = accel.y - lastAccel.y;
		//float z = accel.z - lastAccel.z;
		
		float deltaSquared = x * x + y * y; 
		
		if (deltaSquared > 128)
		{
			isOut = true;
		}
		
		lastAccel = accel;
        
        for (unsigned i = 0; i < numStars; i++) 
		{
            const Float2 center = {32 * i, 64 - 16.0f };
            vid.sprites[i].setImage(Star, frame % Star.numFrames());
            vid.sprites[i].move(stars[i].pos + center);
        }
		
        //Float2 bgVelocity = bgTiltSpeed + vec(0.0f, -1.0f) * bgScrollSpeed;
        //bg += float(timeStep) * bgVelocity;
        vid.bg0.setPanning(bg.round());
		
		vid.bg1.setPanning(text.round());
    }

private:   
    struct {
        Float2 pos, velocity;
    } stars[numStars];
    
    VideoBuffer vid;
    unsigned frame;
	float timeElapsed;
    Float2 bg, text, textTarget;
    float fpsTimespan;

    void writeText(const char *str)
    {
        // Text on BG1, in the 16x2 area we allocated
        vid.bg1.text(vec(0,12), Font, str);
    }
	
	void writeScore(int i)
	{
		int maskWidth = 2;
		
		vid.bg1.setMask(BG1Mask::filled(vec(0,12), vec(maskWidth * 2, 4)));
		text.set(-64 + maskWidth * 6, 82);
		
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

	float timeToStart = 3;
	bool ready = false;
	
    AudioTracker::play(Music);

    for (unsigned i = 0; i < arraysize(instances); i++)
        instances[i].init(i);
    int numOut = 0;
    TimeStep ts;
    while (1) 
	{
		if (!ready)
		{
			timeToStart -= ts.delta();
			
			if (timeToStart <= 0)
			{
				ready = true;
			}
		}
		
        for (unsigned i = 0; i < arraysize(instances); i++)
		{
				instances[i].update(ts.delta(), ready, timeToStart);
				if (instances[i].isOut && instances[i].rank == 0)
				{
					
					numOut++;
					instances[i].rank = numOut;
				}
		}
		if (numOut == arraysize(instances))
		{
			AudioTracker::stop();
		}
		System::paint();
		ts.next();   
    }
}