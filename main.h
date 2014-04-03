#ifndef MAIN_H
#define MAIN_H



//#include <FEHLCD.h>
//#include <FEHIO.h>
//#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
//#include <FEHWONKA.h>
#include <FEHBattery.h>



//enums
#include "commonDependencies.h"









#include "drive/drive.h"

#include "RPS/RPSclasses.h"

#include "classes/classes.h"

#include "setup/menuSetup.h"

#include "other.h"

//#include "RPS/RPSclasses.h"







extern int leftPower;
extern int rightPower;

extern int tempLeftPower;
extern int tempRightPower;

extern int servoMin;
extern int servoMax;

extern float lowThresh;
extern float highThresh;

extern float optoThresh;

extern float bLineDifThresh;
extern float yLineDifThresh;
extern float leftOptoThresh;
extern float rightOptoThresh;
extern float midOptoThresh;

extern bool configLightStart;
extern bool configCourseTimer;
extern bool configDelay;
extern bool configRPS;

extern double displayRate;

extern double courseStartTime;

extern int numOfDisplays;


extern int leftPowerMode;
extern int rightPowerMode;

extern float decisionLight;





//struct set leftCorner;





extern FEHMotor lMotor;
extern FEHMotor rMotor;

extern ButtonBoard buttons;
extern FEHEncoder  leftEncoder;
extern FEHEncoder  rightEncoder;

extern AnalogInputPin CDS;

extern DigitalInputPin Micro1;
extern DigitalInputPin Micro2;

extern AnalogInputPin optoLeft;
extern AnalogInputPin optoMid;
extern AnalogInputPin optoRight;

//extern FEHWONKA TheRPS;
extern FEHServo lolServo;
extern FEHBattery lolBattery;



void MainMenuCall();
void ConfigureMenuCall();



#endif // MAIN_H
