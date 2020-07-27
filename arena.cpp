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
			innerTile->out = outerTile;
			outerTile = outerTile->cw;
			innerTile = innerTile->cw;
		}
	}
	
	Tile* innerTile = rings[0];
	Tile* outerTile = rings[3];
	for (int tile = 0; tile < 12; tile++)
	{		
		Tile* innerAcross = innerTile;
		Tile* outerAcross = outerTile;
		for (int i = 0; i < 6; i++)
		{
			innerAcross = innerAcross->cw;
			outerAcross = outerAcross->cw;
		}
		
		innerTile->in = innerAcross;
		outerTile->out = outerAcross;
		innerTile = innerTile->cw;
		outerTile = outerTile->cw;
		
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

void Arena::slide(int col, int amount)
{
	if (col < 0 || col >= 12)
		return;
		
	Tile* currentTile = rings[3];
	for (int i = 0; i < col; i++)
		currentTile = currentTile->cw;
			
	
	bool enemies[8];
	bool enemyNewPos[8];
	Tile* temp = currentTile;
	for (int i = 0; i < 4; i++)
	{
		enemies[i] = temp->full;
		temp = temp->in;
	}
	
	
	for (int i = 4; i < 8; i++)
	{
		enemies[i] = temp->full;		
		temp = temp->out;
	}

	
	int space;
	for (int i = 0; i < 8; i++)
	{
		if (i + amount >= 8)
			space = (i+amount)%8;
		else
			space = i + amount;
		enemyNewPos[space] = enemies[i];
	}
	

	
	
	currentTile = rings[3];
	for (int i = 0; i < col; i++)
		currentTile = currentTile->cw;
	for (int i = 0; i < 8; i++)
	{
		currentTile->full = enemyNewPos[i];
		if (i < 4)
			currentTile = currentTile->in;
		else
			currentTile = currentTile->out;
	}
	
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

void Arena::setCol(int col, bool enemies[])
{
	Tile* tile = rings[3];
	for (int i = 0; i < col;i++)
		tile = tile->cw;
	
	for (int i = 0; i < 8; i++)
	{
		tile->full = enemies[i];
		if (i < 4)
			tile = tile->in;
		else
			tile = tile->out;
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
			cout << setw(2) << currentTile->id << " ";
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
			cout << setw(2) << currentTile->out->id << "<-" 
			<< setw(2) << currentTile->id << "->" 
			<< setw(2) << currentTile->in->id<<"  ";
			currentTile = currentTile->cw;
		}
		cout << endl;
	}
}


void Arena::printRings()
{
	for (int i = 3; i >= 0;i--)
	{
		Tile* tile = rings[i];
		cout << i << ": ";
		for (int col = 0; col < 12;col++)
		{
			cout << tile->full << " ";
			tile = tile->cw;
		}	
		cout << endl;
	}
}

void Arena::printCol()
{			
		for (int col = 0; col < 6; col++)
		{
			Tile* currentTile = rings[3];
			
			for (int i = 0; i < col;i++)
				currentTile = currentTile->cw;
			
			for (int tile = 0; tile < 8; tile++)
			{
					cout << currentTile->full << " ";
					if (tile < 4)
						currentTile = currentTile->in;
					else
						currentTile = currentTile->out;
			}
			cout << endl;	
		}
		

}


