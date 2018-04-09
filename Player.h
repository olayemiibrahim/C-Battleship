//
//  Player.hpp
//  IbrahimO_Final
//
//  Created by Olayemi Ibrahim on 3/9/18.
//  Copyright © 2018 Olayemi Ibrahim. All rights reserved.
//

#ifndef Player_h
#define Player_h

//include preprocessor directives
#include "WaterVehicle.h"
#include "Grid.h"
#include "Gameplay.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
using namespace std;

//base Player class declaration
class Player
{
protected:
    Grid matrix;
    bool overlap = false;
    bool fitOn = false;

public:
    //Gameplay object declaration for control of game
    Gameplay control;
    
    //virtual member function declarations
    Player(){}
    virtual void placeShips() = 0;
    virtual bool attackBoard(Grid&, Grid& ,ships&) = 0;
    
    void generatePos(WaterVehicle&);
    virtual void checkFit(WaterVehicle&) final;
    virtual void checkOverlap(WaterVehicle&) final;
    
    //member function to increment row or column
    virtual void dirDecide(int& row, int& col, char& dir) final { if(toupper(dir) == 'H') {col++;} else {row++;} }

};

//Derived class for Human user
class Human: public Player
{
private:
    //private variable declaration
    ships humanAccess;

public:
    //Human class constructor
    Human(){}
    
    //Human class accessors
    Grid getGrid() const {return matrix;}
    ships getShips() const {return humanAccess;}
    string getName() const {return humanAccess.username;}
    
    //Member function definitions
    void readFile(string);
    void nameChange(string&);
    void converter(string, string, int&, int&, char&);
    void findSpace();
    
    //Virtual function overiding
    void placeShips();
    bool attackBoard(Grid&, Grid&,ships&);

};

//Ssense class declaration
class Ssense
{
    //Public variable declaration
public:
    int shotsAttempted = 0;
    int missedShots = 0;
    int hitShots = 0;
    string focus = " ";
    int initialRow = 0;
    int initialCol = 0;
    int prevRow=0;
    int prevCol =0;
    char prevDir = ' ';
    bool successful = false;
    bool forwardMove = false;
    bool backWardMove = false;
    bool forwardSucc = false;
    bool backwardSucc = false;
    bool upMove = false;
    bool downMove = false;
    vector<int>noHitRow;
    vector<int>noHitCol;
    void reset(){
        shotsAttempted = 0;
        focus = " ";
        initialRow = 0;
        initialCol = 0;
        prevRow=0;
        prevCol =0;
        prevDir = ' ';
        successful = false;
        forwardMove = false;
        backWardMove = false;
        forwardSucc = false;
        backwardSucc = false;
        upMove = false;
        downMove = false;
    }
};

//Derived class for automated Computer
class Computer: public Player
{
private:
    //private member variable declaration
    //Grid matrix;
    ships computerAccess;
    vector<string>names;
    Ssense brain;
    
public:
    //Computer class constructor
    Computer();
    
    //Computer class accessors
    Grid getGrid() const {return matrix;}
    ships getShips() const {return computerAccess;}
    string getName() const {return computerAccess.username;}
    
    //Member function definitions
    void setShips();
    bool smartAttack(Grid&, Grid&,ships&);
    bool cheatAttack(Grid&, Grid&,ships&);

    //Virtual function overiding
    void placeShips();
    bool attackBoard(Grid&, Grid&,ships&);
};


#endif /* Player_hpp */
