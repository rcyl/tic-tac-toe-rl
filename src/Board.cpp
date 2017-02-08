#include "Board.h"
#include <iostream>

using namespace std;

//initial board
Board::Board(){

	for(int i = 0; i < ROW; i++)
		for(int j = 0; j < COL; j++)
			this->board[i][j] = E;

	for(int i = 0; i < ROW; i++) {
		for(int s = O; s <= X; s++){
			this->row[i][s] = 0;
			this->col[i][s] = 0;
		}
	}

	for(int s = O; s <= X; s++){
		this->diag[s] = 0;
		this->rdiag[s] = 0;
	}

	this->moves = 0;
}

void Board::set(sym s, int i, int j){

	this->board[i][j] = s;
	this->row[i][s]++;
	this->col[j][s]++;
	if (i == j)	this->diag[s]++;
	if (i + j == ROW -1)this->rdiag[s]++;

	this->moves++;

}
void Board::setBoard(Board b){	*this = b; }


void Board::print() const {

	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++) {
			switch(this->board[i][j]){
				case E: cout << ' '; break;
				case X: cout << 'X'; break;
				case O: cout << 'O'; break;
			}
			if (j != COL -1)
				cout << " |";
		}
		if (i == ROW -1)
			cout << endl << endl;
		else
			cout << endl << "-- -- --" << endl;
	}

	cout << "num of moves is: " << this->moves << endl << endl;
}

sym Board::getWinner(){

	for(int i = 0; i < ROW; i++) {
		for(int s = O; s <= X; s++){
			if (this->row[i][s] == ROW) return (sym)s;
			if (this->col[i][s] == COL) return (sym)s;
		}
	}
	for(int s = O; s <= X; s++){
		if (this->diag[s] == ROW) return (sym)s;
		if (this->rdiag[s] == COL) return (sym)s;
	}
	return E;
}

bool Board::isDone(){

	if (this->getWinner() != E)
		return true;
	if (this->moves == ROW * COL)
		return true;
	return false;
}

/* see http://www.christopia.net/blog/teaching-a-computer-to-play-tictactoe */
void Board::getFeatures(int * features){

	for(int i = 0; i < ROW; i++) {
		this->countFeatures(this->row[i], features);
		this->countFeatures(this->col[i], features);
	}
	this->countFeatures(this->diag, features);
	this->countFeatures(this->rdiag, features);
}

void Board::countFeatures(int * row, int * features){

	/* x0 = 1 (always)
	 * x1 = 2 Xs and empty
	 * x2 = 2 Os and empty
	 * X3 = 1X
	 * X4 = 1O
	 * x5 = 3Xs
	 * x6 = 3Os
	 */

	features[0] = 1;

	if (row[O] == ROW) { //3Os
		features[6]++;
	}
	else if (row[O] == ROW - 1 && row[X] == 0) { //2Os
		features[2]++;
	}
	else if (row[O] == ROW - 2 && row[X] == 0){ //1O
		features[4]++;
	}

	if (row[X] == ROW) { //3Xs
		features[5]++;
	}
	else if (row[X] == ROW - 1 && row[O] == 0) { //2Xs
		features[1]++;
	}
	else if (row[X] == ROW - 2 && row[O] == 0){ //1X
		features[3]++;
	}

}

void Board::getSuccessor(sym s,vector<Board> & v){

	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			if (board[i][j] == E){
				Board b(*this);
				b.set(s, i, j);
				v.push_back(b);
			}
		}
	}
}

