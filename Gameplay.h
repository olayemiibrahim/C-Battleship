//
//  Gameplay.hpp
//  IbrahimO_Final
//
//  Created by Olayemi Ibrahim on 4/4/18.
//  Copyright © 2018 Olayemi Ibrahim. All rights reserved.
//

#ifndef Gameplay_hpp
#define Gameplay_hpp

#include "Grid.h"
#include "WaterVehicle.h"
#include <stdio.h>

//Gameplay class declaration
class Gameplay
{
//private variable declaration
private:
    bool restartGame = false;

//public member function declerations
public:
    bool getRestart() const {return restartGame;}
    void setRestart(bool _restart){restartGame =  _restart;}
    void inputValidation(int&);
    void instructions() const;
    void seeFileForm() const;
    int pauseMenu();
    void centerString(string s);             //http://www.dreamincode.net/forums/topic/13749-center-text-with-cout/
    bool quitGame(Grid&, const Grid&) const;
    bool gameOver(Grid&, const Grid&,ships, bool);
};


#endif /* Gameplay_hpp */
