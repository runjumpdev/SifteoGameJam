
#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;

//-- Music = tracker{ "ultrasyd-toy_world.xm" }

// -- SfxAttach = sound{ "attach.raw" }
static Metadata M = Metadata()
	.title("Hello World")
	.package("com.bmg.sifteo.helloworld","1.0")
	.icon(Icon)
	.cubeRange(1);
	
static VideoBuffer vid;

static void playSfx(const AssetAudio& sfx) {
    static int i=0;
    AudioChannel(i).play(sfx);
    i = 1 - i;
}

//static AssetSlot mainSlot = AssetSlot::allocate().bootstrap(BootstrapAssets);

//static AssetLoader loader;
//static AssetConfiguration<1> config;

void main()
{
	vid.initMode(BG0_ROM);
    vid.attach(0);
	
	String <128> text;
	text << "Hello World" << "\n";
	
	vid.bg0rom.text(vec(0,0),text);
	
	playSfx (CountSound);

//	AudioTracker::play(CountSound);

	while (1)
        System::paint();
}
