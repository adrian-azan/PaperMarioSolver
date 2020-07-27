#include "libraries.h"
#include "arena.h"

Arena::Arena()
{
	
	/*
	Creates 4 circular linked lists
	*/
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
	
	
	Tile* column[4];
	Tile* columnAcross[4];
	for(int i = 0; i < 4;i++)
	{
		column[i] = rings[i];
		columnAcross[i] = rings[i];
		for (int k = 0; k < 6; k++)
		{
			columnAcross[i] = columnAcross[i]->cw;	
		}
	}	
		
		/*
	Creates outer and inner connection 
	between each tile foward rings
	Allows outer ring to wrap around
	*/	
	for (int col = 0; col < 6; col++)
	{		
		for (int i = 3; i > 0;i--)
		{
			column[i]->foward = column[i-1];
		}
		
		column[0]->foward = columnAcross[0];
		
		for (int i = 0; i < 3;i++)
		{
			columnAcross[i]->foward = columnAcross[i+1];
		}
		
		columnAcross[3]->foward = column[3];
		
		for (int i = 0; i < 4;i++)
		{
			column[i] = column[i]->cw;
			columnAcross[i] = columnAcross[i]->cw;
		}				
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

/*
Rings can rotate foward a clockwise fasion to move
'opponents' to next position foward the ring
*/
void Arena::rotate(int ring, int amount)
{		
	if (ring < 0 || ring >=4)
		return;

	Tile* currentTile = rings[ring];
	bool enemyPos[12];
	bool enemyNewPos[12];
	int newSpace;
	
	/*
	Finds current position of enemies on selected ring
	*/
	for (int i = 0; i < 12; i++)
	{
		enemyPos[i] = currentTile->full; 
		currentTile = currentTile->cw;
	}
	
	
	/*
	Finds new position of enemies. Will wrap
	enemy around board
	*/
	for (int i = 0; i < 12; i++)
	{
		newSpace = (i+amount)%12;		
		enemyNewPos[newSpace] = enemyPos[i];
	}
	
	
	currentTile = rings[ring];
	for (int i = 0; i < 12; i ++)
	{
		currentTile->full = enemyNewPos[i];
		currentTile = currentTile->cw;
	}
}

/*
Slides a column foward 
*/
void Arena::slide(int col, int amount)
{
	if (col < 0 || col >= 6)
		return;
		
	bool enemies[8];
	bool enemyNewPos[8];
	int newSpace;
	Tile* temp;
			
	/*
	Gets to selected column on outer ring
	*/
	Tile* currentCol = rings[3];
	for (int i = 0; i < col; i++)
		currentCol = currentCol->cw;
			
	
	/*
	Moves foward through column, finding enemy spots
	*/
	temp = currentCol;
	for (int i = 0; i < 8; i++)
	{
		enemies[i] = temp->full;
		temp = temp->foward;
	}
	
	
	for (int i = 0; i < 8; i++)
	{		
		newSpace = (i+amount)%8;		
		enemyNewPos[newSpace] = enemies[i];
	}	
	
	
	for (int i = 0; i < 8; i++)
	{
		currentCol->full = enemyNewPos[i];
		currentCol = currentCol->foward;		
	}
	
}

void Arena::setRing(int ring,bool enemies[])
{
	if (ring < 0 || ring >= 4)
		return;
		
	Tile* tile = rings[ring];
	for (int i = 0; i < 12; i++)
	{
		tile->full = enemies[i];
		tile = tile->cw;
	}
}

void Arena::setCol(int col, bool enemies[])
{
	if (col < 0 || col >= 6)
		return;
		
	Tile* tile = rings[3];
	for (int i = 0; i < col;i++)
		tile = tile->cw;
	
	for (int i = 0; i < 8; i++)
	{
		tile->full = enemies[i];
		tile = tile->foward;		
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
			cout << setw(2) << currentTile->id << "->" 
			<< setw(2) << currentTile->foward->id<<"  ";
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
		Tile* currentCol = rings[3];
		Tile* currentTile = currentCol;
		for (int col = 0; col < 6; col++)
		{						
			for (int tile = 0; tile < 8; tile++)
			{
				cout << currentTile->full << " ";
				currentTile = currentTile->foward;											
			}
			cout << endl;	
			currentCol = currentCol->cw;
			currentTile = currentCol;
		}
		

}


