/*
 * Player.h
 *
 *  Created on: Feb 7, 2017
 *      Author: admin
 */

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

#include "Constants.h"
#include "Board.h"
#include <vector>

class Player{

private:
	Board board;
	double hypothesis[NUMFEAT + 1]; //hypothesis has extra 1 param
	sym mode;
	std::vector<Board> history;
	double updateConstant;

public:
	Player(Board b, double * hypothesis, sym mode);
	void setConstant(double val);
	void setBoard(Board b);
	Board getBoard();
	void setHypothesis(double * hypothesis);
	double * getHypothesis();
	double evalBoard(Board & b);
	void chooseRandom();
	void chooseMove();

};



#endif /* INCLUDE_PLAYER_H_ */
