#ifndef ARENA_H
#define ARENA_H

#include "libraries.h"


struct Tile
{
	Tile* foward;
	Tile* cw; //clockwise
	bool full;
	int id;
	
	Tile()
	{
		foward = nullptr;
		cw = nullptr;
		full = false;
	}
};


class Arena
{
	public:
			
		Arena();
		~Arena();
		
		void solveArena(ofstream &);
		bool solveArenaHelper(string moves, int moveCount,ofstream &);
		bool solveArenaHelperRotate(string moves, int moveCount,ofstream &fout);
		
		void rotate(int ring,int amount);
		void slide(int col, int amount);
		
		bool isColEmpty(int col);
		bool isRingEmpty(int ring);
		bool isSolved();
		bool checkLine(int col);
		bool checkSquare(int col);
		
		void setRing(int ring, bool enemies[]);
		void setCol(int col, bool enemies[]);
		
		void print();
		void printRings();
		void printCol();
		
		Tile* getRing(int ring) {return rings[ring];}
		
	private:
		/*
		Headptr for each linked list
		rings[0] inner most ring
		rings[3] outer most ring
		*/
		
		Tile* rings[4];
		
		
	
};

#endif
