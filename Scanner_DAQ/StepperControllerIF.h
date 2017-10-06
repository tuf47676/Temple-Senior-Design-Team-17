/******************************************************************************
*																			  *
*	Filename:	StepperControllerIF.h				     					  *
*	Version:	2.0.0														  *
*	Date:		15 June 2007												  *
*																			  *
******************************************************************************/

#define kWidthController	1
#define kHeightController	2


// ***************************************************************************************************************


int FP_initialize( void );
int FP_ShutdownCmd( void );
int FP_EmergencyShutdownCmd( void );
int FP_GoHome( int iController );
int FP_SetHomePosition( int iController );
int FP_GoFarLimit( int iController );
int FP_GetLimitSwitchsState( int iController, int *iCCWLimitState, int *iCWLimitState );
int FP_GoToInInches( int iController, double dPosInInches, int iReturnImmediate );
int FP_GoToInCounts( int iController, int iPosInCounts, int iReturnImmediate );
int FP_GetBusyState( int iController );
int FP_SetAccelAndVelocity( int iController, double dAccel, double dVel );
int FP_GetCurrentPositionInCounts( int iController, int *iCounts );
int FP_GetCurrentPositionInInches( int iController, double *dPosInInches );


// ***************************************************************************************************************












