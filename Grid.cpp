//
//  Grid.cpp
//  IbrahimO_Final
//
//  Created by Olayemi Ibrahim on 4/4/18.
//  Copyright © 2018 Olayemi Ibrahim. All rights reserved.
//

//include preprocessor directives
#include "Grid.h"
#include <iostream>
using namespace std;

Grid::Grid()
{
    //nested for loop to access all parts of the array
    for (int index = 0; index < 10; index ++)
    {
        for (int count = 0; count < 10; count++)
        {
            board[index][count] = "~~";
            mocBoard[index][count] = "~~";
        }
    }
}

//function to print board
void Grid::printBoard(const Grid& matrix, int boardChoice) const
{
    std::ios::sync_with_stdio(false);
    
    cout<< "    A   B   C   D   E   F   G   H   I   J"<< endl;
    cout <<"   +---------------------------------------+"<< endl;
    
    for (int index = 0; index < 10; index++)
    {
        cout << " " << " " << index << "|";
        
        //if boardchoice is 0 print the main board with ships
        if(boardChoice == 0)
            cout << matrix.getPos(index, 0);
        
        //anything else print the board with only hit ships
        else
            cout << matrix.getMocPos(index, 0);
        for (int count = 1; count < 10; count++)
        {
            cout << " " << " ";
            if(boardChoice == 0)
            { cout << matrix.getPos(index, count);
                boardChoice = 0;
            }
            else
                cout << matrix.getMocPos(index, count);
        }
        cout << " " << "|" << endl << "   " << "|" <<  "\t\t\t\t\t\t\t\t\t   " << "|" << endl;
    }
    cout <<"   +---------------------------------------+" << endl;
    cout << endl;
}

