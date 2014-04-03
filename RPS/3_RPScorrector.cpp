

#include "RPSclasses.h"

#include "../classes/classes.h"
//#include "../commonDependencies.h"
#include "../other.h"


//************************************************
//*                                              *
//*         BEGIN RPScorrector CLASS             *
//*                                              *
//************************************************


RPScorrector::RPScorrector()
{
    coordTolerance = 2.0;
    angleTolerance = 10.0;

    expected;
    reality;
}


void RPScorrector::premove()
{
    cleaner.update();
    reality = cleaner.getDisplaced();
    expected = mTracker.tracker[currentMove].moveInfo.getExpected();
    mTracker.tracker[currentMove].moveInfo.setStart(reality);
    angleCorrection();

    cleaner.update();
    reality = cleaner.getDisplaced();
    mTracker.tracker[currentMove].moveInfo.setStartPrime(reality);
}


void RPScorrector::postmove()
{
    cleaner.update();
    reality = cleaner.getDisplaced();
    expected = mTracker.tracker[currentMove + 1].moveInfo.getExpected();
    mTracker.tracker[currentMove].moveInfo.setEnd(reality);

    //endMoveCorrection();

    cleaner.update();
    reality = cleaner.getDisplaced();
    mTracker.tracker[currentMove].moveInfo.setEndPrime(reality);
}



void RPScorrector::angleCorrection()
{
    float diff = myAbsolute(reality.Head - expected.Head);
    diff = cleanAngle(diff);
    if (diff > angleTolerance)
    {
        if (myAbsolute(180.0 - diff) > angleTolerance)
        {
            //then the displacement is across 0 or 180
        }
        else
        {

            if ( mTracker.tracker[currentMove].moveInfo.getRPSisWorking() && mTracker.tracker[currentMove].moveInfo.getRPSforMove() )
            {

                mTracker.tracker[currentMove].moveInfo.setCorrectionOccurred(true);

                //if I don't need to cross the 0/180
                if ( diff < myAbsolute(180.0 - diff) )
                {
                    //UnsafeTurnToAngle(expected.Head);
                    //UnsafeTurnToAngle(expected.Head);
                }
                else
                {
                    if (reality.Head > 90.0)
                    {
                        TurnLeftPast180();
                    }
                    else
                    {
                        TurnRightPast0();
                    }

                    //UnsafeTurnToAngle(expected.Head);
                    //UnsafeTurnToAngle(expected.Head);
                }

                UnsafeTurnToAngle(expected.Head);
                UnsafeTurnToAngle(expected.Head);

            } //if RPS is working and RPS is on for this move

        }
    }

    //struct set temp = cleaner.getDisplaced();
    //mTracker.tracker[currentMove].moveInfo.setStart(temp);
}








