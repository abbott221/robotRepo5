



#include "main.h"


//ButtonBoard buttons( FEHIO::Bank3 );




FEHMotor lMotor(FEHMotor::Motor0);
FEHMotor rMotor(FEHMotor::Motor1);

ButtonBoard buttons( FEHIO::Bank3 );
FEHEncoder  leftEncoder( FEHIO::P0_0);
FEHEncoder  rightEncoder( FEHIO::P0_1);

AnalogInputPin CDS(FEHIO::P0_7);

DigitalInputPin Micro1(FEHIO::P1_0);
DigitalInputPin Micro2(FEHIO::P1_1);

AnalogInputPin optoLeft(FEHIO::P2_0);
AnalogInputPin optoMid(FEHIO::P2_2);
AnalogInputPin optoRight(FEHIO::P2_4);

FEHWONKA TheRPS;
FEHServo lolServo(FEHServo::Servo0);
FEHBattery lolBattery (FEHIO::BATTERY_VOLTAGE);


//======================================


RPScleaner cleaner;
RPScorrector corrector;


//======================================


int leftPower = 80;
int rightPower = 78;

int tempLeftPower = 80;
int tempRightPower = 78;

int servoMin = 556;
int servoMax = 2500;

//for the encoders
float lowThresh = 0.388;
float highThresh = 1.547;

//for line following
float optoThresh = 2.0;
float bLineDifThresh = 1.0;
float yLineDifThresh = .4;
float leftOptoThresh = 0.0;
float rightOptoThresh = 0.0;
float midOptoThresh = 0.0;

bool configLightStart = true;
bool configCourseTimer = true;
bool configDelay = true;
bool configRPS = true;

double displayRate = 0.2;

double courseStartTime = 0.0;
int numOfDisplays = 0;

PMode currentPowerMode = STOP;
int leftPowerMode = leftPower;
int rightPowerMode = rightPower;

float decisionLight = 0.0;

int currentMove = 0;


//===================================================


void MainMenuCall();
void ConfigureMenuCall();


//===================================================





MovementTracker mTracker;


//ISSUE HERE MAY HAVE CAUSED INFINITE LOOP?
//OperationTracker opTracker(300);
OperationTracker opTracker(500);





//===================================================

//THESE ARE GLOBALS

// static/final menus

int mainChoice = -1;
Menu mainMenu;

int pageChoice = -1;
Menu pageMenu;

int configureChoice = -1;
Menu configureMenu;

int operationChoice = -1;
Menu operationMenu;


// more static/final menus for operations
int opSubChoice = -1;
Menu opSubTimeMenu;
Menu opSubEncMenu;
Menu opSubLineMenu;

Menu opSubGeneralMenu;
Menu opSubRPSRealMenu;
Menu opSubRPSRealTurnMenu;


// dynamic menus

int moveChoice = -1;
Menu moveMenu;



int main(void)
{
    //LCD.Clear( FEHLCD::Black );
    //LCD.SetFontColor( FEHLCD::White );

    //OperationTracker opTracker(4);

    opTracker.add_fOperation( 0, &DriveForTime );
    opSubTimeMenu.addOption("  Time: Straight", 0);
    opTracker.add_fOperation( 1, &TurnLeftForTime );
    opSubTimeMenu.addOption("  Time: Left", 1);
    opTracker.add_fOperation( 2, &TurnRightForTime );
    opSubTimeMenu.addOption("  Time: Right", 2);
    opTracker.add_fOperation( 3, &BackwardsForTime );
    opSubTimeMenu.addOption("  Time: Backwards", 3);

    opTracker.add_dOperation( 4, &EncForward );
    opSubEncMenu.addOption("  Enc: Straight", 4);
    opTracker.add_dOperation( 5, &EncLeft );
    opSubEncMenu.addOption("  Enc: Left", 5);
    opTracker.add_dOperation( 6, &EncRight );
    opSubEncMenu.addOption("  Enc: Right", 6);
    opTracker.add_dOperation( 7, &EncBackward );
    opSubEncMenu.addOption("  Enc: Backward", 7);

    opTracker.add_dOperation( 12, &ChangeOptoThreshold );
    opSubLineMenu.addOption("  Change Opto Thresh", 12);
    opTracker.add_dOperation( 9, &FollowBlackLine );
    opSubLineMenu.addOption("  Follow Black Line", 9);
    opTracker.add_dOperation( 10, &FollowLightLine );
    opSubLineMenu.addOption("  Follow Light Line", 10);
    opTracker.add_dOperation( 16, &unFollowBlackLine );
    opSubLineMenu.addOption("  unFollow Black Line", 16);
    opTracker.add_dOperation( 17, &unFollowLightLine );
    opSubLineMenu.addOption("  unFollow Light Line", 17);
    //more line
    opTracker.add_vOperation( 20, &GetOptoThresh );
    opSubLineMenu.addOption("  get opto thresh", 20);
    opTracker.add_dOperation( 21, &BlackLineFollow );
    opSubLineMenu.addOption("  black line follow", 21);
    opTracker.add_dOperation( 22, &YellowLineFollow );
    opSubLineMenu.addOption("  yellow line follow", 22);
    opTracker.add_dOperation( 23, &JeffBlackLine );
    opSubLineMenu.addOption("  jeff black line", 23);
    opTracker.add_dOperation( 24, &JeffLightLine );
    opSubLineMenu.addOption("  jeff light line", 24);


    //GENERAL
    opTracker.add_iOperation( 8, &SetServoDegree );
    opSubGeneralMenu.addOption("  set servo degree", 8);
    opTracker.add_vOperation( 13, &DisplayLightValue );
    opSubGeneralMenu.addOption("  display light value", 13);
    opTracker.add_dOperation( 14, &FlyOverLightValue );
    opSubGeneralMenu.addOption("  fly over light value", 14);
    opTracker.add_dOperation( 19, &LightDecisionTurn );
    opSubGeneralMenu.addOption("  light decision turn", 19);
    opTracker.add_vOperation( 26, &PushButton );
    opSubGeneralMenu.addOption("  Push Button", 26);
    opTracker.add_dOperation( 27, &Micro );
    opSubGeneralMenu.addOption("  Micro", 27);


    opTracker.add_dOperation( 50, &MoveToRealX );
    opSubRPSRealMenu.addOption("  Move to real X", 50);
    opTracker.add_dOperation( 51, &MoveToRealY );
    opSubRPSRealMenu.addOption("  move to real Y", 51);


    opTracker.add_vOperation( 60, &TurnLeftPast180 );
    opSubRPSRealTurnMenu.addOption("  Left past 180", 60);
    opTracker.add_vOperation( 61, &TurnRightPast0 );
    opSubRPSRealTurnMenu.addOption("  Right past 0", 61);
    opTracker.add_dOperation( 62, &TurnLeftToAngle );
    opSubRPSRealTurnMenu.addOption("  Left to angle", 62);
    opTracker.add_dOperation( 63, &TurnRightToAngle );
    opSubRPSRealTurnMenu.addOption("  right to angle", 63);
    opTracker.add_dOperation( 64, &UnsafeTurnToAngle );
    opSubRPSRealTurnMenu.addOption("  unsafe turn to angle", 64);
    opTracker.add_dOperation( 80, &RelativeTurnLeft );
    opSubRPSRealTurnMenu.addOption("  Relative Left", 80);
    opTracker.add_dOperation( 81, &RelativeTurnRight );
    opSubRPSRealTurnMenu.addOption("  Relative Right", 81);

    //opSubGeneralMenu;
    //opSubRPSRealMenu;
    //opSubRPSRealTurnMenu;




    //opTracker.add_iOperation( 301, &PrintInt );
    //opTracker.add_fOperation( 302, &PrintFloat );
    //opTracker.add_dOperation( 303, &PrintDouble );
    //opTracker.add_vOperation( 304, &PrintVoid );







    //movement presets start



    for (int i = 0; i < 144; i++)
    {
        mTracker.tracker[i].set_fMovement(0, 0.0);
        mTracker.tracker[i].setState(false);
    }




    //later, determine dataType from dOp and overload the method?
    int holder = 0;

    holder = mTracker.add_fMovement(0, 1.0);
    //mTracker.tracker[holder].moveInfo.setExpected(float x, float y, float angle);
    holder = mTracker.add_fMovement(1, 1.0);
    //mTracker.tracker[holder].moveInfo.setExpected();
    holder = mTracker.add_fMovement(2, 1.0);
    holder = mTracker.add_fMovement(0, 3.0);

    holder = mTracker.add_fMovement(0, 1.0);
    holder = mTracker.add_fMovement(1, 1.0);
    holder = mTracker.add_fMovement(2, 1.0);
    holder = mTracker.add_fMovement(0, 3.0);

    //holder = mTracker.add_iMovement(301, 5);
    //holder = mTracker.add_fMovement(302, 6.0);
    //holder = mTracker.add_dMovement(303, 7.0);
    //holder = mTracker.add_vMovement(304);


    //movement presets end



    mainMenuSetup();

    pageMenuSetup();

    operationMenuSetup();






    for (int i = 0; i < 12; i++)
    {
        pageMenu.selection[i].setState(true);
    }




    struct set tempDisplacement;
    tempDisplacement.X = 0.0;
    tempDisplacement.Y = 0.0;
    tempDisplacement.Head = 0.0;

    cleaner.setDisplacement(tempDisplacement);




    while (true)
    {
        MainMenuCall();
    }



    return 0;
}




void MainMenuCall()
{


    mainChoice = mainMenu.UserInterface();


    int tempNum;
    int incrs[] = {25, 10, 1};





    //option 0: in case your finger slips
    if (mainChoice == 0)
    {
        //
    }



    //Option 1: Run
    else if (mainChoice == 1)
    {
        //driveProcess();
        driveProcess();
    }



    //Option 2: Adjust (Set) Movement
    else if (mainChoice == 2)
    {

        //PAGEANDMOVEINTERFACE REPLACEMENT
        pageChoice = pageMenu.UserInterface();
        //(move selection)
        moveMenuSetup();
        moveChoice = moveMenu.UserInterface();
        moveChoice = moveChoice + (12 * pageChoice);


        //insert menu sets here
        opSubMenusSetup();


        //USER INTERFACE: MOVEMENT TYPE SELECTION
        operationChoice = operationMenu.UserInterface();

        //MOVE THIS TO OPSUBMENUSETUP LATER
        if (operationChoice == 0)
        {
            //frequently used ones
            //opSubChoice =
        }
        else if (operationChoice == 1)
        {
            opSubChoice = opSubTimeMenu.UserInterface();
        }
        else if (operationChoice == 2)
        {
            opSubChoice = opSubEncMenu.UserInterface();
        }
        else if (operationChoice == 3)
        {
            opSubChoice = opSubLineMenu.UserInterface();
        }


        else if (operationChoice == 4)
        {
            opSubChoice = opSubGeneralMenu.UserInterface();
        }
        else if (operationChoice == 5)
        {
            opSubChoice = opSubRPSRealMenu.UserInterface();
        }
        else if (operationChoice == 6)
        {
            opSubChoice = opSubRPSRealTurnMenu.UserInterface();
        }




        //@DEBUGGING
        //I WAS RIGHT!!!
        /*
        if (opSubTimeMenu.getSubOpMenu() == false)
        {
            while (true)
            {
                LCD.WriteLine("ERROR DIAGNOSED");
            }
        }
        else if (opSubEncMenu.getSubOpMenu() == false)
        {
            while (true)
            {
                LCD.WriteLine("ERROR DIAGNOSED");
            }
        }
        else if (opSubLineMenu.getSubOpMenu() == false)
        {
            while (true)
            {
                LCD.WriteLine("ERROR DIAGNOSED");
            }
        }
        else if (opSubGeneralMenu.getSubOpMenu() == false)
        {
            while (true)
            {
                LCD.WriteLine("ERROR DIAGNOSED");
            }
        }
        else if (opSubRPSRealMenu.getSubOpMenu() == false)
        {
            while (true)
            {
                LCD.WriteLine("ERROR DIAGNOSED");
            }
        }
        else if (opSubRPSRealTurnMenu.getSubOpMenu() == false)
        {
            while (true)
            {
                LCD.WriteLine("ERROR DIAGNOSED");
            }
        }
        /**/







        //opSubMenusSetup();




        //Set the time of the adjusted move
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        //TypeEnum checkMe = findDataTypeOfJeffID(opSubChoice);
        TypeEnum checkMe = opTracker.tracker[opSubChoice].getDataType();




        //integer valued move
        if (checkMe == tInt)
        {
            int tempIntValue = mTracker.tracker[moveChoice].getIntValue();

            int incrs[] = {5, 3, 1};

            tempIntValue = SetInteger(tempIntValue, incrs, 3);

            //mTracker.tracker[moveChoice]
            //chet.moreMoves[moveChoice]
            mTracker.tracker[moveChoice].set_iMovement(opSubChoice, tempIntValue);
        }

        //double valued move
        else if (checkMe == tFloat)
        {
            float tempFloatValue = mTracker.tracker[opSubChoice].getFloatValue();

            float incrs[] = {1.0, 0.1, 0.01};

            tempFloatValue = SetFloat(tempFloatValue, incrs, 3);

            mTracker.tracker[moveChoice].set_fMovement(opSubChoice, tempFloatValue);
        }

        //double valued move
        else if (checkMe == tDouble)
        {
            double tempDoubleValue = mTracker.tracker[moveChoice].getDoubleValue();

            double incrs[] = {2.0, 0.1, 0.01};

            tempDoubleValue = SetDouble(tempDoubleValue, incrs, 3);

            mTracker.tracker[moveChoice].set_dMovement(opSubChoice, tempDoubleValue);
        }
        else if (checkMe == tVoid)
        {
            mTracker.tracker[moveChoice].set_vMovement(opSubChoice);
        }



    }



    //Option 3: Display movements
    else if (mainChoice == 3)
    {



        pageChoice = pageMenu.UserInterface();



        //(move selection)
        moveMenuSetup();

        //LCD.WriteAt('c', 13, 13);

        moveChoice = moveMenu.UserInterface();
        moveChoice = moveChoice + (12 * pageChoice);
    }



    //Option 4: Insert movement
    else if (mainChoice == 4)
    {
        LCD.WriteLine("Enter num of move (0-142)");


        tempNum = SetInteger(0, incrs, 3);

        bool tempState;
        for (int i = 142; i >= tempNum; i--)
        {
            tempState = mTracker.tracker[i].getState();
            if (mTracker.tracker[i].getDataType() == tDouble)
            {
                mTracker.tracker[i+1].set_dMovement(mTracker.tracker[i].getOperation(), mTracker.tracker[i].getDoubleValue());
            }
            else
            {
                mTracker.tracker[i+1].set_iMovement(mTracker.tracker[i].getOperation(), mTracker.tracker[i].getIntValue());
            }
            mTracker.tracker[i+1].setState(tempState);
        }
        mTracker.tracker[tempNum].set_dMovement(0, 0.0);
        mTracker.tracker[tempNum].setState(false);
    }



    //Option 5: Turn on (Old Add) movement
    else if (mainChoice == 5)
    {
        //PAGEANDMOVEINTERFACE REPLACEMENT
        pageChoice = pageMenu.UserInterface();
        //(move selection)
        moveMenuSetup();
        moveChoice = moveMenu.UserInterface();
        moveChoice = moveChoice + (12 * pageChoice);





        mTracker.tracker[moveChoice].setState(true);
    }



    //Option 6: Turn off (Old Delete) Movement
    else if (mainChoice == 6)
    {
        //PAGEANDMOVEINTERFACE REPLACEMENT
        pageChoice = pageMenu.UserInterface();
        //(move selection)
        moveMenuSetup();
        moveChoice = moveMenu.UserInterface();
        moveChoice = moveChoice + (12 * pageChoice);






        mTracker.tracker[moveChoice].setState(false);
    }



    //Option 7: Add page
    else if (mainChoice == 7)
    {
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        LCD.WriteLine("Select Page");

        //pageChoice = pageInterface();
        pageChoice = pageMenu.UserInterface();


        for (int i = 0; i < 12; i++)
        {
            mTracker.tracker[i + (12 * pageChoice)].setState(true);
        }

        pageMenu.selection[pageChoice].setState(true);
    }



    //Option 8: Delete Page
    else if (mainChoice == 8)
    {
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        LCD.WriteLine("Select Page");

        //pageChoice = pageInterface();
        pageChoice = pageMenu.UserInterface();


        for (int i = 0; i < 12; i++)
        {
            mTracker.tracker[i + (12 * pageChoice)].setState(false);
        }

        pageMenu.selection[pageChoice].setState(false);
    }



    //Option 9: Calibrate/Configure
    else if (mainChoice == 9)
    {
        ConfigureMenuCall();
    }


    //Option 10: Bottom Left (and Right corners)
    else if (mainChoice == 10)
    {
        while( buttons.MiddlePressed() )
        {
            //this menu is entered by pressing the middle button
        }


        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        LCD.WriteLine("Put robot in lower left corner.");
        LCD.WriteLine("The robot's forklift should face North towards the great switch in the sky.");
        LCD.WriteLine("When this difficult task has been accomplished, press the middle button.");


        while( !buttons.MiddlePressed() )
        {
            //Sleep(0.10);
        }


        //user is ready to calibrate the lower left coordinate
        while( buttons.MiddlePressed() )
        {
            //nothing
        }

        cleaner.mainMenuUpdate();

        struct set tempReal = cleaner.getReal();
        struct set tempExpected;
        tempExpected.X = -11.5;
        tempExpected.Y = 9.7;
        tempExpected.Head = 90.0;

        struct set tempDisplacement;
        tempDisplacement.X = tempExpected.X - tempReal.X;
        tempDisplacement.Y = tempExpected.Y - tempReal.Y;
        tempDisplacement.Head = tempExpected.Head - tempReal.Head;

        cleaner.setDisplacement(tempDisplacement);

    }

}



void ConfigureMenuCall()
{
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    //LCD.WriteLine("Cunfiguer Yor Stuf Heer");

    LCD.Write("Voltage: ");
    LCD.WriteLine(lolBattery.Voltage());

    configureMenu.addOption("  Calibrate Power");

    configureMenu.addOption("  Calibrate Servo");

    configureMenu.addOption("  Start with Light");
    configureMenu.selection[2].setState(configLightStart);

    configureMenu.addOption("  Course Timer");
    configureMenu.selection[3].setState(configCourseTimer);

    configureMenu.addOption("  2 sec delay");
    configureMenu.selection[4].setState(configDelay);

    configureMenu.addOption("  Use RPS");
    configureMenu.selection[5].setState(configRPS);

    configureMenu.addOption("  Read mid-opto value");

    configureMenu.addOption("  Read CDS values");

    configureMenu.addOption("  Read RPS values");

    //configureSelect[9].setOption(11, "  Data Spew Modulus");
    configureMenu.addOption("  Time between displays");





    configureChoice = configureMenu.UserInterface();



    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    //calibrate motor
    if (configureChoice == 0)
    {
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        LCD.WriteLine("Setting Left Motor");

        int tempPower = leftPower;
        int incrs[] = {5, 3, 1};
        tempPower = SetInteger(tempPower, incrs, 3);

        leftPower = tempPower;

        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );
        LCD.WriteLine("Setting Right Motor");


        tempPower = rightPower;
        //int incrs[] = {5, 3, 1};
        tempPower = SetInteger(tempPower, incrs, 3);

        rightPower = tempPower;
    }
    //calibrate servo
    else if (configureChoice == 1)
    {
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        LCD.WriteLine("Commence the calibration?");

        lolServo.Calibrate();

        //INPUT THE NUMBERS


        LCD.WriteLine("Setting Min");

        int tempTicks = 0;
        int incrs[] = {500, 100, 10, 1};
        tempTicks = SetInteger(tempTicks, incrs, 4);

        servoMin = tempTicks;

        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );
        LCD.WriteLine("Setting Max");


        tempTicks = 0;
        //int incrs[] = {5, 3, 1};
        tempTicks = SetInteger(tempTicks, incrs, 4);

        servoMax = tempTicks;



    }

    else if (configureChoice == 2)
    {
        if (configLightStart == true)
        {
            configLightStart = false;
        }
        else
        {
            configLightStart = true;
        }
    }
    else if (configureChoice == 3)
    {
        if (configCourseTimer == true)
        {
            configCourseTimer = false;
        }
        else
        {
            configCourseTimer = true;
        }
    }
    else if (configureChoice == 4)
    {
        if (configDelay == true)
        {
            configDelay = false;
        }
        else
        {
            configDelay = true;
        }
    }
    else if (configureChoice == 5)
    {
        if (configRPS == true)
        {
            configRPS = false;
        }
        else
        {
            configRPS = true;
        }
    }

    //mid-opto values
    else if (configureChoice == 6)
    {
        while( buttons.MiddlePressed() )
        {
            //this menu is entered by pressing the middle button
        }
        while( !buttons.MiddlePressed() )
        {
            LCD.Write(optoLeft.Value());
            LCD.Write(" ");
            LCD.Write(optoMid.Value());
            LCD.Write(" ");
            LCD.WriteLine(optoRight.Value());

            Sleep(0.10);
        }
        while( buttons.MiddlePressed() )
        {
            //nothing
        }
    }

    //CDS values
    else if (configureChoice == 7)
    {
        while( buttons.MiddlePressed() )
        {
            //this menu is entered by pressing the middle button
        }
        while( !buttons.MiddlePressed() )
        {
            LCD.WriteLine(CDS.Value());
            Sleep(.10);
        }
        while( buttons.MiddlePressed() )
        {
            //nothing
        }
    }

    //RPS values
    else if (configureChoice == 8)
    {
        while( buttons.MiddlePressed() )
        {
            //this menu is entered by pressing the middle button
        }
        TheRPS.InitializeMenu();
        TheRPS.Enable();
        while( !buttons.MiddlePressed() )
        {
            LCD.Write(TheRPS.Heading());
            LCD.Write(" ");
            LCD.Write(TheRPS.X());
            LCD.Write(" ");
            LCD.WriteLine(TheRPS.Y());
            Sleep(.10);
        }
        TheRPS.Disable();
        while( buttons.MiddlePressed() )
        {
            //nothing
        }
    }
    else if (configureChoice == 9)
    {
        LCD.WriteLine("Setting display rate");

        double tempRate = displayRate;
        double incrs[] = {1.0, 0.1, 0.01};
        tempRate = SetDouble(tempRate, incrs, 3);

        //dataSpew = tempSpew;
        displayRate = tempRate;
    }
}









