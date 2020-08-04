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

void Arena::solveArena(ofstream &fout)
{
	if(solveArenaHelper("", 3,fout) == true)
		return;	
	Helper2("", 3, fout);
}

bool Arena::Helper2(string moves, int moveCount,ofstream &fout)
{
	
	if (isSolved() == true)
	{
		cout << "SOLUTION: " << moves << "\n";
		
		return true;
	}	
	
	if (moveCount <= 0)
	{		
		fout << moves << endl;
		return false;
	}
	
	string moveSlide;
	string move;	
	for (int ring = 0; ring < 4; ring++)
	{
		for (int amount = 1; amount < 12; amount++)
		{		
		
			if (isRingEmpty(ring) == false)
			{					
			rotate(ring, amount);
			move = "R"+to_string(ring) + ":" + to_string(amount) + " ";
			moves += move;
			moveCount-=1;
			if(Helper2(moves, moveCount,fout))
				return true;
			}
			
			for (int column = 0; column < 6; column++)
			{
				for (int amountCol = 1; amountCol < 8; amountCol++)
				{				
					if (moveCount >=1)
					{	
					
						if (isColEmpty(column) == false)
						{														
							slide(column, amountCol);
							moveSlide = "S"+to_string(column) + ":" + to_string(amountCol) + " ";
							moves += moveSlide;
							
							
							moveCount-=1;
							if(Helper2(moves, moveCount,fout))
								return true;
					
						
						
							moveCount += 1;
							slide(column, 8-amountCol);
							moves = moves.substr(0,moves.size()-moveSlide.size());
						}
					}
					
				}
		
				
			}
			if (isRingEmpty(ring) == false)
				{
				moveCount+=1;
				rotate(ring, 12-amount);
				moves = moves.substr(0,moves.size()-move.size());
				}
		}		
	}	
	return false;
}

bool Arena::solveArenaHelper(string moves, int moveCount,ofstream &fout)
{
	if (isSolved() == true)
	{
		cout << "SOLUTION: " << moves << "\n";
		
		return true;
	}	
	
	if (moveCount <= 0)
	{		
		//fout << moves << endl;
		return false;
	}
	
	string moveSlide;
	string move;
	for (int column = 0; column < 6; column++)
	{
		for (int amountCol = 1; amountCol < 8; amountCol++)
		{				
			if (isColEmpty(column) == false)
			{					
				slide(column, amountCol);
				moveSlide = "S"+to_string(column) + ":" + to_string(amountCol) + " ";
				moves += moveSlide;
				
				
				moveCount-=1;
				if(solveArenaHelper(moves, moveCount,fout))
					return true;
		
			//	printRings();
				
					
				for (int ring = 0; ring < 4; ring++)
				{
					for (int amount = 1; amount < 12; amount++)
					{
					
						if ( moveCount >=1)
						{
							rotate(ring, amount);
							move = "R"+to_string(ring) + ":" + to_string(amount) + " ";
							moves += move;
							if(solveArenaHelper(moves, moveCount-1,fout))
								return true;
						
							rotate(ring, 12-amount);
							moves = moves.substr(0,moves.size()-move.size());
						}
					}		
				}			
			
				moveCount += 1;
				slide(column, 8-amountCol);
				moves = moves.substr(0,moves.size()-moveSlide.size());
			}
			
		}
		
	}		
	
	

	
	return false;
	
}

/*
Rings can rotate foward a clockwise fasion to move
'opponents' to next position foward the ring
*/
void Arena::rotate(int ring, int amount)
{		
	if (ring < 0 || ring >=4 || isRingEmpty(ring))
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
	if (col < 0 || col >= 6 || isColEmpty(col))
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


/*
Checks if a column has no enemies
*/
bool Arena::isColEmpty(int col)
{
	Tile* currentTile = rings[3];
	
	for (int i = 0; i < col; i++)
	{
		currentTile = currentTile->cw;
	}
	
	for (int i = 0; i < 8; i++)
	{
		if (currentTile->full == true)
			return false;
		currentTile = currentTile->foward;
	}	
	return true;
}

/*
Checks that ring has no enemies
*/
bool Arena::isRingEmpty(int ring)
{
	Tile* currentTile = rings[ring];
	
	for (int i = 0; i < 12; i++)
	{
		if (currentTile->full == true)
			return false;
		currentTile = currentTile->cw;
	}	
	return true;	
}

bool Arena::isSolved()
{
	bool squareCheck[12];
	bool lineCheck[12];
	
	for (int i = 0; i < 12;i++)
	{
		lineCheck[i] = checkLine(i);
	}
	
	for (int i = 0; i < 12;i++)
	{
		squareCheck[i] = checkSquare(i);
		
		if (i != 11 && lineCheck[i] == false
					&& squareCheck[i] == true)
		{
			squareCheck[i+1] = true;
			i++;
		}
	}
	
	for (int i = 0; i < 12;i++)
	{
		
		if (squareCheck[i] == false && lineCheck[i] == false)
			return false;
	}
	return true;
	
}

/*
Checks if a line is complete
Line must either be completely full or completely empty
*/
bool Arena::checkLine(int col)
{
	Tile* column = rings[3];
	if (col > 5)
		column = rings[0];
	
	for (int i = 0; i < col; i++)
	{
		column = column->cw;
	}
	
	bool goal = column->full;
	
	for (int i = 0; i < 4; i++)
	{
		if (column->full != goal)
			return false;
		column = column->foward;
	}
	
	return true;
	
}

/*
Checks if a particular 2x2 square of tiles is 
a complete block of enemies
*/
bool Arena::checkSquare(int col)
{
	Tile* column = rings[1];	
	if (col > 5)
		column = rings[0];
	
	for (int i = 0; i < col; i++)
	{
		column = column->cw;
	}
	
	//Special Case
	bool goal = true;
	if (col == 5 || col == 11)
	{
		Tile* split = column->foward->cw;
		if (column->full != goal ||
			column->foward->full != goal ||
			split->full != goal ||
			split->foward->full != goal)
			return false;
		return true;
	}
	
	for (int i = 0; i < 2; i++)
	{
		if (column->full != goal || 
			column->foward->full != goal)
			return false;
		column = column->cw;
	}
	
	return true;
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

