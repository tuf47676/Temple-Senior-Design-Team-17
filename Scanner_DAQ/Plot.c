#include <userint.h>
#include <ansi_c.h>
//#include "FP_SA_V1.h"
#include "Defines.h"
#include "Plot.h"




// ***************************************************************************************************************

extern int hPanelMain;


extern char ascii_data_chan1[kNumTracesCh1][131072];
extern char ascii_data_chan2[kNumTracesCh2][131072];
extern char ascii_freqs_ch1[65536];
extern char ascii_freqs_ch2[65536];


double data_mag_ch1[kNumTracesCh1][801];
double data_mag_ch2[kNumTracesCh2][801];

double data_phase_ch1[kNumTracesCh1][801];
double data_phase_ch2[kNumTracesCh2][801];

double freqs[801];


int iNumberOfPoints = 201;// 801 max unless you chang the arrays above and the ascii array lengths




// ***************************************************************************************************************




