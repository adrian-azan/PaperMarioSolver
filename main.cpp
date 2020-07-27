#include "libraries.h"

#include "Tester.cpp"

/* TODO (#3#): Clean Code */
/* TODO (#3#): Comment Code */
/* TODO (#4#): Start Documentation */
/* TODO (#4#): Start user manual */
/* TODO (#1#): Add sliding functionality
 */

int main()
{
	Arena test;
	Tester tester;
	test.print();
	test.rotate(0,1);
	test.printCol();
	
	
	cout << "\n\n\n";
	tester.rotateTest();
	tester.slideTest();
	return 0;
}
