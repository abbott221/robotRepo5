


#include "drive.h"



void logDataStuffs()
{
    double dTime = TimeNow() - courseStartTime;

    //DO UPDATE CORRECTIVE STUFF HERE



    //CBmidmovePassiveCheck();





    if (dTime > displayRate * numOfDisplays)
    {
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );


        //DO NOT UPDATE CORRECTIVE STUFF HERE



        if (buttons.MiddlePressed())
        {
            SetPowerStop();
            while (buttons.MiddlePressed())
            {
                //nothing
            }
            MainMenuCall();
        }




        LCD.Write(TheRPS.Heading());
        LCD.Write(" ");
        LCD.Write(TheRPS.X());
        LCD.Write(" ");
        LCD.WriteLine(TheRPS.Y());

        LCD.Write(optoLeft.Value());
        LCD.Write(" ");
        LCD.Write(optoMid.Value());
        LCD.Write(" ");
        LCD.WriteLine(optoRight.Value());



        LCD.Write("Left Power: ");
        LCD.WriteLine(leftPowerMode);

        LCD.Write("Right Power: ");
        LCD.WriteLine(rightPowerMode);



        LCD.Write("Power Mode: ");
        if (currentPowerMode == STRAIGHT)
        {
            LCD.WriteLine("Straight");
        }
        else if (currentPowerMode == LEFT)
        {
            LCD.WriteLine("Left");
        }
        else if (currentPowerMode == RIGHT)
        {
            LCD.WriteLine("Right");
        }
        else if (currentPowerMode == BACKWARDS)
        {
            LCD.WriteLine("Backwards");
        }
        else if (currentPowerMode == STOP)
        {
            LCD.WriteLine("Stop");
        }





        LCD.Write("Value of Light = ");

        //COMMENT OUT THIS LINE IF YOU DON'T WANT IT
        LCD.WriteLine(decisionLight);

        //Blue = 0.367
        //Red = 0.164
        //Threshold = 0.265

        if (decisionLight < 0.265)
        {
            LCD.WriteLine("Red");
        }
        else
        {
            LCD.WriteLine("Blue");
        }


        numOfDisplays++;
    }



    //potential for freezing in CBcorrective area
    //down here, middleButton escape still works?
    cleaner.update();
    //cleaner.update() and the methods in RPScleaner shouldn't call logDataStuffs()
    //because that would result in an infinite loop


    //milliCounter++;
}




void SetPowerStraight() {
    currentPowerMode = STRAIGHT;
    leftPowerMode = leftPower;
    rightPowerMode = rightPower;

    rMotor.SetPercent(rightPower);
    lMotor.SetPercent(-1 * leftPower);
}
void SetPowerLeft() {
    currentPowerMode = LEFT;
    leftPowerMode = leftPower;
    rightPowerMode = rightPower;

    rMotor.SetPercent(rightPower);
    lMotor.SetPercent(leftPower);
}
void SetPowerRight() {
    currentPowerMode = RIGHT;
    leftPowerMode = leftPower;
    rightPowerMode = rightPower;

    rMotor.SetPercent(-1 * rightPower);
    lMotor.SetPercent(-1 * leftPower);
}
void SetPowerBackwards() {
    currentPowerMode = BACKWARDS;
    leftPowerMode = leftPower;
    rightPowerMode = rightPower;

    rMotor.SetPercent(-1 * rightPower);
    lMotor.SetPercent(leftPower);
}
void SetPowerStop() {
    currentPowerMode = STOP;
    leftPowerMode = 0;
    rightPowerMode = 0;

    rMotor.Stop();
    lMotor.Stop();
}



void SetPowerStraight(int left, int right) {
    currentPowerMode = STRAIGHT;
    leftPowerMode = left;
    rightPowerMode = right;

    rMotor.SetPercent(rightPowerMode);
    lMotor.SetPercent(-1 * leftPowerMode);
}
void SetPowerLeft(int left, int right) {
    currentPowerMode = LEFT;
    leftPowerMode = left;
    rightPowerMode = right;

    rMotor.SetPercent(rightPowerMode);
    lMotor.SetPercent(leftPowerMode);
}
void SetPowerRight(int left, int right) {
    currentPowerMode = RIGHT;
    leftPowerMode = left;
    rightPowerMode = right;

    rMotor.SetPercent(-1 * rightPowerMode);
    lMotor.SetPercent(-1 * leftPowerMode);
}
void SetPowerBackwards(int left, int right) {
    currentPowerMode = BACKWARDS;
    leftPowerMode = left;
    rightPowerMode = right;

    rMotor.SetPercent(-1 * rightPowerMode);
    lMotor.SetPercent(leftPowerMode);
}

void driveProcess()
{
    //Option 4: Run

    double time;
    int pressOven;

    lMotor.Stop();
    rMotor.Stop();

    leftEncoder.SetThresholds(lowThresh, highThresh);

    lolServo.SetMin(servoMin);
    lolServo.SetMax(servoMax);

    //LCD.WriteLine(lolBattery.Voltage());

    if (configRPS)
    {
        TheRPS.InitializeMenu();
        TheRPS.Enable();
        pressOven = TheRPS.Oven();
    }

    if (configLightStart)
    {
        float value = 0.60;
        while (value > 0.30 && !buttons.MiddlePressed() )
        {
            value = CDS.Value();
            Sleep(.10);

            LCD.WriteLine(value);
        }
    }

    if (configCourseTimer)
    {
        time = TimeNow();
    }
    courseStartTime = TimeNow();
    numOfDisplays = 0;


    //tempBefore();

    theLoop();

    //tempAfter();

    if (configRPS)
    {
        TheRPS.Disable();

        LCD.Write("Oven Presses: ");
        LCD.WriteLine(pressOven);
    }

    if (configCourseTimer)
    {
        time = TimeNow() - time;
        LCD.Write("Time for run: ");
        LCD.WriteLine(time);
    }

    LCD.Write("Voltage: ");
    LCD.WriteLine(lolBattery.Voltage());

    LCD.WriteLine("Press Middle Button");
    while( !buttons.MiddlePressed() )
    {
        //nothing
    }

    lMotor.Stop();
    rMotor.Stop();
}




void theLoop()
{


    TypeEnum tempType;

    for (currentMove = 0; currentMove < 144; currentMove++)
    {
        tempType = mTracker.tracker[currentMove].getDataType();

        if (tempType == tInt)
        {
            mTracker.tracker[currentMove].perform_iMovement();
        }
        else if (tempType == tFloat)
        {
            mTracker.tracker[currentMove].perform_fMovement();
        }
        else if (tempType == tDouble)
        {
            mTracker.tracker[currentMove].perform_dMovement();
        }
        else if (tempType == tVoid)
        {
            mTracker.tracker[currentMove].perform_vMovement();
        }
    }

    //AT END, POTENTIAL TO EXIT THE RUN AND REBOOT
}




void PrintInt(int value)
{
    LCD.Write("Int: ");
    LCD.WriteLine(value);

    Sleep(1.0);
}

void PrintFloat(float value)
{
    LCD.Write("Float: ");
    LCD.WriteLine(value);

    Sleep(1.0);
}

void PrintDouble(double value)
{
    LCD.Write("Double: ");
    LCD.WriteLine(value);

    Sleep(1.0);
}

void PrintVoid()
{
    LCD.Write("Void.");

    Sleep(1.0);
}












