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

static Metadata M = Metadata()
		.title("FlipIt")
		.package("com.bmg.sifteo.flipit","1.0")
		.icon(Icon)
		.cubeRange(1);

static VideoBuffer vid;

static AssetSlot MainSlot = AssetSlot::allocate().bootstrap(BootstrapAssets);

void main()
{
	vid.initMode(BG0);
	vid.attach(0);
	vid.bg0.image(vec(0,0), FlipLeft);

	while (1)
	{
		System::paint();
	}

}





