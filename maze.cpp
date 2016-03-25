/*********************************************/
/* Ryan Bassit               02-Maze         */
/* CISC 3130                 April 30, 2015  */
/*********************************************/

#include <iostream>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

#include "maze.h"

class Maze;

void Maze::load(string filename){
    string line;
    int count =0, len = 0, starx, stary;

    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 100; j++){
            mazeArray[i][j] = false;
            wasHere[i][j] = false;
        }

    mazefile.open(filename.c_str());

    if(!mazefile){cout << "File not found!\n\n"; exit(1);}

    cout << "\nThis is how the MazeFile that you supplied looks...\n";

    getline (mazefile, line);
    len = line.length();

    while (mazefile){
        for (int i = 0; i < len; i++){
            if (line[i] == 'S'){
                ys = count;
                xs = i;
            }
            if (line[i] == 'F'){
                yf = count;
                xf = i;
            }
            if (line[i] == '*'){
                starx = i;
                stary = count;
                mazeArray[stary][starx] = true;
            }
        }

        cout << line << endl;
        count++;
        getline (mazefile, line);
    }

    Location start(xs, ys);
    Location finish(xf, yf);

    cout << "Start coordinate: " << start << endl;
    cout << "Finish coordinate: " << finish << endl;
    cout << "The actual maze size is: " <<  count-2 << " x " << len-2 << endl;

    col = len-2;
    row = count-2;

    mazeArray[ys][xs] = true;
    mazeArray[yf][xf] = true;
}

void Maze::print(){
    for(int i = 0; i <= row+1; i++){
        cout << endl;
        for(int j = 0; j <= col+1; j++){
            if(wasHere[i][j] == false)
                cout << "H";
            if(wasHere[i][j] == true)
                cout << "^";
        }
    }
    cout << endl;
}

void Maze::solveMaze(){
    cout << "\n\n---------- Now traversing paths to find the Finish----------\n";

    xCurr = xs;
    yCurr = ys;

    if (mazeArray[yCurr][xCurr-1]==false && mazeArray[yCurr+1][xCurr]==false && mazeArray[yCurr-1][xCurr]==false)
        moveRight();
    if (mazeArray[yCurr][xCurr+1]==false && mazeArray[yCurr+1][xCurr]==false && mazeArray[yCurr-1][xCurr]==false)
        moveLeft();
    if (mazeArray[yCurr+1][xCurr]==false && mazeArray[yCurr][xCurr+1]==false && mazeArray[yCurr][xCurr-1]==false)
        moveUp();
    if (mazeArray[yCurr-1][xCurr]==false && mazeArray[yCurr][xCurr+1]==false && mazeArray[yCurr][xCurr-1]==false)
        moveDown();
}

void Maze::moveRight(){
    mazeArray[yCurr][xCurr] = false;
    wasHere[yCurr][xCurr] = true;

    if(yCurr == yf && xCurr == xf){
        return;
    }
    //checking positions around yCurr and xCurr and then pushing them onto the stack
    while(mazeArray[yCurr][xCurr+1] == true){
        if(mazeArray[yCurr-1][xCurr] == true){
            yVal.push(yCurr-1);
            xVal.push(xCurr);
            cout << "Stacks pushed from right function\n";
        }
        if(mazeArray[yCurr+1][xCurr] == true){
            yVal.push(yCurr+1);
            xVal.push(xCurr);
            cout << "Stacks pushed from right function\n";
        }

        xCurr++;    //actually moving to the right
        wasHere[yCurr][xCurr] = true;
        mazeArray[yCurr][xCurr] = false;

        cout << "Moved right to location (" << yCurr << "," << xCurr << ")\n";

        print();

        if(yCurr == yf && xCurr == xf){
            cout << "(:(:(:(:(:(:(:-----MAZE SOLVED!!!-----:):):):):):):)\n\n";
            return;
        }
    }

    if(mazeArray[yCurr][xCurr-1] == false && mazeArray[yCurr+1][xCurr] == false && mazeArray[yCurr-1][xCurr] == false && mazeArray[yCurr][xCurr+1] == false){
        cout << "Dead end found moving right. Moving to (" << xVal.top() << "," << yVal.top() << ")\n";
        yCurr = yVal.top();
        xCurr = xVal.top();
        yVal.pop();
        xVal.pop();
    }
    if(mazeArray[yCurr][xCurr+1] == false && mazeArray[yCurr-1][xCurr] == false){
        moveDown();
    }
    if(mazeArray[yCurr][xCurr+1] == false && mazeArray[yCurr+1][xCurr] == false){
        moveUp();
    }
    if(mazeArray[yCurr-1][xCurr] == true && mazeArray[yCurr+1][xCurr] == true){
        yVal.push(yCurr-1);
        xVal.push(xCurr);
        cout << "Stacks pushed from right function\n";
        moveDown();
    }
}

void Maze::moveLeft(){
    mazeArray[yCurr][xCurr] = false;
    wasHere[yCurr][xCurr] = true;

    if(yCurr == yf && xCurr == xf){
        return;
    }

    while(mazeArray[yCurr][xCurr-1] == true){
        if(mazeArray[yCurr-1][xCurr] == true){
            yVal.push(yCurr-1);
            xVal.push(xCurr);
            cout << "Stack pushed from left function\n";
        }
        if(mazeArray[yCurr+1][xCurr] == true){
            yVal.push(yCurr+1);
            xVal.push(xCurr);
            cout << "Stack pushed from left function\n";
        }

        xCurr--;
        wasHere[yCurr][xCurr] = true;
        mazeArray[yCurr][xCurr] = false;

        cout << "Moved left to location (" << yCurr << "," << xCurr << ")\n";

        print();

        if(yCurr == yf && xCurr == xf){
            cout << "(:(:(:(:(:(:(:-----MAZE SOLVED!!!-----:):):):):):):)\n\n";
            return;
        }
    }

    if(mazeArray[yCurr][xCurr-1] == false && mazeArray[yCurr+1][xCurr] == false && mazeArray[yCurr-1][xCurr] == false && mazeArray[yCurr][xCurr+1] == false){
        cout << "Dead end reached moving left. Moving to (" << yVal.top()+1 << "," << xVal.top() << ")\n";
        yCurr = yVal.top()+1;
        xCurr = xVal.top();
        yVal.pop();
        xVal.pop();
    }
    if(mazeArray[yCurr][xCurr-1] == false && mazeArray[yCurr-1][xCurr] == false){
        moveDown();
    }
    if(mazeArray[yCurr][xCurr-1] == false && mazeArray[yCurr+1][xCurr] == false){
        moveUp();
    }
    if(mazeArray[yCurr-1][xCurr] == true && mazeArray[yCurr+1][xCurr] == true){
        yVal.push(yCurr-1);
        xVal.push(xCurr);
        cout << "Stacks pushed from left function\n";
        moveDown();
    }
}

void Maze::moveUp(){
    mazeArray[yCurr][xCurr] = false;
    wasHere[yCurr][xCurr] = true;

    if(yCurr == yf && xCurr == xf){
        return;
    }

    while(mazeArray[yCurr-1][xCurr] == true){
        if(mazeArray[yCurr][xCurr+1] == true){
            yVal.push(yCurr);
            xVal.push(xCurr+1);
            cout << "Stacks pushed from up function\n";
        }
        if(mazeArray[yCurr][xCurr-1] == true){
            yVal.push(yCurr);
            xVal.push(xCurr-1);
            cout << "Stacks pushed from up function\n";
        }

        yCurr--;
        wasHere[yCurr][xCurr] = true;
        mazeArray[yCurr][xCurr] = false;

        cout << "Moved up to location (" << yCurr+1 << "," << xCurr << ")\n";

        print();

        if(yCurr == yf && xCurr == xf){
            cout << "(:(:(:(:(:(:(:-----MAZE SOLVED!!!-----:):):):):):):)\n\n";
            return;
        }
    }

    if(mazeArray[yCurr-1][xCurr] == false && mazeArray[yCurr][xCurr+1] == false && mazeArray[yCurr][xCurr-1] == false && mazeArray[yCurr+1][xCurr] == false){
        cout << "Dead end reached moving up. Moving to (" << xVal.top() << "," << yVal.top() << ")\n";
        yCurr = yVal.top();
        xCurr = xVal.top();
        yVal.pop();
        xVal.pop();
    }
    if(mazeArray[yCurr-1][xCurr] == false && mazeArray[yCurr][xCurr+1] == false){
        moveLeft();
    }
    if(mazeArray[yCurr-1][xCurr] == false && mazeArray[yCurr][xCurr-1] == false){
        moveRight();
    }
    if(mazeArray[yCurr][xCurr-1] == true && mazeArray[yCurr][xCurr+1] == true){
        yVal.push(yCurr);
        xVal.push(xCurr-1);
        cout << "Stacks pushed from up function\n";
        moveRight();
    }
}

void Maze::moveDown(){
    mazeArray[yCurr][xCurr] = false;
    wasHere[yCurr][xCurr] = true;

    if(yCurr == yf && xCurr == xf){
        return;
    }

    while(mazeArray[yCurr+1][xCurr] == true){
        if(mazeArray[yCurr][xCurr+1] == true){
            yVal.push(yCurr);
            xVal.push(xCurr+1);
            cout << "Stacks pushed from down function\n";
        }
        if(mazeArray[yCurr][xCurr-1] == true){
            yVal.push(yCurr);
            xVal.push(xCurr-1);
            cout << "Stacks pushed from down function\n";
        }

        yCurr++;
        wasHere[yCurr][xCurr] = true;
        mazeArray[yCurr][xCurr] = false;

        cout << "\nMoved down to location (" << yCurr << "," << xCurr << ")\n";

        print();

        if(yCurr == yf && xCurr == xf){
            cout << "(:(:(:(:(:(:(:-----MAZE SOLVED!!!-----:):):):):):):)\n\n";
            return;
        }
    }

    if(mazeArray[yCurr+1][xCurr] == false && mazeArray[yCurr][xCurr+1] == false && mazeArray[yCurr][xCurr-1] == false && mazeArray[yCurr-1][xCurr] == false){
        cout << "Dead end reached moving down. Moving to (" << yVal.top() << "," << xVal.top() << ")\n";
        yCurr = yVal.top();
        xCurr = xVal.top();
        yVal.pop();
        xVal.pop();
    }
    if(mazeArray[yCurr+1][xCurr] == false && mazeArray[yCurr][xCurr+1] == false){
        moveLeft();
    }
    if(mazeArray[yCurr+1][xCurr] == false && mazeArray[yCurr][xCurr-1] == false){
        moveRight();
    }
    if(mazeArray[yCurr][xCurr-1] == true && mazeArray[yCurr][xCurr+1] == true){
        yVal.push(yCurr);
        xVal.push(xCurr-1);
        cout << "Stacks pushed from down function\n";
        moveRight();
    }
}
