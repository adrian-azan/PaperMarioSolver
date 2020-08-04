#ifndef FILEREADER_H
#define FILEREADER_H

#include "arena.h"

class fileReader
{
	
	public:
		fileReader();
		
		bool readArena(Arena & arena);
		
	private:
		ifstream fin;
	
	
	
};

#endif
