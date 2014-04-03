#ifndef ENUMS_H
#define ENUMS_H



#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHWONKA.h>


typedef enum
{
    tString = 0,
    tInt,
    tFloat,
    tDouble,
    tVoid

    //opInt,
    //opFloat,
    //opDouble,
    //opVoid
} TypeEnum;

typedef enum
{
    STRAIGHT = 0,
    LEFT,
    RIGHT,
    BACKWARDS,
    STOP
} PMode;







extern int currentMove;







extern ButtonBoard buttons;
extern FEHWONKA TheRPS;








#endif // ENUMS_H
