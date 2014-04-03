

#include "drive.h"


//METHOD 8
void SetServoDegree(int degrees)
{

    //Sleep(500);

    double startTime = TimeNow();
    double dTime = 0.0;
    while( dTime < 0.5)
    {
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    lolServo.SetDegree(degrees);
}



//METHOD 13
void DisplayLightValue()
{
    double average = 0.0;
    for (int i = 0; i<100;i++)
    {
        average += CDS.Value();

        logDataStuffs();
        Sleep(1);
    }
    average = average / 100.0;

    LCD.Write("Value of Light = ");

    //COMMENT OUT THIS LINE IF YOU DON'T WANT IT
    LCD.WriteLine(average);

    //Blue = 0.367
    //Red = 0.164
    //Threshold = 0.265

    if (average < 0.265)
    {
        LCD.WriteLine("Red");
    }
    else
    {
        LCD.WriteLine("Blue");
    }
}

//METHOD 14
void FlyOverLightValue(double time)
{
    rMotor.SetPercent(50);
    lMotor.SetPercent(-1 * 50);

    double highest = 0.0;
    double newVal = 0.0;




    double startTime = TimeNow();
    double dTime = 0.0;
    while( dTime < time )
    {
        newVal = CDS.Value();
        if (newVal > highest)
        {
            highest = newVal;
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }







    //average = average / 100.0;

    LCD.Write("Value of Light = ");

    //COMMENT OUT THIS LINE IF YOU DON'T WANT IT
    LCD.WriteLine(highest);

    decisionLight = highest;

    //Blue = 0.367
    //Red = 0.164
    //Threshold = 0.265

    if (highest < 0.265)
    {
        LCD.WriteLine("Red");
    }
    else
    {
        LCD.WriteLine("Blue");
    }


    lMotor.Stop();
    rMotor.Stop();
}


//METHOD 19
void LightDecisionTurn(double distance)
{


    if (decisionLight < 0.265)
    {
        //LCD.WriteLine("Red");
        EncLeft(distance);
    }
    else
    {
        //LCD.WriteLine("Blue");
        EncRight(distance);
    }


}

/*
//METHOD 30
void SetCustomAction(int action)
{
    RPScustomAction = action;
}
*/


// METHOD 26
void PushButton(){
    int timesPushed = TheRPS.OvenPressed();
    int toPush = TheRPS.Oven();
    while(timesPushed < toPush){
        EncBackward(1.00);
        EncForward(1.00);
        timesPushed = TheRPS.OvenPressed();
    }
}

// METHOD 27
void Micro(double time){

    double startTime = TimeNow();
    double dTime = 0.0;

    while(dTime < time){

        EncBackward(.1);
        if(Micro1.Value() && Micro2.Value()){
            break;
        }


        logDataStuffs();
        dTime = TimeNow() - startTime;
    }
    rMotor.Stop();
    lMotor.Stop();
}





