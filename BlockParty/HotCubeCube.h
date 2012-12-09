/*
 * HotCubeCube.h
 *
 *  Created on: Dec 5, 2012
 *      Author: Ben
 */

#ifndef HOTCUBECUBE_H_
#define HOTCUBECUBE_H_

#include <sifteo.h>
#include "assets.gen.h"
#include "BaseGameCube.h"

using namespace Sifteo;

struct Matchup
{
	unsigned int cubeId;
	unsigned int side;
	bool isMatched = false;
	bool isPaired = false;
	unsigned int color;
	unsigned int stamp;
};

class HotCubeCube : public BaseGameCube
{
public:
	HotCubeCube();

	void init (CubeID initcube);
	void start();
	void stop();

	void cleanUp();

	void paintCountdown (float timeLeft);

	void gameFinished (int totalIterations);

	void clear();

	void setMatchup (Matchup matchup, unsigned int side);
	bool isMatched (unsigned int side);
	unsigned int getMatchupsCount();
	bool isPaired (unsigned int side);

	void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide);

	unsigned int getSuccessfulMatchCount();

private:
	void writeText (const char* str);

	void lightDisconnected (unsigned int side);
	void lightConnected (unsigned int side, unsigned int stampId);

	void paintEdge (unsigned int side, const AssetImage& color);
	void paintStamp (unsigned int side, unsigned int stamp);


	bool checkMatchup (Matchup* matchup, unsigned ID, unsigned side);

	Matchup matchups[4];
	unsigned int successfulMatches = 0;
};

#endif /* HOTCUBECUBE_H_ */
