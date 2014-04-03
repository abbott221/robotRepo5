


#include "RPSclasses.h"



//************************************************
//*                                              *
//*           BEGIN RPSinfo CLASS                *
//*                                              *
//************************************************



RPSinfo::RPSinfo()
{
    expected;
    //expectedDisplaced;

    loggedStart;
    loggedStartPrime;

    loggedEnd;
    loggedEndPrime;

    RPSisWorking = true;
    RPSforMove = true;
    correctionOccurred = false;
}


struct set RPSinfo::getExpected() {
    return expected;
}
//struct set RPSinfo::getExpectedDisplaced() {
//    return expectedDisplaced;
//}

struct set RPSinfo::getStart() {
    return loggedStart;
}
struct set RPSinfo::getStartPrime() {
    return loggedStartPrime;
}

struct set RPSinfo::getEnd() {
    return loggedEnd;
}
struct set RPSinfo::getEndPrime() {
    return loggedEndPrime;
}

bool RPSinfo::getRPSisWorking() {
    return RPSisWorking;
}
bool RPSinfo::getRPSforMove() {
    return RPSforMove;
}
bool RPSinfo::getCorrectionOccurred() {
    return correctionOccurred;
}




void RPSinfo::setExpected(struct set exp) {
    expected = exp;
}
void RPSinfo::setExpected(float dX, float dY, float dHead)
{
    expected.X = dX;
    expected.Y = dY;
    expected.Head = dHead;
}
//void RPSinfo::setExpectedDisplaced(struct set expDisplaced) {
//    expectedDisplaced = expDisplaced;
//}

void RPSinfo::setStart(struct set logStart) {
    loggedStart = logStart;
}
void RPSinfo::setStartPrime(struct set logStartPrime)
{
    loggedStartPrime = logStartPrime;
}

void RPSinfo::setEnd(struct set logEnd)
{
    loggedEnd = logEnd;
}
void RPSinfo::setEndPrime(struct set logEndPrime)
{
    loggedEndPrime = logEndPrime;
}

void RPSinfo::setRPSisWorking(bool value) {
    RPSisWorking = value;
}
void RPSinfo::setRPSforMove(bool value) {
    RPSforMove = value;
}
void RPSinfo::setCorrectionOccurred(bool value) {
    correctionOccurred = value;
}















