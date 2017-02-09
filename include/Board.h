/*
 * Board.h
 *
 *  Created on: 23 Jan, 2017
 *      Author: rcyl
 */

#ifndef INCLUDE_BOARD_H_
#define INCLUDE_BOARD_H_

#include "Constants.h"
#include <vector>
#define ROW 3
#define COL 3
//#define DEBUG

class Board{

private:
	sym board[ROW][COL];
	int row[ROW][SYMNUM-1]; //row 0, 1, 2, followed by num of symbols in row,col,diag
	int col[COL][SYMNUM-1]; // see above
	int diag[SYMNUM-1];
	int rdiag[SYMNUM-1];
	void countFeatures(int * row, int * features);
	int moves;

public:
	Board();
	void print() const;
	void set(sym s, int i, int j);
	sym getWinner();
	bool isDone();
	void getFeatures(int * features);
	void getSuccessor(sym s,std::vector<Board> & v);
	void setBoard(Board b);

};


#endif /* INCLUDE_BOARD_H_ */
