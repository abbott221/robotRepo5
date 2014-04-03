#ifndef DRIVE_H
#define DRIVE_H



#include "../main.h"


void driveProcess();

void theLoop();


void logDataStuffs();

void SetPowerStraight();
void SetPowerLeft();
void SetPowerRight();
void SetPowerBackwards();
void SetPowerStop();

void SetPowerStraight(int left, int right);
void SetPowerLeft(int left, int right);
void SetPowerRight(int left, int right);
void SetPowerBackwards(int left, int right);

//TIMERS
void DriveForTime(float time);
void TurnLeftForTime(float time);
void TurnRightForTime(float time);
void BackwardsForTime(float time);
void Pause(double time);

//ENCODERS
void EncForward(double distance);
void EncLeft(double distance);
void EncRight(double distance);
void EncBackward(double distance);

//LINE FOLLOWERS
void ChangeOptoThreshold(double optoThresh);
void FollowBlackLine(double goThisLong);
void FollowLightLine(double goThisLong);
void unFollowBlackLine(double goThisLong);
void unFollowLightLine(double goThisLong);

void GetOptoThresh();
void BlackLineFollow(double time);
void YellowLineFollow(double time);
void JeffBlackLine(double goThisLong);
void JeffLightLine(double goThisLong);

//GENERAL
void SetServoDegree(int degrees);
void DisplayLightValue();
void FlyOverLightValue(double time);
void LightDecisionTurn(double distance);
//void SetCustomAction(int action);
void PushButton(); //METHOD 26
void Micro(double time); //METHOD 27

//REAL RPS
void MoveToRealX(double givenX);
void MoveToRealY(double givenY);
//void CheckRealX(double givenX);
//void CheckRealY(double givenY);

//REAL RPS TURN
void TurnLeftPast180();
void TurnRightPast0();
void TurnLeftToAngle(double angle);
void TurnRightToAngle(double angle);
void UnsafeTurnToAngle(double angle);
void RelativeTurnLeft(double angle);
void RelativeTurnRight(double angle);




void SlowEncLeft(double distance, int lowPower);
void SlowEncRight(double distance, int lowPower);




void PrintInt(int value);
void PrintFloat(float value);
void PrintDouble(double value);
void PrintVoid();





#endif // DRIVE_H
