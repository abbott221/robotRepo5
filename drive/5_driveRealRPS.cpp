


#include "drive.h"








//METHOD 50
void MoveToRealX(double givenX)
{
    float targetX = (float) givenX;

    //float currentX = TheRPS.X();
    float currentX = cleaner.getCurrentX();

    double travel = 0.0;

    if ( targetX < currentX )
    {
        travel = currentX - targetX;
    }
    else
    {
        travel = targetX - currentX;
    }



    /*********CORRECTIVE BEHAVIOUR************/
    //travel = PerformComparison(travel);



    EncForward(travel);

}

//METHOD 51
void MoveToRealY(double givenY)
{
    float targetY = (float) givenY;

    //float currentY = TheRPS.Y();
    float currentY = cleaner.getCurrentY();

    double travel = 0.0;

    if ( targetY < currentY )
    {
        travel = currentY - targetY;
    }
    else
    {
        travel = targetY - currentY;
    }





    /*********CORRECTIVE BEHAVIOUR************/
    //travel = PerformComparison(travel);





    EncForward(travel);
}




////METHOD 52
//void CheckRealX(double givenX)
//{

//    float targetX = (float) givenX;

//    float currentX = TheRPS.X();

//    if ( myAbsolute(targetX - currentX) > RPStolerance )
//    {
//        //corrective behaviour
//        //fillerForActionTaken();
//    }


//}

////METHOD 53
//void CheckRealY(double givenY)
//{

//    float targetY = (float) givenY;

//    float currentY = TheRPS.Y();

//    if ( myAbsolute(targetY - currentY) > RPStolerance )
//    {
//        //corrective behaviour
//        //fillerForActionTaken();
//    }


//}






