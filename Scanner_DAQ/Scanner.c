/******************************************************************************
*																			  *
*	Filename:	Scanner.c							     					  *
*	Date:		13 November 2006											  *
*																			  *
******************************************************************************/

#include <ansi_c.h>
#include <cvirte.h>	
#include "Defines.h"
#include "E5071.h"
#include <formatio.h>
#include "inifile.h"
#include "Plot.h"
#include "Points.h"
#include <rs232.h>
#include "SaveData.h" 
#include <Setup.h> 
#include "StepperControllerIF.h"
#include <userint.h>
#include <utility.h>
#include "agena.h"

//#define NOSCAN

int hPanelMain;
int hPanelInit;
static int hPanelDrive;

char ascii_freqs_ch1[65536];
char ascii_freqs_ch2[65536];

int iCurrentFPPoint;

// ***************************************************************************************************************

int goToPointPosition ( void );
int runExperiment( void );
int enableAllControls( int iEnable );
extern int readNetworkSetup(void);

// ***************************************************************************************************************



int main(int argc, char *argv[])
{
    if (InitCVIRTE (0, argv, 0) == 0) 
        return (-1);    /* out of memory */
        
	//open FIELD PROBE window
	if ((hPanelMain = LoadPanel (0, "Setup.uir", FIELDPROBE)) < 0) return -1;



	enableAllControls(0);
	
	if ((hPanelInit = LoadPanel (hPanelMain, "Setup.uir", PNL_INIT)) < 0)
	{
		return(-1);
	}
	
//	SetPanelAttribute (hPanelMain, ATTR_WINDOW_ZOOM, VAL_MAXIMIZE);
	
	DisplayPanel (hPanelMain);
	
	DisplayPanel (hPanelInit);	
	
	RunUserInterface ();
	DiscardPanel(hPanelMain);

    return 0;       
}
