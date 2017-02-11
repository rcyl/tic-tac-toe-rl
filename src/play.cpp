/*
 * play.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: admin
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include "Constants.h"
#include "Board.h"
#include "Player.h"

using namespace std;

int main(){

	string line;
	ifstream f("hypothesis.txt");
	double hyp[NUMFEAT];
	int index = 0;

	if (f.is_open()){
		while(getline(f, line)) {
			stringstream stream(line);
			double token;
			while(stream >> token){
				hyp[index++] = token;
			}
		}
		f.close();
	}
	Board b;
	Player playerO(hyp, O);
	playerO.printHypothesis();
	int i, j;

	while(!b.isDone()){
		cout << "my turn" << endl;
		b = playerO.chooseMove(b);
		b.print();
		if (b.isDone())
			break;
		cout << "enter i" << endl;
		cin >> i;
		cout << "enter j" << endl;
		cin >> j;
		b.set(X, i, j);
		b.print();
		if (b.isDone())
			break;
	}
	if (b.getWinner() == O)
		cout << "I win" << endl;
	else if (b.getWinner() == X)
		cout << "You win" << endl;
	else
		cout << "draw" << endl;

	return 0;
}

