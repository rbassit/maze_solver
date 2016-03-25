/*********************************************/
/* Ryan Bassit               02-Maze         */
/* CISC 3130                 April 30, 2015  */
/*********************************************/

#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>

#include "maze.h"
#include "maze.cpp"

using namespace std;

int main(){
    string filename;
    cout << "Enter a valid MazeFile name: ";
    cin >> filename;

    Maze maze;

    maze.load(filename);
    maze.solveMaze();

	return 0;
}
