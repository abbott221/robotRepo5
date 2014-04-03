


#include "drive.h"





void DriveForTime(float time)
{

    rMotor.SetPercent(80);
    lMotor.SetPercent(-1 * 80);

    float startTime = TimeNow();
    float dTime = 0.0;
    while( dTime < time )
    {
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}

void TurnLeftForTime(float time)
{
    rMotor.SetPercent(80);
    lMotor.SetPercent(80);

    float startTime = TimeNow();
    float dTime = 0.0;
    while( dTime < time)
    {
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}

void TurnRightForTime(float time)
{
    rMotor.SetPercent(-1 * 80);
    lMotor.SetPercent(-1 * 80);

    float startTime = TimeNow();
    float dTime = 0.0;
    while( dTime < time)
    {
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}



void BackwardsForTime(float time)
{
    rMotor.SetPercent(-1 * 80);
    lMotor.SetPercent(80);

    float startTime = TimeNow();
    float dTime = 0.0;
    while( dTime < time)
    {
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}



//METHOD 18
void Pause(double time)
{
    SetPowerStop();

    //rMotor.Stop();
    //lMotor.Stop();

    //Sleep(time);

    double startTime = TimeNow();
    double dTime = 0.0;
    while( dTime < time )
    {
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}








