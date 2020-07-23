#include "libraries.h"
#include "arena.h"

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
			if (nextTile)
				nextTile = nextTile->cw;
		}
		
	}
}


void Arena::rotate(int ring, int amount)
{		
	Tile* currentTile = rings[ring];
	bool enemyPos[12];
	bool enemyNewPos[12];
	for (int i = 0; i < 12; i++)
	{
		enemyPos[i] = currentTile->full; 
		currentTile = currentTile->cw;
	}
	
	int space;
	for (int i = 0; i < 12; i++)
	{
		if (i - amount < 0)
			space = 12-(amount-i);
		else
			space = i - amount;
		enemyNewPos[i] = enemyPos[space%12];
	}
	
	currentTile = rings[ring];
	for (int i = 0; i < 12; i ++)
	{
		currentTile->full = enemyNewPos[i];
		currentTile = currentTile->cw;
	}
}

void Arena::slide()
{
	
}

void Arena::setRing(int ring,bool enemies[])
{
	Tile* tile = rings[ring];
	for (int i = 0; i < 12; i++)
	{
		tile->full = enemies[i];
		tile = tile->cw;
	}
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

void Arena::printContent()
{
	for (int ring = 0; ring < 4; ring++)
	{
		printContent(ring);
	}
}

void Arena::printContent(int ring)
{
	
		
		Tile* currentTile = rings[ring];
		cout << ring << ": ";
		for (int tile = 0; tile < 12; tile++)
		{
			cout << currentTile->full << " ";
			currentTile = currentTile->cw;
		}
		cout << endl;
	
	
}


