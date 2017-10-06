#include <utility.h>
/******************************************************************************
*																			  *
*	Filename:	E5071.c								     					  *
*	Version:	0.xx														  *
*	Date:		24 September 2008											  *
*																			  *
******************************************************************************/

//#include <userint.h>
//#include <ansi_c.h>
#include <visa.h>
#include "E5071.h"
#include <visa.h>
#include <ansi_c.h>
#include <userint.h>
#include "Setup.h"
#include "Defines.h"
#include "agena.h"

//*****************************************************************************
//	Variable Declarations
//

static ViSession visa_rm;	// visa resource manager session
static ViSession visa_na;	// visa spectrum analyzer session
extern char ascii_network_analyzer_setup[131072];
extern char ascii_data_chan1[kNumTracesCh1][131072];
extern char ascii_data_chan2[kNumTracesCh2][131072];
extern char ascii_freqs_ch1[65536];
extern char ascii_freqs_ch2[65536];
extern unsigned char ch1numberofmeasurements, ch2numberofmeasurements;

//ViPSession network_analyzer;

extern int startfreq;
extern int stopfreq;
extern char powerlevel;
extern char ch1sweeptype;
extern char ch2sweeptype;
extern char ch1sweepmode;
extern char ch2sweepmode;
extern int ch1ifbandwidth;
extern int ch2ifbandwidth;
extern unsigned short int ch1numbpoints;
extern unsigned short int ch2numbpoints;
extern int ch1averageon;
extern int ch2averageon;
extern unsigned short int ch1averagefactor;
extern unsigned short int ch2averagefactor;
extern int CH1M[17];
extern int CH2M[17];
extern int CH1MFORM[17];
extern int CH2MFORM[17];  
//const char sparam[16][4] = {"S11", "S12", "S13", "S14", "S21", "S22", "S23", "S24", "S31", "S32", "S33", "S34", "S41", "S42", "S43", "S44"};


//*****************************************************************************
//	Functions
//

int network_analyzer_open( void )
{
ViStatus iStatus;
char msg[1024];
char rsp[1024];
int iNumBytes;

//#ifndef NOEQUIP
	
		// open the VISA resource manager
		iStatus = viOpenDefaultRM( &visa_rm );
		if( iStatus != 0 )
		{  // error
			return( -1 );
		}


		// open the network analyzer
		iStatus = agena_init ("E5071B-2", VI_TRUE, VI_TRUE, &visa_na);
		if( iStatus != 0 )
		{  // error
			MessagePopup ("Error", "Could not open VISA device with alias \"E5071B-2\".\nProgram will exit.");
		
			return( -1 );
		}
	
		agena_actRecall (visa_na, AGENA_FILE_DATA_TYPE_INSTR_STATE, "Autorec.sta");

	
//#endif

/*
   	iStatus = viOpen(visa_rm, "E5071B-1", VI_NULL, VI_NULL, &visa_na );
	if( iStatus != 0 )
	{  // error
		MessagePopup ("Error", "Could not open VISA device with alias \"E5071B-1\".\nProgram will exit.");
		
		return( -1 );
	}
 
    // talk to the network analyzer
	sprintf( msg, "*IDN?\n" );
	iStatus = viWrite( visa_na, msg, strlen(msg), VI_NULL );
	if( iStatus != 0 )
	{  // error
		MessagePopup ("Error", "Could not write to VISA device with alias \"E5071B-1\".\nProgram will exit.");
		
		return( -1 );
	}
	
  	iStatus = viRead (visa_na, rsp, 1023, &iNumBytes);
	rsp[iNumBytes] = 0x0;
	if( iStatus != 0 )
	{  // error
		MessagePopup ("Error", "Could not read from VISA device with alias \"E5071B-1\".\nProgram will exit.");
		
		return( -1 );
	}
*/
	return( 0 ); 
}

// ***************************************************************************************************************

int network_analyzer_close( void )
{
#ifndef NOEQUIP 
	agena_close (visa_na);


#endif
//	viClose( visa_na );
	
	return( 0 );
}

// ***************************************************************************************************************

int downloadNetworkSetup(void)
{
int index;
	// download parameters to the Network Analyzer

//#ifndef NOEQUIP
		// reset agena
			//agena_reset (visa_na);
			
			// channel 1 settings
		
			// start freq
			agena_confSweepStimulus (visa_na, 1, VI_TRUE, AGENA_STIMULUS_START, startfreq, AGENA_STIMULUS_UNITS_MHZ);
			// stop freq
			agena_confSweepStimulus (visa_na, 1, VI_TRUE, AGENA_STIMULUS_STOP, stopfreq, AGENA_STIMULUS_UNITS_MHZ);
			// power
			agena_confPower (visa_na, 1, 1, VI_TRUE, VI_FALSE, 0.0, VI_FALSE, 0.0, powerlevel);
			
			agena_confSweep (visa_na, 1, ch1numbpoints, 0.001, ch1sweeptype, ch1sweepmode, VI_FALSE, 0.001, VI_TRUE);
			agena_confIFBwid (visa_na, 1, ch1ifbandwidth);
			agena_confAveraging (visa_na, 1, ch1averageon, ch1averagefactor);
			// set chan/display/format
			DebugPrintf("Channel 1 Network Dump:\n");
			for (index = 1; index <= ch1numberofmeasurements; index++)
			{
				agena_confChannelTrace (visa_na, 1, index, ch1numberofmeasurements, CH1M[index], CH1MFORM[index]);
				DebugPrintf("%d  %d  %d\n", index, CH1M[index], CH1MFORM[index]);
			}
	
		// channel 2 settings
		
			// start freq
			agena_confSweepStimulus (visa_na, 2, VI_TRUE, AGENA_STIMULUS_START, startfreq, AGENA_STIMULUS_UNITS_MHZ);
			// stop freq
			agena_confSweepStimulus (visa_na, 2, VI_TRUE, AGENA_STIMULUS_STOP, stopfreq, AGENA_STIMULUS_UNITS_MHZ);
			// power
			agena_confPower (visa_na, 2, 1, VI_TRUE, VI_FALSE, 0.0, VI_FALSE, 0.0, powerlevel);
		
			agena_confSweep (visa_na, 2, ch2numbpoints, 0.001, ch2sweeptype, ch2sweepmode, VI_FALSE, 0.001, VI_TRUE);
			agena_confIFBwid (visa_na, 2, ch2ifbandwidth);
			agena_confAveraging (visa_na, 2, ch2averageon, ch2averagefactor);
			// set chan/display/format
			
			if (ch2numberofmeasurements == 0) agena_confChannelTrace (visa_na, 2, 1, 0, 0, 5);
			DebugPrintf("Channel 2 Network Dump:\n");
			for (index = 1; index <= ch2numberofmeasurements; index++) 
			{
				agena_confChannelTrace (visa_na, 2, index, ch2numberofmeasurements, CH2M[index], CH2MFORM[index]);
				DebugPrintf("%d  %d  %d\n", index, CH2M[index], CH2MFORM[index]); 
			}
			// not sure why this line is needed, if it's not then the last trace always displays in the wrong format
			agena_confChannelTrace (visa_na, 2, index - 1, ch2numberofmeasurements, CH2M[index - 1], CH2MFORM[index - 1]);

//#endif			
			return(0);
}


/*
int network_analyzer_configure_V2( void )					// this function should be replaced		****
{															// with calls to 'agena.fp'
char config_copy[65536];
int iNumBytes;
ViStatus iStatus;
char *tok;

	strcpy( config_copy, ascii_network_analyzer_setup );
	
	tok = strtok( config_copy, "\n" );
	while( tok != NULL )
	{
		iStatus = viWrite (visa_na, tok, strlen(tok), &iNumBytes);
		if( iStatus != 0 )
		{
			return( -1 );
		}
		tok = strtok( NULL, "\n" );
	}
	
	
	
	return( 0 );	
}
*/
// ***************************************************************************************************************

int network_analyzer_enable_display( int enable )			 // this function should be replaced       ****
{															 // with calls to 'agena.fp'
char msg[1024];
int iNumBytes;
ViStatus iStatus;

	//
	if( enable )
	{
		sprintf( msg, ":DISP:ENAB ON\n" );
	}
	else
	{
		sprintf( msg, ":DISP:ENAB OFF\n" );
	}
	iStatus = viWrite (visa_na, msg, strlen(msg), &iNumBytes);


	return( 0 );	
}

// ***************************************************************************************************************

int network_analyzer_trigger( void )						 // this function should be replaced  		****
{															 // with calls to 'agena.fp' 
char msg[1024];
int iNumBytes;
ViStatus iStatus;


/*
	// trigger one acquisition
	iStatus = agena_actTrigger (visa_na, VI_FALSE, VI_TRUE);
  	if( iStatus != 0 )
  	{
  		return( -1 );
  	}

*/



	// trigger one acquisition
	sprintf( msg, ":TRIG:SING\n" );
	iStatus = viWrite (visa_na, msg, strlen(msg), &iNumBytes);

	// send the operation complete message
	sprintf( msg, "*OPC?\n" );
	iStatus = viWrite (visa_na, msg, strlen(msg), &iNumBytes);
  
	// hold here untill the operation is complete			// may need to increase timeout for reads
	// returned value is unimportant
  	iStatus = viRead (visa_na, msg, 1023, &iNumBytes);
  	if( iStatus != 0 )
 	{
  		return( -1 );
  	}

	return( 0 );	
}

// ***************************************************************************************************************

int network_analyzer_collect_data( void )					// this function should be replaced  		****
{															// with calls to 'agena.fp'
char msg[1024];
int iNumBytes;
ViStatus iStatus;
int iCount1;

	for ( iCount1 = 0; iCount1 < ch1numberofmeasurements; iCount1++ )
//	for( iCount1 = 0; iCount1 < kNumTracesCh1; iCount1++ )
	{
		// make trace active and read data
		sprintf( msg, ":CALC1:PAR%d:SEL\n:CALC1:DATA:FDAT?\n", iCount1 + 1 );
		iStatus = viWrite (visa_na, msg, strlen(msg), &iNumBytes);
	  	if( iStatus != 0 )
	  	{
	  		return( -1 );
	  	}

		// bring in the data
	 	iStatus = viRead (visa_na, ascii_data_chan1[iCount1], 131072, &iNumBytes);
	 	ascii_data_chan1[iCount1][iNumBytes] = 0x0;
	  	if( iStatus != 0 )
	  	{
	  		return( -1 );
	  	}
	}
	

	for ( iCount1 = 0; iCount1 < ch2numberofmeasurements; iCount1++ )
//	for( iCount1 = 0; iCount1 < kNumTracesCh2; iCount1++ )
	{
		// make trace active and read data
		sprintf( msg, ":CALC2:PAR%d:SEL\n:CALC2:DATA:FDAT?\n", iCount1 + 1 );
		iStatus = viWrite (visa_na, msg, strlen(msg), &iNumBytes);
	  	if( iStatus != 0 )
	  	{
	  		return( -1 );
	  	}

		// bring in the data
	 	iStatus = viRead (visa_na, ascii_data_chan2[iCount1], 131072, &iNumBytes);
	 	ascii_data_chan2[iCount1][iNumBytes] = 0x0;
	  	if( iStatus != 0 )
	  	{
	  		return( -1 );
	  	}
	}
	
	return( 0 );	
}

// ***************************************************************************************************************

int network_analyzer_collect_freqs( void )
{
char msg[1024];
int iNumBytes;
ViStatus iStatus;

	// make channel 1 active and read freqs
	sprintf( msg, ":SENS1:FREQ:DATA?\n" );
	iStatus = viWrite (visa_na, msg, strlen(msg), &iNumBytes);
  	if( iStatus != 0 )
  	{
  		return( -1 );
  	}

	// bring in the data
 	iStatus = viRead (visa_na, ascii_freqs_ch1, 65535, &iNumBytes);
 	ascii_freqs_ch1[iNumBytes] = 0x0;
  	if( iStatus != 0 )
  	{
  		return( -1 );
  	}
  	
	// make channel 2 active and read freqs
	sprintf( msg, ":SENS2:FREQ:DATA?\n" );
	iStatus = viWrite (visa_na, msg, strlen(msg), &iNumBytes);
  	if( iStatus != 0 )
  	{
  		return( -1 );
  	}

	// bring in the data
 	iStatus = viRead (visa_na, ascii_freqs_ch2, 65535, &iNumBytes);
 	ascii_freqs_ch2[iNumBytes] = 0x0;
  	if( iStatus != 0 )
  	{
  		return( -1 );
  	}
	
  	
	
	return( 0 );	
}

// ***************************************************************************************************************
	 



//*****************************************************************************
//	CVICALLBACK Functions
//






