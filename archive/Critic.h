/*
 * Critic.h
 *
 *  Created on: Feb 8, 2017
 *      Author: admin
 */

#ifndef INCLUDE_CRITIC_H_
#define INCLUDE_CRITIC_H_

#include "Constants.h"
#include "Board.h"
#include <vector>

class Critic{

private:
	sym mode;
	double hypothesis[NUMFEAT];
	double getValues(Board & b, sym mode);
	double evalBoard(Board & b);
	void updateTraining(int * features, double tr_values, std::vector<train_t> & train);

public:
	Critic(sym mode);
	std::vector<train_t> getTrainingExamples(std::vector<Board> & history);
	void setHypothesis(double * hypothesis);
	void printHypothesis();
};


#endif /* INCLUDE_CRITIC_H_ */
