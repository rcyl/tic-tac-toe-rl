/*
 * main.cpp
 *
 *  Created on: 23 Jan, 2017
 *      Author: rcyl
 */

#include <iostream>
#include "Board.h"
#include <vector>
#include "Constants.h"

using namespace std;

int main(){

	Board b;

	b.print();
	b.set(X, 0, 0);
	b.set(X, 1, 1);
	b.set(O, 0, 2);
	b.print();
	vector<Board> v;
//	b.getSuccessor(O, v);
//
//	for(unsigned int i = 0; i < v.size(); i++){
//		v.at(i).print();
//	}
	int features[NUMFEAT] = {};
	b.getFeatures(features);

	for(int i = 0; i < NUMFEAT; i++)
		cout << "x" << i << ": " << features[i] << endl;

	//Board b2(b);

	//b2.print();
}
