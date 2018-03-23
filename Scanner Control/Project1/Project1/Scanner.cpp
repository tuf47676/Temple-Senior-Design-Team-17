//#include <stdio.h>
//#include "rs232.h"
//#include <use_ansi.h>
//#include <Windows.h>
//#include <libserialport.h>
//
//extern struct sp_port* comport;
//
//int timeout = 0;
//static double maxVelocity = 1.0; //This variable sets the max velocity of the motor in revolutions per second
//static double maxAcceleration = 0.5; //This variable sets the max acceleration of the motor in revolutions per second^2
//static double dHeightCal = 0.000390136121975;  // inches/step
//static double dWidthCal = 0.000389979983108;  // inches/step
//
//int Scan_Shutdown(void); //Function to shutdown the motors
//int Scan_LimSwitchStatus(int NumController, int *CCWLimStatus, int *CWLimStatus); // Function to obtain limit switch status
//int Scan_MoveInSteps(int NumController, int PosInSteps, int ReturnImmediate); //move motor desired number of steps
//int Scan_CurrentPosInSteps(int NumController, int *Steps); //Obtain current position of motor in steps
//
//int Scan_Init(void);
//int Scan_GoHome(int NumController);
//int set_home(int NumController);
//int set_accel_and_velocity(int NumController, double accel, double vel);
//
////This function sends the shutdown command
////<PortNum>ST1 is the command sytax
//int Scan_Shutdown(void) {
//
//	char cmd[64]; //Declare array for command 
//	sprintf(cmd, "ST1%c", 0x0D); //print command to the array
//	unsigned char *cmdbuffer = (unsigned char*)&cmd[0];
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//
//	return(0);
//}
//
////This function obtains a boolean for each of the limit switches
////Each motor has two limit switches, a CW and a CCW switch
////The <a>IS command returns an array with 9 indices of boolean values
////indicating different states, index[4] and [5] are regarding the limit switches
////Reply[4] contains the status of the CCW Limit Switch, Switches are Activated HIGH (1)
////Reply[5] contains the status of the CCW Limit Switch, Switches are Activated HIGH (1)
//int Scan_LimSwitchStatus(int NumController, int *CCWLimStatus, int *CWLimStatus) {
//
//	char cmd[64];
//	char reply[64];//Declare arrays for command, response
//	int status; //Declare integer for status
//	//double TimeOut = 0.1;
//
//	sprintf(cmd, "%dIS%c", NumController, 0x0D); 							
//	unsigned char *cmdbuffer = (unsigned char*)&cmd[0];
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//
//	status = sp_blocking_read(comport, reply, strlen(reply), timeout); //catch the reply of the ST command
//	sp_blocking_read(comport, reply, strlen(reply), timeout);
//	if (status < 0)
//	{
//		return(-1);
//	}
//
//	status = sp_blocking_read(comport, reply, strlen(reply), timeout); //catch the reply of the ST command
//	if (status < 0)
//	{
//		return(-1);
//	}
//
//	if (reply[4] == '0') { 
//		*CCWLimStatus = 0; //Switch is LOW
//	}
//	else if (reply[4] == '1') {
//		*CCWLimStatus = 1; //Switch is HIGH
//	}
//	else {
//		*CCWLimStatus = -1; //Else Switch is NEITHER
//	}
//
//	if (reply[5] == '0') {
//		*CWLimStatus = 0; //Switch is LOW
//	}
//	else if (reply[5] == '1') {
//		*CWLimStatus = 1; //Switch is HIGH
//	}
//	else {
//		*CWLimStatus = -1; //Else Switch is NEITHER
//	}
//}
//
////This function sends the distance in steps to the controller 
////<PortNum>D<NumController><NumSteps> - is the sytax for the command
////The Go command is then executed to move the motors the number of steps specified by the Distance command
//int Scan_MoveInSteps(int NumController, int PosInSteps, int ReturnImmediate) {
//	int status;
//	char cmd[64];
//	unsigned char *cmdbuffer = (unsigned char*)&cmd[0];
//	char reply[64];
//	int ctr = 0;
//	int Delay = 0.25;
//	int TimeLimGoToHome = 40;
//	int Iterations = TimeLimGoToHome/ Delay;
//
//	Sleep(250);
//
//	sp_flush(comport, SP_BUF_INPUT); //flush input buffers
//
//	sprintf(cmd, "%dD%d%c", NumController, PosInSteps, 0x0D);
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//	status = sp_blocking_read(comport, reply, strlen(reply), timeout);
//
//	sprintf(cmd, "%dG%c", NumController, 0x0D);
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//	status = sp_blocking_read(comport, reply, strlen(reply), timeout);
//
//	if (ReturnImmediate) {
//		return(0);
//	}
//
//	for (ctr < 0; ctr < Iterations; ctr++) {
//
//		sprintf(cmd, "%dR", NumController); //<a>R command- Request Index Status
//		sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//
//		sp_blocking_read(comport, reply, strlen(reply), timeout);
//		sp_blocking_read(comport, reply, strlen(reply), timeout);
//
//
//		Sleep(250);
//	}
//
//	Scan_Shutdown();
//}
//
////This function obtains the current step count of the motor
////<a>PR command- Absolute Position Report
//int Scan_CurrentPosInSteps(int NumController, int *Steps) {
//	char cmd[64];
//	char reply[64];
//	int status;
//	int TimeOut = 0.25; 
//
//	Sleep(250);
//	sp_flush(comport, SP_BUF_BOTH);
//
//	sprintf(cmd, "%dPR%c", NumController, 0x0D); //<a>PR command- Absolute Position Report
//	
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//	
//	status = sp_blocking_read(comport, reply, strlen(reply), timeout);
//	if (status < 0) {
//		return(-1);
//	}
//
//	status = sp_blocking_read(comport, reply, strlen(reply), timeout);
//	if (status < 0) {
//		return(-1);
//	}
//
//	
//	sscanf(reply, "%d", Steps);
//}
//
//int Scan_Init(void) {
//	int status;
//	int NumController;
//	char cmd[64];
//	unsigned char *cmdbuffer = (unsigned char*)&cmd[0];
//
//	sprintf(cmd, "1SSA0%c2SSA0%c", 0x0D, 0x0D);
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//	Sleep(2000);
//
//	for (NumController = 1; NumController <= 2; NumController++) {
//		sprintf(cmd, "%dZ%c", NumController, 0x0D);
//		sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//		Sleep(2000);
//
//		sprintf(cmd, "%dST0%c", NumController, 0x0D);
//		sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//
//		status = Scan_GoHome(NumController);
//		if (status != 0) {
//			return(-1);
//		}
//
//		status = set_home(NumController);
//	}
//
//	return(0);
//}
//
//int Scan_GoHome(int NumController) {
//	int status;
//	char cmd[64];
//	unsigned char *cmdbuffer = (unsigned char*)&cmd[0];
//	int count;
//	int CCWLimStatus;
//	int CWLimStatus;
//	double TimeLimGoToHome = 30;	//seconds
//	double Delay = 0.1;			//seconds
//	int Iterations = TimeLimGoToHome / Delay;
//
//	set_accel_and_velocity(NumController, 0.5, 0.5);
//
//	sprintf(cmd, "%dMC%c", NumController, 0x0D);
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//	sprintf(cmd, "%dH-%c", NumController, 0x0D);
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//	sprintf(cmd, "%dG%c", NumController, 0x0D);
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//
//	for (count = 0; count < Iterations; count++) {
//		//process system events
//		status = Scan_LimSwitchStatus(NumController, &CCWLimStatus, &CWLimStatus);
//
//		if (CCWLimStatus == 1) {
//			return(0);
//		}
//
//		Sleep(100); //delay
//	}
//
//	//timeout
//	Scan_Shutdown();
//	return(-1);
//}
//
//int set_home(int NumController) {
//	char cmd[64];
//	unsigned char *cmdbuffer = (unsigned char*)&cmd[0];
//
//	//set position index counter to zero
//	sprintf(cmd, "%dPZ%c", NumController, 0x0D);
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//
//	//set indexer to mode normal
//	sprintf(cmd, "%dMN%c%dMPA%c", NumController, 0x0D, NumController, 0x0D);
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//
//	//set acceleration and velocity
//	set_accel_and_velocity(NumController, maxAcceleration, maxVelocity);
//
//	//move slightly off limit switch
//	Scan_MoveInSteps(NumController, 100, 0);
//
//	//set position index counter to zero
//	sprintf(cmd, "%dPZ%c", NumController, 0x0D);
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//
//	return(0);
//}
//
//int set_accel_and_velocity(int NumController, double accel, double vel) {
//	char cmd[64];
//	unsigned char *cmdbuffer = (unsigned char*)&cmd[0];
//
//	sprintf(cmd, "%dA%5.3f%c%dV%5.3f%c%dCR%c", NumController, accel, 0x0D, NumController, vel, 0x0D, NumController, 0x0D);
//	sp_blocking_write(comport, cmd, strlen(cmd), timeout);
//
//	return(0);
//}