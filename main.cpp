#include "libraries.h"

#include "Tester.cpp"

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
	tester.rotateTest();
	cout << "Rotate Test Passed\n";
	tester.slideTest();
	cout << "Slide Test Passed\n";
	
	return 0;
}
