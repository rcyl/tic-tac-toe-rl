/*
 * main.cpp
 *
 *  Created on: 23 Jan, 2017
 *      Author: rcyl
 */

#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Critic.h"
#include <vector>
#include "Constants.h"

using namespace std;

int main(){

	const int NUM_GAMES = 100000;

	vector<Board> history;
	double hypO[NUMFEAT] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
	double hypX[NUMFEAT] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
	Player playerO(hypO, O);
	Player playerX(hypX, X);
	Critic criticO(O);
	Critic criticX(X);
	int winner[SYMNUM] = {};

	for(int i = 0; i < NUM_GAMES; i++ ) {
		Board b;
		history.clear();

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
		winner[(int)win]++;

		double * htemp = playerO.getHypothesis();
		criticO.setHypothesis(htemp);
		htemp = playerX.getHypothesis();
		criticX.setHypothesis(htemp);

		vector<train_t> example = criticO.getTrainingExamples(history);
		playerO.updateWeights(history, example);
		example = criticX.getTrainingExamples(history);
		playerX.updateWeights(history, example);

	}

	cout << "O won " << winner[O] << " times" << endl;
	cout << "X won " << winner[X] << " times" << endl;
	cout << "Drew " << winner[E] << " times" << endl;


}
