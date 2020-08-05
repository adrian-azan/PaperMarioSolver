#include "libraries.h"
#include "arena.h"
#include "Tester.h"
#include "fileReader.h"

/* DONE (#3#): Clean Code */
/* DONE (#3#): Comment Code */
/* TODO (#4#): Start Documentation */
/* TODO (#4#): Start user manual */
/* DONE (#1#): Add sliding functionality
 */


int main()
{	
	Arena myArena;
	Tester tester;	
	fileReader fin;
	string input;	
	ofstream fout;
	
	fout.open("moves.txt");
	//tester.rotateTest();
	//cout << "Rotate Test Passed\n";
	//tester.slideTest();
	//cout << "Slide Test Passed\n";
	if(fin.readArena(myArena) == false)
	{
		exit(-1);
	}
	
	
	do
	{
		fin.readArena(myArena);
		cout << "n to quit\n";
		myArena.printRings();
		myArena.solveArena(fout);
		myArena.printRings();
		cout << "Please make file Changes (hit Enter)\n";
		getline(cin, input);
	} while (input != "n");
	
	
	fout.close();
	return 0;
}
