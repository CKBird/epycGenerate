#include <iostream>
#include <string>
#include <vector>

class epyc {
public:
	epyc(int numPlayers);
	~epyc();
	void printInfo();
	void printTable();
	void printUsedTable();
	void insertElement(int chain, int round, int value);
	void createFirst();
	bool updateUsedOrders(int chain, int round);
	void removeUsedOrders(int chain, int round);
	bool brute(int nChain, int nRound);


private:
	int _numPlayers;

	std::vector<std::vector<int>> playerOrder;
	std::vector<std::vector<int>> usedOrders;
	int _run;
};