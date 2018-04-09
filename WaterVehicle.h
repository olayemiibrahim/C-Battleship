//
//  WaterVehicle.hpp
//  IbrahimO_Final
//
//  Created by Olayemi Ibrahim on 3/9/18.
//  Copyright © 2018 Olayemi Ibrahim. All rights reserved.
//

#ifndef WaterVehicle_h
#define WaterVehicle_h

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

// Forward struct declaration
struct ships;

// WaterVehicle class declaration
class WaterVehicle
{
//private variable declaration
private:
    string name;
    int length;
    int row, col;
    char orientaion;
    int hit = 0;
    bool sunk;
    
//public member function declaration
public:
    //constructor declaration
    WaterVehicle(){}
    WaterVehicle(const string&, const int&, const int&, const int&, const char&);
    
    //mutators
    void setName(string _name){name = _name;}
    void setLength(int _length){length = _length;}
    void setRow(int _row){row =_row;}
    void setCol(int _col){col = _col;}
    void setOrientation(char _orien){orientaion = _orien;}
    void setSunk();
    
    //accessors
    string getName() const {return name;}
    int getLength() const {return length;}
    int getRow() const {return row;}
    int getCol() const {return col;}
    char getOrientation()const {return orientaion;}
    bool getSunk() const {return sunk;}
    
};

struct ships
{
    string username = " " ;
    vector<WaterVehicle>boats;
};

#endif /* WaterVehicle_hpp */
