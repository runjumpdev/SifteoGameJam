/*
 * TCMCube.h
 *
 *  Created on: Dec 12, 2012
 *      Author: Ben
 */

#ifndef TCMCUBE_H_
#define TCMCUBE_H_

#include "BaseGameCube.h"

class TCMCube: public BaseGameCube {
public:
	TCMCube();

	void init(CubeID initCube);

	void showKey();
	void showBlank();

	void displayResult (bool isWinner);

	bool isFlipped();
	bool isUpright();

};

#endif /* TCMCUBE_H_ */
