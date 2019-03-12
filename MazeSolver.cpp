/*
Cai Hui Yang
Project 4
CSCI 235

*/

#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <stack>
#include <iostream>
#include "MazeSolver.h"
using namespace std;


MazeSolver::MazeSolver(std::string input_file) {

	ifstream myInput;
	myInput.open(input_file);


	if (myInput.fail()) {
		cerr << "Fail to open file"<< input_file;
		exit(1);
	}

	myInput >> maze_rows_;
	myInput >> maze_columns_;

	initializeMaze(maze_rows_, maze_columns_);

  fillMaze(myInput);
	initializeSolution();
	copyMazetoSolution();




	myInput.close();

}


MazeSolver::~MazeSolver() {

	for (int i = 0; i < maze_rows_; i++) {
		delete[] maze_[i];

		delete[] solution_[i];

	}

delete [] maze_;
delete [] solution_;
}


bool MazeSolver::mazeIsReady() {

	return maze_ready;

}


bool MazeSolver::solveMaze() {

	Position myPosition;

	myPosition.row = 0;
	myPosition.column = 0;

	backtrack_stack_.push(myPosition);


	while (backtrack_stack_.size()!= 0) {

		if ( solution_[myPosition.row][myPosition.column] == '$') {
			cout << "Found the exit!!!" << endl;
			return true;
		}



		else if (extendPath(myPosition)== true) {

			solution_[myPosition.row][myPosition.column] = '>';

			myPosition = backtrack_stack_.top();

		}

		else if (extendPath(myPosition) == false) {

			maze_[myPosition.row][myPosition.column] = 'X';
			solution_[myPosition.row][myPosition.column] = '@';

			backtrack_stack_.pop();

			if (backtrack_stack_.size() != 0) {

				myPosition = backtrack_stack_.top();

			}
			else if (backtrack_stack_.size() == 0) {
				cout << "This maze has no solution."<< endl;
				return false;
			}

		}

	} // while loop



	return false;

}


void MazeSolver::printSolution() {
	cout << "The solution to this maze is: " << endl;

	for (int r = 0; r < maze_rows_; r++) {

		for (int c = 0; c < maze_columns_; c++) {

			cout << solution_[r][c] << " ";

		}
		cout << endl;
	}
	cout <<endl;
}




void MazeSolver::initializeMaze(int rows, int columns) {



	maze_ = new char* [rows];

	for (int i = 0; i < rows; i++) {

		maze_[i] = new char[columns];

	}



} // end initializeMaze



void MazeSolver::fillMaze(std::ifstream& input_stream) {

	string strVersion;
	getline(input_stream, strVersion);

	int counter = 0;

	for (int r = 0; r < maze_rows_; r++) {

		for (int c = 0; c < maze_columns_;) {

			if (strVersion[counter] != ' ') {
				maze_[r][c] = strVersion[counter];
				c++;
			}

			counter++;


		} // column
	}// row

	maze_ready = true;
} // end fillMaze


void MazeSolver::initializeSolution() {


	solution_ = new char*[maze_rows_];

	for (int i = 0; i < maze_rows_; i++) {

		solution_[i] = new char[maze_columns_];

	}

	// copyMazetoSolution();

} // end func

void MazeSolver::copyMazetoSolution() {

	for (int r = 0; r < maze_rows_; r++) {

		for (int c = 0; c < maze_columns_; c++) {

			solution_[r][c] = maze_[r][c];

		}
	}

} // end func

bool MazeSolver::extendPath(Position current_position) {
	bool extend = false;

	if ( isExtensible(current_position, SOUTH) ){

		backtrack_stack_.push( getNewPosition(current_position, SOUTH) );

		extend = true;
	}

	if (isExtensible(current_position, EAST)) {

		backtrack_stack_.push(getNewPosition(current_position, EAST));

		extend = true;
	}

	return extend;
} // end func

Position MazeSolver::getNewPosition(Position old_position, direction dir) {

	Position newPosition;

	if (dir == SOUTH) {

			newPosition.row = old_position.row + 1;
			newPosition.column = old_position.column;

	}

 if (dir == EAST) {

			newPosition.row = old_position.row;
			newPosition.column = old_position.column + 1;

	}

	return newPosition;
} // end func

bool MazeSolver::isExtensible(Position current_position, direction dir) {

bool canExtend = false;


	if (dir == SOUTH) {
		if ((current_position.row + 1) > (maze_rows_ - 1)) {return false;}
		if ((maze_[current_position.row + 1][current_position.column] == '_') || (maze_[current_position.row + 1][current_position.column]  == '$')){

			canExtend = true;
		}
	} // if south


	else if (dir == EAST) {
		if ((current_position.column + 1) > (maze_columns_ - 1)) {return false;}
		if ((maze_[current_position.row][current_position.column + 1]  == '_') || (maze_[current_position.row][current_position.column + 1]  == '$')){

			canExtend = true;
		}
	} // if east

return canExtend;
} // end func
