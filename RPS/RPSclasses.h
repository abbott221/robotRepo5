#ifndef RPSCLASSES_H
#define RPSCLASSES_H


#include "../commonDependencies.h"



//based on killed struct
struct set
{
    float X;
    float Y;
    float Head;
};



//based on killed struct
class RPSinfo
{
public:
    RPSinfo();

    struct set getExpected();
    //struct set getExpectedDisplaced();

    struct set getStart();
    struct set getStartPrime();

    struct set getEnd();
    struct set getEndPrime();

    bool getRPSisWorking();
    bool getRPSforMove();
    bool getCorrectionOccurred();



    void setExpected(struct set exp);
    void setExpected(float dX, float dY, float dHead);
    //void setExpectedDisplaced(struct set exp);

    void setStart(struct set logStart);
    void setStartPrime(struct set logStartPrime);

    void setEnd(struct set logEnd);
    void setEndPrime(struct set logEndPrime);

    void setRPSisWorking(bool value);
    void setRPSforMove(bool value);
    void setCorrectionOccurred(bool value);

private:
    struct set expected;
    //struct set expectedDisplaced;

    struct set loggedStart;
    struct set loggedStartPrime;

    struct set loggedEnd;
    struct set loggedEndPrime;

    bool RPSisWorking;
    bool RPSforMove;
    bool correctionOccurred;
};












class RPScleaner
{
    public:
        RPScleaner();

        //set initial move values
        //void initiateMoveData();
        //set current values
        //stalls out after x time?
        //continues to scan until values aren't 0,0,0
        //SETTER method
        void update();

        void mainMenuUpdate();

        //DO INTERNAL CALLS NEED [THIS.]METHOD();???

        //called internally, avoid externally
        //checks for 0,0,0
        bool currentValuesAreLegit();


        //real
//        float getRealX();
//        float getRealY();
//        float getRealHead();


        //displaced
        float getCurrentX();
        float getCurrentY();
        float getCurrentHead();


        struct set getReal();
        struct set getDisplaced();
        struct set getDisplacement();

        void setReal(struct set dReal);
        void setDisplaced(struct set dDisplaced);

        //ONLY SHOULD BE CALLED IN MAIN MENU CALIBRATION
        void setDisplacement(struct set dDisplacement);


    private:

        //bool RPSisWorking;
        //bool RPSforMove;

        //bool correctionOccurred;

        //bool above180;
        //bool below0;

        struct set real;
        struct set displaced;
        struct set displacement;

//        float realX;
//        float realY;
//        float realHead;
//        float displacedX;
//        float displacedY;
//        float displacedHead;
//        float displacementX;
//        float displacementY;
//        float displacementHead;
};


class RPScorrector
{
public:
    RPScorrector();
    void premove();
    //midmove?
    void postmove();



    void angleCorrection();

private:
    float coordTolerance;
    float angleTolerance;

    struct set expected;
    struct set reality;
};








extern RPScleaner cleaner;

extern RPScorrector corrector;








#endif // RPSCLASSES_H
