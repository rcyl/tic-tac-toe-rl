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
	double hypothesis[NUMFEAT]; //hypothesis has extra 1 param
	sym mode;
	double updateConstant;
	double getValues(Board & b, sym mode);
	double getTrainingValues(std::vector<Board> & history);
	double evalBoard(Board & b);
	double evalBoard(Board & b, int * features);

public:
	Player(double * hypothesis, sym mode);
	void setConstant(double val);
	void setHypothesis(double * hypothesis);
	Board chooseRandom(Board & b);
	Board chooseMove(Board & b);
	void printHypothesis();
	void getHypothesis(double * hyp);
	void updateWeights(std::vector<Board> & history);

};



#endif /* INCLUDE_PLAYER_H_ */
