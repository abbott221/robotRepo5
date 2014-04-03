


#include "RPSclasses.h"
#include "../classes/classes.h"
#include "../other.h"







//************************************************
//*                                              *
//*          BEGIN RPScleaner CLASS              *
//*                                              *
//************************************************


//"CONSTRUCTOR" METHODS HERE
RPScleaner::RPScleaner()
{
    //above180 = false;
    //below0 = false;

    real;
    displaced;
    displacement;

    //displacement.X = 0.0;
    //displacement.Y = 0.0;
    //displacement.Head = 0.0;
}




void RPScleaner::update()
{
    float time = 0.010;

    /*
    if ( RPSisWorking )
    {
        time = 0.010;
    }
    else
    {
        time = 0.010;
    }
    /**/

    float startTime = TimeNow();
    float dTime = 0.0;
    do {
        real.X = TheRPS.X();
        real.Y = TheRPS.Y();
        real.Head = TheRPS.Heading();

        dTime = TimeNow() - startTime;
    } while ( !currentValuesAreLegit() && (dTime < time) );
    //continue until we don't have 0,0,0


    if ( currentValuesAreLegit() )
    {
        mTracker.tracker[currentMove].moveInfo.setRPSisWorking(true);
    }
    else
    {
        mTracker.tracker[currentMove].moveInfo.setRPSisWorking(false);
    }



    //struct set tempExpected;
    //tempExpected = mTracker.tracker[currentMove].moveInfo.getExpected();

    //DISPLACEMENT SET AT START OF RUN
    //struct set tempDisplacement;
    //tempDisplacement.X = tempExpected.X - real.X;
    //tempDisplacement.Y = tempExpected.Y - real.Y;
    //tempDisplacement.Head = tempExpected.Head - real.Head;

    //setDisplacement(tempDisplacement);

    //struct set tempDisplaced;
    displaced.X = real.X + displacement.X;
    displaced.Y = real.Y + displacement.Y;
    displaced.Head = real.Head + displacement.Head;
    displaced.Head = cleanAngle(displaced.Head);
}




void RPScleaner::mainMenuUpdate()
{
    do {
        real.X = TheRPS.X();
        real.Y = TheRPS.Y();
        real.Head = TheRPS.Heading();
    } while ( !currentValuesAreLegit() && !buttons.MiddlePressed() );
    //continue until we don't have 0,0,0
}




bool RPScleaner::currentValuesAreLegit()
{
    bool returnThis = false;

    //check x =/= 0
    if (real.X > 0.0 || real.X < 0.0)
    {
        returnThis = true;
    }
    //check y =/= 0
    else if (real.Y > 0.0 || real.Y < 0.0)
    {
        returnThis = true;
    }
    //check angle =/= 0
    else if (real.Head > 0.0)
    {
        returnThis = true;
    }
    else
    {
        returnThis = false;
    }

    return returnThis;
}






float RPScleaner::getCurrentX()
{

    return displaced.X;
}
float RPScleaner::getCurrentY()
{
    return displaced.Y;
}
float RPScleaner::getCurrentHead()
{
    return displaced.Head;
}








struct set RPScleaner::getReal()
{
    return real;
}
struct set RPScleaner::getDisplaced()
{
    return displaced;
}
struct set RPScleaner::getDisplacement()
{
    return displacement;
}



void RPScleaner::setReal(struct set dReal)
{
    real.X = dReal.X;
    real.Y = dReal.Y;
    real.Head = dReal.Head;
}
void RPScleaner::setDisplaced(struct set dDisplaced)
{
    displaced.X = dDisplaced.X;
    displaced.Y = dDisplaced.Y;
    displaced.Head = dDisplaced.Head;
}
void RPScleaner::setDisplacement(struct set dDisplacement)
{
    displacement.X = dDisplacement.X;
    displacement.Y = dDisplacement.Y;
    displacement.Head = dDisplacement.Head;
}
















