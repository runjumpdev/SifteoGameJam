/*
 * Cointainer
 *
 * - One cube displays coin tube, the other displays a moneybag
 * - Orient properly so tube is up, bag is down
 * - Neighbor tap to transfer a coin from the bag to the tube
 *
 */

#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;

static const unsigned gNumCubes = 2;
Random gRandom;

// static AssetSlot MainSlot = AssetSlot::allocate()
//     .bootstrap(GameAssets);

static Metadata M = Metadata()
    .title("Stars SDK Example")
    .package("com.sifteo.sdk.stars", "1.0")
    .icon(Icon)
    .cubeRange(gNumCubes);

class CoinStateMachine {
public:
  bool tap()   {
    if ( is_tapped ) {
      return false;
    } else {
      return is_tapped = true;
    }
  }

  bool untap() {
    if ( is_tapped ) {
      is_tapped = false;
      return true;
    } else {
      return false;
    }
  }

private:
  bool is_tapped = false;
};


class Cointainer {
public:
  void init(unsigned cid) {
    Events::neighborAdd.set(&Cointainer::onNeighborAdd, this);
    Events::neighborRemove.set(&Cointainer::onNeighborRemove, this);
  }

  void update(float delta) {
  }

  void onNeighborAdd(unsigned cube0, unsigned side0, unsigned cube1,
                     unsigned side1)
  {
    // State machine untapped => tapped
    // Add a coin to the animation list
    // Flip SFX on for next paint
    // Increment score
    if ( g_state.tap() ) {
      add_coin();
    }
  }

  void onNeighborRemove(unsigned cube0, unsigned side0, unsigned cube1,
                        unsigned side1)
  {
    g_state.untap();
  }

  void add_coin() {
    LOG("coin added");
  }

private:
  CoinStateMachine g_state;
};

void main() {
  static Cointainer instances[gNumCubes];

  // AudioTracker::play(Music);

  for (unsigned i = 0; i < arraysize(instances); i++)
      instances[i].init(i);

  TimeStep ts;
  while (1) {
      for (unsigned i = 0; i < arraysize(instances); i++)
          instances[i].update(ts.delta());

      System::paint();
      ts.next();
  }
}
