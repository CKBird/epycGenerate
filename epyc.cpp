#include <iostream>
#include <string>
#include <vector>

#include "epyc.h"

using namespace std;

epyc::epyc(int numPlayers) {
	_numPlayers = numPlayers;
	_run = 0;
	for (int i = 0; i < numPlayers; ++i) {
		std::vector<int> v1;
		std::vector<int> v2;
		for (int j = 0; j < numPlayers; ++j) {
			if (j == 0)
				v1.push_back(i);
			else
				v1.push_back(-2);
			if (i == j)
				v2.push_back(-1);
			else
				v2.push_back(0);
		}
		playerOrder.push_back(v1);
		usedOrders.push_back(v2);
	}
}

epyc::~epyc() {

}

void epyc::printInfo() {
	for (int i = 0; i < playerOrder.size(); ++i) {
		for (int j = 0; j < playerOrder[i].size(); ++j) {
			cout << "Item: [" << i << "][" << j << "] - " << playerOrder[i][j] << endl;
		}
	}
}

void epyc::printTable() {
	for (int i = 0; i < playerOrder.size(); ++i) {
		for (int j = 0; j < playerOrder[i].size(); ++j) {
			cout << playerOrder[i][j] << " ";
		}
		cout << endl;
	}
}

void epyc::printUsedTable() {
	for (int i = 0; i < usedOrders.size(); ++i) {
		for (int j = 0; j < usedOrders[i].size(); ++j) {
			cout << usedOrders[i][j] << " ";
		}
		cout << endl;
	}
}

void epyc::insertElement(int chain, int round, int value) {
	playerOrder[chain][round] = value;
}

void epyc::createFirst() {
	int initial = 0;
	for (int i = 0; i < playerOrder[0].size(); ++i) {
		playerOrder[0][i] = initial;
		if (!updateUsedOrders(0, i)) {
			cout << "Error!!" << endl;
			return;
		}
		initial++;
	}
}

bool epyc::updateUsedOrders(int chain, int round) {
	if (round == 0) {
		return true;
	}
	int newV = playerOrder[chain][round];
	int oldV = playerOrder[chain][round - 1];
	if (usedOrders[newV][oldV] == 1)
		return false;
	usedOrders[newV][oldV] = 1;
	return true;
}

void epyc::removeUsedOrders(int chain, int round) {
	int newV = playerOrder[chain][round];
	int oldV = playerOrder[chain][round - 1];
	usedOrders[newV][oldV] = 0;
	return;
}

bool epyc::brute(int nChain, int nRound) {
	_run++;
	if (_run >= 1000)
		return true;
	int nC = nChain;
	int nR = nRound;

	if (nRound >= _numPlayers) {
		nC++;
		nR = 1;
	}

	if (nC >= _numPlayers) {
		return true; //We completed
	}
	

	for (int i = 0; i < _numPlayers; ++i) {
		bool used = false;
		for (int x = 0; x < nR; ++x) {
			if (playerOrder[nC][x] == i)
				used = true;
			else if (playerOrder[x][nR] == i)
				used = true;
		}
		if (used)
			continue;
		
		if (usedOrders[i][playerOrder[nC][nR-1]] == -1) {
			//Skip, shouldn't happen
			continue;
		}
		else if (usedOrders[i][playerOrder[nC][nR-1]] == 1) {
			//Already used
			continue;
		}
		else if (usedOrders[i][playerOrder[nC][nR-1]] == 0) {
			//Can work, insert and try next one
			int old = playerOrder[nC][nR];
			playerOrder[nC][nR] = i;
			if (!updateUsedOrders(nC, nR)) {
				playerOrder[nC][nR] = old;
				continue;
			}
			/*cout << "Intermediate." << endl;
			this->printTable();
			cout << endl;
			this->printUsedTable();
			cout << endl;*/
			if (!brute(nC, nR + 1)) {
				removeUsedOrders(nC, nR);
				playerOrder[nC][nR] = old;
				continue;
			}
		}
	}
	if (playerOrder[nC][nR] == -2)
		return false;
	return true;
}