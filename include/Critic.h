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
#include <tuple>

//tuple takes in array of features, and their training values
typedef std::tuple<int *, double> train_t;

class Critic{

private:
	sym mode;
	double hypothesis[NUMFEAT + 1];
	double getValues(Board & b, sym mode);
	double evalBoard(Board & b);

public:
	Critic(sym mode, double * hypothesis);
	std::vector<train_t> getTrainingExamples(std::vector<Board> & history);
};


#endif /* INCLUDE_CRITIC_H_ */
