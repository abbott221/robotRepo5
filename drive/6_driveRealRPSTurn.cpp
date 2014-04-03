


#include "drive.h"






//METHOD 60
void TurnLeftPast180()
{
    float currentAngle = TheRPS.Heading();

    float dAngle = 180.0 - currentAngle;

    double travel = 0.0;
    travel = (dAngle / 180.0) * 10.0;

    EncLeft(travel);

}

//METHOD 61
void TurnRightPast0()
{
    float currentAngle = TheRPS.Heading();

    float dAngle = currentAngle;

    double travel = 0.0;
    travel = (dAngle / 180.0) * 10.0;

    EncRight(travel);

}


//METHOD 62
void TurnLeftToAngle(double angle)
{
    RelativeTurnLeft(angle);
}

//METHOD 63
void TurnRightToAngle(double angle)
{
    RelativeTurnRight(angle);
}

//METHOD 64
void UnsafeTurnToAngle(double angle)
{
    //float currentAngle = TheRPS.Heading();
    float currentAngle = cleaner.getCurrentHead();

    float targetAngle = (float) angle;

    float dAngle = myAbsolute(currentAngle - targetAngle);

    double travel = 0.0;
    travel = (dAngle / 180.0) * 10.0;




    //need to turn right to the angle
    if ( targetAngle > currentAngle )
    {
        SlowEncLeft(travel, 40);
    }
    else
    {
        SlowEncRight(travel, 40);
    }





    //RelativeTurnRight(angle);
}








//METHOD 80
void RelativeTurnLeft(double angle)
{
    double travel = 0.0;

    travel = (angle / 180.0) * 10.0;

    EncLeft(travel);
}

//METHOD 81
void RelativeTurnRight(double angle)
{
    double travel = 0.0;

    travel = (angle / 180.0) * 10.0;

    EncRight(travel);
}






//METHOD not used
void SlowEncLeft(double distance, int lowPower)
{
    SetPowerLeft(lowPower, lowPower);

    //rMotor.SetPercent(rightPower);
    //lMotor.SetPercent(leftPower);


    while (rightEncoder.Counts() <= ((distance * 36) / (2.75 * 3.1415)))
    {
        if(leftEncoder.Counts() - rightEncoder.Counts() > 2){

              rMotor.SetPercent(lowPower+6);

              lMotor.SetPercent(lowPower);
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() < -2){

              rMotor.SetPercent(lowPower);

              lMotor.SetPercent(lowPower+4);

        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() > -2 && leftEncoder.Counts() - rightEncoder.Counts() < 2 ){

              rMotor.SetPercent(lowPower);

              lMotor.SetPercent(lowPower);
        }
        logDataStuffs();
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}


//METHOD not used
void SlowEncRight(double distance, int lowPower)
{
    SetPowerRight(lowPower, lowPower);

    //rMotor.SetPercent(-1 * rightPower);
    //lMotor.SetPercent(-1* leftPower);

    while (rightEncoder.Counts() <= ((distance * 36) / (2.75 * 3.1415)))
    {
        if(leftEncoder.Counts() - rightEncoder.Counts() > 2){

             rMotor.SetPercent(-1 * (lowPower+6));

             lMotor.SetPercent(-1 *lowPower);
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() < -2){

             rMotor.SetPercent(-1 * lowPower);

             lMotor.SetPercent(-1 *(lowPower+4));

        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() > -2 && leftEncoder.Counts() - rightEncoder.Counts() < 2 ){

             rMotor.SetPercent(-1 * lowPower);

             lMotor.SetPercent(-1 *lowPower);
        }
        logDataStuffs();
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}













