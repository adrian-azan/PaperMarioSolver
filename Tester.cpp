#include "arena.cpp"

class Tester: public Arena
{
	public:
		Tester(): Arena(){}
		
		void rotateTest();
		void slideTest();
		bool compare(Tile* tile, bool *enemies);	
		
	
	
};


void printEnemies(bool enemies[])
{
	cout << "   ";
	for (int i = 0; i < 12;i++)
		cout << enemies[i] << " ";
	cout << endl;
}

void Tester::rotateTest()
{
	bool enemies[12] = {0,0,1,1,0,0,1,1,0,0,0,1};
	bool rotate1[12] = {1,0,0,1,1,0,0,1,1,0,0,0};
	bool rotate2[12] = {0,1,0,0,1,1,0,0,1,1,0,0};
	bool rotate3[12] = {0,0,1,0,0,1,1,0,0,1,1,0};
	bool rotate10[12]= {1,1,0,0,1,1,0,0,0,1,0,0};
	bool rotate11[12]= {0,1,1,0,0,1,1,0,0,0,1,0};
	
	setRing(0, enemies);
	
	rotate(0,1);
	assert(compare(getRing(0),rotate1));
				
	rotate(0,1);
	assert(compare(getRing(0),rotate2));
	
	setRing(0,enemies);
	rotate(0,3);
	assert(compare(getRing(0),rotate3));
	
	setRing(1,enemies);
	rotate(1,10);
	assert(compare(getRing(1),rotate10));
	
	setRing(2,enemies);
	rotate(2,11);
	assert(compare(getRing(2),rotate11));
	
	setRing(3, enemies);
	rotate(3,12);
	assert(compare(getRing(3),enemies));
	
}

void Tester::slideTest()
{
	bool enemies3[12] = {1,1,1,1,1,1,1,0,1,0,0,0};
	bool enemies2[12] = {1,1,0,1,0,0,0,0,0,0,0,1};
	bool enemies1[12] = {1,0,0,0,1,0,0,0,0,0,0,0};
	bool enemies0[12] = {1,0,0,1,1,0,0,0,0,0,0,0};

	bool slide1_3[12] = {0,1,0,0,0,1,1,1,0,0,0,0};
	bool slide1_2[12] = {0,0,0,0,0,0,1,0,0,0,1,1};
	bool slide1_1[12] = {0,0,0,1,0,0,1,0,1,1,1,0};
	bool slide1_0[12] = {1,0,0,1,1,0,1,0,1,0,0,0};
	
	setRing(0,enemies0);
	setRing(1,enemies1);
	setRing(2,enemies2);
	setRing(3,enemies3);
	
	slide(0,4);
	slide(1,7);
	slide(2,5);
	slide(3,2);
	slide(4,3);
	slide(5,0);
	
	assert(compare(getRing(3),slide1_3));
	assert(compare(getRing(2),slide1_2));
	assert(compare(getRing(1),slide1_1));
	assert(compare(getRing(0),slide1_0));
		
}

bool Tester::compare(Tile* tile, bool enemies[])
{
	Tile* currentTile = tile;
	for (int i = 0; i < 12; i++)
	{
		if (currentTile->full != enemies[i])
			return false;
		currentTile = currentTile->cw;
	}
	
	return true;
}





