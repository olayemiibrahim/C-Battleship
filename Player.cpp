//
//  Player.cpp
//  IbrahimO_Final
//
//  Created by Olayemi Ibrahim on 3/9/18.
//  Copyright © 2018 Olayemi Ibrahim. All rights reserved.
//

//Include preprocessor directives
#include "Player.h"
#include "WaterVehicle.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;



void Player::generatePos(WaterVehicle& ship)
{
    //generate random positions
    ship.setRow(rand() % 10);
    ship.setCol(rand() % 10);
}


void Player::checkFit(WaterVehicle& ship)
{
    // Variable decleration
    int row = ship.getRow();
    int col = ship.getCol();
    int length = ship.getLength();
    
    // If value does not fit on board
    while(!(col+length <= 9)||!(row+length <= 9))
    {
        generatePos(ship);
        row = ship.getRow();
        col = ship.getCol();
    }
}

void Player::checkOverlap(WaterVehicle& ship)
{
    // Variable decleration
    int row = ship.getRow();
    int col = ship.getCol();
    int length = ship.getLength();
    char dir = ship.getOrientation();
    
    // Loop to "mok" place ships and test if it overlaps at any position
    for (int count = 0; count <= length-1; count++)
    {
        // If space is occupied
        while(!(matrix.getPos(row, col) == "~~"))
        {
            overlap = true;
            generatePos(ship);
            checkFit(ship);
            row = ship.getRow();
            col = ship.getCol();
            count = - 1;
            continue;
        }
        dirDecide(row, col, dir);                                                                   //increment row or column
    }
}



/**********************************************************************************************************************************************
 
 
 
                                                 HUMAN CLASS FUNCTION DEFINITIONS
 
 
 
 **********************************************************************************************************************************************/

class MAXFILESIZE{};
class MINFILESIZE{};

//Human class member function to read ships and positions from file
void Human::readFile(string file)
{
    std::ios::sync_with_stdio(false);
    
    //variable declaration
    int i=0;
    string name, place;
    string orientation;
    int row=0, col=0;
    char orien;
    const int maxCount = 5;
    const int minCount = 5;

    ifstream inFile;
    
    //Open input file
    inFile.open(file);
    
    //if file fails to open
    if(inFile.fail())
    {
        cout << "Your file failed to open. Please check and try again.\n";
        cout << "NOTE: MAKE SURE IT IS IN THE SAME DIRECTORY AS THIS PROGRAM\n";

        exit(0);
    }
    else
    {
        //string to accept first line of file with no useable data
        string dummyLine;
        getline(inFile, dummyLine);
        
        //while there is data to read
        try{
            while(getline(inFile, name, ',' ))
            {
                if(i > maxCount)
                    throw MAXFILESIZE();
                
                if(i < minCount && name == "\r\n")
                    throw MINFILESIZE();
                
                getline(inFile, place, ',');
                getline(inFile, orientation);
                
                //convert the strings into correct data types
                converter(orientation, place, col, row, orien);
                
                //check if name entered is valid
                nameChange(name);
                (humanAccess.boats).emplace_back(name, row, col, i, orien);
                checkFit(humanAccess.boats[i]);
                if(fitOn == true){
                    cout << "Your " << name << " had to be re-positioned due to space available on the board\n";
                    fitOn = false;
                }
                i++;
            }
        }//catch errors
        catch(MAXFILESIZE){cout << "Your file has more than 5 ships." << endl;}
        catch(MINFILESIZE){cout << "You are missing one or more ships in your file.\n";
            cout << "It is necessary to have 5 ships to play the game.\n";
            cout << "Carrier, Battleship, Cruiser, Submarine, Destroyer.\n";
            cout << "Please check your file and make sure you have all these ships.\n";
            control.seeFileForm();
            exit(0);}
        catch(...){
            cout << "There was an unexpected error when reading the file. Please check your file format and try again\n";
            control.seeFileForm();
        }
    }
}

// Member function to convert string data to proper data type
void Human::converter(string orientaion, string place, int& col, int& row, char& orien)
{
    std::ios::sync_with_stdio(false);
    
    orien = orientaion[0];
    
    // If file orientation is not valid
    if(orien != 'H' && orien != 'V')
    {
        char orienArr[2] = {'H','V'};
        int randOr = rand()%2;
        orien = orienArr[randOr];
    }
    
    try {
        stringstream convert(place.substr(1));
        convert >> row;
        
        //if user input is a letter instead of number for row
        if(convert.fail())
            throw -999;
    } catch (int) {
        row = tolower(place[1]) - 'a';
    }
    
    //if user input is greater than board width/height
    if(row > 9 || row < 0)
    {
        cout << "\nOne of your row choices is not within range.\n"
            << "Please check your file and try again.\n\n";
        exit(0);
    }
    
    col = tolower(place[0]) - 'a';
    if(col > 9 || col < 0)
    {
        cout << "\nOne of your column choices is not within range.\n"
        << "Please check your file and try again.\n\n";
        exit(0);
    }
}

// Member function to check if ship name is valid
void Human::nameChange(string& name)
{
    std::ios::sync_with_stdio(false);
    
    // Variable declaration
    char proceed;
    bool leave = true;
    string initials[5] = {"Ca", "Ba","Cr","Su","De"};
    string shipNames[5] = {"Carrier", "Battleship","Cruiser","Submarine","Destroyer"};
    for (int i = 0; i < 5; i++)
    {
        //If the first two letters of the ship name are the same, but the ship name is not the same
        if(name.substr(0,2) == initials[i] && name != shipNames[i])
        {
            //Notify user
            cout <<"\nI think you have a slight typo in your file. I'm going to help you change " << name << " to " << shipNames[i];
            cout << "\nProceed?[Y/N]";
            cin >> proceed;
            //If they choose to fix it
            if (toupper(proceed) == 'Y') {
                name = shipNames[i];
                return;
            }
        }
        // If name is correct return
        else if(name == shipNames[i])
        {
            leave = false;
            return;
        }
    }
    //If computer could not recongnize name at all
    if (leave == true)
    {
        cout << "\nThe computer could not recognize the name " << name  << endl;
        cout << "Please check the file and try again.\n";
        control.seeFileForm();
        exit(0);
    }
}

// Member fuction to place ships on board
void Human::placeShips()
{
    //loop to access every ship
    for(int index = 0;index < 5;index++)
    {
        checkOverlap(humanAccess.boats[index]);
        
        //variable decleration
        WaterVehicle ship = humanAccess.boats[index];
        int row = ship.getRow();
        int col = ship.getCol();
        int length = ship.getLength();
        char dir = ship.getOrientation();
        string name = (ship.getName()).substr(0,2);
        
        if(overlap == true){
            cout << "Your " << ship.getName() << " had to be re-positioned due to overlapping\n";
            overlap = false;
        }
        
        //for loop to place ships data then increment the row or column
        for (int count = 0; count <= length-1; count++)
        {
            matrix.setPos(row, col, name);
            dirDecide(row, col, dir);            
        }
    }
}

//Member function to attack opponents board
bool Human::attackBoard(Grid& _matrix, Grid& _matrix2, ships& access)
{
    std::ios::sync_with_stdio(false);
    
    // Variable declaration
    char column;
    int row, col, pauseChoice;
    
    //Accept and validate input from user
    cout << "Where would you like to fire[ROW, COLUMN]\n";
    cout << "ROW (Numbers on left): ";
    cin >> row;
    control.inputValidation(row);
    cout << "COLUMN (Letters on top): ";
    cin >> column;
    
    //If user enters P to pause game
    if(toupper(column) == 'P')
    {
       pauseChoice = control.pauseMenu();
        if (pauseChoice == 2) {
            control.setRestart(true);
            return true;
        }
        else if (pauseChoice == 3)
        {
            control.instructions();
        }
        else if (pauseChoice == 4)
        {
            control.quitGame(_matrix, _matrix2);
            exit(0);
        }
    }

    // Calculate the column
    col = tolower(column) - 'a';
    
    // While value entered does not fit on board
    while(!(col <= 9)||!(row <= 9) || isdigit(column))
    {
        cout << "Please re-enter your row and column with valid values.\nTHANK YOU!\n";
        cout << "ROW (Numbers on left): ";
        cin >> row;
        control.inputValidation(row);
        cout << "COLUMN (Letters on top): ";
        cin >> column;
        col = tolower(column) - 'a';
    }
    
    //If board location is equal to ship name
    if(_matrix.getPos(row, col) != "~~" && _matrix.getMocPos(row, col) == "~~" )
    {
        for(int i = 0; i < (access.boats).size(); i++)
        {
            //if first two letters of ship name is equal to characters on board
            if(((access.boats[i]).getName()).substr(0,2) == _matrix.getPos(row, col))
            {
                string place = _matrix.getPos(row, col);
                cout <<  endl << access.boats[i].getName() << " was hit!" << endl;
                access.boats[i].setSunk();
                if(access.boats[i].getSunk() == true)
                {
                    cout<< endl << access.boats[i].getName() << " has been completely sunk!" << endl;
                }
                _matrix2.incHit();
                
                // Set the position as hit on the MOC board
                _matrix.setMocPos(row, col, place) ;
                return true;
            }
        }
    }
    
    // If board does not hit
    else
    {
        cout << endl;
        cout << "Sorry, you missed!\n\n";
        return false;
    }
    return false;
}




/**********************************************************************************************************************************************

 
 
                                                COMPUTER CLASS FUNCTION DEFINITIONS
 

 
 **********************************************************************************************************************************************/

// Computer class constructor
Computer::Computer()
{
    // Set ship names
    names.push_back("Carrier");
    names.push_back("Battleship");
    names.push_back("Cruiser");
    names.push_back("Submarine");
    names.push_back("Destroyer");
    
    //Set name for computer
    string usernames[10] = {"Nathan","Caroline","Yemi","Victoria","Umi","Anthony","Ian","Lola","David","Obama"};
    int randNum = (rand()%11) - 1;
    string randName = usernames[randNum];
    computerAccess.username = randName;
}

// Member function to set ships data
void Computer::setShips()
{
    //loop to set all ships
    for(int index = 0;index < 5;index++)
    {
        //randomize orientation
        char temp[2] = {'H','V'};
        int randTemp = rand()%2;
        char orien = temp[randTemp];
        
        //generate random ship positions
        WaterVehicle ship;
        generatePos(ship);
        
        //get ship name
        string name = names[index];
        
        //emplace then check if ship fits on board
        (computerAccess.boats).emplace_back(name, ship.getRow(), ship.getCol(), index, orien);
        checkFit(computerAccess.boats[index]);
    }
}

// Computer member function to place ships on board
void Computer::placeShips()
{
    // Loop to access every  available ship
    for(int index = 0;index < 5;index++)
    {
        // Varibale decleration
        checkOverlap(computerAccess.boats[index]);
        WaterVehicle ship = computerAccess.boats[index];
        int row = ship.getRow();
        int col = ship.getCol();
        int length = ship.getLength();
        char dir = ship.getOrientation();
        string name = (ship.getName()).substr(0,2);
        
        // For loop to place ships data then increment the row or column
        for (int count = 0; count <= length-1; count++)
        {
            matrix.setPos(row, col, name);
            
            //increment row or column based on direction
            dirDecide(row, col, dir);
        }
    }
    cout << " ";
}

// Computer member function to attack users board
bool Computer::attackBoard(Grid& _matrix, Grid& _matrix2, ships& access)
{
    int  a = 0;
    int  b = 0;
    bool validGen = false;
    //generate random positions to guess
    if(brain.shotsAttempted > 0){
        while (validGen == false) {
            a = (rand() % 10);
            b = (rand() % 10);
            for (int i=0; i < brain.noHitRow.size(); i++) {
                if (brain.noHitRow[i] != a && brain.noHitCol[i] != b) {
                    validGen = true;
                }
                else
                    continue;
            }
        }
    }
    else{
        a = (rand() % 10);
        b = (rand() % 10);
    }
   
    
    //while it is still the computers chance to attack
    while(1)
    {
        //If board location is equal to ship name
        if(_matrix.getPos(a, b) != "~~" && _matrix.getPos(a, b) != "**" )
        {
            //for loop to check if board location is equal to ship name
            for(int i=0; i < access.boats.size(); i++)
            {
                //If board location is equal to ship name
                if((access.boats[i]).getName().substr(0,2) == _matrix.getPos(a, b))
                {
                    //set the ships sunk equal to true
                    access.boats[i].setSunk();
                    
                    cout << "Your " << access.boats[i].getName() << " was hit!" << endl;
                    _matrix2.incHit();
                    _matrix.setPos(a, b, "**");
                    break;
                }//end if
            }//end for
            continue;
       }//end if
       else
       {
           brain.prevRow = a;
           brain.prevCol = b;
           cout <<"I missed!\n";
          // brain = 0;
           return false;
       }//end else
    }
        return false;    
}

bool Computer::smartAttack(Grid& _matrix, Grid& _matrix2, ships& access)
{
    int  a = 0;
    int  b = 0;
    if(brain.focus == " "){
        bool validGen = false;
        //generate random positions to guess
        while (validGen == false) {
            if (0 == brain.noHitRow.size()) {
                a = (rand() % 10);
                b = (rand() % 10);
                break;
            }
            a = (rand() % 10);
            b = (rand() % 10);
            for (int i=0; i < brain.noHitRow.size(); i++) {
                if (brain.noHitRow[i] != a && brain.noHitCol[i] != b) {
                    validGen = true;
                }
                else
                    continue;
            }
        }
    }
    else{
        a = brain.prevRow;
        b = brain.prevCol;
    }
    
    //while it is still the computers chance to attack
    while(1)
    {
        //if there is no direction for the next hit, make one
        if(brain.prevDir == ' ')
        {
            char temp[2] = {'H','V'};
            int randTemp = rand()%2;
            brain.prevDir = temp[randTemp];
        }//end if
        
        if(brain.prevDir == 'H' && brain.successful == true)
        {
            if(a==0)
            {
                b = b+1;
                brain.forwardMove = true;
                brain.backWardMove = false;
                brain.shotsAttempted++;
            }//end if
            else
            {
                if(brain.shotsAttempted == 0)
                {
                    int bTemp = b;
                    int temp[2] = {b+1,b-1};
                    int randTemp = rand()%2;
                    b = temp[randTemp];
                    
                    if(b > bTemp){
                        brain.forwardMove = true;
                        brain.backWardMove = false;
                    }
                    else{
                        brain.backWardMove = true;
                        brain.forwardMove = false;
                    }
                    brain.shotsAttempted++;
                }
                else if(brain.forwardSucc == true && brain.shotsAttempted > 0){
                    b++;
                    brain.forwardMove = true;
                    brain.backWardMove = false;
                }
                else if(brain.backwardSucc == true && brain.shotsAttempted > 0) {
                    b--;
                    brain.backWardMove = true;
                    brain.forwardMove = false;
                }
            }//end else
        }//end if
        else if(brain.prevDir == 'V' && brain.successful == true)
        {
            if(b==0)
            {
                a = a+1;
                brain.forwardMove = true;
                brain.backWardMove = false;
                brain.shotsAttempted++;
            }//end if
            else
            {
                if(brain.shotsAttempted == 0)
                {
                    int aTemp = a;
                    int temp[2] = {a+1,a-1};
                    int randTemp = rand()%2;
                    a = temp[randTemp];
                    
                    if(a > aTemp){
                        brain.forwardMove = true;
                        brain.backWardMove = false;
                    }
                    else{
                        brain.backWardMove = true;
                        brain.forwardMove = false;
                    }
                    brain.shotsAttempted++;
                }
                else if(brain.forwardSucc == true && brain.shotsAttempted > 0){
                    a++;
                    brain.forwardMove = true;
                    brain.backWardMove = false;
                }
                else if(brain.backwardSucc == true && brain.shotsAttempted > 0) {
                    a--;
                    brain.backWardMove = true;
                    brain.forwardMove = false;
                }
            }//end else
        }//end if
            
            //If board location is equal to ship name
            if(_matrix.getPos(a, b) != "~~" && _matrix.getPos(a, b) != "**" )
            {
                //for loop to check if board location is equal to ship name
                for(int i=0; i < access.boats.size(); i++)
                {
                    //If board location is equal to ship name
                    if((access.boats[i]).getName().substr(0,2) == _matrix.getPos(a, b))
                    {
                        //set the ships sunk equal to true
                        access.boats[i].setSunk();
                        brain.successful = true;
                        brain.focus = access.boats[i].getName();
                        if (brain.shotsAttempted ==0) {
                            brain.initialRow = a;
                            brain.initialCol = b;
                        }
                        
                        cout << "Your " << access.boats[i].getName() << " was hit!" << endl;
                        if (access.boats[i].getSunk()) {
                            cout << "Your " << access.boats[i].getName() << " has been completely sunk!\n";
                            brain.reset();
                        }
                        std::this_thread::sleep_for (std::chrono::milliseconds(200));
                        brain.missedShots = 0;
                        brain.hitShots++;
                        _matrix2.incHit();
                        _matrix.setPos(a, b, "**");
                        if(brain.forwardMove == true)
                            brain.forwardSucc = true;
                        else if (brain.backWardMove == true)
                            brain.backwardSucc = true;
                        
                        brain.prevRow = a;
                        brain.prevCol = b;
                        
                        break;
                    }//end if
                }//end for
                continue;
            }//end if
            else
            {
                brain.noHitRow.push_back(a);
                brain.noHitCol.push_back(b);

                if(brain.forwardMove == true){
                    brain.forwardSucc = false;
                    brain.backwardSucc = true;
                }
                else if (brain.backWardMove == true)
                {
                    brain.backwardSucc = false;
                    brain.forwardSucc = true;
                }

                brain.prevRow = brain.initialRow;
                brain.prevCol = brain.initialCol;
                brain.missedShots++;
                if(brain.missedShots == 2 && brain.hitShots > 0)
                {
                    if (brain.prevDir == 'H')
                        brain.prevDir = 'V';
                    else
                        brain.prevDir = 'H';
                }
                cout <<"I missed!\n";
                // brain = 0;
                return false;
            }//end else
    }
    return false;
}

bool Computer::cheatAttack(Grid& _matrix, Grid& _matrix2, ships& access)
{
    int  a = 0;
    int  b = 0;
    if(brain.focus == " "){
        //generate random positions to guess
        for (int index = 0; index < 10; index ++)
        {
            for (int count = 0; count < 10; count++)
            {
                if (_matrix.getPos(index, count) != "~~" && _matrix.getPos(index, count) != "**") {
                    a = index;
                    b = count;
                }
            }
        }
        
    }
    else{
        a = brain.prevRow;
        b = brain.prevCol;
    }
    
    //while it is still the computers chance to attack
    while(1)
    {
        //if there is no direction for the next hit, make one
        if(brain.prevDir == ' ')
        {
            char temp[2] = {'H','V'};
            int randTemp = rand()%2;
            brain.prevDir = temp[randTemp];
        }//end if
        
        if(brain.prevDir == 'H' && brain.successful == true)
        {
            if(a==0)
            {
                b = b+1;
                brain.forwardMove = true;
                brain.backWardMove = false;
                brain.shotsAttempted++;
            }//end if
            else
            {
                if(brain.shotsAttempted == 0)
                {
                    int bTemp = b;
                    int temp[2] = {b+1,b-1};
                    int randTemp = rand()%2;
                    b = temp[randTemp];
                    
                    if(b > bTemp){
                        brain.forwardMove = true;
                        brain.backWardMove = false;
                    }
                    else{
                        brain.backWardMove = true;
                        brain.forwardMove = false;
                    }
                    brain.shotsAttempted++;
                }
                else if(brain.forwardSucc == true && brain.shotsAttempted > 0){
                    b++;
                    brain.forwardMove = true;
                    brain.backWardMove = false;
                }
                else if(brain.backwardSucc == true && brain.shotsAttempted > 0) {
                    b--;
                    brain.backWardMove = true;
                    brain.forwardMove = false;
                }
            }//end else
        }//end if
        else if(brain.prevDir == 'V' && brain.successful == true)
        {
            if(b==0)
            {
                a = a+1;
                brain.forwardMove = true;
                brain.backWardMove = false;
                brain.shotsAttempted++;
            }//end if
            else
            {
                if(brain.shotsAttempted == 0)
                {
                    int aTemp = a;
                    int temp[2] = {a+1,a-1};
                    int randTemp = rand()%2;
                    a = temp[randTemp];
                    
                    if(a > aTemp){
                        brain.forwardMove = true;
                        brain.backWardMove = false;
                    }
                    else{
                        brain.backWardMove = true;
                        brain.forwardMove = false;
                    }
                    brain.shotsAttempted++;
                }
                else if(brain.forwardSucc == true && brain.shotsAttempted > 0){
                    a++;
                    brain.forwardMove = true;
                    brain.backWardMove = false;
                }
                else if(brain.backwardSucc == true && brain.shotsAttempted > 0) {
                    a--;
                    brain.backWardMove = true;
                    brain.forwardMove = false;
                }
            }//end else
        }//end if
        
        //If board location is equal to ship name
        if(_matrix.getPos(a, b) != "~~" && _matrix.getPos(a, b) != "**" )
        {
            //for loop to check if board location is equal to ship name
            for(int i=0; i < access.boats.size(); i++)
            {
                //If board location is equal to ship name
                if((access.boats[i]).getName().substr(0,2) == _matrix.getPos(a, b))
                {
                    //set the ships sunk equal to true
                    access.boats[i].setSunk();
                    brain.successful = true;
                    brain.focus = access.boats[i].getName();
                    if (brain.shotsAttempted ==0) {
                        brain.initialRow = a;
                        brain.initialCol = b;
                    }
                    
                    cout << "Your " << access.boats[i].getName() << " was hit!" << endl;
                    if (access.boats[i].getSunk()) {
                        cout << "Your " << access.boats[i].getName() << " has been completely sunk!\n";
                        brain.reset();
                    }
                    std::this_thread::sleep_for (std::chrono::milliseconds(200));
                    brain.missedShots = 0;
                    brain.hitShots++;
                    _matrix2.incHit();
                    _matrix.setPos(a, b, "**");
                    if(brain.forwardMove == true)
                        brain.forwardSucc = true;
                    else if (brain.backWardMove == true)
                        brain.backwardSucc = true;
                    
                    brain.prevRow = a;
                    brain.prevCol = b;
                    
                    break;
                }//end if
            }//end for
            continue;
        }//end if
        else
        {
            brain.noHitRow.push_back(a);
            brain.noHitCol.push_back(b);
            
            if(brain.forwardMove == true){
                brain.forwardSucc = false;
                brain.backwardSucc = true;
            }
            else if (brain.backWardMove == true)
            {
                brain.backwardSucc = false;
                brain.forwardSucc = true;
            }
            
            brain.prevRow = brain.initialRow;
            brain.prevCol = brain.initialCol;
            brain.missedShots++;
            if(brain.missedShots == 2 && brain.hitShots > 0)
            {
                if (brain.prevDir == 'H')
                    brain.prevDir = 'V';
                else
                    brain.prevDir = 'H';
            }
            cout <<"I missed!\n";
            // brain = 0;
            return false;
        }//end else
    }
    return false;
}


























