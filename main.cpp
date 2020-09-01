#include <iostream>
#include "epyc.h"

using namespace std;

int main() {
	int nP = 10;
	epyc *newGame = new epyc(nP);
	//newGame->insertElement(0, 0, 3);
	newGame->createFirst();

	newGame->printTable();
	cout << endl;
	newGame->printUsedTable();
	cout << endl;

	newGame->brute(1,1);

	newGame->printTable();
	cout << endl;
	newGame->printUsedTable();
	cout << endl;



	return 0;
}