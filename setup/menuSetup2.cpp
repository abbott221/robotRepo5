

#include "menuSetup.h"




//dynamic menus?











void moveMenuSetup()
{
    //pageChoice IS A GLOBAL
    //no need to pass it in as a parameter

    //WILL THIS WORK???
    //delete moveMenu; no
    //Menu moveMenu; no

    moveMenu.setSelectionSize(0);
    //moveMenu.selection = new option[0];


    Movement tempMoves[12];


    //LCD.WriteAt('e', 13, 13);


    int tempCurrentMove = 0;

    for (int i = 0; i < 12; i++)
    {
        //LCD.WriteLine("freeze");
        //LCD.WriteLine(i);

        tempCurrentMove = i + (12 * pageChoice);

        //LCD.WriteLine("unfreeze");
        //LCD.WriteLine(i);

        //LCD.WriteAt(i, (17*i) , (17*1) );

        tempMoves[i].setMovement(mTracker.tracker[tempCurrentMove]);

        //LCD.WriteAt(i, (17*i) , (17*2) );

        moveMenu.addOption(tempMoves[i]);

        //LCD.WriteAt(i, (17*i) , (17*3) );
    }

    //this next line is left to main.cpp
    //moveChoice = moveMenu.UserInterface();

}




void opSubMenusSetup()
{
    //opSubTimeMenu = new Menu;
    opSubTimeMenu.setSubOpMenu(true);
    //opSubEncMenu = new Menu;
    opSubEncMenu.setSubOpMenu(true);
    //opSubLineMenu = new Menu;
    opSubLineMenu.setSubOpMenu(true);

    opSubGeneralMenu.setSubOpMenu(true);
    opSubRPSRealMenu.setSubOpMenu(true);
    opSubRPSRealTurnMenu.setSubOpMenu(true);

}










