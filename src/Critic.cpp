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

using namespace std;

Critic::Critic(sym mode){

	this->mode = mode;
	this->hypothesis[NUMFEAT] =  {};
}

vector<train_t> Critic::getTrainingExamples(vector<Board> & history){

	vector<train_t> train;
	int features[NUMFEAT] = {};

	double tr_values;
	for(unsigned int i = 0; i < history.size(); i++){
		tr_values = 0;
		history[i].getFeatures(features);

		if (history[i].isDone()){
			tr_values = getValues(history[i], this->mode);
			this->updateTraining(features, tr_values, train);
			break;
		}

		else if (i + 2 >= history.size()){ //game played until end
			tr_values = getValues(history[history.size()-1], this->mode);
			this->updateTraining(features, tr_values, train);
		}
		else{
			tr_values = this->evalBoard(history[i+2]); // train value based on the move after current
			this->updateTraining(features, tr_values, train);
		}
	}

	return train;
}

double Critic::evalBoard(Board & b){

	double val = 0;
	int features[NUMFEAT] = {};

	b.getFeatures(features);

	for(int i = 0; i < NUMFEAT; i++)
		val += this->hypothesis[i] * features[i];

	return val;
}

void Critic::updateTraining(int * features, double tr_values, vector<train_t> & train){

	int cpy[NUMFEAT];
	for(int i = 0 ; i < NUMFEAT; i++)
		cpy[i] = features[i];

	train_t example(cpy, tr_values);
	train.push_back(example);
}

double Critic::getValues(Board & b, sym mode){

	if (b.getWinner() == mode)
		return 100.0;
	if (b.getWinner() == !mode)
		return -100.0;
	return 0;
}


void Critic::setHypothesis(double * hypothesis){

	for(int i = 0; i < NUMFEAT; i++)
		this->hypothesis[i] = hypothesis[i];
}
