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
	int cpy[NUMFEAT] = {};

	double tr_values;
	for(unsigned int i = 0; i < history.size(); i++){
		tr_values = 0;
		history[i].getFeatures(features);
		copy(begin(features), end(features), begin(cpy));

//		cout << "in getTraining examples, printing features" << endl;
//		for(int k = 0; k < NUMFEAT; k++)
//			cout << features[k] << ",";
//		cout << endl;

		if (history[i].isDone()){
			tr_values = getValues(history[i], this->mode);
			this->updateTraining(cpy, tr_values, train);
			break;
		}

		else if (i + 2 >= history.size()){ //game played until end
			tr_values = getValues(history[history.size()-1], this->mode);
			this->updateTraining(cpy, tr_values, train);
		}
		else{
			tr_values = this->evalBoard(history[i+2]); // train value based on the move after current
			this->updateTraining(cpy, tr_values, train);
		}
	}

	cout << "in getTraining examples, iterating train before return" << endl;

	for(unsigned int i = 0; i < train.size(); i++){
		train_t temp = train[i];
		int * f = get<0>(temp);
		cout << "features" << endl;
		for(int k = 0; k < NUMFEAT; k++)
			cout << f[k] << ",";
		cout << endl;
		cout << "tr value: " << get<1>(temp) << endl;
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

	//cout << "in updateTraining, printing features" << endl;
//	for(int i = 0 ; i < NUMFEAT; i++) {
//		cpy[i] = features[i];
//		//cout << cpy[i] << ",";clea
//	}
	//cout << endl;

	train_t example(features, tr_values);
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

void Critic::printHypothesis(){

	for(int i = 0; i < NUMFEAT; i++)
		cout << this->hypothesis[i] << " ";
}
