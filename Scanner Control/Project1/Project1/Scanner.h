#pragma once

//Function Definitions

int Scan_Shutdown(void); //Function to shutdown the motors
int Scan_LimSwitchStatus(int NumController, int *CCWLimStatus, int *CWLimStatus); // Function to obtain limit switch status
int Scan_MoveInSteps(int NumController, int PosInSteps, int ReturnImmediate); //move motor desired number of steps
int Scan_CurrentPosInSteps(int NumController, int *Steps); //Obtain current position of motor in steps

int Scan_Init(void);
int Scan_GoHome(int NumController);
int set_home(int NumController);
int set_accel_and_velocity(int NumController, double accel, double vel);

//These two functions will just be conversions from the Step Functions to obtain info in inches 
int Scan_MoveInInches(int NumController, int *PosInches, int); //move motor desired number of Inches
int Scan_CurrentPosInInches(int NumController, int *Steps); //Obtain current position of motor in Inches


