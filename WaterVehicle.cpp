//
//  WaterVehicle.cpp
//  IbrahimO_Final
//
//  Created by Olayemi Ibrahim on 3/9/18.
//  Copyright © 2018 Olayemi Ibrahim. All rights reserved.
//


#include "WaterVehicle.h"

//constructor to initialze private variables
WaterVehicle::WaterVehicle(const string& name, const int& row, const int& column,  const int& length, const char& dir)
{
    //arrays of ship names and lengths
    const string shipNames[5] = {"Carrier", "Battleship","Cruiser","Submarine","Destroyer"};
    const int shipLengths[5] = {5, 4, 3, 3, 2};

    //set length to appropriate ship
    for(int i = 0; i < 5; i++){
        if(name == shipNames[i]){
            this->length = shipLengths[i];
        }
    }
    
    //assign the data based on user input
    this->name = name;
    this->row = row;
    this->col = column;
    this->orientaion = dir;
    this->sunk = false;

}

//member function to incerement amount of times ship has been hit
void WaterVehicle::setSunk()
{
    hit++;
    //if ship has been hit completely 
    if(hit == length)
    sunk = true;
}
