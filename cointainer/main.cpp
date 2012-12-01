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
// Intended to be part of a linked list, but *next init to NULL caused linker errors.
class Coin {
private:
  Float2 _velocity;
  Float2 _position;

public:
  Coin *next = NULL;

  Float2 pos()                     { return _position; }
  Float2 pos(Float2 new_pos)       { return _position = new_pos; }
  Float2 velocity()                { return _velocity; }
  Float2 velocity(Float2 new_velo) { return _velocity = new_velo; }
};


// The game!
class Cointainer {
private:
  const Float2 COIN_START_POS = { 64.0, 64.0 };
  const Float2 COIN_START_VELOCITY = { 0.0, -5.0 };
  CoinStateMachine g_state;
  VideoBuffer vid;
  Float2 bg, text, textTarget;

  Coin *coins_head = NULL;
  Coin *coins_tail = NULL;

public:
  void init(unsigned cid) {
    Events::neighborAdd.set(&Cointainer::onNeighborAdd, this);
    Events::neighborRemove.set(&Cointainer::onNeighborRemove, this);
//     // String<32> logmsg;
//     // logmsg << "init cube #" << Fixed(cid, 2);
//     LOG("init cube #%d\n", cid);
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
    // create a coin
    // set its initial position & velocity
    // add to linked list
    // update coins_head
    Coin *new_coin = new Coin();
    // new_coin->pos(COIN_START_POS);
    // new_coin->velocity(COIN_START_VELOCITY);

    // coins_head->next = new_coin;
    // coins_head = new_coin;
  }

//   void delete_coin(Coin *target_coin = NULL) {
//     Coin *current_coin = coins_tail;

//     if ( current_coin == target_coin || target_coin == NULL ) {
//       // Target is tail? Update the tail.
//       coins_tail = current_coin->next;
//     } else {
//       // Comb thru list for target coin.
//       while ( current_coin != NULL ) {
//         if ( current_coin->next == target_coin ) {
//           // Found it! Remove from the list.
//           current_coin->next == target_coin->next;
//           current_coin = target_coin;
//           break;
//         }
//         current_coin = current_coin->next;
//       }
//     }

//     // Cleanup.
//     if ( current_coin != NULL ) delete current_coin;
//   }

  void animate_coins(float delta) {
    Coin *current_coin = coins_tail;
    while ( current_coin != NULL ) {
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
