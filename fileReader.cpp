
#include "fileReader.h"


fileReader::fileReader()
{
	
}

bool fileReader::readArena(Arena &arena)
{
	fin.open("input.txt");
	
	if(!fin)
	{
		cout << "Could not open input.txt\n";
		return false;
	}
	
	bool enemies[4][12];
	for (int ring = 3; ring >= 0; ring--)
	{
		for (int col = 0; col < 12; col++)
		{
			fin >> enemies[ring][col];
			if (fin.eof())
			{
				cout << "Not enough values in file\n";
				fin.close();
				return false;
			}
		}
	}

	for (int ring = 0; ring < 4; ring++)
	{
		arena.setRing(ring, enemies[ring]);
	}
	
	fin.close();
	return true;
}

