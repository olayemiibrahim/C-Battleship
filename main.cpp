//
//  main.cpp
//  IbrahimO_Final
//
//  Created by Olayemi Ibrahim on 3/9/18.
//  Copyright © 2018 Olayemi Ibrahim. All rights reserved.
//

#include "Player.h"
#include "WaterVehicle.h"

//Preprocessor directives
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <string>
using namespace std;

Gameplay control;

//forward declaration of playGame function
bool playGame(int difficulty, string gamefile);
int attempt = 0;
int main() {
    //variable declarations
    char replay = 'N';
    int menuChoice;
    int difficultyChoice;
    Computer temp;
    string gameFile = "ship_placement.csv";
    
    std::ios::sync_with_stdio(false);

    //do while loop to replaty game
    do
    {
        //restart boolean to allow user to restart game at any time
        bool restart = false;
        
        //Display menu to user and read input
        control.centerString("WELCOME TO BATTLESHIP!!!\n");
        control.centerString("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        control.centerString("MAIN MENU\n");
        control.centerString("1. Start Game                 \n");
        control.centerString("2. Start Game with custom file\n");
        control.centerString("3. Quit                       \n");
        control.centerString("                  4. Help                         ____            \n");
        control.centerString("                                                 /|  /            \n");
        control.centerString("                                                /_|_/             \n");
        control.centerString("                                               ___|___            \n");
        control.centerString("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| o o o |~~~~~~~~~~~\n");
        control.centerString("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        cout << "ENTER MENU CHOICE: ";
        cin >> menuChoice;
        control.inputValidation(menuChoice);
        control.centerString("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        //switch based on user input
        switch (menuChoice) {
            case 1:
                //if playGame returns true game will restart automatically
                control.centerString("DIFFICULTY\n");
                control.centerString("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                control.centerString("1. EASY        \n");
                control.centerString("2. INTERMEDIATE\n");
                control.centerString("3. DIFFICULT   \n");
                control.centerString("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                cout << "ENTER MENU CHOICE: ";
                cin >> difficultyChoice;
                control.inputValidation(difficultyChoice);
                control.centerString("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                
                restart = playGame(difficultyChoice, gameFile);
                break;
            case 2:
                cout << "What is the name of the file?\n";
                cout << "[NOTE: CASE SENSITIVE AND ADD EXTENTION NAME eg. ship_placement.csv]\n";
                cout << "[ALL CHARACTERS WILL BE STORED INCLUDING SPACES]\n";
                
                cout << "NAME OF FILE: ";
                cin >> gameFile;
                //if playGame returns true game will restart automatically
                control.centerString("DIFFICULTY\n");
                control.centerString("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                control.centerString("1. EASY        \n");
                control.centerString("2. INTERMEDIATE\n");
                control.centerString("3. DIFFICULT   \n");
                control.centerString("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                cout << "ENTER MENU CHOICE: ";
                cin >> difficultyChoice;
                control.inputValidation(difficultyChoice);
                control.centerString("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                restart = playGame(difficultyChoice, gameFile);

                break;
            case 3:
                cout << "Goodbye!\n";
                exit(0);
                break;
            case 4:
                control.instructions();
                break;
            default:
                cout << "ERROR: INVALID MENU CHOICE\n";
                break;
        }
        if(restart == true)
        {
            //change replay to Y and continue loop to restart
            replay = 'Y';
            continue;
        }
        cout << "Would you like to return to the main menu?[ENTER 'Y' FOR YES AND 'N' FOR NO]\n";
        cin >> replay;
        
    }while(toupper(replay) == 'Y');
    
    cout << "Goodbye!\n";


    return 0;
}


bool playGame(int difficulty, string gameFile)
{
    //varibale declaration
    char choice;
    srand((unsigned)time(0));
    Human User;
    Computer Machine;
    bool humanTurn = true;
    bool compTurn = true;
    bool gameOver = false;
    
    std::ios::sync_with_stdio(false);

    
    User.readFile(gameFile);
    
    //Set and place computers ships
    Machine.setShips();
    Machine.placeShips();
    ships compShip = Machine.getShips();
    Grid compGrid = Machine.getGrid();
    string compName = Machine.getName();

    //Display o
    cout << "\nHey, I'm your opponent, " << (string)compName << ". Get ready to play!\n";
    cout << "Press enter to continue...\n";
    cin.ignore();
    cin.get();

    cout << "\nSetting up board";
    for (int i = 0; i < 3; i++) {
        std::cout << ".";
        std::this_thread::sleep_for (std::chrono::milliseconds(450));
    }
    cout << endl;
    
    //place users ships
    User.placeShips();
    ships humanShip = User.getShips();
    Grid humanGrid = User.getGrid();
    Grid humanMocGrid = User.getGrid();


    //display set board to user
    cout << "\nHere is your board!\n";
    humanGrid.printBoard(humanGrid, 0);
    cout << "Press enter to continue...\n";
    cin.get();

    //while the game is not over
    while(gameOver == false)
    {
        cout << "--------------------------------------------------\n";
        cout << "PAUSE AT ANY TIME BY ENTERING P FOR COLUMN\n";
        cout << "--------------------------------------------------\n";
        cout << "OPTION TO QUIT AND INSTRUCTIONS ARE IN PAUSE MENU\n";
        cout << "---------------------------------------------------\n";
        
        //while it is still the users turn, and the game is not over
        while((humanTurn == true) && (gameOver == false))
        {
            //Allow user to attack opponents board
            cout << "It's your turn!\n";
            cout << "---------------\n";
            humanTurn = User.attackBoard(compGrid, humanGrid, compShip);
            attempt++;
            cout << attempt << endl;
            
            //if the user chooses to restart
            if ((User.control).getRestart() == true)
            {
                return true;
            }
            //check if it is gameover
            gameOver = control.gameOver(compGrid, humanGrid, compShip, gameOver);
            if(gameOver == true){return false;}
            
            //display opponents boars
            cout << (string)compName << "'s BOARD\n";
            
            //1 stands for the moc board whereas 0 is the original board
            compGrid.printBoard(compGrid, 1);
            
        }
        
        cout << endl;
        
        
            cout << "Now it's my turn!\n";
            for (int i = 0; i < 3; i++) {
                std::cout << "." << std::endl;
                std::this_thread::sleep_for (std::chrono::milliseconds(350));
        }
        
        while((compTurn == true) && (gameOver == false))
        {
            if (difficulty == 1)
                compTurn = Machine.attackBoard(humanGrid, compGrid,humanShip);

            else if (difficulty == 2)
                compTurn = Machine.smartAttack(humanGrid, compGrid,humanShip);
            
            else if (difficulty == 3)
                compTurn = Machine.cheatAttack(humanGrid, compGrid,humanShip);

                gameOver = control.gameOver(compGrid, humanGrid, humanShip, gameOver);
            if(gameOver == true){return false;}

            cout << attempt << endl;
            cout << attempt << endl;
            cout << "\nYOUR BOARD\n";
            humanGrid.printBoard(humanGrid, 0);
        }
        humanTurn = true;
        compTurn = true;
    }
    return false;
}







