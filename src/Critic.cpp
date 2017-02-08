/*
 * Critic.cpp
 *
 *  Created on: Feb 8, 2017
 *      Author: admin
 */

#include "Board.h"
#include "Critic.h"
#include "Constants.h"
#include <iostream>
#include <tuple>
#include <cstdlib>

using namespace std;

Critic::Critic(sym mode, double * hypothesis){

	this->mode = mode;
	for(int i = 0; i < NUMFEAT + 1; i++)
		this->hypothesis[i] = hypothesis[i];
}

vector<train_t> Critic::getTrainingExamples(vector<Board> & history){

	vector<train_t> train;
	int features[NUMFEAT];
	double tr_values;

	for(unsigned int i = 0; i < history.size(); i++){
		fill(features, features + NUMFEAT, 0);
		tr_values = 0;
		history[i].getFeatures(features);
		if (history[i].isDone()){
			tr_values = getValues(history[i], this->mode);
			break;
		}
		else if (i + 2 == history.size()){ //game played until end
			tr_values = getValues(history[history.size()-1], this->mode);
			break;
		} else{
			tr_values = this->evalBoard(history[i+2]);
		}
	}
	train_t example(features, tr_values);
	train.push_back(example);
	return train;
}

double Critic::evalBoard(Board & b){

	double val = 0;
	int features[NUMFEAT] = {};

	b.getFeatures(features);

	for(int i = 0; i < NUMFEAT; i++)
		val += this->hypothesis[i + 1] * features[i];

	val += this->hypothesis[0];

	return val;
}

double Critic::getValues(Board & b, sym mode){
	if (b.getWinner() == mode)
		return 100.0;
	if (b.getWinner() == !mode)
		return -100.0;
	return 0;

}
