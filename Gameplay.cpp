//
//  Gameplay.cpp
//  IbrahimO_Final
//
//  Created by Olayemi Ibrahim on 4/4/18.
//  Copyright © 2018 Olayemi Ibrahim. All rights reserved.
//

//include preprocessor directives
#include "Gameplay.h"
#include <iostream>
using namespace std;

//Gameplay member function to validate input
void Gameplay::inputValidation(int& A)
{
    //Loop until user ipnut does not fail
    while(cin.fail())
    {
        //clear input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        //request new input
        cout << "ERROR \nINVALID INPUT: PLEASE ENTER AN INTEGER BELOW\n";
        cin >> A;
    }
    
}

//Gameplay member function to display instructions to user
void Gameplay::instructions() const
{
    std::ios::sync_with_stdio(false);
    
    //print instructions to user
    cout << "\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "OBJECTIVE OF THE GAME:\n";
    cout << "Be the first to sink all of your opponents ships\n\n";
    cout << "HOW TO PLAY:\n";
    cout << "(STEP 1)To play this game, the computer will first prompt you to enter the\n";
    cout << "row of the opponents board you would like to fire in. The row will always\n";
    cout << "be a number value. Once you enter your value press the [ENTER] key.\n";
    cout << "(STEP 2)Next you will be prompted for the column, which will be an alphabetical.\n";
    cout << "character. Repeat the process for the first step.\n";
    cout << "(STEP 3)If you hit one of the opponents ships, you will be allowed to fire again.\n";
    cout << "If you miss, it will be the opponents turn to fire.\n";
    cout << "(STEP 4)Steps 1 through 3 will be repeated until one players ships are all sunk\n\n";
    cout << "HAVE FUN!\n\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

//Gameplay member function to display pause menu
int Gameplay::pauseMenu()
{
    std::ios::sync_with_stdio(false);
    
    //display menu to user
    int menuChoice;
    centerString("GAME PAUSED\n");
    centerString("************************************************************************\n");
    centerString("MAIN MENU\n");
    centerString("1. Resume Game \n");
    centerString("2. Restart Game\n");
    centerString("3. Help        \n");
    centerString("4. Quit        \n");
    centerString("************************************************************************\n");
    cout << "ENTER MENU CHOICE: ";
    cin >> menuChoice;
    centerString("************************************************************************\n");
    return menuChoice;
}

//Gameplay member function to display proper file format to user
void Gameplay::seeFileForm() const
{
    cout << "\nPROPER FILE FORMAT\n";
    cout << "TypeOfShip,Location,HorizOrVer\n"
    <<"Carrier,A1,H\n"
    <<"Battleship,B5,H\n"
    << "Cruiser,C2,H\n"
    << "Submarine,G6,V\n"
    << "Destroyer,H6,V\n\n";
}

//Gameplay member function to center text output
void Gameplay::centerString(string s)              //http://www.dreamincode.net/forums/topic/13749-center-text-with-cout/
{
    std::ios::sync_with_stdio(false);
    //get the length of the string
    long l = (long)s.length();
    int pos=(int)((80-l)/2);
    
    //create space till center and print text
    for(int i = 0; i < pos; i++)
        cout<<" ";
    cout << s;
}

//Gameplay member function to decide game over
bool Gameplay::gameOver(Grid& computer, const Grid& human, ships access, bool gameOver)
{
    vector<string>temp;
    //for loop to access each ship
    for(int i = 0; i < 5;i++)
    {
        //if boat has been completely sunk
        if(access.boats[i].getSunk() == true)
        {
            //store boat name is vector
            temp.push_back(access.boats[i].getName());
            
            //if length of vector is equal to amount of boats
            if(temp.size() == access.boats.size())
            {
                gameOver = true;
            }
        }
    }
    
    //if game is over
    if(gameOver == true)
    {
        //Quit game
        quitGame(computer, human);
        return gameOver;
    }
    else
        return gameOver;
}

//Gameplay member function to quit current game
bool Gameplay::quitGame(Grid& computer, const Grid& human) const
{
    //if statements to decide winner
    if(computer.gethits() > human.gethits())
        cout << "Your opponent hit your board " << computer.gethits() << " times.\nYOU LOSE!\n\n";
    else if(computer.gethits() < human.gethits())
        cout << "You hit your oppenents board " << human.gethits() << " times.\nYOU WIN!\n\n";
    else
        cout << "You and your oppenent tied at " << human.gethits() << " hits.\nTIE GAME!\n\n";
    
    cout << "Press enter to view your opponents board...\n";
    cin.ignore();
    cin.get();
    
    // Make the Moc boards hit positions appear hit
    for (int index = 0; index < 10; index ++)                               //nested for loop to access all parts of the array
    {
        for (int count = 0; count < 10; count++)
        {
            if(computer.getMocPos(index, count) != "~~")
            {
                computer.setMocPos(index, count, "**");
            }
        }
    }

    // Display boards to user
    cout << "Thanks for playing!\n";
    cout << "This was your opponents board!\n\n";
    computer.printBoard(computer, 0);
    cout << "This was your opponents board AFTER your hits!\n\n";
    computer.printBoard(computer, 1);
    return true;
}
