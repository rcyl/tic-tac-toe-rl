/*
 * Player.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: admin
 */

#include "Player.h"
#include <ctime>
#include <cstdlib>
using namespace std;

Player::Player(double * hypothesis, sym mode = X ){

	this->mode = mode;
	this->updateConstant = 0.1;

	for(int i = 0; i < NUMFEAT + 1; i++)
		this->hypothesis[i] = hypothesis[i];
}

void Player::setConstant(double val){ this->updateConstant = val; }


void Player::setHypothesis(double * hypothesis){

	for(int i = 0; i < NUMFEAT + 1; i++)
		this->hypothesis[i] = hypothesis[i];
}

double * Player::getHypothesis() { return this->hypothesis; }

double Player::evalBoard(Board & b){

	double val = 0;
	int features[NUMFEAT] = {};

	b.getFeatures(features);

	for(int i = 0; i < NUMFEAT; i++)
		val += this->hypothesis[i + 1] * features[i];

	val += this->hypothesis[0];

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

	for(uint i = 1; i < v.size(); i++){
		double temp = this->evalBoard(v[i]);
		if (temp > bestValue){
			bestValue = temp;
			bestBoard = v[i];
		}
	}
	return bestBoard;
}


