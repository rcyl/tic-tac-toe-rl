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

double Player::evalBoard(Board & b){

	double val = 0;
	int features[NUMFEAT] = {};

	b.getFeatures(features);

	for(int i = 0; i < NUMFEAT; i++)
		val += this->hypothesis[i] * features[i];

	return val;
}

double Player::evalBoard(Board & b, int * features){

	double val = 0;

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

	Board bestBoard = v.front();
	double bestValue = this->evalBoard(bestBoard);

	double temp = 0;
	for(Board b : v){
		temp = this->evalBoard(b);
		if (temp > bestValue){
			bestValue = temp;
			bestBoard = b;
		}
	}
	return bestBoard;
}

void Player::updateWeights(vector<Board> & history){

	double vEst, vTrain, diff;
	int features[NUMFEAT] = {};

	for(unsigned int i = 0; i < history.size(); i++){
		Board cur = history[i];
		fill(features, features + NUMFEAT, 0);
		cur.getFeatures(features);
#ifdef DEBUG
		cur.print();
		cout << "printing features" << endl;
		for(int i = 0; i < NUMFEAT; i++)
			cout << "X" << i << ": " << features[i] << endl;
		cout << endl;
#endif

		if (cur.isDone())
			vTrain = this->getValues(cur, this->mode);
		else if (i + 2 >= history.size())
			vTrain = this->getValues(history.back(), this->mode);
		else
			vTrain = this->evalBoard(history[i + 2], features);

		vEst = this->evalBoard(cur, features);
		diff = vTrain - vEst;

		for(int j = 0; j < NUMFEAT; j++){
			this->hypothesis[j] += this->updateConstant * diff * features[j];
		}
	}
}

void Player::getHypothesis(double * hyp){

	for(int i = 0; i < NUMFEAT; i++)
		hyp[i] = this->hypothesis[i];
}

void Player::printHypothesis(){

	cout << "printing hypothesis" << endl;
	for(int i = 0; i < NUMFEAT; i++)
		cout << this->hypothesis[i] << " ";
	cout << endl;
}

double Player::getValues(Board & b, sym mode){

	if (b.getWinner() == mode)
		return 100.0;
	if (b.getWinner() == !mode)
		return -100.0;
	return 0.0;
}


