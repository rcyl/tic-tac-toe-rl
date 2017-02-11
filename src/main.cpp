/*
 * main.cpp
 *
 *  Created on: 23 Jan, 2017
 *      Author: rcyl
 */

#include <iostream>
#include <vector>
#include <fstream>
#include "Board.h"
#include "Player.h"
#include "Constants.h"

using namespace std;

int main(int argc, char * argv[]){

	if (argc < 2) {
		cout << "please enter number of training games" << endl;
		return 0;
	}
	long num_games = atol(argv[1]);

	vector<Board> history;
	//double hyp[NUMFEAT] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
	double hyp[NUMFEAT] = {};

	srand(time(NULL));
	for(int i  = 0; i < NUMFEAT; i++){
		hyp[i] = (rand() % 100) + 1;
	}
	cout << "random starting hypothesis" << endl;
	for(double d : hyp){
		cout << d << ",";
	}
	cout << endl;

	Player playerO(hyp, O);
	Player playerX(hyp, X);
	playerX.setConstant(0.4);
	int winner[SYMNUM] = {};

	/*training phase */

	for(long i = 0; i < num_games; i++ ) {
		Board b;
		history.clear();
		//playerO.printHypothesis();

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

	playerO.getHypothesis(hyp);

	for(double d : hyp)
		cout << d << ",";
	cout << endl;

	ofstream f("hypothesis.txt");
	if (f.is_open()){
		for(double d : hyp)
			f << d << " ";
		f.close();
	}

}
