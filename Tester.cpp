#include "arena.cpp"

class Tester: public Arena
{
	public:
		Tester(): Arena(){}
		
		void rotateTest();
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





