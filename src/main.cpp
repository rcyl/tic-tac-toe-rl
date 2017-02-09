/*
 * main.cpp
 *
 *  Created on: 23 Jan, 2017
 *      Author: rcyl
 */

#include <iostream>
#include "Board.h"
#include "Player.h"
#include <vector>
#include "Constants.h"

using namespace std;

int main(int argc, char * argv[]){

	if (argc < 2) {
		cout << "please enter number of training games" << endl;
		return 0;
	}
	long num_games = atol(argv[1]);

	vector<Board> history;
	double hypO[NUMFEAT] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
	double hypX[NUMFEAT] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
	Player playerO(hypO, O);
	Player playerX(hypX, X);
	playerX.setConstant(0.4);
	int winner[SYMNUM] = {};

	/*training phase */

	for(long i = 0; i < num_games; i++ ) {
		Board b;
		history.clear();
		//playerO.printHypothesis();cl

		while(!b.isDone()){
			Board boardO = playerO.chooseMove(b);
			history.push_back(boardO);
#ifdef DEBUG
			boardO.print();
#endif
			if (boardO.isDone()) {
				b = boardO;
				break;
			}
			Board boardX = playerX.chooseRandom(boardO);
			//Board boardX = playerX.chooseMove(boardO);
			history.push_back(boardX);
#ifdef DEBUG
			boardX.print();
#endif
			b = boardX;
		}

		sym win = b.getWinner();
#ifdef DEBUG
		cout << "winner is " << win << endl;
#endif
		winner[win]++;

		playerO.updateWeights(history);
		playerX.updateWeights(history);

	}

	cout << "O won " << winner[O] << " times" << endl;
	cout << "X won " << winner[X] << " times" << endl;
	cout << "Drew " << winner[E] << " times" << endl;

	/* playing phase */

//	Board b;
//	int i, j;
//
//	playerO.printHypothesis();
//
//	while(!b.isDone()){
//		cout << "my turn" << endl;
//		b = playerO.chooseMove(b);
//		b.print();
//		if (b.isDone())
//			break;
//		cout << "enter i" << endl;
//		cin >> i;
//		cout << "enter j" << endl;
//		cin >> j;
//		b.set(X, i, j);
//		b.print();
//		if (b.isDone())
//			break;
//	}
//	if (b.getWinner() == O)
//		cout << "I win" << endl;
//	else if (b.getWinner() == X)
//		cout << "You win" << endl;
//	else
//		cout << "draw" << endl;

	return 0;
}
