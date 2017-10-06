/******************************************************************************
*																			  *
*	Filename:	Setup.c								     					  *
*	Version:	0.xx														  *
*	Date:		18 November 2006											  *
*																			  *
******************************************************************************/

#include "agena.h"
#include <utility.h>
#include <userint.h>
#include "Setup.h"
#include <formatio.h>
#include "Points.h"
#include <rs232.h>
#include "SaveData.h"
#include "stdlib.h"
#include "StepperControllerIF.h"
#include "toolbox.h"
#include "E5071.h"
#include "Defines.h"
#include "Plot.h"
#include <cvidef.h>
#include "Setup.h"

//#define NOSCAN
//*****************************************************************************
//	Variable Declarations
//																			  
int active;
int error;
int fileHandle;
char directory[MAX_PATHNAME_LEN];
char pathName[MAX_PATHNAME_LEN];
char setupline[64];
int setupvalue;
unsigned char ch1numberofmeasurements, ch2numberofmeasurements;
char ascii_data_chan1[kNumTracesCh1][131072];
char ascii_data_chan2[kNumTracesCh2][131072];
int iComPort = 1;
int iStart = 1;
char ascii_network_analyzer_setup[131072];
char exp_name[1024];
char exp_path[1024];
int Network_Setup;
int hNetPanel; 

struct FPPoint {
	double x;   //width
	double y;   //height
}theFPPoints[100000];

struct FPPosGen {
	int iNumCol;
	double dPosFirstCol;
	double dPosLastCol;
	int iNumRow;
	double dPosFirstRow;
	double dPosLastRow;
}FPPosGenNums;

struct FP2PosGen {				
	int iNumCol;
	double dPosCol[1000];
	int iNumRow;
	double dPosRow[1000];
}FP2PosGenNums;

int iCurrentFPPoint;
double posXInInches = 0.0;
double posYInInches = 0.0;
int iFPPosValid = 0; 
int iStopExperiment = 0;
int iNumFPPoints;
extern int hPanelMain;
extern int hPanelInit;
char data_dir[] = {"c:\\Data"}; 
extern char ascii_network_analyzer_setup[];
extern ViSession visa_na;


int intdummyvar;
char chardummyvar;
unsigned short int unshortintdummyvar;

int startfreq = 1000;
int stopfreq = 3000;
char powerlevel = 0;
char ch1sweeptype = 0;
char ch2sweeptype = 0;
char ch1sweepmode = 0;
char ch2sweepmode = 0;
int ch1ifbandwidth = 100000;
int ch2ifbandwidth = 100000;
unsigned short int ch1numbpoints = 2;
unsigned short int ch2numbpoints = 2;
int ch1averageon = 0;
int ch2averageon = 0;
unsigned short int ch1averagefactor = 1;
unsigned short int ch2averagefactor = 1;
//char CH1M[17];
//char CH2M[17];
//char CH1MFORM[17];
//char CH2MFORM[17];  
int CH1M[17];
int CH2M[17];
int CH1MFORM[17];
int CH2MFORM[17];  



const char sparam[16][4] = {"S11", "S21", "S31", "S41", "S12", "S22", "S32", "S42", "S13", "S23", "S33", "S43", "S14", "S24", "S34", "S44"};
const char sformat[17][24] = {"Log Magnitude", "Phase", "Group Delay", "Smith Chart (Lin/Phase)", "Smith Chart (Log/Phase)",
							"Smith Chart (Re/Im)", "Smith Chart (R+jX)", "Smith Chart (G+jB)", "Polar (Lin/Phase)",
							"Polar (Log/Phase)", "Polar (Re/Im)", "Linear Magnitude", "SWR", "Real", "Imaginary", "Expanded Phase",
							"Positive Phase"};
							
							
const char sweeptype[4][8] = {"Linear", "Log", "Segment", "Power"};
const char sweepmode[4][13] = {"Stepped", "Swept", "Fast Stepped", "Fast Swept"};

//func decl
int enableAllControls( int iEnable );
int readNetworkSetup(void);


//*****************************************************************************
//	Functions
//



int Load_Network_Setup_File(char* pathName)
{
	DebugPrintf("\n\n");
	DebugPrintf("Starting Network Setup Load\n");
	DebugPrintf("Opening File - %s\n", pathName);   
	fileHandle = OpenFile (pathName, VAL_READ_ONLY, 0, VAL_ASCII);
	DebugPrintf("FileHandle = %d\n", fileHandle);


	//read header line
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	
	//read start frequency
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_startfreq, setupvalue); 
	
	//read stop frequency
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_stopfreq, setupvalue); 	

	//read rf power
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_powerlevel, (char)setupvalue); 	
	
	//read channel 1 sweep type
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_RING_sweeptype1, (char)setupvalue); 	

	//read channel 1 sweep mode
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_RING_sweepmode1, (char)setupvalue); 	

	//read channel 1 if bandwidth
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_ifbandwidth1, setupvalue); 	

	//read channel 1 number of points
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_numpoints1, setupvalue); 	
	
	//read channel 1 average ON?
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_RADIO_average_on1, setupvalue);
	if (setupvalue == 1) SetCtrlAttribute(NETSETUP, NETSETUP_NUMERIC_aver1, ATTR_DIMMED, 0); 
	
	//read channel 1 average factor
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_aver1, setupvalue); 	

	//read channel 1 number of measurements
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	ch1numberofmeasurements = (unsigned char)setupvalue;

	active1_2 (NETSETUP, NETSETUP_RADIO_active1_2, EVENT_COMMIT, 0, 0, 0);		//clear channel 1 measurement settings

	if (ch1numberofmeasurements >= 1)
	{
		//read channel 1 measurement 1
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_1, (unsigned char)setupvalue); 	
		//read channel 1 measurement 1 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_1, (unsigned char)setupvalue); 	
	}
	
	if (ch1numberofmeasurements >= 2)
	{
		//read channel 1 measurement 2
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_2, (unsigned char)setupvalue); 	
		//read channel 1 measurement 2 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_2, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_2, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_2, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_2, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_2, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_3, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_3, ATTR_VISIBLE, 1);
	}
	
	if (ch1numberofmeasurements >= 3)
	{
		//read channel 1 measurement 3
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_3, (unsigned char)setupvalue); 	
		//read channel 1 measurement 3 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_3, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_3, 1);

		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_3, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_3, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_3, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_4, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_4, ATTR_VISIBLE, 1);
	
	}

	if (ch1numberofmeasurements >= 4)
	{
		//read channel 1 measurement 4
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_4, (unsigned char)setupvalue); 	
		//read channel 1 measurement 4 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_4, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_4, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_4, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_4, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_4, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_5, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_5, ATTR_VISIBLE, 1);

	}

	if (ch1numberofmeasurements >= 5)
	{
		//read channel 1 measurement 5
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_5, (unsigned char)setupvalue); 	
		//read channel 1 measurement 5 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_5, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_5, 1);

		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_5, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_5, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_5, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_6, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_6, ATTR_VISIBLE, 1);	
	}

	if (ch1numberofmeasurements >= 6)
	{
		//read channel 1 measurement 6
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_6, (unsigned char)setupvalue); 	
		//read channel 1 measurement 6 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_6, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_6, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_6, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_6, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_6, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_7, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_7, ATTR_VISIBLE, 1);		
	}

	if (ch1numberofmeasurements >= 7)
	{
		//read channel 1 measurement 7
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_7, (unsigned char)setupvalue); 	
		//read channel 1 measurement 7 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_7, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_7, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_7, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_7, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_7, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_8, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_8, ATTR_VISIBLE, 1);		
	}

	if (ch1numberofmeasurements >= 8)
	{
		//read channel 1 measurement 8
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_8, (unsigned char)setupvalue); 	
		//read channel 1 measurement 8 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_8, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_8, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_8, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_8, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_8, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_9, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_9, ATTR_VISIBLE, 1);		
	}
	
	if (ch1numberofmeasurements >= 9)
	{
		//read channel 1 measurement 9
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_9, (unsigned char)setupvalue); 	
		//read channel 1 measurement 9 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_9, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_9, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_9, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_9, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_9, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_10, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_10, ATTR_VISIBLE, 1);		
	}

	if (ch1numberofmeasurements >= 10)
	{
		//read channel 1 measurement 10
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_10, (unsigned char)setupvalue); 	
		//read channel 1 measurement 10 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_10, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_10, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_10, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_10, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_10, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_11, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_11, ATTR_VISIBLE, 1);		
	}

 	if (ch1numberofmeasurements >= 11)
	{
		//read channel 1 measurement 11
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_11, (unsigned char)setupvalue); 	
		//read channel 1 measurement 11 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_11, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_11, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_11, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_11, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_11, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_12, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_12, ATTR_VISIBLE, 1);		
	}

	if (ch1numberofmeasurements >= 12)
	{
		//read channel 1 measurement 12
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_12, (unsigned char)setupvalue); 	
		//read channel 1 measurement 12 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_12, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_12, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_12, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_12, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_12, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_13, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_13, ATTR_VISIBLE, 1);		
	}

	if (ch1numberofmeasurements >= 13)
	{
		//read channel 1 measurement 13
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_13, (unsigned char)setupvalue); 	
		//read channel 1 measurement 13 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_13, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_13, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_13, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_13, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_13, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_14, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_14, ATTR_VISIBLE, 1);		
	}

	if (ch1numberofmeasurements >= 14)
	{
		//read channel 1 measurement 14
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_14, (unsigned char)setupvalue); 	
		//read channel 1 measurement 14 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_14, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_14, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_14, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_14, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_14, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_15, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_15, ATTR_VISIBLE, 1);		
	}

	if (ch1numberofmeasurements >= 15)
	{
		//read channel 1 measurement 15
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_15, (unsigned char)setupvalue); 	
		//read channel 1 measurement 15 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_15, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_15, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_15, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_15, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_15, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_16, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_16, ATTR_VISIBLE, 1);		
	}

	if (ch1numberofmeasurements == 16)
	{
		//read channel 1 measurement 16
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_16, (unsigned char)setupvalue); 	
		//read channel 1 measurement 16 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format1_16, (unsigned char)setupvalue); 	
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_16, 1);
		
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_16, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_16, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_16, ATTR_VISIBLE, 1); 
	}

	//read channel 2 sweep type
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_RING_sweeptype2, (char)setupvalue);  
 
	//read channel 2 sweep mode
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
    strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_RING_sweepmode2, (char)setupvalue);  
 
	//read channel 2 if bandwidth    
    ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_ifbandwidth2, setupvalue); 	 

	//read channel 2 number of points
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_numpoints2, setupvalue); 	

	//read channel 2 average ON?
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_RADIO_average_on2, setupvalue);
	if (setupvalue == 1) SetCtrlAttribute(NETSETUP, NETSETUP_NUMERIC_aver2, ATTR_DIMMED, 0); 

	//read channel 2 average factor
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_aver2, setupvalue); 

	//read channel 2 number of measurements
	ReadLine (fileHandle, setupline, -1);
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	strtok(setupline, "=");
	StrToInt(strtok(0, "="), &setupvalue);
	ch2numberofmeasurements = (unsigned char)setupvalue;

	active2_1 (NETSETUP, NETSETUP_RADIO_active2_1, EVENT_COMMIT, 0, 0, 0);		//clear channel 2 measurement settings

	if (ch2numberofmeasurements > 0)
	{
		//read channel 2 measurement 1
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_1, (unsigned char)setupvalue); 	
		//read channel 2 measurement 1 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_1, (unsigned char)setupvalue);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_1, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_1, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_1, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_1, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_2, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_2, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 1) 
	{
		//read channel 2 measurement 2
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_2, (unsigned char)setupvalue); 	
		//read channel 2 measurement 2 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_2, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_2, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_2, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_2, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_2, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_2, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_3, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_3, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 2) 
	{
		//read channel 2 measurement 3
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_3, (unsigned char)setupvalue); 	
		//read channel 2 measurement 3 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_3, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_3, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_3, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_3, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_3, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_3, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_4, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_4, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 3) 
	{
		//read channel 2 measurement 4
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_4, (unsigned char)setupvalue); 	
		//read channel 2 measurement 4 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_4, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_4, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_4, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_4, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_4, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_4, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_5, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_5, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 4) 
	{
		//read channel 2 measurement 5
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_5, (unsigned char)setupvalue); 	
		//read channel 2 measurement 5 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_5, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_5, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_5, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_5, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_5, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_5, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_6, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_6, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 5) 
	{
		//read channel 2 measurement 6
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_6, (unsigned char)setupvalue); 	
		//read channel 2 measurement 6 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_6, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_6, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_6, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_6, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_6, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_6, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_7, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_7, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 6) 
	{
		//read channel 2 measurement 7
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_7, (unsigned char)setupvalue); 	
		//read channel 2 measurement 7 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_7, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_7, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_7, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_7, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_7, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_7, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_8, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_8, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 7) 
	{
		//read channel 2 measurement 8
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_8, (unsigned char)setupvalue); 	
		//read channel 2 measurement 8 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_8, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_8, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_8, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_8, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_8, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_8, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_9, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_9, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 8) 
	{
		//read channel 2 measurement 9
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_9, (unsigned char)setupvalue); 	
		//read channel 2 measurement 9 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_9, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_9, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_9, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_9, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_9, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_9, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_10, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_10, ATTR_VISIBLE, 1);
	}

 	if (ch2numberofmeasurements > 9) 
	{
		//read channel 2 measurement 10
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_10, (unsigned char)setupvalue); 	
		//read channel 2 measurement 10 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_10, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_10, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_10, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_10, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_10, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_10, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_11, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_11, ATTR_VISIBLE, 1);
	}
	
	if (ch2numberofmeasurements > 10) 
	{
		//read channel 2 measurement 11
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_11, (unsigned char)setupvalue); 	
		//read channel 2 measurement 11 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_11, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_11, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_11, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_11, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_11, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_11, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_12, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_12, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 11) 
	{
		//read channel 2 measurement 12
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_12, (unsigned char)setupvalue); 	
		//read channel 2 measurement 12 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_12, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_12, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_12, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_12, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_12, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_12, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_13, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_13, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 12) 
	{
		//read channel 2 measurement 13
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_13, (unsigned char)setupvalue); 	
		//read channel 2 measurement 13 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_13, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_13, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_13, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_13, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_13, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_13, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_14, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_14, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 13) 
	{
		//read channel 2 measurement 14
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_14, (unsigned char)setupvalue); 	
		//read channel 2 measurement 14 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_14, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_14, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_14, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_14, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_14, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_14, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_15, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_15, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 14) 
	{
		//read channel 2 measurement 15
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_15, (unsigned char)setupvalue); 	
		//read channel 2 measurement 15 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_15, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_15, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_15, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_15, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_15, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_15, ATTR_VISIBLE, 1); 
		SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_16, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_16, ATTR_VISIBLE, 1);
	}

	if (ch2numberofmeasurements > 15) 
	{
		//read channel 2 measurement 16
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_16, (unsigned char)setupvalue); 	
		//read channel 2 measurement 16 data format  	
		ReadLine (fileHandle, setupline, -1);
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 		
		strtok(setupline, "=");
		StrToInt(strtok(0, "="), &setupvalue);
		SetCtrlVal(NETSETUP, NETSETUP_RING_format2_16, (unsigned char)setupvalue); 
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_16, 1);
		
		SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_16, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_16, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_16, ATTR_VISIBLE, 1);
		SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_16, ATTR_VISIBLE, 1); 
	}

	DebugPrintf("Closing File - %s\n", pathName);
	CloseFile(fileHandle);

	return 0;
}


int Save_Network_Setup_File(char* pathName)
{
	char chardummyvar;
	int intdummyvar;
	unsigned short int unshortintdummyvar;
	
	DebugPrintf("\n\n");
	DebugPrintf("Starting Network Setup Save\n");
	DebugPrintf("Opening File - %s\n", pathName);   
	fileHandle = OpenFile (pathName, VAL_WRITE_ONLY, 0, VAL_ASCII);
	DebugPrintf("FileHandle = %d\n", fileHandle);


	//write header line
	sprintf(setupline, "#E5071 Scanner Software Network Setup File"); 
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline)); 
	
	//write start frequency
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_startfreq, &intdummyvar);
	sprintf(setupline, "STARTF=%d", intdummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write stop frequency
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_stopfreq, &intdummyvar);
	sprintf(setupline, "STOPF=%d", intdummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write rf power	
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_powerlevel, &chardummyvar);
	sprintf(setupline, "RFPOWER=%d", chardummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 1 sweep type	
	GetCtrlVal(NETSETUP, NETSETUP_RING_sweeptype1, &chardummyvar);
	sprintf(setupline, "CH1SWEEPTYPE=%d", chardummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 1 sweep mode
	GetCtrlVal(NETSETUP, NETSETUP_RING_sweepmode1, &chardummyvar);
	sprintf(setupline, "CH1SWEEPMODE=%d", chardummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 1 if bandwidth	
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_ifbandwidth1, &intdummyvar);
	sprintf(setupline, "CH1IFBANDWIDTH=%d", intdummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 1 number of points
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_numpoints1, &unshortintdummyvar);
	sprintf(setupline, "CH1NUMBEROFPOINTS=%d", unshortintdummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 1 average ON?
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_average_on1, &intdummyvar);
	sprintf(setupline, "CH1AVERAGEON=%d", intdummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 1 average factor	
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_aver1, &unshortintdummyvar);
	sprintf(setupline, "CH1AVERAGE=%d", unshortintdummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 1 number of measurements	
	ch1numberofmeasurements = 1;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_2, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 2;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_3, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 3;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_4, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 4;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_5, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 5;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_6, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 6;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_7, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 7;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_8, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 8;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_9, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 9;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_10, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 10;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_11, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 11;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_12, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 12;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_13, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 13;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_14, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 14;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_15, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 15;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_16, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 16;
	
	sprintf(setupline, "CH1NUMBEROFMEAS=%d", ch1numberofmeasurements);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	if (ch1numberofmeasurements >= 1)
	{
		//write channel 1 measurement 1
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_1, &chardummyvar);
		sprintf(setupline, "CH1M1=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 1 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_1, &chardummyvar);
		sprintf(setupline, "CH1M1FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
	
	if (ch1numberofmeasurements >= 2)
	{
		//write channel 1 measurement 2
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_2, &chardummyvar);
		sprintf(setupline, "CH1M2=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 2 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_2, &chardummyvar);
		sprintf(setupline, "CH1M2FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
	
	if (ch1numberofmeasurements >= 3)
	{
		//write channel 1 measurement 3
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_3, &chardummyvar);
		sprintf(setupline, "CH1M3=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 3 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_3, &chardummyvar);
		sprintf(setupline, "CH1M3FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch1numberofmeasurements >= 4)
	{
		//write channel 1 measurement 4
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_4, &chardummyvar);
		sprintf(setupline, "CH1M4=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 4 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_4, &chardummyvar);
		sprintf(setupline, "CH1M4FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch1numberofmeasurements >= 5)
	{
		//write channel 1 measurement 5
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_5, &chardummyvar);
		sprintf(setupline, "CH1M5=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 5 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_5, &chardummyvar);
		sprintf(setupline, "CH1M5FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch1numberofmeasurements >= 6)
	{
		//write channel 1 measurement 6
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_6, &chardummyvar);
		sprintf(setupline, "CH1M6=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 6 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_6, &chardummyvar);
		sprintf(setupline, "CH1M6FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch1numberofmeasurements >= 7)
	{
		//write channel 1 measurement 7
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_7, &chardummyvar);
		sprintf(setupline, "CH1M7=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 7 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_7, &chardummyvar);
		sprintf(setupline, "CH1M7FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch1numberofmeasurements >= 8)
	{
		//write channel 1 measurement 8
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_8, &chardummyvar);
		sprintf(setupline, "CH1M8=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 8 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_8, &chardummyvar);
		sprintf(setupline, "CH1M8FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch1numberofmeasurements >= 9)
	{
		//write channel 1 measurement 9
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_9, &chardummyvar);
		sprintf(setupline, "CH1M9=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 9 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_9, &chardummyvar);
		sprintf(setupline, "CH1M9FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch1numberofmeasurements >= 10)
	{
		//write channel 1 measurement 10
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_10, &chardummyvar);
		sprintf(setupline, "CH1M10=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 10 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_10, &chardummyvar);
		sprintf(setupline, "CH1M10FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch1numberofmeasurements >= 11)
	{
		//write channel 1 measurement 11
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_11, &chardummyvar);
		sprintf(setupline, "CH1M11=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 11 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_11, &chardummyvar);
		sprintf(setupline, "CH1M11FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	if (ch1numberofmeasurements >= 12)
	{
		//write channel 1 measurement 12
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_12, &chardummyvar);
		sprintf(setupline, "CH1M12=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 12 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_12, &chardummyvar);
		sprintf(setupline, "CH1M12FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	if (ch1numberofmeasurements >= 13)
	{
		//write channel 1 measurement 13
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_13, &chardummyvar);
		sprintf(setupline, "CH1M13=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 13 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_13, &chardummyvar);
		sprintf(setupline, "CH1M13FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	if (ch1numberofmeasurements >= 14)
	{
		//write channel 1 measurement 14
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_14, &chardummyvar);
		sprintf(setupline, "CH1M14=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 14 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_14, &chardummyvar);
		sprintf(setupline, "CH1M14FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	if (ch1numberofmeasurements >= 15)
	{
		//write channel 1 measurement 15
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_15, &chardummyvar);
		sprintf(setupline, "CH1M15=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 15 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_15, &chardummyvar);
		sprintf(setupline, "CH1M15FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	if (ch1numberofmeasurements >= 16)
	{
		//write channel 1 measurement 16
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_16, &chardummyvar);
		sprintf(setupline, "CH1M16=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 1 measurement 16 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_16, &chardummyvar);
		sprintf(setupline, "CH1M16FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	//write channel 2 sweep type	
	GetCtrlVal(NETSETUP, NETSETUP_RING_sweeptype2, &chardummyvar);
	sprintf(setupline, "CH2SWEEPTYPE=%d", chardummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 2 sweep mode
	GetCtrlVal(NETSETUP, NETSETUP_RING_sweepmode2, &chardummyvar);
	sprintf(setupline, "CH2SWEEPMODE=%d", chardummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 2 if bandwidth	
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_ifbandwidth2, &intdummyvar);
	sprintf(setupline, "CH2IFBANDWIDTH=%d", intdummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 2 number of points
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_numpoints2, &unshortintdummyvar);
	sprintf(setupline, "CH2NUMBEROFPOINTS=%d", unshortintdummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 2 average ON?
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_average_on2, &intdummyvar);
	sprintf(setupline, "CH2AVERAGEON=%d", intdummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 2 average factor	
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_aver2, &unshortintdummyvar);
	sprintf(setupline, "CH2AVERAGE=%d", unshortintdummyvar);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	
	//write channel 2 number of measurements	
	ch2numberofmeasurements = 0;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_1, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 1;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_2, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 2;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_3, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 3;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_4, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 4;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_5, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 5;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_6, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 6;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_7, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 7;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_8, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 8;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_9, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 9;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_10, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 10;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_11, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 11;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_12, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 12;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_13, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 13;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_14, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 14;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_15, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 15;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_16, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 16;
	
	sprintf(setupline, "CH2NUMBEROFMEAS=%d", ch2numberofmeasurements);
	WriteLine (fileHandle, setupline, strlen(setupline));
	DebugPrintf("%s, %d\n", setupline, StringLength (setupline));

	if (ch2numberofmeasurements >= 1)
	{
		//write channel 2 measurement 1
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_1, &chardummyvar);
		sprintf(setupline, "CH2M1=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 1 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_1, &chardummyvar);
		sprintf(setupline, "CH2M1FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
	
	if (ch2numberofmeasurements >= 2)
	{
		//write channel 2 measurement 2
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_2, &chardummyvar);
		sprintf(setupline, "CH2M2=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 2 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_2, &chardummyvar);
		sprintf(setupline, "CH2M2FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
	
	if (ch2numberofmeasurements >= 3)
	{
		//write channel 2 measurement 3
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_3, &chardummyvar);
		sprintf(setupline, "CH2M3=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 3 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_3, &chardummyvar);
		sprintf(setupline, "CH2M3FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch2numberofmeasurements >= 4)
	{
		//write channel 2 measurement 4
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_4, &chardummyvar);
		sprintf(setupline, "CH2M4=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 4 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_4, &chardummyvar);
		sprintf(setupline, "CH2M4FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch2numberofmeasurements >= 5)
	{
		//write channel 2 measurement 5
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_5, &chardummyvar);
		sprintf(setupline, "CH2M5=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 5 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_5, &chardummyvar);
		sprintf(setupline, "CH2M5FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch2numberofmeasurements >= 6)
	{
		//write channel 2 measurement 6
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_6, &chardummyvar);
		sprintf(setupline, "CH2M6=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 6 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_6, &chardummyvar);
		sprintf(setupline, "CH2M6FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch2numberofmeasurements >= 7)
	{
		//write channel 2 measurement 7
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_7, &chardummyvar);
		sprintf(setupline, "CH2M7=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 7 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_7, &chardummyvar);
		sprintf(setupline, "CH2M7FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch2numberofmeasurements >= 8)
	{
		//write channel 2 measurement 8
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_8, &chardummyvar);
		sprintf(setupline, "CH2M8=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 8 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_8, &chardummyvar);
		sprintf(setupline, "CH2M8FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch2numberofmeasurements >= 9)
	{
		//write channel 2 measurement 9
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_9, &chardummyvar);
		sprintf(setupline, "CH2M9=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 9 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_9, &chardummyvar);
		sprintf(setupline, "CH2M9FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch2numberofmeasurements >= 10)
	{
		//write channel 2 measurement 10
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_10, &chardummyvar);
		sprintf(setupline, "CH2M10=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 10 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_10, &chardummyvar);
		sprintf(setupline, "CH2M10FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}
		
	if (ch2numberofmeasurements >= 11)
	{
		//write channel 2 measurement 11
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_11, &chardummyvar);
		sprintf(setupline, "CH2M11=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 11 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_11, &chardummyvar);
		sprintf(setupline, "CH2M11FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	if (ch2numberofmeasurements >= 12)
	{
		//write channel 2 measurement 12
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_12, &chardummyvar);
		sprintf(setupline, "CH2M12=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 12 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_12, &chardummyvar);
		sprintf(setupline, "CH2M12FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	if (ch2numberofmeasurements >= 13)
	{
		//write channel 2 measurement 13
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_13, &chardummyvar);
		sprintf(setupline, "CH2M13=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 13 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_13, &chardummyvar);
		sprintf(setupline, "CH2M13FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	if (ch2numberofmeasurements >= 14)
	{
		//write channel 2 measurement 14
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_14, &chardummyvar);
		sprintf(setupline, "CH2M14=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 14 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_14, &chardummyvar);
		sprintf(setupline, "CH2M14FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	if (ch2numberofmeasurements >= 15)
	{
		//write channel 2 measurement 15
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_15, &chardummyvar);
		sprintf(setupline, "CH2M15=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 15 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_15, &chardummyvar);
		sprintf(setupline, "CH2M15FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	if (ch2numberofmeasurements >= 16)
	{
		//write channel 2 measurement 16
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_16, &chardummyvar);
		sprintf(setupline, "CH2M16=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
		
		//write channel 2 measurement 16 data format  	
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_16, &chardummyvar);
		sprintf(setupline, "CH2M16FORM=%d", chardummyvar);
		WriteLine (fileHandle, setupline, strlen(setupline));
		DebugPrintf("%s, %d\n", setupline, StringLength (setupline));
	}

	DebugPrintf("Closing File - %s\n", pathName);
	CloseFile(fileHandle);

	return 0;
}


int goToPointPosition ( void )
{
int iStatus;

	enableAllControls( 0 );

	// move the FP to the next point
	iStatus = FP_GoToInInches( kWidthController,  theFPPoints[iCurrentFPPoint].x, 0 );
	if( iStatus != 0 ) {
		return( -1 );
	}
	iStatus = FP_GoToInInches( kHeightController, theFPPoints[iCurrentFPPoint].y, 0 );
	if( iStatus != 0 ) {
		return( -1 );
	}
	
	// get current position
	iStatus = FP_GetCurrentPositionInInches( kWidthController, &posXInInches );
	if( iStatus != 0 ) {
		return( -1 );
	}
	iStatus = FP_GetCurrentPositionInInches( kHeightController, &posYInInches );
	if( iStatus != 0 ) {
		return( -1 );
	}

#ifdef NOSCAN

	posXInInches = theFPPoints[iCurrentFPPoint].x;
	posYInInches = theFPPoints[iCurrentFPPoint].y;

#endif
	
	// update graph
	displayPos();
	
	iFPPosValid = 1;

	enableAllControls( 1 );

	return( 0 );

}



int runExperiment( void )
{
int iStatus = 0;
int iDone = 0;
int iBusy;
int iHour;
int iMin;
int iSec;

			
	DebugPrintf("iStopExperiment = %d\n", iStopExperiment);
	while( iStopExperiment == 0 )
	{

	

//GetSystemTime (&iHour, &iMin, &iSec);
//printf( "Before spectrum_analyzer_trigger\n" );
//printf( "Time = Hour = %d, Min = %d, Sec = %d\n", iHour, iMin, iSec );
	
	
		ProcessSystemEvents(); 


		iStatus = network_analyzer_trigger( );
		
		DebugPrintf("iStatus = %d\n", iStatus);
		
		if( ( iStatus != 0 ) || ( iStopExperiment == 1 ) ) {
			return( -1 );
		}
		
		ProcessSystemEvents(); 

		DebugPrintf("iNumFPPoints = %d\n", iNumFPPoints);

		if( ( iCurrentFPPoint + 1 ) == iNumFPPoints ) {
			iDone = 1;
		}


		if( iDone != 1 ) {
		
			// move the FP to the next point
			// but don't increment variable iCurrentFPPoint yet since the save routine needs the present value
			
			
			iStatus = FP_GoToInInches( kWidthController,  theFPPoints[iCurrentFPPoint + 1].x, 1 );
			if( ( iStatus != 0 ) || ( iStopExperiment == 1 ) ) {
				return( -1 );
			}
 			
			iStatus = FP_GoToInInches( kHeightController, theFPPoints[iCurrentFPPoint + 1].y, 1 );
			if( ( iStatus != 0 ) || ( iStopExperiment == 1 ) ) {
				return( -1 );
			}
		}

	
		ProcessSystemEvents(); 


		iStatus = network_analyzer_collect_data( );
		if( ( iStatus != 0 ) || ( iStopExperiment == 1 ) ) {
			return( -1 );
		}

		ProcessSystemEvents(); 



		iStatus = saveTraceData( );
		if( ( iStatus != 0 ) || ( iStopExperiment == 1 ) ) {
			return( -1 );
		}



		// after we saved the data we can increment this variable
		iCurrentFPPoint++;
	
		if( iCurrentFPPoint >= iNumFPPoints ) {
			iCurrentFPPoint = 0;
		}
			


//	REMOVED BECAUSE THERE ARE NO PLOT DIPLAYS ON MAIN SCREEN
//		iStatus = convert_asciis_to_doubles( );
//		if( ( iStatus != 0 ) || ( iStopExperiment == 1 ) ) {
//			return( -1 );
//		}

//	REMOVED BECAUSE THERE ARE NO PLOT DIPLAYS ON MAIN SCREEN
//		iStatus = plot_doubles( );
//		if( ( iStatus != 0 ) || ( iStopExperiment == 1 ) ) {
//			return( -1 );
//		}
		
 
		iBusy = 1;
		while( iBusy ) { 
  			iBusy = FP_GetBusyState( kWidthController );
 			ProcessSystemEvents(); 
  		}

		iBusy = 1;
		while( iBusy ) { 
  			iBusy = FP_GetBusyState( kHeightController );
 			ProcessSystemEvents(); 
  		}


		// get current position
		iStatus = FP_GetCurrentPositionInInches( kWidthController, &posXInInches );
		if( ( iStatus != 0 ) || ( iStopExperiment == 1 ) ) {
			return( -1 );
		}
		
		ProcessSystemEvents(); 


		iStatus = FP_GetCurrentPositionInInches( kHeightController, &posYInInches );
		if( ( iStatus != 0 ) || ( iStopExperiment == 1 ) ) {
			return( -1 );
		}

#ifdef NOSCAN

	posXInInches = theFPPoints[iCurrentFPPoint].x;
	posYInInches = theFPPoints[iCurrentFPPoint].y;

#endif

		ProcessSystemEvents(); 

		// update graph
		displayPos();

		ProcessSystemEvents(); 

		if( iDone == 1 ) {
			return( 0 );
		}
	
	}


	return( 0 );
}


int enableAllControls( int iEnable )
{
int iDimmed;

	if( iEnable == 0 )
	{
		iDimmed = 1;
		SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_BEGIN_EXP, ATTR_DIMMED, iDimmed);
	}
	else
	{
		iDimmed = 0;
		if (Network_Setup == 1) SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_BEGIN_EXP, ATTR_DIMMED, iDimmed);
	}


	
	SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_netsetup, 		 ATTR_DIMMED, iDimmed);
	SetCtrlAttribute (hPanelMain, FIELDPROBE_BINARYSWITCH, 		 ATTR_DIMMED, iDimmed);
	
	SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_NUM_COL,         ATTR_DIMMED, iDimmed);
	SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_START_COL_POS,   ATTR_DIMMED, iDimmed);
	SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_LAST_COL_POS,    ATTR_DIMMED, iDimmed);
	
	SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_NUM_ROWS,        ATTR_DIMMED, iDimmed);
	SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_START_ROW_POS,   ATTR_DIMMED, iDimmed);
	SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_LAST_ROW_POS,    ATTR_DIMMED, iDimmed);

	SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_SAVE_FP_POS_FILE, ATTR_DIMMED, iDimmed);
	SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_LOAD_FP_POS_FILE, ATTR_DIMMED, iDimmed);
	
	SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_GO_FIRST_POS,     ATTR_DIMMED, iDimmed);
	SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_GO_NEXT_POS,      ATTR_DIMMED, iDimmed);
	SetCtrlAttribute (hPanelMain, FIELDPROBE_RING_GOTO_POS,       ATTR_DIMMED, iDimmed);

	return( 0 );
}




int readNetworkSetup(void)
{
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_startfreq, &intdummyvar); 
	startfreq = intdummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_stopfreq, &intdummyvar); 
	stopfreq = intdummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_powerlevel, &chardummyvar);
	powerlevel = chardummyvar;
	
	DebugPrintf("\nPowerlevel is %d\n", powerlevel);
	
	GetCtrlVal(NETSETUP, NETSETUP_RING_sweeptype1, &chardummyvar);
	ch1sweeptype = chardummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_RING_sweepmode1, &chardummyvar);
	ch1sweepmode = chardummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_ifbandwidth1, &intdummyvar);
	ch1ifbandwidth = intdummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_numpoints1, &unshortintdummyvar); 
	ch1numbpoints = unshortintdummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_average_on1, &intdummyvar); 
	ch1averageon = intdummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_aver1, &unshortintdummyvar); 
	ch1averagefactor = unshortintdummyvar;
	ch1numberofmeasurements = 1;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_2, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 2;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_3, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 3;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_4, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 4;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_5, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 5;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_6, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 6;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_7, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 7;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_8, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 8;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_9, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 9;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_10, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 10;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_11, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 11;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_12, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 12;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_13, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 13;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_14, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 14;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_15, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 15;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_16, &intdummyvar);
	if (intdummyvar == 1) ch1numberofmeasurements = 16;	
	
	if (ch1numberofmeasurements >= 1)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_1, &chardummyvar);
		CH1M[1] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 1), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_1, &chardummyvar);
		CH1MFORM[1] = chardummyvar;
	}

	if (ch1numberofmeasurements >= 2)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_2, &chardummyvar);
		CH1M[2] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 2), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_2, &chardummyvar);
		CH1MFORM[2] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 2), ""); 

	if (ch1numberofmeasurements >= 3)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_3, &chardummyvar);
		CH1M[3] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 3), sparam[chardummyvar]); 				
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_3, &chardummyvar);
		CH1MFORM[3] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 3), ""); 
	
	if (ch1numberofmeasurements >= 4)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_4, &chardummyvar);
		CH1M[4] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 4), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_4, &chardummyvar);
		CH1MFORM[4] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 4), ""); 

	if (ch1numberofmeasurements >= 5)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_5, &chardummyvar);
		CH1M[5] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 5), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_5, &chardummyvar);
		CH1MFORM[5] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 5), ""); 
	
	if (ch1numberofmeasurements >= 6)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_6, &chardummyvar);
		CH1M[6] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 6), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_6, &chardummyvar);
		CH1MFORM[6] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 6), ""); 
	
	if (ch1numberofmeasurements >= 7)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_7, &chardummyvar);
		CH1M[7] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 7), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_7, &chardummyvar);
		CH1MFORM[7] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 7), ""); 
	
	if (ch1numberofmeasurements >= 8)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_8, &chardummyvar);
		CH1M[8] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 8), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_8, &chardummyvar);
		CH1MFORM[8] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 8), ""); 
	
	if (ch1numberofmeasurements >= 9)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_9, &chardummyvar);
		CH1M[9] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 9), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_9, &chardummyvar);
		CH1MFORM[9] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 9), ""); 
	
	if (ch1numberofmeasurements >= 10)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_10, &chardummyvar);
		CH1M[10] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 10), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_10, &chardummyvar);
		CH1MFORM[10] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 10), ""); 
	
	if (ch1numberofmeasurements >= 11)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_11, &chardummyvar);
		CH1M[11] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 11), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_11, &chardummyvar);
		CH1MFORM[11] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 11), ""); 
	
	if (ch1numberofmeasurements >= 12)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_12, &chardummyvar);
		CH1M[12] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 12), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_12, &chardummyvar);
		CH1MFORM[12] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 12), ""); 
	
	if (ch1numberofmeasurements >= 13)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_13, &chardummyvar);
		CH1M[13] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 13), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_13, &chardummyvar);
		CH1MFORM[13] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 13), ""); 
	
	if (ch1numberofmeasurements >= 14)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_14, &chardummyvar);
		CH1M[14] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 14), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_14, &chardummyvar);
		CH1MFORM[14] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 14), ""); 
	
	if (ch1numberofmeasurements >= 15)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_15, &chardummyvar);
		CH1M[15] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 15), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_15, &chardummyvar);
		CH1MFORM[15] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 15), ""); 		

	if (ch1numberofmeasurements >= 16)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas1_16, &chardummyvar);
		CH1M[16] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 16), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format1_16, &chardummyvar);
		CH1MFORM[16] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (1, 16), ""); 		

	GetCtrlVal(NETSETUP, NETSETUP_RING_sweeptype2, &chardummyvar);
	ch2sweeptype = chardummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_RING_sweepmode2, &chardummyvar);
	ch2sweepmode = chardummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_ifbandwidth2, &intdummyvar);
	ch2ifbandwidth = intdummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_numpoints2, &unshortintdummyvar); 
	ch2numbpoints = unshortintdummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_average_on2, &intdummyvar); 
	ch2averageon = intdummyvar;
	GetCtrlVal(NETSETUP, NETSETUP_NUMERIC_aver2, &unshortintdummyvar); 
	ch2averagefactor = unshortintdummyvar;
	ch2numberofmeasurements = 0; 
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_1, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 1;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_2, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 2;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_3, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 3;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_4, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 4;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_5, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 5;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_6, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 6;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_7, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 7;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_8, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 8;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_9, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 9;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_10, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 10;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_11, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 11;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_12, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 12;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_13, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 13;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_14, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 14;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_15, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 15;
	GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_16, &intdummyvar);
	if (intdummyvar == 1) ch2numberofmeasurements = 16;

	if (ch2numberofmeasurements >= 1)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_1, &chardummyvar);
		CH2M[1] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 1), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_1, &chardummyvar);
		CH2MFORM[1] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 1), ""); 

	if (ch2numberofmeasurements >= 2)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_2, &chardummyvar);
		CH2M[2] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 2), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_2, &chardummyvar);
		CH2MFORM[2] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 2), ""); 

	if (ch2numberofmeasurements >= 3)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_3, &chardummyvar);
		CH2M[3] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 3), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_3, &chardummyvar);
		CH2MFORM[3] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 3), ""); 
	
	if (ch2numberofmeasurements >= 4)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_4, &chardummyvar);
		CH2M[4] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 4), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_4, &chardummyvar);
		CH2MFORM[4] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 4), ""); 
	
	if (ch2numberofmeasurements >= 5)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_5, &chardummyvar);
		CH2M[5] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 5), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_5, &chardummyvar);
		CH2MFORM[5] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 5), ""); 
	
	if (ch2numberofmeasurements >= 6)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_6, &chardummyvar);
		CH2M[6] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 6), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_6, &chardummyvar);
		CH2MFORM[6] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 6), ""); 
	
	if (ch2numberofmeasurements >= 7)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_7, &chardummyvar);
		CH2M[7] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 7), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_7, &chardummyvar);
		CH2MFORM[7] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 7), ""); 
	
	if (ch2numberofmeasurements >= 8)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_8, &chardummyvar);
		CH2M[8] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 8), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_8, &chardummyvar);
		CH2MFORM[8] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 8), ""); 
	
	if (ch2numberofmeasurements >= 9)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_9, &chardummyvar);
		CH2M[9] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 9), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_9, &chardummyvar);
		CH2MFORM[9] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 9), ""); 
	
	if (ch2numberofmeasurements >= 10)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_10, &chardummyvar);
		CH2M[10] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 10), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_10, &chardummyvar);
		CH2MFORM[10] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 10), ""); 
	
	if (ch2numberofmeasurements >= 11)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_11, &chardummyvar);
		CH2M[11] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 11), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_11, &chardummyvar);
		CH2MFORM[11] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 11), ""); 
	
	if (ch2numberofmeasurements >= 12)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_12, &chardummyvar);
		CH2M[12] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 12), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_12, &chardummyvar);
		CH2MFORM[12] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 12), ""); 
	
	if (ch2numberofmeasurements >= 13)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_13, &chardummyvar);
		CH2M[13] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 13), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_13, &chardummyvar);
		CH2MFORM[13] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 13), ""); 
	
	if (ch2numberofmeasurements >= 14)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_14, &chardummyvar);
		CH2M[14] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 14), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_14, &chardummyvar);
		CH2MFORM[14] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 14), ""); 			

	if (ch2numberofmeasurements >= 15)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_15, &chardummyvar);
		CH2M[15] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 15), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_15, &chardummyvar);
		CH2MFORM[15] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 15), ""); 

	if (ch2numberofmeasurements >= 16)
	{
		GetCtrlVal(NETSETUP, NETSETUP_RING_meas2_16, &chardummyvar);
		CH2M[16] = chardummyvar;
		SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 16), sparam[chardummyvar]);
		GetCtrlVal(NETSETUP, NETSETUP_RING_format2_16, &chardummyvar);
		CH2MFORM[16] = chardummyvar;
	}
	else SetTableCellVal (FIELDPROBE, FIELDPROBE_GRID_NA_SETTINGS, MakePoint (2, 16), ""); 	

	return(0);
}

/*
int calcFP2_Points (void)
{
int index;
extern struct FP2PosGen temp2Nums;

	iFPPosValid = 0;

	FP2PosGenNums.iNumCol = temp2Nums.iNumCol;
	for (index = 1; index <= FP2PosGenNums.iNumCol; index++)
	{
		FP2PosGenNums.dPosCol[index] = temp2Nums.dPosCol[index];
	}

	FP2PosGenNums.iNumRow = temp2Nums.iNumRow;
	for (index = 1; index <= FP2PosGenNums.iNumRow; index++)
	{
		FP2PosGenNums.dPosRow[index] = temp2Nums.dPosRow[index];
	}

	
	calcFPPositions( );
	displayFPPositions( ); 
	displayPos();

	return 0;
}

*/











//*****************************************************************************
//	CVICALLBACK Functions
//							

int CVICALLBACK active1_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_2, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_2, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_2, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_2, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_3, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_3, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_3, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_3, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_3, 4);
			active1_3 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_3, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_3, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_3, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_3, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_4, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_4, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_4, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_4, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_4, 4);
			active1_4 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_4, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_4, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_4, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_4, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_5, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_5, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_5, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_5, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_5, 4);
			active1_5 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_5 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_5, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_5, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_5, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_5, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_6, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_6, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_6, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_6, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_6, 4);
			active1_6 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}


int CVICALLBACK active1_6 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_6, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_6, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_6, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_6, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_7, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_7, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_7, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_7, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_7, 4);
			active1_7 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_7 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_7, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_7, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_7, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_7, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_8, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_8, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_8, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_8, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_8, 4);
			active1_8 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_8 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_8, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_8, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_8, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_8, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_9, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_9, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_9, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_9, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_9, 4);
			active1_9 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_9 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_9, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_9, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_9, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_9, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_10, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_10, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_10, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_10, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_10, 4);
			active1_10 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_10 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_10, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_10, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_10, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_10, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_11, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_11, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_11, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_11, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_11, 4);
			active1_11 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_11 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_11, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_11, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_11, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_11, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_12, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_12, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_12, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_12, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_12, 4);
			active1_12 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_12 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_12, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_12, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_12, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_12, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_13, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_13, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_13, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_13, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_13, 4);
			active1_13 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_13 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_13, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_13, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_13, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_13, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_14, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_14, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_14, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_14, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_14, 4);
			active1_14 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_14 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_14, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_14, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_14, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_14, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_15, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_15, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_15, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_15, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_15, 4);
			active1_15 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_15 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_15, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_15, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_15, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_15, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_16, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_16, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_16, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_16, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format1_16, 4);
			active1_16 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active1_16 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_16, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_16, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_16, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_16, ATTR_VISIBLE, active); 
			break;
		}
	return 0;
}


int CVICALLBACK active2_1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_1, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_1, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_1, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_1, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_2, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_2, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_2, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_2, 0); 
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_2, 4);
			active2_2 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_2, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_2, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_2, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_2, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_3, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_3, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_3, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_3, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_3, 4);
			active2_3 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_3, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_3, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_3, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_3, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_4, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_4, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_4, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_4, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_4, 4);
			active2_4 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_4, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_4, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_4, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_4, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_5, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_5, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_5, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_5, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_5, 4);
			active2_5 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_5 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_5, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_5, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_5, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_5, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_6, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_6, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_6, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_6, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_6, 4);
			active2_6 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;			   
}

int CVICALLBACK active2_6 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_6, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_6, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_6, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_6, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_7, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_7, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_7, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_7, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_7, 4);
			active2_7 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_7 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_7, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_7, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_7, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_7, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_8, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_8, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_8, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_8, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_8, 4);
			active2_8 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_8 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_8, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_8, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_8, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_8, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_9, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_9, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_9, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_9, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_9, 4);
			active2_9 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_9 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_9, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_9, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_9, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_9, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_10, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_10, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_10, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_10, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_10, 4);
			active2_10 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_10 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_10, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_10, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_10, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_10, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_11, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_11, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_11, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_11, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_11, 4);
			active2_11 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_11 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_11, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_11, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_11, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_11, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_12, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_12, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_12, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_12, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_12, 4);
			active2_12 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_12 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_12, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_12, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_12, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_12, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_13, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_13, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_13, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_13, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_13, 4);
			active2_13 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_13 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_13, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_13, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_13, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_13, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_14, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_14, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_14, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_14, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_14, 4);
			active2_14 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_14 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_14, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_14, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_14, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_14, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_15, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_15, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_15, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_15, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_15, 4);
			active2_15 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_15 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_15, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_15, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_15, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_15, ATTR_VISIBLE, active); 
			SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_16, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_16, ATTR_VISIBLE, active);
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_16, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_16, 0);
			SetCtrlVal(NETSETUP, NETSETUP_RING_format2_16, 4);
			active2_16 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK active2_16 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_16, &active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_16, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_16, ATTR_VISIBLE, active);
			SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_16, ATTR_VISIBLE, active); 
			break;
		}
	return 0;
}

int CVICALLBACK load_setup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			
			SetCtrlAttribute(NETSETUP, NETSETUP_CB_netsetup_OK, ATTR_DIMMED, 1);
			SetCtrlAttribute(NETSETUP, NETSETUP_COMMAND_save, ATTR_DIMMED, 1);
			SetCtrlAttribute(NETSETUP, NETSETUP_COMMAND_load, ATTR_DIMMED, 1);
			
			GetDir(directory);
			error = FileSelectPopup (directory, "*.nsi", "*.nsi", "Load Setup File",
			     VAL_LOAD_BUTTON, 0, 0, 1, 1, pathName);
			
			if (FileExists(pathName, 0))
			{
				Load_Network_Setup_File(pathName);
			}
			else
			{
				//
			}
			
			SetCtrlAttribute(NETSETUP, NETSETUP_CB_netsetup_OK, ATTR_DIMMED, 0);
			SetCtrlAttribute(NETSETUP, NETSETUP_COMMAND_save, ATTR_DIMMED, 0);
			SetCtrlAttribute(NETSETUP, NETSETUP_COMMAND_load, ATTR_DIMMED, 0);

			break;
		}
	return 0;
}

int CVICALLBACK save_setup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			
			SetCtrlAttribute(NETSETUP, NETSETUP_CB_netsetup_OK, ATTR_DIMMED, 1);
			SetCtrlAttribute(NETSETUP, NETSETUP_COMMAND_save, ATTR_DIMMED, 1);
			SetCtrlAttribute(NETSETUP, NETSETUP_COMMAND_load, ATTR_DIMMED, 1);
			
			GetDir(directory);
			error = FileSelectPopup (directory, "*.nsi", "*.nsi", "Saved Setup File",
			     VAL_SAVE_BUTTON, 0, 0, 1, 1, pathName);
			
			Save_Network_Setup_File(pathName);
			
			SetCtrlAttribute(NETSETUP, NETSETUP_CB_netsetup_OK, ATTR_DIMMED, 0);
			SetCtrlAttribute(NETSETUP, NETSETUP_COMMAND_save, ATTR_DIMMED, 0);
			SetCtrlAttribute(NETSETUP, NETSETUP_COMMAND_load, ATTR_DIMMED, 0);
			
			break;
		}
	return 0;
}

int CVICALLBACK average_on1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_average_on1, &active);   
			SetCtrlAttribute(NETSETUP, NETSETUP_NUMERIC_aver1, ATTR_DIMMED, !active);   
			break;
		}
	return 0;
}

int CVICALLBACK average_on2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
			case EVENT_COMMIT:
			GetCtrlVal(NETSETUP, NETSETUP_RADIO_average_on2, &active);   
			SetCtrlAttribute(NETSETUP, NETSETUP_NUMERIC_aver2, ATTR_DIMMED, !active);   
			break;
		}
	return 0;
}







int CVICALLBACK calcFP_Points (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		
			iFPPosValid = 0;
		
			GetCtrlVal (hPanelMain, FIELDPROBE_NUM_NUM_COL, 		 &FPPosGenNums.iNumCol);
			GetCtrlVal (hPanelMain, FIELDPROBE_NUM_START_COL_POS, &FPPosGenNums.dPosFirstCol);
			GetCtrlVal (hPanelMain, FIELDPROBE_NUM_LAST_COL_POS,  &FPPosGenNums.dPosLastCol);
			
			
			SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_START_COL_POS, ATTR_MAX_VALUE, FPPosGenNums.dPosLastCol);
			SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_LAST_COL_POS,  ATTR_MIN_VALUE, FPPosGenNums.dPosFirstCol);
			
		
			GetCtrlVal (hPanelMain, FIELDPROBE_NUM_NUM_ROWS, 	 &FPPosGenNums.iNumRow);
			GetCtrlVal (hPanelMain, FIELDPROBE_NUM_START_ROW_POS, &FPPosGenNums.dPosFirstRow);
			GetCtrlVal (hPanelMain, FIELDPROBE_NUM_LAST_ROW_POS,  &FPPosGenNums.dPosLastRow);
			
	
			SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_START_ROW_POS, ATTR_MAX_VALUE, FPPosGenNums.dPosLastRow);
			SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_LAST_ROW_POS,  ATTR_MIN_VALUE, FPPosGenNums.dPosFirstRow);
			
			SetCtrlVal (hPanelMain, FIELDPROBE_TEXTMSG_FILE, "File = None");
			
			calcFPPositions( );
			displayFPPositions( ); 
			displayPos();

		break;
		}
	return 0;
}

int CVICALLBACK loadFile (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

	switch( event ) {
		case EVENT_COMMIT:
			loadFPPosFile( );
		break;
	}
	return 0;
}

int CVICALLBACK saveFile (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

	switch( event ) {
		case EVENT_COMMIT:
			saveFPPosFile( );
			break;
	}
	return 0;
} 

int CVICALLBACK goNextPosition (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int iStatus;

	switch (event)
		{
		case EVENT_COMMIT:
		
			iCurrentFPPoint++;
			
			if( iCurrentFPPoint >= iNumFPPoints )
			{
				iCurrentFPPoint = 0;
			}
			
			goToPointPosition();
		

		break;
		}
	return 0;
}

int CVICALLBACK goFirstPosition (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			iCurrentFPPoint = 0;
			goToPointPosition();
		break;
		}
	return 0;
}

int CVICALLBACK gotoSelectedPosition (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int iIndex;

	switch (event)
		{
		case EVENT_COMMIT:
		
			GetCtrlIndex (hPanelMain, FIELDPROBE_RING_GOTO_POS, &iIndex);
			
			if( ( iIndex >= 0 ) && ( iIndex < iNumFPPoints ) ) {
				iCurrentFPPoint = iIndex;
				goToPointPosition();
			}
			

		break;
		}
	return 0;
}

int CVICALLBACK network_setup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		
			//open network setup window
			if ((hNetPanel = LoadPanel (0, "Setup.uir", NETSETUP)) < 0) return -1;

			DisplayPanel (hNetPanel);
		
		
			//*******************************

			SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_startfreq, startfreq); 
			SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_stopfreq, stopfreq); 	
			SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_powerlevel, powerlevel); 	
			SetCtrlVal(NETSETUP, NETSETUP_RING_sweeptype1, ch1sweeptype); 	
			SetCtrlVal(NETSETUP, NETSETUP_RING_sweepmode1, ch1sweepmode); 	
			SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_ifbandwidth1, ch1ifbandwidth); 	
		   	SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_numpoints1, ch1numbpoints); 	
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_average_on1, ch1averageon); 	
			SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_aver1, ch1averagefactor);
			if (ch1averageon == 1) SetCtrlAttribute(NETSETUP, NETSETUP_NUMERIC_aver1, ATTR_DIMMED, 0);
			active1_2 (NETSETUP, NETSETUP_RADIO_active1_2, EVENT_COMMIT, 0, 0, 0);		//clear channel 1 measurement settings

			if (ch1numberofmeasurements >= 1)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_1, CH1M[1]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_1, CH1MFORM[1]); 	
			}
	
			if (ch1numberofmeasurements >= 2)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_2, CH1M[2]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_2, CH1MFORM[2]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_2, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_2, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_2, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_2, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_3, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_3, ATTR_VISIBLE, 1);
			}
	
			if (ch1numberofmeasurements >= 3)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_3, CH1M[3]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_3, CH1MFORM[3]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_3, 1);

				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_3, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_3, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_3, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_4, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_4, ATTR_VISIBLE, 1);
			}

			if (ch1numberofmeasurements >= 4)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_4, CH1M[4]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_4, CH1MFORM[4]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_4, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_4, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_4, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_4, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_5, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_5, ATTR_VISIBLE, 1);

			}

			if (ch1numberofmeasurements >= 5)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_5, CH1M[5]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_5, CH1MFORM[5]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_5, 1);

				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_5, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_5, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_5, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_6, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_6, ATTR_VISIBLE, 1);	
			}

			if (ch1numberofmeasurements >= 6)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_6, CH1M[6]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_6, CH1MFORM[6]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_6, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_6, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_6, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_6, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_7, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_7, ATTR_VISIBLE, 1);		
			}

			if (ch1numberofmeasurements >= 7)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_7, CH1M[7]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_7, CH1MFORM[7]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_7, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_7, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_7, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_7, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_8, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_8, ATTR_VISIBLE, 1);		
			}

			if (ch1numberofmeasurements >= 8)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_8, CH1M[8]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_8, CH1MFORM[8]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_8, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_8, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_8, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_8, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_9, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_9, ATTR_VISIBLE, 1);		
			}
	
			if (ch1numberofmeasurements >= 9)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_9, CH1M[9]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_9, CH1MFORM[9]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_9, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_9, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_9, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_9, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_10, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_10, ATTR_VISIBLE, 1);		
			}

			if (ch1numberofmeasurements >= 10)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_10, CH1M[10]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_10, CH1MFORM[10]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_10, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_10, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_10, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_10, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_11, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_11, ATTR_VISIBLE, 1);		
			}

		 	if (ch1numberofmeasurements >= 11)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_11, CH1M[11]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_11, CH1MFORM[11]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_11, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_11, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_11, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_11, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_12, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_12, ATTR_VISIBLE, 1);		
			}

			if (ch1numberofmeasurements >= 12)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_12, CH1M[12]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_12, CH1MFORM[12]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_12, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_12, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_12, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_12, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_13, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_13, ATTR_VISIBLE, 1);		
			}

			if (ch1numberofmeasurements >= 13)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_13, CH1M[13]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_13, CH1MFORM[13]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_13, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_13, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_13, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_13, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_14, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_14, ATTR_VISIBLE, 1);		
			}

			if (ch1numberofmeasurements >= 14)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_14, CH1M[14]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_14, CH1MFORM[14]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_14, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_14, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_14, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_14, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_15, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_15, ATTR_VISIBLE, 1);		
			}

			if (ch1numberofmeasurements >= 15)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_15, CH1M[15]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_15, CH1MFORM[15]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_15, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_15, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_15, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_15, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active1_16, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_1_16, ATTR_VISIBLE, 1);		
			}

			if (ch1numberofmeasurements == 16)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas1_16, CH1M[16]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format1_16, CH1MFORM[16]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active1_16, 1);
		
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas1_16, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format1_16, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_1_16, ATTR_VISIBLE, 1); 
			}


			SetCtrlVal(NETSETUP, NETSETUP_RING_sweeptype2, ch2sweeptype);  
 			SetCtrlVal(NETSETUP, NETSETUP_RING_sweepmode2, ch2sweepmode);  
 			SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_ifbandwidth2, ch2ifbandwidth); 	 
			SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_numpoints2, ch2numbpoints); 	
			SetCtrlVal(NETSETUP, NETSETUP_RADIO_average_on2, ch2averageon); 
			SetCtrlVal(NETSETUP, NETSETUP_NUMERIC_aver2, ch2averagefactor);
			if (ch2averageon == 1) SetCtrlAttribute(NETSETUP, NETSETUP_NUMERIC_aver2, ATTR_DIMMED, 0); 
		  	active2_1 (NETSETUP, NETSETUP_RADIO_active2_1, EVENT_COMMIT, 0, 0, 0);		//clear channel 2 measurement settings

			if (ch2numberofmeasurements > 0)
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_1, CH2M[1]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_1, CH2MFORM[1]);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_1, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_1, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_1, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_1, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_2, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_2, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 1) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_2, CH2M[2]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_2, CH2MFORM[2]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_2, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_2, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_2, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_2, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_2, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_3, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_3, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 2) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_3, CH2M[3]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_3, CH2MFORM[3]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_3, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_3, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_3, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_3, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_3, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_4, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_4, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 3) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_4, CH2M[4]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_4, CH2MFORM[4]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_4, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_4, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_4, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_4, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_4, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_5, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_5, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 4) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_5, CH2M[5]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_5, CH2MFORM[5]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_5, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_5, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_5, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_5, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_5, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_6, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_6, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 5) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_6, CH2M[6]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_6, CH2MFORM[6]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_6, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_6, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_6, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_6, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_6, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_7, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_7, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 6) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_7, CH2M[7]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_7, CH2MFORM[7]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_7, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_7, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_7, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_7, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_7, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_8, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_8, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 7) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_8, CH2M[8]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_8, CH2MFORM[8]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_8, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_8, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_8, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_8, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_8, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_9, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_9, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 8) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_9, CH2M[9]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_9, CH2MFORM[9]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_9, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_9, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_9, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_9, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_9, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_10, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_10, ATTR_VISIBLE, 1);
			}
			
			if (ch2numberofmeasurements > 9) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_10, CH2M[10]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_10, CH2MFORM[10]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_10, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_10, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_10, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_10, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_10, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_11, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_11, ATTR_VISIBLE, 1);
			}			
			
			if (ch2numberofmeasurements > 10) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_11, CH2M[11]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_11, CH2MFORM[11]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_11, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_11, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_11, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_11, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_11, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_12, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_12, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 11) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_12, CH2M[12]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_12, CH2MFORM[12]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_12, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_12, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_12, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_12, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_12, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_13, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_13, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 12) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_13, CH2M[13]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_13, CH2MFORM[13]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_13, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_13, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_13, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_13, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_13, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_14, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_14, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 13) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_14, CH2M[14]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_14, CH2MFORM[14]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_14, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_14, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_14, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_14, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_14, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_15, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_15, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 14) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_15, CH2M[15]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_15, CH2MFORM[15]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_15, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_15, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_15, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_15, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_15, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(NETSETUP, NETSETUP_RADIO_active2_16, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_DECORATION_2_16, ATTR_VISIBLE, 1);
			}

			if (ch2numberofmeasurements > 15) 
			{
				SetCtrlVal(NETSETUP, NETSETUP_RING_meas2_16, CH2M[16]); 	
				SetCtrlVal(NETSETUP, NETSETUP_RING_format2_16, CH2MFORM[16]); 
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_16, 1);
		
				SetCtrlVal(NETSETUP, NETSETUP_RADIO_active2_16, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_meas2_16, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_RING_format2_16, ATTR_VISIBLE, 1);
				SetCtrlAttribute(NETSETUP, NETSETUP_TEXTMSG_2_16, ATTR_VISIBLE, 1); 
			}		
		
		
		
		
		
		
		
		
		
		
		
			//****************************
		
			RunUserInterface ();  
			
			break;
		}
	return 0;
}

int CVICALLBACK emergencyStop (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			FP_EmergencyShutdownCmd();
			break;
		}
	return 0;
}

int CVICALLBACK quit (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			network_analyzer_close();
			QuitUserInterface(0);
			break;
		}
	return 0;
}

int CVICALLBACK init (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int iStatus;
char msg[1024];
int hFile;
char proj_dir[1024];
char filepath[1024];
int len;

	switch( event ) {
		case EVENT_COMMIT:

		
		
			SetCtrlAttribute (hPanelInit, PNL_INIT_CB_INIT, ATTR_VISIBLE, 0);
			SetCtrlAttribute (hPanelInit, PNL_INIT_TEXTMSG, ATTR_VISIBLE, 1);
			SetCtrlAttribute (hPanelInit, PNL_INIT_CB_EMERG_STOP, ATTR_VISIBLE, 1);
			ProcessSystemEvents(); 


			// make sure the Data directory exists
			iStatus = MakeDir( data_dir );
			if( ( ( iStatus < 0 ) && ( iStatus > -9 ) ) || ( iStatus < -9 ) )
			{
				sprintf( msg, "Error Creating %s.\nProgram Will Exit." , data_dir );
				MessagePopup ("Unrecoverable Error", msg);
				QuitUserInterface (0);
				exit (EXIT_SUCCESS);
				return( -1 );
			}
				
			
			// setup the initial state of the Network Analyzer
			Network_Setup = 0;	// Indicates that the network analyzer has not been setup.  Need to open network setup panel to
								// setup analyzer and set this variable to 1.
			
			
#ifndef NOSCAN

			// open COM port for communications
			iStatus = OpenComConfig ( iComPort, "", 9600, 0, 8, 1, 512, 512);
			
			if( iStatus != 0 ) {
				sprintf( msg, "Error Opening COM %d.\nProgram Will Exit.", iComPort );
				MessagePopup ("Unrecoverable Error", msg);
				QuitUserInterface (0);
				exit (EXIT_SUCCESS);
				return( -1 );
			}

#endif
			
			iStatus = FP_initialize( );
			if( iStatus != 0 ) {
				MessagePopup ("Unrecoverable Error", "Error Initializing Field Probe.\nProgram Will Exit.");
	 			iStart = -1;
				QuitUserInterface (0);
				exit (EXIT_SUCCESS);
				return( - 1 );
			}


			// get current position
			iStatus = FP_GetCurrentPositionInInches( kWidthController, &posXInInches );
			iStatus = FP_GetCurrentPositionInInches( kHeightController, &posYInInches );

		
		    // open communications with network analyzer
			iStatus = network_analyzer_open( );
			if( iStatus != 0 ) {
				MessagePopup ("Unrecoverable Error", "Error Connecting To Network Analyzer.\nProgram Will Exit.");
				QuitUserInterface (0);
				exit (EXIT_SUCCESS);
				return( -1 );
			}

		
			calcFP_Points( hPanelMain, FIELDPROBE_NUM_START_COL_POS, EVENT_COMMIT, NULL, 0, 0 );
			goFirstPosition(hPanelMain, FIELDPROBE_CB_GO_FIRST_POS, EVENT_COMMIT, NULL, 0, 0 );		
	


			iStart = 0;
			DiscardPanel (hPanelInit);
	

			enableAllControls( 1 );

		break;
	}
	return 0;
}

int CVICALLBACK beginExperiment (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int iStatus;
char msg[1024];

	switch( event ) {
		case EVENT_COMMIT:

			enableAllControls( 0 );
			
			// field probe must be at one of the valid positions to start
			if( iFPPosValid != 1 )
			{
				sprintf( msg, "You Must Move Field Probe To A Valid Position." );
				MessagePopup ("Error", msg);
				enableAllControls( 1 );
				return( -1 );
			}
			
			
			
			// get experiment name from user
			exp_name[0] = 0x0;
			iStatus = GenericMessagePopup ("Begin Experiment", "Enter Experiment Name", "Cancel", "OK", "", exp_name, 1023, 0,
										   VAL_GENERIC_POPUP_INPUT_STRING, VAL_GENERIC_POPUP_BTN2, VAL_GENERIC_POPUP_NO_CTRL);

			if( ( strlen( exp_name ) == 0 ) || ( iStatus != 2 ) ) {
				enableAllControls( 1 );
				return( -1 );
			}
	
			// create the experiment directory
			sprintf( exp_path, "%s\\%s", data_dir, exp_name );	
			iStatus = MakeDir( exp_path );
			if( iStatus == -9 ) {
				sprintf( msg, "Experiment %s already exists.", exp_path );
				MessagePopup ("Error", msg);
				enableAllControls( 1 );
				return( -1 );
			}
			else if( iStatus < 0 ) {
				sprintf( msg, "Error Creating %s.", exp_path );
				MessagePopup ("Error", msg);
				enableAllControls( 1 );
				return( -1 );
			}
	
				
			// create the experiment's raw data directory
			sprintf( exp_path, "%s\\RawData", exp_path );	
			iStatus = MakeDir( exp_path );
			if( iStatus == -9 ) {
				sprintf( msg, "Directory %s already exists.", exp_path );
				MessagePopup ("Error", msg);
				enableAllControls( 1 );
				return( -1 );
			}
			else if( iStatus < 0 ) {
				sprintf( msg, "Error Creating %s.", exp_path );
				MessagePopup ("Error", msg);
				enableAllControls( 1 );
				return( -1 );
			}
	
			// update "Experiment" text box
			sprintf( msg, "Experiment = %s", exp_name );
			SetCtrlVal (hPanelMain, FIELDPROBE_TEXTMSG_EXP, msg);
			
			
			// save the field probes point number and position
			iStatus = saveFieldProbePointPositions( );
			if( iStatus != 0 ) {
				enableAllControls( 1 );
				return( -1 );
			}

			// save the network analyzer setup
			iStatus = saveNetworkAnalyzerSetup( );
			if( iStatus != 0 ) {
				enableAllControls( 1 );
				return( -1 );
			}

			// get the frequency points
			iStatus = network_analyzer_collect_freqs( );
 			if( iStatus != 0 ) {
				enableAllControls( 1 );
				return( -1 );
			}

			// save the frequency points
			iStatus = saveFrequencyPoints( );
			if( iStatus != 0 ) {
				enableAllControls( 1 );
				return( -1 );
			}
			
			network_analyzer_enable_display( 0 );

			// begin the data collection
			iStopExperiment = 0;
			SetCtrlAttribute( hPanelMain, FIELDPROBE_CB_STOP_EXP, ATTR_DIMMED, 0 );
			iStatus = runExperiment( );
			SetCtrlAttribute( hPanelMain, FIELDPROBE_CB_STOP_EXP, ATTR_DIMMED, 1 );

			network_analyzer_enable_display( 1 );

			MessagePopup ("Success", "Experiment Finished Without Error.");

			displayFPPositions( ); 
			displayPos();
			
			enableAllControls( 1 );

		break;
	}
	return 0;
}

int CVICALLBACK stopExperiment (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch( event ) {
		case EVENT_COMMIT:

			iStopExperiment = 1;
			SetCtrlAttribute( hPanelMain, FIELDPROBE_CB_STOP_EXP, ATTR_DIMMED, 1 );
		break;
	}
	return 0;
}

int CVICALLBACK collectAndDisplay (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int iStatus;

	switch(event) {
		case EVENT_TIMER_TICK:

			iStatus = network_analyzer_trigger( );
			if( iStatus != 0 ) {
				return( -1 );
			}
	
			ProcessSystemEvents(); 

			iStatus = network_analyzer_collect_data( );
			if( iStatus != 0 ) {
				return( -1 );
			}

			ProcessSystemEvents(); 

//			iStatus = convert_asciis_to_doubles( );
//			if( iStatus != 0 ) {
//				return( -1 );
//			}
//  
//			ProcessSystemEvents(); 
//
//			iStatus = plot_doubles( );
//			if( iStatus != 0 ) {
//				return( -1 );
//			}
//
//			ProcessSystemEvents(); 

		break;
	}
	return 0;
}


int CVICALLBACK netsetup_OK (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		
			Network_Setup = 1;
			readNetworkSetup();
			downloadNetworkSetup();
			
			SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_BEGIN_EXP, ATTR_DIMMED, 0); 
		
			QuitUserInterface(0);
			DiscardPanel(hNetPanel);  
			break;
		}
	return 0;
}


	

	

int CVICALLBACK position_data_type (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
int temp;

	switch (event)
		{
		case EVENT_COMMIT:

			GetCtrlAttribute (hPanelMain, FIELDPROBE_BINARYSWITCH, ATTR_CTRL_VAL , &temp);
			if (temp == 0)
			{
				//make controls on 'Random Delta' panel invisible
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_NUM_COL_2, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_NUM_ROWS_2, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_TEXTMSG_FILE_2, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_LOAD_FP_POS_FILE_2, ATTR_VISIBLE, 0);
				
				//make controls on 'Fixed Delta' panel visible
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_NUM_COL, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_START_COL_POS, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_LAST_COL_POS, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_COL_SPACING, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_NUM_ROWS, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_START_ROW_POS, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_LAST_ROW_POS, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_ROW_SPACING, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_TEXTMSG_FILE, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_LOAD_FP_POS_FILE, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_SAVE_FP_POS_FILE, ATTR_VISIBLE, 1);
				
				calcFPPositions( );
				displayFPPositions( );
				displayPos( );
			}
			else
			{
				//make controls on 'Random Delta' panel visible
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_NUM_COL_2, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_NUM_ROWS_2, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_TEXTMSG_FILE_2, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_LOAD_FP_POS_FILE_2, ATTR_VISIBLE, 1);
				
				//make controls on 'Fixed Delta' panel invisible
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_NUM_COL, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_START_COL_POS, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_LAST_COL_POS, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_COL_SPACING, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_NUM_ROWS, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_START_ROW_POS, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_LAST_ROW_POS, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_NUM_ROW_SPACING, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_TEXTMSG_FILE, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_LOAD_FP_POS_FILE, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hPanelMain, FIELDPROBE_CB_SAVE_FP_POS_FILE, ATTR_VISIBLE, 0);
				
				calcFP2Positions( );
				displayFPPositions( );
				displayPos( );
				
			}




//update list of positions in drop-down box



			break;
		}
	return 0;
}

int CVICALLBACK loadFile2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			loadFPPosFile( );
			break;
		}
	return 0;
}

