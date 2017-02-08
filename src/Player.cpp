/*
 * Player.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: admin
 */

#include "Player.h"
#include "Constants.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

Player::Player(double * hypothesis, sym mode = X ){

	this->mode = mode;
	this->updateConstant = 0.1;

	for(int i = 0; i < NUMFEAT; i++)
		this->hypothesis[i] = hypothesis[i];
}

void Player::setConstant(double val){ this->updateConstant = val; }


void Player::setHypothesis(double * hypothesis){

	for(int i = 0; i < NUMFEAT; i++)
		this->hypothesis[i] = hypothesis[i];
}

double * Player::getHypothesis() { return this->hypothesis; }

double Player::evalBoard(Board & b){

	double val = 0;
	int features[NUMFEAT] = {};

	b.getFeatures(features);

	for(int i = 0; i < NUMFEAT; i++)
		val += this->hypothesis[i] * features[i];

	return val;
}

Board Player::chooseRandom(Board & b){

	std::vector<Board> v;
	b.getSuccessor(this->mode, v);

	srand(time(NULL));
	return v[rand() % v.size()];

}

Board Player::chooseMove(Board & b){

	std::vector<Board> v;
	b.getSuccessor(this->mode, v);

	Board bestBoard = v[0];
	double bestValue = this->evalBoard(bestBoard);

	for(unsigned int i = 1; i < v.size(); i++){
		double temp = this->evalBoard(v[i]);
		if (temp > bestValue){
			bestValue = temp;
			bestBoard = v[i];
		}
	}
	return bestBoard;
}

void Player::updateWeights(vector<Board> & history, vector<train_t> & train){

	double vEst, vTrain, diff;
	int * features;

	for(unsigned int i = 0; i < history.size(); i++){

		features = get<0>(train[i]);

		vEst = this->evalBoard(history[i]);
		vTrain = get<1>(train[i]);
		diff = vTrain - vEst;

		for(int j = 0; j < NUMFEAT; j++){
			this->hypothesis[j] += this->updateConstant * diff * features[j];
		}
	}

}


