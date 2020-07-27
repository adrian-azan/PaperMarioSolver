#include "libraries.h"

struct Tile
{
	Tile* in;
	Tile* out;
	Tile* cw; //clockwise
	bool full;
	int id;
	
	Tile()
	{
		in = nullptr;
		out = nullptr;
		cw = nullptr;
		full = false;
	}
};


class Arena
{
	public:
		
		Arena();
		~Arena();
		
		void rotate(int ring,int amount);
		void slide(int col, int amount);
		
		void setRing(int ring, bool enemies[]);
		void setCol(int col, bool enemies[]);
		void print();
		void printRings();
		void printCol();
		
		Tile* getRing(int ring) {return rings[ring];}
		
	private:
		Tile* rings[4];
		
		
	
};
