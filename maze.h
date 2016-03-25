/*********************************************/
/* Ryan Bassit               02-Maze         */
/* CISC 3130                 April 30, 2015  */
/*********************************************/

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

struct Location{
	friend ostream &operator <<(ostream &os, const Location &location) {
		os << "(" << location.x << ", " << location.y << ")";
		return os;
	}

	bool operator ==(const Location &rhs) const {return x == rhs.x && y == rhs.y;}
	bool operator !=(const Location &rhs) const {return !(*this == rhs);}
	operator bool() const {return x >= 0;}
	//Location();
	Location(int x=-1, int y=-1) : x(x), y(y) {}
	int x, y;
};


class Maze {
private:
	//bool contains(const Location &location) const;
	//bool isPath(const Location &location) const;

    fstream mazefile;
    bool mazeArray[100][100];
    bool wasHere[100][100];
    int row, col, xs, xf, ys, yf, yCurr, xCurr;
	Location start, finish;
    stack<int> xVal;
    stack<int> yVal;

public:
    bool solve();
    void load(string filename);
    void solveMaze();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void print();

};

#endif
