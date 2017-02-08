/*
 * main.cpp
 *
 *  Created on: 23 Jan, 2017
 *      Author: rcyl
 */

#include <iostream>
#include "Board.h"
#include <vector>
#include <array>
#include <tuple>
#include "Constants.h"

using namespace std;

typedef tuple<int *, double> train;

int main(){

	Board b;

	b.print();
	b.set(X, 0, 0);
	b.set(X, 1, 1);
	b.set(O, 0, 2);
	b.print();
	vector<Board> v;
	b.getSuccessor(O, v);

	for(unsigned int i = 0; i < v.size(); i++){
		v[i].print();
	}
//	int features[NUMFEAT] = {};
//	b.getFeatures(features);
//
//	for(int i = 0; i < NUMFEAT; i++)
//		cout << "x" << i << ": " << features[i] << endl;
//	vector<Board> h;
//
//	cout << "setting board" << endl;
//	b.setBoard(v[2]);
//	h.push_back(v[2]);
//	b.print();
//
//	b.setBoard(v[3]);
//	h.push_back(v[3]);
//	b.print();
//
//	b.setBoard(v[4]);
//	h.push_back(v[4]);
//	b.print();
//
//	cout << "printing history" << endl;
//
//	for(unsigned int i = 0; i < h.size(); i++){
//		h[i].print();
//	}

	int features[NUMFEAT] = {1,2,3,4,5,6};
	int dest[NUMFEAT];

	copy(begin(features), end(features), begin(dest));

	train ex(dest, 99.9);

	int * test = get<0>(ex) ;

	for(int i = 0; i < NUMFEAT; i++)
		cout << test[i] << endl;

	features[0] = 412412;
	features[1] = 512512;

	for(int i = 0; i < NUMFEAT; i++)
		cout << test[i] << endl;

}
