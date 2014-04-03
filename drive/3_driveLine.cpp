

#include "drive.h"



//void ChangeOptoThreshold(double optoThresh);
//void FollowBlackLine(double goThisLong);
//void FollowLightLine(double goThisLong);
//void unFollowBlackLine(double goThisLong);
//void unFollowLightLine(double goThisLong);

//void GetOptoThresh();
//void BlackLineFollow(double time);
//void YellowLineFollow(double time);



//METHOD 12
void ChangeOptoThreshold(double thresh)
{
    optoThresh = thresh;
}


//METHOD 9
void FollowBlackLine(double goThisLong)
{
    lMotor.SetPercent(-1 * 60);
    rMotor.SetPercent(60);


    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if (optoMid.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }
        else if (optoRight.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 5);
            rMotor.SetPercent(75);
        }
        else if (optoLeft.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 75);
            rMotor.SetPercent(5);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}

//METHOD 10
void FollowLightLine(double goThisLong)
{
    lMotor.SetPercent(-1 * 60);
    rMotor.SetPercent(60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if (optoMid.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }
        else if (optoRight.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 75);
            rMotor.SetPercent(5);
        }
        else if (optoLeft.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 5);
            rMotor.SetPercent(75);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}



//METHOD 16
void unFollowBlackLine(double goThisLong)
{
    lMotor.SetPercent(60);
    rMotor.SetPercent(-1 * 60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if (optoMid.Value() > optoThresh)
        {
            lMotor.SetPercent(60);
            rMotor.SetPercent(-1 * 60);
        }
        else if (optoRight.Value() > optoThresh)
        {
            lMotor.SetPercent(5);
            rMotor.SetPercent(-1 * 75);
        }
        else if (optoLeft.Value() > optoThresh)
        {
            lMotor.SetPercent(75);
            rMotor.SetPercent(-1 * 5);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}

//METHOD 17
void unFollowLightLine(double goThisLong)
{
    lMotor.SetPercent(60);
    rMotor.SetPercent(-1 * 60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if (optoMid.Value() > optoThresh)
        {
            lMotor.SetPercent(60);
            rMotor.SetPercent(-1 * 60);
        }
        else if (optoRight.Value() > optoThresh)
        {
            lMotor.SetPercent(75);
            rMotor.SetPercent(-1 * 5);
        }
        else if (optoLeft.Value() > optoThresh)
        {
            lMotor.SetPercent(5);
            rMotor.SetPercent(-1 * 75);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}



//METHOD 20
void GetOptoThresh(){
    double leftAverage = 0.0;
    double rightAverage = 0.0;
    double midAverage = 0.0;

    for(int i = 0; i < 100 ; i++){
        leftAverage += optoLeft.Value();
        rightAverage += optoRight.Value();
        midAverage += optoMid.Value();
    }
    leftOptoThresh = leftAverage/100;
    rightOptoThresh = rightAverage/100;
    midOptoThresh = midAverage/100;

}


//METHOD  21
void BlackLineFollow(double time){
    lMotor.SetPercent(60);
    rMotor.SetPercent(-1 * 60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while(dTime < time){
        if(myAbsolute(midOptoThresh-optoMid.Value())>= bLineDifThresh){
            lMotor.SetPercent(60);
            rMotor.SetPercent(-1 * 60);

        }
        else if (myAbsolute(rightOptoThresh-optoRight.Value())>= bLineDifThresh){
            lMotor.SetPercent(75);
            rMotor.SetPercent(-1 * 5);


    }
        else if(myAbsolute(leftOptoThresh-optoLeft.Value())>= bLineDifThresh){
            lMotor.SetPercent(5);
            rMotor.SetPercent(-1 * 75);

        }
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }
    rMotor.Stop();
    lMotor.Stop();

}

//METHOD 22
void YellowLineFollow(double time){
    lMotor.SetPercent(60);
    rMotor.SetPercent(-1 * 60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while(dTime < time){
        if(myAbsolute(midOptoThresh-optoMid.Value())>= yLineDifThresh){
            lMotor.SetPercent(60);
            rMotor.SetPercent(-1 * 60);

        }
        else if (myAbsolute(rightOptoThresh-optoRight.Value())>= yLineDifThresh){
            lMotor.SetPercent(75);
            rMotor.SetPercent(-1 * 5);


    }
        else if(myAbsolute(leftOptoThresh-optoLeft.Value())>= yLineDifThresh){
            lMotor.SetPercent(5);
            rMotor.SetPercent(-1 * 75);

        }
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }
    rMotor.Stop();
    lMotor.Stop();

}




//METHOD 23
void JeffBlackLine(double goThisLong)
{
    lMotor.SetPercent(-1 * 60);
    rMotor.SetPercent(60);


    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if ((optoMid.Value () -.6) > optoThresh)
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }
        else if ((optoRight.Value() + 1.6) > optoThresh)
        {
            lMotor.SetPercent(-1 * 75);
            rMotor.SetPercent(5);
        }
        else if (optoLeft.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 75);
            rMotor.SetPercent(5);
        }
        //go straight if nothing?
        else
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}

//METHOD 24
void JeffLightLine(double goThisLong)
{
    lMotor.SetPercent(-1 * 60);
    rMotor.SetPercent(60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if ((optoMid.Value() -1.1)< optoThresh)
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }
        else if ((optoRight.Value()- .06) < optoThresh)
        {
            lMotor.SetPercent(-1 * 75);
            rMotor.SetPercent(5);
        }
        else if (optoLeft.Value() < optoThresh)
        {
            lMotor.SetPercent(-1 * 5);
            rMotor.SetPercent(75);
        }
        //go straight if nothing?
        else
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}













