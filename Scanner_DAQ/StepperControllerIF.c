/******************************************************************************
*																			  *
*	Filename:	StepperControllerIF.c				     					  *
*	Version:	2.0.0														  *
*	Date:		15 June 2007												  *
*																			  *
******************************************************************************/

#include <userint.h>
#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include "StepperControllerIF.h"

//#define NOSCAN

//*****************************************************************************
//	Variable Declarations
//	

extern int iStart;
extern int iComPort;
static double dMaxVelocity = 1.0;
static double dMaxAcceleration = 0.5;
static double dHeightCal = 0.000390136121975;  // inches/step
static double dWidthCal  = 0.000389979983108;  // inches/step


//*****************************************************************************
//	Functions
//

int FP_initialize( void )
{
int iStatus;
int iController;
char cmd[64];

#ifndef NOSCAN
	
		// set timeout for COM Port
		SetComTime (iComPort, 5.0);
	// might have to change this timeout for different reasons!!!!!!

		// see if controllers are present
	
		// turn rs232 echo on
		sprintf( cmd, "1SSA0%c2SSA0%c", 0x0D, 0x0D );
		ComWrt (iComPort, cmd, strlen(cmd));
		Delay( 2 );
	
	
		for( iController = 1; iController <= 2; iController++ ) {
	
	
			// reset positioner
			sprintf( cmd, "%dZ%c", iController, 0x0D );
			ComWrt (iComPort, cmd, strlen(cmd));
			Delay( 2 );
	
			// enable current to motors positioner
			sprintf( cmd, "%dST0%c", iController, 0x0D );
			ComWrt (iComPort, cmd, strlen(cmd));

		
			// move to home position at a slow acceleration and velocity
			iStatus = FP_GoHome( iController );
			if( iStatus != 0 )
			{
				return( -1 );
			}

			iStatus = FP_SetHomePosition( iController );

		}
	
#endif

	return( 0 );
}

// ***************************************************************************************************************

int FP_SetHomePosition( int iController )
{
char cmd[64];

#ifndef NOSCAN

	// set the position index counter to zero
	sprintf( cmd, "%dPZ%c", iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));

	// set indexer to mode normal and mode positioner absolute
	sprintf( cmd, "%dMN%c%dMPA%c", iController, 0x0D, iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));

	// set user selected acceleration and velocity
	FP_SetAccelAndVelocity( iController, dMaxAcceleration, dMaxVelocity );

	// move just off the limit switch
	FP_GoToInCounts( iController, 100, 0 );

	// set the position index counter to zero
	sprintf( cmd, "%dPZ%c", iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));
#endif

	return( 0 );
}

// ***************************************************************************************************************

int FP_ShutdownCmd( void )
{
char cmd[64];

#ifndef NOSCAN

	sprintf( cmd, "ST1%c", 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));

#endif

	return( 0 );
}

// ***************************************************************************************************************

int FP_EmergencyShutdownCmd( void )
{
char cmd[64];
int iStatus;

#ifndef NOSCAN

//	sprintf( cmd, "S%c", 0x0D );
//	ComWrt (iComPort, cmd, strlen(cmd));
	sprintf( cmd, "%cS%c1ST1%c2ST1%c", 0x0D, 0x0D, 0x0D, 0x0D );		  // WHY DOESN'T THIS WORK RIGHT
	
	iStatus = ComWrt (iComPort, cmd, strlen(cmd));
	
	Delay( 0.5 );
	iStart = -1;
	QuitUserInterface (0);
	exit (EXIT_SUCCESS);

#endif

	return( 0 );
}

// ***************************************************************************************************************

int FP_GoHome( int iController )
{
int iStatus;
char cmd[64];
char rsp[64];
int iByte;
int iCount1;
double dGoHomeTimeLimit = 30;	//seconds
double dDelay = 0.1;			//seconds
int iNumIterations = dGoHomeTimeLimit / dDelay;
int iNumCRs = 0;

int iCCWLimitState;
int iCWLimitState;

#ifndef NOSCAN

	FP_SetAccelAndVelocity( iController, 0.5, 0.5 );

	sprintf( cmd, "%dMC%c", iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));
	sprintf( cmd, "%dH-%c", iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));
	sprintf( cmd, "%dG%c",  iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));
	
	// simply wait for the two CRs. the one from the transmitted
	// command and the one after the command completion
	for(iCount1 = 0; iCount1 < iNumIterations; iCount1++ ) {
	
		ProcessSystemEvents(); 
	
		iStatus = FP_GetLimitSwitchsState( iController, &iCCWLimitState, &iCWLimitState );
		
		if( iCCWLimitState == 1 )
		{
			return( 0 );
		}
		
		Delay( dDelay );
	}
	
	// if we got here then we timed out on out Go Home Command
	FP_ShutdownCmd( );

#endif

	return( -1 );
	
}

// ***************************************************************************************************************

int FP_GoFarLimit( int iController )
{
int iStatus;
char cmd[64];
char rsp[64];
int iByte;
int iCount1;
double dGoHomeTimeLimit = 30;	//seconds
double dDelay = 0.25;			//seconds
int iNumIterations = dGoHomeTimeLimit / dDelay;
int iNumCRs = 0;

int iCCWLimitState;
int iCWLimitState;

#ifndef NOSCAN

	FP_SetAccelAndVelocity( iController, 0.5, 0.5 );

 	
	sprintf( cmd, "%dMC%c", iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));
	sprintf( cmd, "%dH+%c", iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));
	sprintf( cmd, "%dG%c",  iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));
	
	// simply wait for the two CRs. the one from the transmitted
	// command and the one after the command completion
	for(iCount1 = 0; iCount1 < iNumIterations; iCount1++ ) {
	
		ProcessSystemEvents(); 
	
		iStatus = FP_GetLimitSwitchsState( iController, &iCCWLimitState, &iCWLimitState );
		
		if( iCWLimitState == 1 )
		{
			return( 0 );
		}
		
		Delay( dDelay );
	}
	
	// if we got here then we timed out on out Go Home Command
	FP_ShutdownCmd( );

#endif

	return( -1 );
	
}

// ***************************************************************************************************************

int FP_GetLimitSwitchsState( int iController, int *iCCWLimitState, int *iCWLimitState )
{
char cmd[64];
char rsp[64];
int iByte;
double dCOMTimeOut = 0.1;		//seconds
int iStatus;

#ifndef NOSCAN

	SetComTime( iComPort, dCOMTimeOut ); 

	Delay( 0.1 );  // was 0.25
	FlushInQ( iComPort );

	sprintf( cmd, "%dIS%c", iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));

	// this will read the echoed command that was sent
 	iStatus = ComRdTerm (iComPort, rsp, 15, 0x0D);
 	if( iStatus < 0 )
 	{
 		return( -1 );
 	}
 	
	// this will read the response to IS command that was sent
 	iStatus = ComRdTerm (iComPort, rsp, 15, 0x0D);
 	if( iStatus < 0 )
 	{
 		return( -1 );
 	}
 	
/* 	
 	
	if( strlen(rsp) != 11 ) {	  // 11th byte is a 0x0C
//	if( strlen(rsp) != 10 ) {
		return( -1 );
	}
*/	
	
	if( rsp[4] == '0' )
	{
		*iCCWLimitState = 0;
	}
	else if(  rsp[4] == '1' )
	{
		*iCCWLimitState = 1;
	}
	else
	{
		*iCCWLimitState = -1;
	}



	if( rsp[5] == '0' )
	{
		*iCWLimitState = 0;
	}
	else if(  rsp[5] == '1' )
	{
		*iCWLimitState = 1;
	}
	else
	{
		*iCWLimitState = -1;
	}

#endif
	
	return( 0 );

}

// ***************************************************************************************************************

int FP_GoToInInches( int iController, double dPosInInches, int iReturnImmediate )
{
int iStatus;
int iPosInCounts;

#ifndef NOSCAN

	if( iController == kWidthController )
	{
		iPosInCounts =  (int)( dPosInInches / dWidthCal );
	}
	else if( iController == kHeightController )
	{ 
		iPosInCounts =  (int)( dPosInInches / dHeightCal );
	}
	else
	{
		return( -1 );
	}


	iStatus = FP_GoToInCounts( iController, iPosInCounts, iReturnImmediate );
	if( iStatus != 0 )
	{
		return( -1 );
	}

#endif

	return( 0 );
}

// ***************************************************************************************************************

int FP_GoToInCounts( int iController, int iPosInCounts, int iReturnImmediate )
{
int iStatus;
char cmd[64];
char rsp[64];
int iByte;
int iCount1;
double dGoHomeTimeLimit = 40;	//seconds
double dDelay = 0.25;		//seconds
int iNumIterations = dGoHomeTimeLimit / dDelay;
int iNumCRs = 0;

#ifndef NOSCAN

	SetComTime( iComPort, dDelay ); 
	
	Delay( 0.25 );
	FlushInQ( iComPort );


	sprintf( cmd, "%dD%d%c", iController, iPosInCounts, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));
 	iStatus = ComRdTerm (iComPort, rsp, 15, 0x0D);
	
	sprintf( cmd, "%dG%c", iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));
 	iStatus = ComRdTerm (iComPort, rsp, 15, 0x0D);
	
	
	if( iReturnImmediate )
	{
		return( 0 );
	}
	

	for(iCount1 = 0; iCount1 < iNumIterations; iCount1++ )
	{
	
		ProcessSystemEvents(); 

		sprintf( cmd, "%dR%c",  iController, 0x0D );
		ComWrt (iComPort, cmd, strlen(cmd));
	 	iStatus = ComRdTerm (iComPort, rsp, 15, 0x0D);
	 	iStatus = ComRdTerm (iComPort, rsp, 15, 0x0D);
		rsp[2] = 0x0;// don't know why I'm getting extra bytes from the unit???
		if( ( 0 == strcmp( rsp, "*R" ) ) || ( 0 == strcmp( rsp, "*S" ) ) ) 
		{
			return( 0 );
		}
	
		Delay( dDelay );	
	}
	
	// if we got here then we timed out on out Go To Command
	FP_ShutdownCmd( );

	return( -1 );

#else

	return( 0 );

#endif
}

// ***************************************************************************************************************

int FP_GetBusyState( int iController )
{
int iStatus;
char cmd[64];
char rsp[64];
double dCOMTimeOut = 0.25;     //seconds

#ifndef NOSCAN

	SetComTime( iComPort, dCOMTimeOut ); 
	
	Delay( 0.25 );
	FlushInQ( iComPort );

	sprintf( cmd, "%dR%c",  iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));
 	iStatus = ComRdTerm (iComPort, rsp, 15, 0x0D);
 	iStatus = ComRdTerm (iComPort, rsp, 15, 0x0D);
	rsp[2] = 0x0;// don't know why I'm getting extra bytes from the unit???
	if( ( 0 == strcmp( rsp, "*R" ) ) || ( 0 == strcmp( rsp, "*S" ) ) )
	{
		return( 0 );   // not busy
	}

	return( 1 );// busy

#else

	return( 0 );

#endif

}

// ***************************************************************************************************************

int FP_SetAccelAndVelocity( int iController, double dAccel, double dVel )
{
char cmd[64];

#ifndef NOSCAN

	sprintf( cmd, "%dA%5.3f%c%dV%5.3f%c%dCR%c", iController, dAccel, 0x0D, iController, dVel, 0x0D, iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));

#endif

	return( 0 );
}

// ***************************************************************************************************************

int FP_GetCurrentPositionInCounts( int iController, int *iCounts )
{
char cmd[64];
char rsp[64];
int iByte;
double dCOMTimeOut = 0.25;		//seconds
int iStatus;

#ifndef NOSCAN

	SetComTime( iComPort, dCOMTimeOut ); 
	
	Delay( 0.25 );
	FlushInQ( iComPort );

	sprintf( cmd, "%dPR%c", iController, 0x0D );
	ComWrt (iComPort, cmd, strlen(cmd));

	// this will read the echoed command that was sent
 	iStatus = ComRdTerm (iComPort, rsp, 15, 0x0D);
 	if( iStatus < 0 )
 	{
 		return( -1 );
 	}
 	
	// this will read the response to IS command that was sent
 	iStatus = ComRdTerm (iComPort, rsp, 60, 0x0D);
 	if( iStatus < 0 )
 	{
 		return( -1 );
 	}
 	
	sscanf( rsp, "%d", iCounts);

#endif

	return( 0 );

}

// ***************************************************************************************************************

int FP_GetCurrentPositionInInches( int iController, double *dPosInInches )
{
int iStatus;
int iPosInCounts;

#ifndef NOSCAN

	iStatus = FP_GetCurrentPositionInCounts( iController, &iPosInCounts );

	if( iController == kWidthController )
	{
		*dPosInInches = (double)iPosInCounts * dWidthCal;
		return( 0 );
	}
	else if( iController == kHeightController )
	{ 
		*dPosInInches = (double)iPosInCounts * dHeightCal;
		return( 0 );
	}

	return( -1 );
	
#else

	return( 0 );
	
#endif
}

// ***************************************************************************************************************


