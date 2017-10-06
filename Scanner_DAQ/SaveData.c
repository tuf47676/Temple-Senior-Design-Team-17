#include <formatio.h>
#include <utility.h>
#include "inifile.h"
#include <ansi_c.h>
#include <userint.h>
#include "Defines.h"
//#include "FP_SA_V1.h"
#include "SaveData.h"

// ********************************************************************************************************

extern struct FPPoint {
	double x;   //width
	double y;   //height
}theFPPoints[100000];

extern int iNumFPPoints;

extern int iCurrentFPPoint;

extern char ascii_network_analyzer_setup[131072];

extern char ascii_data_chan1[kNumTracesCh1][131072];
extern char ascii_data_chan2[kNumTracesCh2][131072];
extern char ascii_freqs_ch1[65536];
extern char ascii_freqs_ch2[65536];
extern unsigned char ch1numberofmeasurements, ch2numberofmeasurements;

extern char exp_path[1024];

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

extern const char sweeptype[4][8];
extern const char sweepmode[4][13];
extern const char sparam[16][4];
extern const char sformat[17][24];


// ********************************************************************************************************


// ********************************************************************************************************

int saveFieldProbePointPositions( void )
{
int iStatus;
int iCount1;
char msg[1024];
char filepath[1024];
int hFile;
int len;



	sprintf( filepath, "%s\\POSITIONS.dat", exp_path );	
	hFile = OpenFile (filepath, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	if( hFile == -1 ) {
		sprintf( msg, "Error Creating File %s.\nData Collection Will Terminate.", filepath );
		MessagePopup ("Error", msg);
		return( -1 );
	}

	for( iCount1 = 0; iCount1 < iNumFPPoints; iCount1++ ) {

		sprintf( msg, "%04d,%f,%f\n", iCount1 + 1, theFPPoints[iCount1].x, theFPPoints[iCount1].y );

		len = strlen( msg );
		iStatus = WriteFile (hFile, msg, len );
		if( len != iStatus ) {
			sprintf( msg, "Error Writing To File %s.\nData Collection Will Terminate", filepath );
			MessagePopup ("Error", msg);
			return( -1 );
		}
	
	}
	
	CloseFile (hFile);

 
 	return( 0 );
}

// ********************************************************************************************************

int saveNetworkAnalyzerSetup( void )
{
int iStatus;
char filepath[1024];
char setuptext[100];
char msg[1024];
int hFile;
int len;
int index;

	sprintf( filepath, "%s\\NETWORK_ANALYZER_SETUP.dat", exp_path );	
	hFile = OpenFile (filepath, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	if( hFile == -1 ) {
		sprintf( msg, "Error Creating File %s.\nData Collection Will Terminate.", filepath );
		MessagePopup ("Error", msg);
		return( -1 );
	}

	//ADD ERROR TRAPPING
	sprintf( setuptext, "START_FREQ = %d MHz\n", startfreq );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );

	sprintf( setuptext, "STOP_FREQ = %d MHz\n", stopfreq );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );

	sprintf( setuptext, "POWER = %d dBm\n\n", powerlevel );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );
	
	sprintf( setuptext, "CH1\n" );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );

	sprintf( setuptext, "SWEEPTYPE = %s\n", sweeptype[ch1sweeptype] );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );

	sprintf( setuptext, "SWEEPMODE = %s\n", sweepmode[ch1sweepmode] );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );

	sprintf( setuptext, "IF Bandwidth = %d\n", ch1ifbandwidth );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );
	
	sprintf( setuptext, "Number of Points = %d\n", ch1numbpoints );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );
	
	sprintf( setuptext, "Average On? = %d\n", ch1averageon );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );
	
	sprintf( setuptext, "Average Factor = %d\n", ch1averagefactor );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );

	for (index = 1; index <= ch1numberofmeasurements; index++)
	{
		sprintf( setuptext, "Trace%d = %s  %s\n", index, sparam[CH1M[index]], sformat[CH1MFORM[index]] );
		len = strlen( setuptext );
		iStatus = WriteFile (hFile, setuptext, len );
	}

	sprintf( setuptext, "\nCH2\n" );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );

	sprintf( setuptext, "SWEEPTYPE = %s\n", sweeptype[ch2sweeptype] );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );

	sprintf( setuptext, "SWEEPMODE = %s\n", sweepmode[ch2sweepmode] );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );

	sprintf( setuptext, "IF Bandwidth = %d\n", ch2ifbandwidth );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );
	
	sprintf( setuptext, "Number of Points = %d\n", ch2numbpoints );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );
	
	sprintf( setuptext, "Average On? = %d\n", ch2averageon );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );
	
	sprintf( setuptext, "Average Factor = %d\n", ch2averagefactor );
	len = strlen( setuptext );
	iStatus = WriteFile (hFile, setuptext, len );

	for (index = 1; index <= ch2numberofmeasurements; index++)
	{
		sprintf( setuptext, "Trace%d = %s  %s\n", index, sparam[CH2M[index]], sformat[CH2MFORM[index]] );
		len = strlen( setuptext );
		iStatus = WriteFile (hFile, setuptext, len );
	}
	
	
	
	
//	if( len != iStatus )
//	{
//		sprintf( msg, "Error Writing To File %s.\nData Collection Will Terminate", filepath );
//		MessagePopup ("Error", msg);
//		return( -1 );
//	}
	
	
	CloseFile (hFile);


	return( 0 );
}

// ********************************************************************************************************

int saveFrequencyPoints( void )
{
int iStatus;
char filepath[1024];
char msg[1024];
int hFile;
int len;

	sprintf( filepath, "%s\\FREQUENCIES.dat", exp_path );	
	hFile = OpenFile (filepath, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	if( hFile == -1 ) {
		sprintf( msg, "Error Creating File %s.\nData Collection Will Terminate.", filepath );
		MessagePopup ("Error", msg);
		return( -1 );
	}


	//write channel 1 freq list
	sprintf( msg, "Channel 1\n" );
	len = strlen( msg );
	iStatus = WriteFile (hFile, msg, len );
	if( len != iStatus )
	{
		sprintf( msg, "Error Writing To File %s.\nData Collection Will Terminate", filepath );
		MessagePopup ("Error", msg);
		return( -1 );
	}
	
	len = strlen( ascii_freqs_ch1 );
	iStatus = WriteFile (hFile, ascii_freqs_ch1, len );
	if( len != iStatus )
	{
		sprintf( msg, "Error Writing To File %s.\nData Collection Will Terminate", filepath );
		MessagePopup ("Error", msg);
		return( -1 );
	}

	//write channel 2 freq list
	sprintf( msg, "\nChannel 2\n" );
	len = strlen( msg );
	iStatus = WriteFile (hFile, msg, len );
	if( len != iStatus )
	{
		sprintf( msg, "Error Writing To File %s.\nData Collection Will Terminate", filepath );
		MessagePopup ("Error", msg);
		return( -1 );
	}
	
	len = strlen( ascii_freqs_ch2 );
	iStatus = WriteFile (hFile, ascii_freqs_ch2, len );
	if( len != iStatus )
	{
		sprintf( msg, "Error Writing To File %s.\nData Collection Will Terminate", filepath );
		MessagePopup ("Error", msg);
		return( -1 );
	}
	
	
	CloseFile (hFile);

	return( 0 );
}

// ********************************************************************************************************

int saveTraceData( void )
{
int iStatus;
int iCount1;
char msg[1024];
char filepath[1024];
int hFile;
int len;


	for( iCount1 = 0; iCount1 < ch1numberofmeasurements; iCount1++ )
	{
	
		// channel 1
		sprintf( filepath, "%s\\POS%04d_CHAN%01d_TRACE%04d.dat", exp_path, iCurrentFPPoint + 1, 1, iCount1 + 1 );	
		hFile = OpenFile (filepath, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
		if( hFile == -1 )
		{
			sprintf( msg, "Error Creating File %s.\nData Collection Will Terminate", filepath );
			MessagePopup ("Error", msg);
			return( -1 );
		}
		
		len = strlen( ascii_data_chan1[iCount1] );
		iStatus = WriteFile (hFile, ascii_data_chan1[iCount1], len );
		if( len != iStatus ) 
		{
			sprintf( msg, "Error Writing To File %s.\nData Collection Will Terminate", filepath );
			MessagePopup ("Error", msg);
			return( -1 );
		}
		
		
		CloseFile (hFile);
	}		
		
		
		
		
	for( iCount1 = 0; iCount1 < ch2numberofmeasurements; iCount1++ ) {

		// channel 2
		sprintf( filepath, "%s\\POS%04d_CHAN%01d_TRACE%04d.dat", exp_path, iCurrentFPPoint + 1, 2, iCount1 + 1 );	
		hFile = OpenFile (filepath, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
		if( hFile == -1 ) 
		{
			sprintf( msg, "Error Creating File %s.\nData Collection Will Terminate", filepath );
			MessagePopup ("Error", msg);
			return( -1 );
		}
		
		len = strlen( ascii_data_chan2[iCount1] );
		iStatus = WriteFile (hFile, ascii_data_chan2[iCount1], len );
		if( len != iStatus ) 
		{
			sprintf( msg, "Error Writing To File %s.\nData Collection Will Terminate", filepath );
			MessagePopup ("Error", msg);
			return( -1 );
		}
		
		
		CloseFile (hFile);
		
	
	}



	return( 0 );
}

// ********************************************************************************************************
