#ifndef TESTER_H
#define TESTER_H

#include "arena.h"


class Tester: public Arena
{
	public:
		Tester(): Arena(){}
		
		void rotateTest();
		void slideTest();
		bool compare(Tile* tile, bool *enemies);
};


#endif
