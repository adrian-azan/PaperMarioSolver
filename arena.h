#include "libraries.h"

struct Tile
{
	Tile* in;
	Tile* cw; //clockwise
	bool full;
	int id;
	
	Tile()
	{
		in = nullptr;
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
		void slide();
		
		void setRing(int ring, bool enemies[]);
		void print();
		void printContent();
		void printContent(int ring);
		Tile* getRing(int ring) {return rings[ring];}
		
	private:
		Tile* rings[4];
		
		
	
};
