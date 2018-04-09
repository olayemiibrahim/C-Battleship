//
//  Grid.hpp
//  IbrahimO_Final
//
//  Created by Olayemi Ibrahim on 4/4/18.
//  Copyright © 2018 Olayemi Ibrahim. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>
#include <string>
using namespace std;

//Grid class declaration
class Grid
{
//private variable declaration
private:
    string board[10][10];
    string mocBoard[10][10];
    int hits = 0;
    
//public member function declaration
public:
    
    //constructor
    Grid();
    
    //accessors
    string getPos(int i, int c) const {return board[i][c];}
    string getMocPos(int i, int c) const {return mocBoard[i][c];}
    int gethits() const {return hits;}
    
    //mutators
    void setPos(int i, int c, string Y){board[i][c] = Y;}
    void setMocPos(int i, int c, string moc) {mocBoard[i][c] = moc;}
    void setBoard(int row, int col, char name){board[row][col] = name;}
    
    //functions
    void mocEnd() const;
    void incHit(){hits++;}    
    void printBoard(const Grid&, int) const;
    
};

#endif /* Grid_hpp */
