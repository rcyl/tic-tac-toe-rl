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
	double hypothesis[NUMFEAT + 1]; //hypothesis has extra 1 param
	sym mode;
	double updateConstant;

public:
	Player(double * hypothesis, sym mode);
	void setConstant(double val);
	void setHypothesis(double * hypothesis);
	double * getHypothesis();
	double evalBoard(Board & b);
	Board chooseRandom(Board & b);
	Board chooseMove(Board & b);
	void updateWeights(std::vector<Board> & history, std::vector<train_t> & train);

};



#endif /* INCLUDE_PLAYER_H_ */
