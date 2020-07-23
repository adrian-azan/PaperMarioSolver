#include "libraries.h"

struct Tile
{
	Tile* in;
	Tile* cw; //clockwise
	bool full;
	int id;
	
//	tile()
//	{
//		in = nullptr;
//		cw = nullptr;
//		full = false;
//	}
};


class Arena
{
	public:
		
		Arena();
		~Arena();
		
		void rotate();
		void slide();
		
		void print();
		
	private:
		Tile* rings[4];
		
	
};


Arena::Arena()
{
	for (int ring = 0; ring < 4; ring++)
	{
		
		rings[ring] = new Tile;
		Tile* currentTile = rings[ring];
		for (int tile = 0; tile < 11; tile++)
		{
			currentTile->id = tile+1;
			currentTile->cw = new Tile;
			currentTile = currentTile->cw;
			
		}
		currentTile->id = 12;
		currentTile->cw = rings[ring];
	}
	
	for (int ring = 3; ring > 0; ring--)
	{
		
		Tile* outerTile = rings[ring];
		Tile* innerTile = rings[ring-1];
		for (int tile = 0; tile < 12; tile++)
		{
			outerTile->in = innerTile;
			outerTile = outerTile->cw;
			innerTile = innerTile->cw;
		}
	}
	
	Tile* currentTile = rings[0];
	for (int tile = 0; tile < 12; tile++)
	{
		
		Tile* across = currentTile;
		for (int i = 0; i < 6; i++)
		{
			across = across->cw;
		}
		currentTile->in = across;
		currentTile = currentTile->cw;
		
	}
	
}

Arena::~Arena()
{
	for (int ring = 0; ring < 4; ring++)
	{
		
		Tile* currentTile = rings[ring];
		Tile* nextTile = currentTile->cw;
		for (int tile = 0; tile < 12; tile++)
		{
			delete currentTile;
			currentTile = nextTile;
			nextTile = nextTile->cw;
		}
		delete currentTile;
	}
}


void Arena::rotate()
{
	
}

void Arena::slide()
{
	
}

void Arena::print()
{
	for (int ring = 0; ring < 4; ring++)
	{
		
		Tile* currentTile = rings[ring];
		cout << ring << ": ";
		for (int tile = 0; tile < 12; tile++)
		{
			cout << currentTile->id << " ";
			currentTile = currentTile->cw;
		}
		cout << endl;
	}
	
	cout << "\n\n";
	for (int ring = 0; ring < 4; ring++)
	{
		
		Tile* currentTile = rings[ring];
		cout << ring << ": ";
		for (int tile = 0; tile < 12; tile++)
		{
			cout << currentTile->id << "->" <<currentTile->in->id<<"\t";
			currentTile = currentTile->cw;
		}
		cout << endl;
	}
}
