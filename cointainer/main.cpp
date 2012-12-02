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


// For debouncing tap/untap motions.
class CoinStateMachine {
private:
  bool is_tapped = false;

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
};


// Single coin
//
// Intended to be a class in a linked list, but *next init to NULL caused
// linker errors.
struct Coin {
  Float2 pos, velocity;
};


// The game!
class Cointainer {
private:
  const Float2 COIN_START_POS = { 64.0, 64.0 };
  const Float2 COIN_START_VELOCITY = { 0.0, -5.0 };
  CoinStateMachine g_state;
  VideoBuffer vid;
  Float2 bg, text, textTarget;

  int animated_coin_count = 0;

  Coin *coins_head = NULL;
  Coin *coins_tail = NULL;

  int score = 0;

public:
  void init(unsigned cid) {
    Events::neighborAdd.set(&Cointainer::onNeighborAdd, this);
    Events::neighborRemove.set(&Cointainer::onNeighborRemove, this);
    // String<32> logmsg;
    // logmsg << "init cube #" << Fixed(cid, 2);
    LOG("init cube #%d\n", cid);
  }

  void update(float delta) {
    animate_coins(delta);
  }

  void onNeighborAdd(unsigned cube0, unsigned side0, unsigned cube1,
                     unsigned side1)
  {
    // State machine untapped => tapped
    // Add a coin to the animation list
    // Flip SFX on for next paint
    // Increment score
    LOG("neighbor %d added cube %d as a neighbor\n", cube0, cube1);
    if ( g_state.tap() ) {
      add_coin();
    }
  }

  void onNeighborRemove(unsigned cube0, unsigned side0, unsigned cube1,
                        unsigned side1)
  {
    LOG("neighbor %d added cube %d as a neighbor\n", cube0, cube1);
    g_state.untap();
  }

  void add_coin() {
    LOG("coin added\n");
    animated_coin_count++;
    score++;
    LOG("score: %d\n", score);
  }

  void delete_coin() {
    LOG("coin finished\n");
    animated_coin_count--;
  }

  void animate_coins(float delta) {
    if ( animated_coin_count > 0 ) {
      // Animate!
    }
  }

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
