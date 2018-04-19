#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visatype.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visaext.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visaext.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visa.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <conio.h>
#include <ctime>
#include <Windows.h>
#using <System.dll>

#pragma warning(disable:4996)
#include "MainForm.h"

#define RESOLUTION 12800 //in steps/rev
#define ACCELERATION 1 //in rev/sec^2
#define VELOCITY 1 //in rev/sec
#define ANTENNA_OFFSET  7.5 //distance from center of antenna to edge of bracket

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {

	std::cout << " _______ _______ _______ __   __                                     \n";
	std::cout << "|       |       |   _   |  |_|  |                                    \n";
	std::cout << "|_     _|    ___|  |_|  |       |                                    \n";
	std::cout << "  |   | |   |___|       |       |                                    \n";
	std::cout << "  |   | |    ___|       |       |                                    \n";
	std::cout << "  |   | |   |___|   _   | ||_|| |                                    \n";
	std::cout << "  |___| |_______|__| |__|_|   |_|                                    \n";
	std::cout << " _______ _______ ______   _______                                    \n";
	std::cout << "|       |       |    _ | |       |                                   \n";
	std::cout << "|____   |    ___|   | || |   _   |                                   \n";
	std::cout << " ____|  |   |___|   |_||_|  | |  |                                   \n";
	std::cout << "| ______|    ___|    __  |  |_|  |                                   \n";
	std::cout << "| |_____|   |___|   |  | |       |                                   \n";
	std::cout << "|_______|_______|___|  |_|_______|                                   \n";
	std::cout << " ___ __   __ _______ _______ ______  _______ __    _ _______ _______ \n";
	std::cout << "|   |  |_|  |       |       |      ||   _   |  |  | |       |       |\n";
	std::cout << "|   |       |    _  |    ___|  _    |  |_|  |   |_| |       |    ___|\n";
	std::cout << "|   |       |   |_| |   |___| | |   |       |       |       |   |___ \n";
	std::cout << "|   |       |    ___|    ___| |_|   |       |  _    |      _|    ___|\n";
	std::cout << "|   | ||_|| |   |   |   |___|       |   _   | | |   |     |_|   |___ \n";
	std::cout << "|___|_|   |_|___|   |_______|______||__| |__|_|  |__|_______|_______|\n";




	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Design_Project::MainForm form;

	Application::Run(%form);




}

//Function Definitions
//

//TODO: setup return
bool InitPort(HANDLE *hComm, char ComPortName[]) {
	bool Status;

	//Opening the Serial Port
	//Purpose: This section uses the CreateFile function to initialize the serial port connection
	//
	*hComm = CreateFile(TEXT("COM1"),        // Name of the Port to be Opened
		GENERIC_READ | GENERIC_WRITE,      // Read/Write Access
		0,                                 // No Sharing, ports cant be shared
		NULL,                              // No Security
		OPEN_EXISTING,                     // Open existing port only
		0,                                 // Non Overlapped I/O
		NULL);                             // Null for Comm Devices

	if (*hComm == INVALID_HANDLE_VALUE)
		printf("\nError: - Port %s Not Opened", ComPortName);
	else
		printf("\nSuccess: %s Opened\n ", ComPortName);

	//Setting Parameters (Buadrate, Bytesize, Stopbits, Parity, etc.)
	//Purpose: This section uses the DCB (Device Control Bus) structure to set the parameters of the desired
	//communication port then configures the port according to those parameters. 
	//
	DCB dcbSerialParams = { 0 };                          // Initializing DCB structure
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);  // Obtain size of Parmaters

	Status = GetCommState(*hComm, &dcbSerialParams);       //retreives  the current settings

	if (Status == FALSE)
		printf("\nError: Cannot Retrieve Current Settings)");

	dcbSerialParams.BaudRate = CBR_9600;                  // Setting BaudRate = 9600
	dcbSerialParams.ByteSize = 8;              			  // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;    			  // Setting StopBits = 1
	dcbSerialParams.Parity = NOPARITY;      			  // Setting Parity = None 
	dcbSerialParams.fBinary = TRUE;
	dcbSerialParams.fDtrControl = FALSE;
	dcbSerialParams.fInX = FALSE;
	dcbSerialParams.EofChar = ' ';

	Status = SetCommState(*hComm, &dcbSerialParams);  	  //Configuring the port according to settings in DCB 

	if (Status == FALSE)
	{
		printf("\nError: DCB Structure Not Set!");
	}
	else
	{
		printf("\nSuccess: DCB Structure Set with the Following Parameters: ");
		printf("\n-Baudrate = %d", dcbSerialParams.BaudRate);
		printf("\n-ByteSize = %d", dcbSerialParams.ByteSize);
		printf("\n-StopBits = %d", (dcbSerialParams.StopBits) + 1);
		printf("\n-Parity   = %d", dcbSerialParams.Parity);
	}
	//Setting Timeouts
	//Purpose: This sections sets the values for the various Read/Write timeouts for the desired port then
	//configures the port with those parameters.
	//
	COMMTIMEOUTS timeouts = { 0 };

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (SetCommTimeouts(*hComm, &timeouts) == FALSE)
		printf("\nError: Time Outs Not Set!");
	else
		printf("\n\nSuccess: Time Outs Set");

	PurgeComm(*hComm, PURGE_TXCLEAR); //Purge output buffer on startup
	return true; //change later
}

//Set Receive Mask Function
//
bool SetRxMask(HANDLE *hComm) {

	bool Status;

	Status = SetCommMask(*hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception

	if (Status == FALSE)
		printf("\n\nError: CommMask Not Set!");
	else
		printf("\n\nSuccess: CommMask Set");

	return true;
}

//Closing Serial Port Function
//
bool ClosePort(HANDLE *hComm, char ComPortName[]) {
	CloseHandle(*hComm);
	printf("\n\n   Success: %s closed", ComPortName);

	return true;
}

//Writing Command Function
//
bool WriteCmd(HANDLE *hComm, char lpBuffer[], char ComPortName[]) {
	DWORD  dNoOFBytestoWrite;              // No of bytes to write into the port
	DWORD  dNoOfBytesWritten = 0;          // No of bytes written to the port
	bool Status;

	PurgeComm(*hComm, PURGE_TXCLEAR); //Purge output buffer

	dNoOFBytestoWrite = strlen(lpBuffer);   // Calculating the no of bytes to write into the port

	Status = WriteFile(*hComm,               // Handle to the Serialport
		lpBuffer,            				// Data to be written to the port 
		dNoOFBytestoWrite,  				// No of bytes to write into the port
		&dNoOfBytesWritten, 				// No of bytes written to the port
		NULL);

	if (Status == TRUE) {
		printf("\n\n    Characters Written to %s:", ComPortName);
		printf("\n          %s \n", lpBuffer);
	}
	else
		printf("\n\n   Error %d in Writing to Serial Port", GetLastError());

	return true;
}

//Reading Response Function
//
bool ReadRsp(HANDLE *hComm, char ComPortName[]) {
	//Set WaitComm() event and listen for response
	//
	bool Status;
	DWORD dwEventMask;                     // Event mask to trigger
	char  TempChar;                        // Temporary Character
	char  SerialBuffer[256];               // Buffer Containing Rxed Data
	DWORD NoBytesRead;                     // Bytes read by ReadFile()
	int i = 0;

	printf("\nWaiting for Data Reception...");

	Status = WaitCommEvent(*hComm, &dwEventMask, NULL); //Wait for the character to be received
	if (Status == FALSE)
	{
		printf("\n    Error: WaitCommEvent() Not Set!");
	}
	else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
	{
		printf("\n\n    Characters Received from %s:", ComPortName);
		do
		{
			Status = ReadFile(*hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
			SerialBuffer[i] = TempChar;
			i++;
		} while (NoBytesRead > 0);

		//Print Received Messages to Console
		//
		printf("\n          ");
		int j = 0;
		for (j = 0; j < i - 1; j++)		// j < i-1 to remove the dupliated last character
			printf("%c", SerialBuffer[j]);

		FlushFileBuffers(*hComm);
		PurgeComm(*hComm, PURGE_RXCLEAR);
	}
	return true;
}

//Go Home Function
//
bool GoHome(HANDLE *hComm, char ComPortName[]) {

	//TO DO: 
	//1) Need to check if limit switches are already engaged
	//IF they are, can skip part one/ two depending on which
	//switch is hit
	//2) Couldn't get motors to move of limit switch after long delay for 1st moves

	//move x and y motor to (0,0) position
	//
	//char lpBuffer[] = "D-250000 1G T10 2G ";
	char lpBuffer[] = "D-250000 1G T10 ";
	WriteCmd(hComm, lpBuffer, ComPortName);
	ReadRsp(hComm, ComPortName);

	//Sleep(3500);

	//move just off limit switches
	//
	//char lpBuffer1[] = "D600 1G 2G ";
	char lpBuffer1[] = "D600 1G ";
	WriteCmd(hComm, lpBuffer1, ComPortName);
	ReadRsp(hComm, ComPortName);

	Sleep(2000);

	//set counter to zero
	//
	char lpBuffer2[] = "PZ ";
	WriteCmd(hComm, lpBuffer1, ComPortName);
	ReadRsp(hComm, ComPortName);

	return true;

}

//Enable Limit Switches, Set to Normal Mode, Set Acceleration, Set Velocity
//
bool SetAcelandVel(HANDLE *hComm, char ComPortName[]) {
	char lpBuffer[] = "LD0 MN A2 V1 ";
	WriteCmd(hComm, lpBuffer, ComPortName);
	return true;
}

double ConvertCmtoSteps(double cm) {
	int stepsPerCm = 1010;
	double Steps = (cm*stepsPerCm);

	return Steps;
}

//Convert movement steps into time in milliseconds based on motor settings
int ConvertStepstoSeconds(int steps) {
	//seconds = revs/sec; revs = steps/resolution
	double seconds = steps*VELOCITY / RESOLUTION;
	int time = seconds * 1000;

	return time;
}

bool GoToFirstPos(HANDLE * hComm, char ComPortName[], int xstart_steps, int ystart_steps)
{
	char lpBuffer[64];
	int x_init = xstart_steps - ConvertCmtoSteps(ANTENNA_OFFSET);
	//sprintf(lpBuffer, "D%d 1G D%d 2G ", xstart_steps, ystart_steps);
	sprintf(lpBuffer, "D%d 1G ", x_init);
	WriteCmd(hComm, lpBuffer, ComPortName);
	ReadRsp(hComm, ComPortName);

	return true;
}

bool GoToNextPos(HANDLE * hComm, char ComPortName[], int xstep_size, int ystep_size, int xPoints,
	int yPoints, int row_size, int x_index, int y_index, bool new_line, bool line_scan)
{
	char lpBuffer[64];

	//std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
	//std::cout << "+     Moving to next scan position     +\n";
	//std::cout << "++++++++++++++++++++++++++++++++++++++++\n";


	if (new_line == false) {
		if (x_index != xPoints - 1) {
			//move horizontally by xstep_size
			//
			sprintf(lpBuffer, "D%d 1G ", xstep_size);
			WriteCmd(hComm, lpBuffer, ComPortName);
			ReadRsp(hComm, ComPortName);

			//delay so mount has time to reach desired position
			Sleep(ConvertStepstoSeconds(xstep_size) + 300);

			//delay at position for 1 second
			sprintf(lpBuffer, "1T1 ");
			WriteCmd(hComm, lpBuffer, ComPortName);
			ReadRsp(hComm, ComPortName);
		}

		return true;
	}
	else if (new_line == true && y_index != (yPoints - 1) && line_scan == false) {
		//return to the start of the row
		//
		sprintf(lpBuffer, "D-%d 1G ", row_size);
		WriteCmd(hComm, lpBuffer, ComPortName);
		ReadRsp(hComm, ComPortName);
		//Sleep(10000);
		Sleep(ConvertStepstoSeconds(xstep_size * 4) + 300);
		//move down by ystep_size
		//
		sprintf(lpBuffer, "D%d 2G ", ystep_size);
		WriteCmd(hComm, lpBuffer, ComPortName);
		ReadRsp(hComm, ComPortName);
		Sleep(ConvertStepstoSeconds(ystep_size) + 300);

		//delay at position for 1 second
		sprintf(lpBuffer, "1T1 ");
		WriteCmd(hComm, lpBuffer, ComPortName);
		ReadRsp(hComm, ComPortName);

		return true;
	}
	else {
		return false;
	}

	
}