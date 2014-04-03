

#include "classes.h"



//************************************************
//*                                              *
//*          BEGIN Operation CLASS               *
//*                                              *
//************************************************

Operation::Operation()
{
    iPtr;
    fPtr;
    dPtr;
    vPtr;

    dataType = tVoid;
}




void Operation::set_iOperation( void ( *intPtr ) (int iValue))
{
    iPtr = intPtr;

    dataType = tInt;
}

void Operation::set_fOperation( void ( *floatPtr ) (float fValue))
{
    fPtr = floatPtr;

    dataType = tFloat;
}

void Operation::set_dOperation( void ( *doublePtr ) (double dValue))
{
    dPtr = doublePtr;

    dataType = tDouble;
}

void Operation::set_vOperation( void ( *voidPtr ) ())
{
    vPtr = voidPtr;

    dataType = tVoid;
}




TypeEnum Operation::getDataType()
{
    return dataType;
}




void Operation::perform_iOperation(int iValue)
{
    (*iPtr)(iValue);
}

void Operation::perform_fOperation(float fValue)
{
    (*fPtr)(fValue);
}

void Operation::perform_dOperation(double dValue)
{
    (*dPtr)(dValue);
}

void Operation::perform_vOperation()
{
    (*vPtr)();
}







//************************************************
//*                                              *
//*       BEGIN OperationTracker CLASS           *
//*                                              *
//************************************************

OperationTracker::OperationTracker(int size)
{
    trackerSize = size;
    tracker = new Operation[size];
}




void OperationTracker::add_iOperation(int callID, void ( *intPtr ) (int iValue) )
{
    tracker[callID].set_iOperation( (*intPtr) );
}

void OperationTracker::add_fOperation(int callID, void ( *floatPtr ) (float fValue) )
{
    tracker[callID].set_fOperation( (*floatPtr) );
}

void OperationTracker::add_dOperation(int callID, void ( *doublePtr ) (double dValue) )
{
    tracker[callID].set_dOperation( (*doublePtr) );
}

void OperationTracker::add_vOperation(int callID, void ( *voidPtr ) () )
{
    tracker[callID].set_vOperation( (*voidPtr) );
}


int OperationTracker::getTrackerSize()
{
    return trackerSize;
}

















