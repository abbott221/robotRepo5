

#include "drive.h"


//METHOD 4
void EncForward(double distance)
{
    SetPowerStraight();

    //rMotor.SetPercent(rightPower);
    //lMotor.SetPercent(-1 * leftPower);

    while (rightEncoder.Counts() <= ((distance * 36) / (2.75 * 3.1415)))
    {
        if(leftEncoder.Counts() - rightEncoder.Counts() > 2){

            rMotor.SetPercent(rightPower+6);

            lMotor.SetPercent(-1 * leftPower);
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() < -2){
            rMotor.SetPercent(rightPower);

            lMotor.SetPercent(-1 * (leftPower+4));

        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() > -2 && leftEncoder.Counts() - rightEncoder.Counts() < 2 ){

            rMotor.SetPercent(rightPower);

            lMotor.SetPercent(-1 * leftPower);
        }
        logDataStuffs();
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}


//METHOD 5
void EncLeft(double distance)
{
    SetPowerLeft();

    //rMotor.SetPercent(rightPower);
    //lMotor.SetPercent(leftPower);


    while (rightEncoder.Counts() <= ((distance * 36) / (2.75 * 3.1415)))
    {
        if(leftEncoder.Counts() - rightEncoder.Counts() > 2){

              rMotor.SetPercent(rightPower+6);

              lMotor.SetPercent(leftPower);
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() < -2){

              rMotor.SetPercent(rightPower);

              lMotor.SetPercent(leftPower+4);

        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() > -2 && leftEncoder.Counts() - rightEncoder.Counts() < 2 ){

              rMotor.SetPercent(rightPower);

              lMotor.SetPercent(leftPower);
        }
        logDataStuffs();
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}


//METHOD 6
void EncRight(double distance)
{
    SetPowerRight();

    //rMotor.SetPercent(-1 * rightPower);
    //lMotor.SetPercent(-1* leftPower);

    while (rightEncoder.Counts() <= ((distance * 36) / (2.75 * 3.1415)))
    {
        if(leftEncoder.Counts() - rightEncoder.Counts() > 2){

             rMotor.SetPercent(-1 * (rightPower+6));

             lMotor.SetPercent(-1 *leftPower);
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() < -2){

             rMotor.SetPercent(-1 * rightPower);

             lMotor.SetPercent(-1 *(leftPower+4));

        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() > -2 && leftEncoder.Counts() - rightEncoder.Counts() < 2 ){

             rMotor.SetPercent(-1 * rightPower);

             lMotor.SetPercent(-1 *leftPower);
        }
        logDataStuffs();
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}



//METHOD 7
void EncBackward(double distance)
{
    SetPowerBackwards();

    //rMotor.SetPercent(-1 * rightPower);
    //lMotor.SetPercent(leftPower);

    while (rightEncoder.Counts() <= ((distance * 36) / (2.75 * 3.1415)))
    {
        if(leftEncoder.Counts() - rightEncoder.Counts() > 2){

             rMotor.SetPercent(-1 * (rightPower+6));

             lMotor.SetPercent(leftPower);
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() < -2){

             rMotor.SetPercent(-1 * rightPower);

             lMotor.SetPercent(leftPower+4);

        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() > -2 && leftEncoder.Counts() - rightEncoder.Counts() < 2 ){

             rMotor.SetPercent(-1 * rightPower);

             lMotor.SetPercent(leftPower);
        }
        logDataStuffs();
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}

