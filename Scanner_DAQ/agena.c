#include <utility.h>
#include <ansi_c.h>
#include <visa.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "agena.h"

/*****************************************************************************/
/*  Agilent ENA Series RF Network Analyzer                                   */
/*                                                                           */
/*  LabWindows/CVI 7.0 Instrument Driver                                     */
/*  Original Release: August 2005                                            */
/*  By: K. Pisala                                                            */
/*                                                                           */
/* Modification History:													 */
/*																			 */
/*		May 2006, Rev 1.2, 05/2006 [LH]									 	 */
/*		- added fully support for Agilent E5061A/E5062A ENA Series			 */
/*		- agena_confLimitTest - Added new control "Limit Line Clip"			 */
/*		- agena_confMarkerSearch - added support for the multi peak search   */
/*		- agena_actExecuteECal - added support for enhanced response		 */
/*		- agena_confCal - added support for enhanced response		 		 */
/*		- added new functions:												 */
/*			- agena_dataMathMarkerData						 				 */
/*			- agena_confMarkerFunction										 */
/*			- agena_dataMarkerNotchSearchResult								 */
/*			- agena_confNotchSearch							 				 */
/*			- agena_actRecallChannelCoefficient								 */
/*			- agena_actStoreChannelCoefficient								 */
/*			- agena_actSecurityLevel										 */
/*		April 2006, Rev 1.1, 04/2006										 */
/* 		- agena_confSweep - Removed unused parameter channel 		         */
/* 		- agena_confDisplay - Title text placed inside string quotes         */
/* 		- agena_confMarker - Removed unused parameter unit          		 */
/* 		- agena_confFreqOffset - Fixed invalid command string       		 */
/* 		- agena_confSweepSegments - Removed unused parameter sweepTimeEnabled*/ 		  											 
/* 		- agena_actDirContents - Changed type of parameters usedSize and 	 */
/*        freeSpace from ViInt32 to ViReal64 to fix problem with overflow    */
/*                                                                           */
/*****************************************************************************/


/*= DEFINES =================================================================*/
#define AGENA_REVISION      "Rev 1.2, 05/2006, CVI 7.0" /* Instrument driver revision */
#define BUFFER_SIZE         2048L                       /* File I/O buffer size */
#define DOUBLE_BYTE_SIZE	15

/*= Macros ==================================================================*/
#define CHECKERR(fCal) \
    if (agena_status = (fCal), agena_status < VI_SUCCESS) \
        goto Error; else

#define CHECKPARAM(fCal, error) \
    if (fCal) \
    { \
    	agena_status = (error); \
        goto Error; \
    } \
    else

/*****************************************************************************/
/*= INSTRUMENT-DEPENDENT STATUS/RANGE STRUCTURE  ============================*/
/*****************************************************************************/
typedef struct  agena_stringValPair
{
   ViStatus	stringVal;
   ViString	stringName;
}  agena_tStringValPair;

typedef struct {
    int     typeID;
    char*   modelString;
} SStringTableEntry;

typedef struct agena_statusDataRanges
{
    ViBoolean   errorChecking;
    ViChar      instrDriverRevision[256];
    ViInt32		numChannels;
    ViInt32		numTraces;
    ViInt32		numPorts;
    ViInt32		systemVersion;
    ViInt32		modelType;
} *agena_instrRange;

/* Supported models         */
enum {
    AGENA_MODEL_E5061A = 5061,
    AGENA_MODEL_E5062A,
    AGENA_MODEL_E5070B = 5070,
    AGENA_MODEL_E5071B
};
    
static SStringTableEntry    agena_SupportedModel[] =
    {
        {AGENA_MODEL_E5061A,    "E5061A"},
        {AGENA_MODEL_E5062A,    "E5062A"},
        {AGENA_MODEL_E5070B,    "E5070B"},
        {AGENA_MODEL_E5071B,    "E5071B"},
        {NULL,                  NULL}
    };

#define IS_E506x      ((model_type == AGENA_MODEL_E5061A) || (model_type == AGENA_MODEL_E5062A))

/* Command parameters list     */
static ViString agena_measParameters[] = {"S11", "S21", "S31", "S41", "S12",
        "S22", "S32", "S42", "S13", "S23", "S33", "S43", "S14", "S24", "S34",
        "S44", "A", "B", "C", "D", "R1", "R2", "R3", "R4", VI_NULL};
        
static ViString agena_dataFormat[] = {"MLOG", "PHAS", "GDEL", "SLIN", "SLOG",
        "SCOM", "SMIT", "SADM", "PLIN", "PLOG", "POL", "MLIN", "SWR", "REAL",
        "IMAG", "UPH", "PPH", VI_NULL};
        
static ViString agena_sweepType[] = {"LIN", "LOG", "SEGM", "POW", VI_NULL};

static ViString agena_sweepMode[] = {"STEP", "ANAL", "FST", "FAN", VI_NULL};

static ViString agena_xAxisFreq[] = {"NORM", "RFPL", "RFML", "LOMR",
									 "BASE", "STIM", "RESP", VI_NULL};

static ViString agena_graphLayout[] = {"D1", "D12", "D1_2", "D112", "D1_1_2",
									   "D123", "D1_2_3", "D12_33", "D11_23",
									   "D13_23", "D12_13", "D1234", "D1_2_3_4",
									   "D12_34", "D123_456", "D12_34_56",
									   "D1234_5678", "D12_34_56_78", "D123_456_789",
									   "D123__ABC", "D1234__9ABC", "D1234__CDEF",
									   VI_NULL};

static ViString agena_displayType[] = {"NORM", "INV", VI_NULL};

static ViString agena_dispTableType[] = {"MARK", "LIM", "SEGM", "ECHO", "PLOS",
										 "SCF", VI_NULL};

static ViString agena_dispTraceType[] = {"NORM", "SUBT", "DIV", "ADD", "MULT",
										 VI_NULL};

static ViString agena_dispMethod[] = {"LIN", "OBAS", VI_NULL};

static ViString agena_calKitStandard[] = {"OPEN", "SHOR", "LOAD", "THRU", "ARBI",
										  "NONE", VI_NULL};

static ViString agena_ECalCharacterization[] = {"CHAR0", "CHAR1", "CHAR2", "CHAR3",
												"CHAR4", "CHAR5", VI_NULL};

static ViString agena_triggerSource[] = {"INT", "EXT", "MAN", "BUS", VI_NULL};

static ViString agena_peakPolarity[] = {"POS", "NEG", "BOTH", VI_NULL};

static ViString agena_targetPolarity[] = {"POS", "NEG", "BOTH", VI_NULL};

static ViString agena_analysisType[] = {"PTP", "STDEV", "MEAN", "MAX", "MIN",
										"PEAK", "APE", "ATAR", VI_NULL};

static ViString agena_balanceDevType[] = {"SBAL", "BBAL", "SSB", VI_NULL};

/*static ViString agena_balanceParameter[] = {"SSS11", "SSS21", "SSS12", "SSS22",
											"SDS21", "SDS31", "SDS32", "SSD12",
											"SSD13", "SSD23", "SCS21", "SCS31",
											"SCS32", "SSC12", "SSC13", "SSC23",
											"SDD11", "SDD21", "SDD12", "SDD22",
											"SDD33", "SCD11", "SCD21", "SCD12",
											"SCD22", "SCD33", "SDC11", "SDC21",
											"SDC12", "SDC22", "SDC33", "SCC11",
											"SCC21", "SCC12", "SCC22", "SCC33",
											"IMB1", "IMB2", "IMB3", "IMB4",
											"CMRR", "CMRR2", VI_NULL};
*/											
static ViString agena_balanceParameter[] = {"SSS","SDS","SSD",
											"SCS","SSC","SDD","SCD",
											"SDC","SCC","IMB1", "IMB2",
											"IMB3","IMB4","CMRR1","CMRR2",VI_NULL};
											
static ViString agena_circuitType[] = {"NONE", "SLPC", "PCSL", "PLSC", "SCPL",
									   "PLPC", "USER", VI_NULL};

static ViString agena_networkDeembedding[] = {"NONE", "USER", VI_NULL};

static ViString agena_topologyType[] = {"A", "B", "C", VI_NULL};

static ViString agena_networkType[] = {"NONE", "EMB", "DEEM", VI_NULL};

static ViString agena_transformationType[] = {"BPAS", "LPAS", VI_NULL};

static ViString agena_stimulusType[] = {"IMP", "STEP", VI_NULL};

static ViString agena_gateType[] = {"BPAS", "NOTC", VI_NULL};

static ViString agena_shapeType[] = {"MAX", "WIDE", "NORM", "MIN", VI_NULL};

static ViString agena_parameter[] = {"ZREF", "ZTR", "YREF", "YTR", "INV", "ZTSH",
									 "YTSH", "CONJ", VI_NULL};

static ViString agena_portDirection[] = {"INP", "OUTP", VI_NULL, VI_NULL};

static ViString agena_port1E5091A[] = {"A", "T1", VI_NULL};

static ViString agena_port2E5091A[] = {"T1", "T2", VI_NULL};

static ViString agena_port3E5091A[] = {"R1", "R2", "R3", VI_NULL};

static ViString agena_port4E5091A[] = {"R1", "R2", "R3", VI_NULL};

static ViString agena_fileHandlingItems[] = {"STAT", "CST", "DST", "CDST", VI_NULL};

static ViString agena_printColor[] = {"NORM", "INV", VI_NULL};

static ViString agena_sensorType[] = {"ASEN", "BSEN", VI_NULL};

static ViString agena_markerSearchFunc[] = {"MAX", "MIN", "PEAK", "LPE", "RPE",
											"TARG", "LTAR", "RTAR", VI_NULL};

static ViString agena_markerTo[] = {"STAR", "STOP", "CENT", "RLEV", "DEL", VI_NULL};

static ViString agena_memoryRegister[] = {"A", "B", "C", "D", VI_NULL};

static ViString agena_macroOperation[] = {"RUN", "STOP", VI_NULL};

static ViString agena_extSignalState[] = {"INT", "EXT", VI_NULL};

static ViString agena_portName[] = {"A", "B", "C", "D", "E", "F", VI_NULL};

/*****************************************************************************/
/*= UTILITY ROUTINE DECLARATIONS (Non-Exportable Functions) =================*/
/*****************************************************************************/
ViBoolean agena_invalidViBooleanRange (ViBoolean val);
ViBoolean agena_invalidViInt32Range (ViInt32 val, ViInt32 min, ViInt32 max);
ViBoolean agena_invalidViReal64Range (ViReal64 val, ViReal64 min, ViReal64 max);
ViBoolean agena_invalidViString (ViString val, ViUInt32 maxLength);
ViBoolean agena_isInStringTable (
    ViString            modelString,
    SStringTableEntry   stringTable[]
);
ViInt32 agena_getModelIndex (
    ViString            modelString,
    SStringTableEntry   stringTable[]
);
ViInt32 agena_getValueIndex (
    ViString            stringValue,
    ViString			stringTable[]
);
ViStatus agena_readDataUnknownLength(
	ViSession	instrSession,
	ViChar**	outBuffer,
	ViUInt32*	count
);
static void RemoveSurroundingWhiteSpace(ViChar string[]);
ViStatus agena_defaultInstrSetup (ViSession openInstrSession);
ViStatus agena_checkStatus(ViSession instrumentHandle);
void agena_delay (ViReal64 numberOfSeconds);
ViStatus agena_waitOPC (ViSession instrumentHandle, ViPString command, ViPString instrResp, ViInt32 timeout);



/*****************************************************************************/
/*====== USER-CALLABLE FUNCTIONS (Exportable Functions) =====================*/
/*****************************************************************************/

/*===========================================================================*/
/*===========================================================================*/
/* Function: Initialize
/* Purpose:  This function performs the following initialization actions:
/*           
/*           - Opens a session to the Default Resource Manager resource and 
/*           a session to the specified device using the interface and 
/*           address specified in the Resource_Name control.
/*           
/*           - Performs an identification query on the Instrument.
/*           
/*           - Resets the instrument to a known state.
/*           
/*           - Sends initialization commands to the instrument that set any 
/*           necessary programmatic variables such as Headers Off, Short 
/*           Command form, and Data Transfer Binary to the state necessary 
/*           for the operation of the instrument driver.
/*           
/*           - Returns an Instrument Handle which is used to differentiate 
/*           between different sessions of this instrument driver.
/*           
/*           - Each time this function is invoked a Unique Session is 
/*           opened.  It is possible to have more than one session open for 
/*           the same resource.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_init (
    ViRsrc      resourceName,
    ViBoolean   IDQuery,
    ViBoolean   resetDevice,
    ViSession*  instrumentHandle
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViSession   rmSession = 0;
    ViUInt16    interface = VI_INTF_GPIB;
    ViByte      rdBuffer[BUFFER_SIZE];
    agena_instrRange	instrPtr;
    
    *instrumentHandle = NULL;   //was *instrumentHandle

    /*- Check input parameter ranges ----------------------------------------*/
    if (agena_invalidViBooleanRange (IDQuery))
        return VI_ERROR_PARAMETER2;
    if (agena_invalidViBooleanRange (resetDevice))
        return VI_ERROR_PARAMETER3;

    /*- Open instrument session ---------------------------------------------*/
    *instrumentHandle = NULL;	  //was *instrumentHandle
    CHECKERR (viOpenDefaultRM (&rmSession));
    CHECKERR (viOpen (rmSession, resourceName, VI_LOAD_CONFIG, VI_NULL,
                      instrumentHandle));

    /* VI_ATTR_SEND_END_EN will stay with this attribute set to VI_TRUE */
    CHECKERR(viSetAttribute (*instrumentHandle, VI_ATTR_SEND_END_EN, VI_TRUE));

    /*- Configure VISA Formatted I/O ----------------------------------------*/
    CHECKERR (viSetAttribute (*instrumentHandle, VI_ATTR_TMO_VALUE, 15000));
    CHECKERR (viSetBuf (*instrumentHandle, VI_READ_BUF|VI_WRITE_BUF, 4000));
    CHECKERR (viSetAttribute (*instrumentHandle, VI_ATTR_WR_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS));
    CHECKERR (viSetAttribute (*instrumentHandle, VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS));
    
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR( viGetAttribute (*instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

    if (instrPtr == NULL)
        instrPtr = malloc (sizeof (struct agena_statusDataRanges));

    CHECKERR( viSetAttribute (*instrumentHandle, VI_ATTR_USER_DATA, (ViUInt32)instrPtr));

    /*- Identification Query ------------------------------------------------*/
    if (IDQuery)
    {
        ViInt32     read_count;
        ViChar*     p2model = NULL;
        
        CHECKERR (viWrite (*instrumentHandle, "*IDN?\n", strlen("*IDN?\n"), VI_NULL));
        CHECKERR (viRead (*instrumentHandle, rdBuffer, BUFFER_SIZE, &read_count));
        /* TODO: detect all supported instrument */
        
        p2model = strtok(rdBuffer, ",");
        if (p2model != NULL)
        {
            p2model = strtok(NULL, ",");
            if (!agena_isInStringTable(p2model, agena_SupportedModel))
            {
                CHECKERR( VI_ERROR_FAIL_ID_QUERY);
            }
			
			instrPtr->modelType = agena_getModelIndex(p2model, agena_SupportedModel); 		
        }
    }

    /*- Reset instrument ----------------------------------------------------*/
    if (resetDevice)
    {
        CHECKERR (agena_reset (*instrumentHandle));
    }
    else  /*- Send Default Instrument Setup ---------------------------------*/
        CHECKERR (agena_defaultInstrSetup (*instrumentHandle));

    return VI_SUCCESS;

Error:
    if (rmSession != 0)
        viClose(rmSession);
        
    if (*instrumentHandle != NULL)
    {
        viClose(*instrumentHandle);
        *instrumentHandle = NULL;
    }
    
    return agena_status;
}

/*===========================================================================*/
/* Function: Configuration Example
/* Purpose:  This function configure instrument for measurement.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_configureAppExample (
	ViRsrc		resourceName,
	ViBoolean	idQuery,
	ViBoolean	reset,
	ViReal64	centerFrequencyHz,
	ViReal64	spanFrequencyHz,
	ViReal64	IFBandwidthHz,
	ViReal64	powerdBm
)
{
	ViSession	io = 0;
	ViStatus	agena_status = VI_SUCCESS;
	
    CHECKERR( agena_init(resourceName, idQuery, reset, &io));
    CHECKERR( agena_confSweepStimulus (io, 1, VI_FALSE, AGENA_STIMULUS_CENTER,
								  centerFrequencyHz, AGENA_STIMULUS_UNITS_HZ));
	CHECKERR( agena_confSweepStimulus (io, 1, VI_FALSE, AGENA_STIMULUS_SPAN,
								  spanFrequencyHz, AGENA_STIMULUS_UNITS_HZ));
	CHECKERR( agena_confSweep (io, 1, 401, 0.001,
							   AGENA_SWEEP_MODE_STEPPED, AGENA_SWEEP_TYPE_LINEAR,
							   VI_FALSE, 0.001, VI_FALSE));
	CHECKERR( agena_confIFBwid (io, 1, IFBandwidthHz));
	CHECKERR( agena_confPower (io, 1, 1, VI_TRUE, VI_FALSE,
							   0.0, VI_FALSE, 0.0, powerdBm));
	CHECKERR( agena_confChannelTrace (io, 1, 1, 1,
									  AGENA_MEASUREMENT_PARAMETER_S21,
									  AGENA_FORMAT_LOG_MAGNITUDE));
	CHECKERR( agena_confCal (io, 1, 4, AGENA_CALIBRATION_TYPE_2_PORT, 1, 2, 1,
							 VI_FALSE, VI_FALSE, 1.0, 50.0));

Error:
	if (io != 0)
		agena_close(io);

	return agena_status;
}

/*===========================================================================*/
/* Function: Open Calibration Example
/* Purpose:  This function performs open calibration for port 1 and port 2.
/*           For this function you must set OPEN Port 1 and Port 2 on instrument.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_openCalibrationExample (
	ViRsrc		resourceName,
	ViBoolean	idQuery,
	ViBoolean	reset
)
{
	ViSession	io = 0;
	ViStatus	agena_status = VI_SUCCESS;
	
    CHECKERR( agena_init(resourceName, idQuery, reset, &io));
	
	CHECKERR( agena_actMeasureCalData (io, 1, AGENA_MEASURE_CAL_DATA_STANDARD_OPEN,
									   1, 1));
							 
	CHECKERR( agena_actMeasureCalData (io, 1, AGENA_MEASURE_CAL_DATA_STANDARD_OPEN,
									   2, 1));

Error:
	if (io != 0)
		agena_close(io);

	return agena_status;
}

/*===========================================================================*/
/* Function: Short Calibration Example
/* Purpose:  This function performs short calibration for port 1 and port 2.
/*           For this function you must set SHORT Port 1 and Port 2 on instrument.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_shortCalibrationExample (
	ViRsrc		resourceName,
	ViBoolean	idQuery,
	ViBoolean	reset
)
{
	ViSession	io = 0;
	ViStatus	agena_status = VI_SUCCESS;
	
    CHECKERR( agena_init(resourceName, idQuery, reset, &io));
	
	CHECKERR( agena_actMeasureCalData (io, 1, AGENA_MEASURE_CAL_DATA_STANDARD_SHORT,
									   1, 1));
							 
	CHECKERR( agena_actMeasureCalData (io, 1, AGENA_MEASURE_CAL_DATA_STANDARD_SHORT,
									   2, 1));

Error:
	if (io != 0)
		agena_close(io);

	return agena_status;
}

/*===========================================================================*/
/* Function: Load Calibration Example
/* Purpose:  This function performs load calibration for port 1 and port 2.
/*           For this function you must set LOAD Port 1 and Port 2 on instrument.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_loadCalibrationExample (
	ViRsrc		resourceName,
	ViBoolean	idQuery,
	ViBoolean	reset
)
{
	ViSession	io = 0;
	ViStatus	agena_status = VI_SUCCESS;
	
    CHECKERR( agena_init(resourceName, idQuery, reset, &io));
	
	CHECKERR( agena_actMeasureCalData (io, 1, AGENA_MEASURE_CAL_DATA_STANDARD_LOAD,
									   1, 1));
							 
	CHECKERR( agena_actMeasureCalData (io, 1, AGENA_MEASURE_CAL_DATA_STANDARD_LOAD,
									   2, 1));

Error:
	if (io != 0)
		agena_close(io);

	return agena_status;
}

/*===========================================================================*/
/* Function: Thru Between Port1 and Port2 Calibration Example
/* Purpose:  This function performs thru calibration between port 1 and port 2.
/*           For this function you must set THRU between Port 1 and Port 2
/*           on instrument.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_thru12CalibrationExample (
	ViRsrc		resourceName,
	ViBoolean	idQuery,
	ViBoolean	reset
)
{
	ViSession	io = 0;
	ViStatus	agena_status = VI_SUCCESS;
	
    CHECKERR( agena_init(resourceName, idQuery, reset, &io));
	
	CHECKERR( agena_actMeasureCalData (io, 1, AGENA_MEASURE_CAL_DATA_STANDARD_THRU,
									   1, 2));

Error:
	if (io != 0)
		agena_close(io);

	return agena_status;
}

/*===========================================================================*/
/* Function: Thru Between Port2 and Port1 Calibration Example
/* Purpose:  This function performs thru calibration between port 2 and port 1.
/*           For this function you must set THRU between Port 2 and Port 1
/*           on instrument.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_thru21CalibrationExample (
	ViRsrc		resourceName,
	ViBoolean	idQuery,
	ViBoolean	reset
)
{
	ViSession	io = 0;
	ViStatus	agena_status = VI_SUCCESS;
	
    CHECKERR( agena_init(resourceName, idQuery, reset, &io));
	
	CHECKERR( agena_actMeasureCalData (io, 1, AGENA_MEASURE_CAL_DATA_STANDARD_THRU,
									   2, 1));

Error:
	if (io != 0)
		agena_close(io);

	return agena_status;
}

/*===========================================================================*/
/* Function: Application Example
/* Purpose:  This function performs full 2-port calibration using the 85032F 
/*           calibration kit, measures a band-pass filter (center frequency: 
/*           947.5 MHz), and calculates and displays its bandwidth, insertion 
/*           loss, and so on.
/*           For this function you must set DUT on instrument. 
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_appExample (
	ViRsrc		resourceName,
	ViBoolean	idQuery,
	ViBoolean	reset,
	ViReal64*	bandwidth,
	ViReal64*	center,
	ViReal64*	low,
	ViReal64*	high,
	ViReal64*	q,
	ViReal64*	loss
)
{
	ViSession	io = 0;
	ViStatus	agena_status = VI_SUCCESS;
	ViReal64	x_value;
	ViReal64	y_value;
	ViReal64	y_imaginary;
	
    CHECKERR( agena_init(resourceName, idQuery, reset, &io));
    
    CHECKERR( agena_confTrigger (io, 1, VI_TRUE, VI_FALSE, AGENA_TRIGGER_SOURCE_BUS));
	CHECKERR( agena_confMarker (io, 1, 1, 0.0, VI_TRUE));
	CHECKERR( agena_confBandwidthSearch (io, 1, 1, VI_TRUE, -3.0));
	CHECKERR( agena_actTrigger (io, VI_TRUE, VI_TRUE));
	
	Delay(0.100);
	CHECKERR( agena_actSetMarkerValues (io, 1, 1, AGENA_MARKER_SET_TO_CENTER));
	CHECKERR( agena_dataMarkerData (io, 1, 1, &x_value, &y_value, &y_imaginary));
	
	CHECKERR( agena_dataMarkerBandwidthSearchResult (io, 1, 1, bandwidth, center, q,
													 loss));
	
	*low = *center - *bandwidth / 2;
	*high = *center + *bandwidth / 2;
	
Error:
	if (io != 0)
		agena_close(io);

	return agena_status;
}

/*===========================================================================*/
/* Function: Configure Channel And Trace
/* Purpose:  This function sets active channel and trace and configures 
/*           parameters of active trace.
/*===========================================================================*/
ViStatus _VI_FUNC agena_confChannelTrace (
    ViSession   instrumentHandle,
    ViInt32     activeChannel,
    ViInt32     activeTrace,
    ViInt32     numberOfTraces,
    ViInt32     measurementParameter,
    ViInt32     dataFormat
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32		model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(activeChannel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(activeTrace, 1, instrPtr->numTraces),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViInt32Range(measurementParameter, 0, 23),
				VI_ERROR_PARAMETER5);
				
	model_type = instrPtr->modelType;				
	if(IS_E506x)
	{
		CHECKPARAM((measurementParameter != 0 && measurementParameter != 1 && measurementParameter != 4 && 
					measurementParameter != 5), VI_ERROR_PARAMETER5);
	}
		
	CHECKPARAM( agena_invalidViInt32Range(dataFormat, 0, 16),
				VI_ERROR_PARAMETER6);

    p2buffer += sprintf(p2buffer, ":CALC%ld:PAR%ld:SEL\n", activeChannel,
                        activeTrace);
    p2buffer += sprintf(p2buffer, ":CALC%ld:FORM %s;", activeChannel,
                        agena_dataFormat[dataFormat]);
    p2buffer += sprintf(p2buffer, ":CALC%ld:PAR%ld:DEF %s;", activeChannel,
                        activeTrace, agena_measParameters[measurementParameter]);
    p2buffer += sprintf(p2buffer, ":CALC%ld:PAR:COUN %ld;", activeChannel,
                        numberOfTraces);
    p2buffer += sprintf(p2buffer, ":DISP:WIND%ld:ACT;", activeChannel);
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    DebugPrintf("%s\n", send_buffer);
    CHECKERR( agena_checkStatus( instrumentHandle));
    
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Sweep Stimulus
/* Purpose:  This function sets frequency, power or time sweep parameters.
/*           			
/*===========================================================================*/
ViStatus _VI_FUNC agena_confSweepStimulus (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean	signalOutput,
    ViInt32     stimulus,
    ViReal64    parameter,
    ViInt32     unit
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViBooleanRange(signalOutput),
				VI_ERROR_PARAMETER3);				
	CHECKPARAM( agena_invalidViInt32Range(stimulus, 0, 3),
				VI_ERROR_PARAMETER4);
    CHECKPARAM( agena_invalidViInt32Range(unit, 0, 5),
				VI_ERROR_PARAMETER6);
    
    p2buffer += sprintf(p2buffer, ":OUTP:STAT %s;", (signalOutput) ? "ON" : "OFF");  
    
    switch (unit)
    {
    case AGENA_STIMULUS_UNITS_GHZ:
        parameter *= 1.0e3;
    case AGENA_STIMULUS_UNITS_MHZ:
        parameter *= 1.0e3;
    case AGENA_STIMULUS_UNITS_KHZ:
        parameter *= 1.0e3;
    case AGENA_STIMULUS_UNITS_HZ:
        p2buffer += sprintf(p2buffer, ":SENS%ld:FREQ:", channel);
        break;

    case AGENA_STIMULUS_UNITS_DBM:
        p2buffer += sprintf(p2buffer, ":SOUR%ld:POW:", channel);
        break;

    case AGENA_STIMULUS_UNITS_S:
        p2buffer += sprintf(p2buffer, ":SENS%ld:SWE:TIME:AUTO ", channel);
        break;
    }
    
    if (unit != AGENA_STIMULUS_UNITS_S)
    {
        switch (stimulus)
        {
        case AGENA_STIMULUS_START:
            p2buffer += sprintf(p2buffer, "STAR ");
            break;
        case AGENA_STIMULUS_STOP:
            p2buffer += sprintf(p2buffer, "STOP ");
            break;
        case AGENA_STIMULUS_CENTER:
            p2buffer += sprintf(p2buffer, "CENT ");
            break;
        case AGENA_STIMULUS_SPAN:
            p2buffer += sprintf(p2buffer, "SPAN ");
            break;
        }
        p2buffer += sprintf(p2buffer, "%lf\n", parameter);
    }
    else
    {
        if (parameter < 0.0)
        {
            p2buffer += sprintf(p2buffer, "ON\n");
        }
        else
        {
            p2buffer += sprintf(p2buffer, "OFF;:SENS%ld:SWE:TIME %lf\n",
                                channel, parameter);
        }
    }
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Power
/* Purpose:  This function configures power settings.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confPower (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     port,
    ViBoolean   portCoupling,
    ViBoolean   autoPowerRange,
    ViReal64    powerRange,
    ViBoolean   powerSlope,
    ViReal64    powerSlopeCoefficient,
    ViReal64    powerLevel
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(port, 0, instrPtr->numPorts),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViBooleanRange(portCoupling),
				VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViBooleanRange(autoPowerRange),
				VI_ERROR_PARAMETER5);
	CHECKPARAM( agena_invalidViBooleanRange(powerSlope),
				VI_ERROR_PARAMETER7);
	CHECKPARAM( agena_invalidViReal64Range(powerSlopeCoefficient, -2.0, 2.0),
				VI_ERROR_PARAMETER8);
	CHECKPARAM( agena_invalidViReal64Range(powerSlopeCoefficient, -50.0, 10.0),
				VI_ERROR_INSTR_PARAMETER9);				
	    
    p2buffer += sprintf(p2buffer, ":SOUR%ld:POW", channel);
    if (port > 0)
    {
        p2buffer += sprintf(p2buffer, ":PORT%ld", port);
    }
    p2buffer += sprintf(p2buffer, " %lf;", powerLevel);

 
    p2buffer += sprintf(p2buffer, ":SOUR%ld:POW:PORT:COUP %s;", channel,
                        (portCoupling) ? "ON" : "OFF");
    
    if(!IS_E506x)
    {
    	p2buffer += sprintf(p2buffer, ":SOUR%ld:POW:ATT:AUTO %s;", channel,
                        (autoPowerRange) ? "ON" : "OFF");
	}                        
    if (!autoPowerRange)
        p2buffer += sprintf(p2buffer, ":SOUR%ld:POW:ATT %lf;", channel, powerRange);
    
    p2buffer += sprintf(p2buffer, ":SOUR%ld:POW:SLOP:STAT %s;", channel,
                        (powerSlope) ? "ON" : "OFF");
    if (powerSlope)
        p2buffer += sprintf(p2buffer, ":SOUR%ld:POW:SLOP %lf", channel, powerSlopeCoefficient);
    
    p2buffer += sprintf(p2buffer, "\n");
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Fixed Frequency
/* Purpose:  This function sets the fixed frequency (CW frequency) for the 
/*           power sweep.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confFixedFreq (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViReal64    fixedFrequency
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar		send_buffer[1024] = "";
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    sprintf(send_buffer, ":SENS%ld:FREQ %lf\n", channel, fixedFrequency);
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));
    
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Sweep
/* Purpose:  This function configure sweep paramters.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confSweep (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     numberOfMeasurementPoints,
    ViReal64    delayTime,
	ViInt32     sweepType,
    ViInt32     sweepMode,
    ViInt32     autoSweepTime,
    ViReal64    sweepTime,
	ViBoolean 	spuriousAvoidMode
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    model_type = instrPtr->modelType;
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(numberOfMeasurementPoints, 2, 1601),
    			VI_ERROR_PARAMETER3);
    CHECKPARAM( agena_invalidViReal64Range(delayTime, 0.0, 1.0),
    			VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViInt32Range(sweepType, 0, 3),
    			VI_ERROR_PARAMETER5);    			
    CHECKPARAM( agena_invalidViInt32Range(sweepMode, 0, 3),
    			VI_ERROR_PARAMETER6);
    CHECKPARAM( agena_invalidViBooleanRange(autoSweepTime),
    			VI_ERROR_PARAMETER7);
	CHECKPARAM( agena_invalidViBooleanRange(spuriousAvoidMode),
    			VI_ERROR_INSTR_PARAMETER9);
    
    p2buffer += sprintf(p2buffer, ":SENS%ld:SWE:POIN %ld;", channel, numberOfMeasurementPoints);
    p2buffer += sprintf(p2buffer, "DEL %lf;", delayTime);
    if(!IS_E506x)
    {
    	p2buffer += sprintf(p2buffer, "GEN %s;", agena_sweepMode[sweepMode]);
    }
    p2buffer += sprintf(p2buffer, "TYPE %s;", agena_sweepType[sweepType]);
   
    if(!IS_E506x)
    {
    	p2buffer += sprintf(p2buffer, "ASP %s;", spuriousAvoidMode ? "ON" : "OFF");
    }
    p2buffer += sprintf(p2buffer, "TIME:AUTO %s", autoSweepTime ? "ON" : "OFF");
    if (!autoSweepTime)
    {
        p2buffer += sprintf(p2buffer, ";:SENS%ld:SWE:TIME %lf", channel, sweepTime);
    }
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Define Sweep Segments Table
/* Purpose:  This function load sweep segments into instrument.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confSweepSegments (ViSession instrumentHandle,
	ViInt32 channel,
	ViInt32 stimulusSettingMode,
	ViBoolean eachSegmentIFBwidSetting,
	ViBoolean eachSegmentPowerSetting,
	ViBoolean eachSegmentSwDelaySetting,
	ViBoolean eachSegmentSwModeSetting,
	ViBoolean eachSegmentSwTimeSetting,
	ViInt32 number_ofSegments,
	ViReal64 startCenterValues[],
	ViReal64 stopSpanValues[],
	ViInt32 numbers_ofMeasPoints[],
	ViReal64 IFBandwidths[],
	ViReal64 powers[],
	ViReal64 sweepDelayTimes[],
	ViReal64 sweepModes[],
	ViReal64 sweepTimes[]
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViInt32		buffer_size = 0,
    			i = 0;
    ViChar*		send_buffer = NULL;
    ViChar*     p2buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(stimulusSettingMode, 0, 1),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViBooleanRange(eachSegmentIFBwidSetting),
				VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViBooleanRange(eachSegmentPowerSetting),
				VI_ERROR_PARAMETER5);
	CHECKPARAM( agena_invalidViBooleanRange(eachSegmentSwDelaySetting),
				VI_ERROR_PARAMETER6);
	CHECKPARAM( agena_invalidViBooleanRange(eachSegmentSwModeSetting),
				VI_ERROR_PARAMETER7);
	CHECKPARAM( agena_invalidViBooleanRange(eachSegmentSwTimeSetting),
				VI_ERROR_PARAMETER8);
	CHECKPARAM( agena_invalidViInt32Range(number_ofSegments, 1, 201),
				VI_ERROR_INSTR_PARAMETER9);
    
    if (startCenterValues == NULL)
    	CHECKERR( VI_ERROR_INSTR_PARAMETER10);
    if (stopSpanValues == NULL)
    	CHECKERR( VI_ERROR_INSTR_PARAMETER11);
    if (numbers_ofMeasPoints == NULL)
    	CHECKERR( VI_ERROR_INSTR_PARAMETER12);
    	
    if (eachSegmentIFBwidSetting)
	{
		if (IFBandwidths == NULL)
    		CHECKERR( VI_ERROR_INSTR_PARAMETER13);
	}
	if (eachSegmentPowerSetting)
	{
		if (powers == NULL)
    		CHECKERR( VI_ERROR_INSTR_PARAMETER14);
	}
	if (eachSegmentSwDelaySetting)
	{
		if (sweepDelayTimes == NULL)
    		CHECKERR( VI_ERROR_INSTR_PARAMETER15);
	}
	if (eachSegmentSwModeSetting)
	{
		if (sweepModes == NULL)
    		CHECKERR( VI_ERROR_INSTR_PARAMETER16);
	}
	if (eachSegmentSwTimeSetting)
	{
		if (sweepTimes == NULL)
    		CHECKERR( VI_ERROR_INSTR_PARAMETER17);
	}

	/* Allocate correct buffer size for send */
	/* 20 - command size                     */
	/* 12 - data mode, IF Bandwidth, Power, Sweep delay, Sweep mode, Sweep Time */
	/* log(number_ofSegments) + 1 - character count of array size               */
	/* rest - size of arrays values                                             */
	buffer_size = 20 + 12 + log(number_ofSegments) + 1 + number_ofSegments * 8 * DOUBLE_BYTE_SIZE;
    send_buffer = (char*) malloc (buffer_size * sizeof(char));
    p2buffer = send_buffer;
    
    p2buffer += sprintf(p2buffer, ":SENS%ld:SEGM:DATA 6,", channel);
    
    p2buffer += sprintf(p2buffer, "%ld,", stimulusSettingMode);
    p2buffer += sprintf(p2buffer, "%ld,", eachSegmentIFBwidSetting);
    p2buffer += sprintf(p2buffer, "%ld,", eachSegmentPowerSetting);
    p2buffer += sprintf(p2buffer, "%ld,", eachSegmentSwDelaySetting);
    p2buffer += sprintf(p2buffer, "%ld,", eachSegmentSwModeSetting);
    p2buffer += sprintf(p2buffer, "%ld,", eachSegmentSwTimeSetting);
    p2buffer += sprintf(p2buffer, "%ld", number_ofSegments);
    														 
    for (i = 0; i < number_ofSegments; i++)
    {
    	p2buffer += sprintf(p2buffer, ",%le,%le,%ld", startCenterValues[i], stopSpanValues[i],
    						numbers_ofMeasPoints[i]);

    	if (eachSegmentIFBwidSetting)
    	{
    		p2buffer += sprintf(p2buffer, ",%le", IFBandwidths[i]);
    	}
    	if (eachSegmentPowerSetting)
    	{
    		p2buffer += sprintf(p2buffer, ",%le", powers[i]);
    	}
    	if (eachSegmentSwDelaySetting)
    	{
    		p2buffer += sprintf(p2buffer, ",%le", sweepDelayTimes[i]);
    	}
    	if (eachSegmentSwModeSetting)
    	{
    		p2buffer += sprintf(p2buffer, ",%le", sweepModes[i]);
    	}
    	if (eachSegmentSwTimeSetting)
    	{
    		p2buffer += sprintf(p2buffer, ",%le", sweepTimes[i]);
    	}
    }
    
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	if (send_buffer != NULL)
	{
		free(send_buffer);
		send_buffer = NULL;
	}
	
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure IF Bandwidth
/* Purpose:  This function configure IF bandwidth setting.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confIFBwid (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViReal64    IFBandwidth
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar		send_buffer[1024] = "";
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViReal64Range(IFBandwidth, 10.0, 1.0e+5),
				VI_ERROR_PARAMETER3);

    sprintf(send_buffer, ":SENS%ld:BAND %lf\n", channel, IFBandwidth);
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Averaging
/* Purpose:  This function configure averaging of active channel.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confAveraging (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   state,
    ViInt32     factor
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViBooleanRange(state),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViInt32Range(factor, 1, 999),
				VI_ERROR_PARAMETER4);

    p2buffer += sprintf(p2buffer, ":SENS%ld:AVER %s", channel, state ? "ON" : "OFF");
    
    if (state)
    {
    	p2buffer += sprintf(p2buffer, ";AVER:COUN %ld", factor);
    }
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Smoothing
/* Purpose:  This function configure the smoothing for active channel.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confSmoothing (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   state,
    ViReal64    smoothingAperture
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViBooleanRange(state),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViReal64Range(smoothingAperture, 0.05, 25.0),
				VI_ERROR_PARAMETER4);

    p2buffer += sprintf(p2buffer, ":CALC%ld:SMO %s", channel, state ? "ON" : "OFF");
    
    if (state)
    {
    	p2buffer += sprintf(p2buffer, ";SMO:APER %lf", smoothingAperture);
    }
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Absolute Measurement
/* Purpose:  This function configure absolute measurement of active channel.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confAbsoluteMeasurement (
    ViSession	instrumentHandle,
    ViInt32		channel,
    ViInt32		port,
	ViInt32		trace,
    ViInt32		measurementParameter
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32		model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
				VI_ERROR_PARAMETER3);				
    CHECKPARAM( agena_invalidViInt32Range(trace, 1, instrPtr->numTraces),
				VI_ERROR_PARAMETER4);
    CHECKPARAM( agena_invalidViInt32Range( measurementParameter, 0, 23),
    			VI_ERROR_PARAMETER5); 

	model_type = instrPtr->modelType;				
	if(!IS_E506x)
	{
    	p2buffer += sprintf(p2buffer, ":CALC%ld:PAR%ld:SPOR %ld;", channel, trace, port);
	    p2buffer += sprintf(p2buffer, "DEF %s\n", agena_measParameters[measurementParameter]);
    } 
    else
    {
		CHECKPARAM((measurementParameter != 0 && measurementParameter != 1 && measurementParameter != 4 && 
					measurementParameter != 5), VI_ERROR_PARAMETER5);

	    p2buffer += sprintf(p2buffer, ":CALC%ld:PAR%ld:DEF %s\n", channel, trace, 
    						agena_measParameters[measurementParameter]);
	}
	
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure External Signal Source
/* Purpose:  This function configure external signal source for selected 
/*           channel.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confExtSignalSource (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   controlState,
    ViBoolean   frequencyOffsetState,
    ViInt32     multiplier,
    ViInt32     divisor,
    ViReal64    offset,
    ViReal64    start,
    ViReal64    stop,
    ViBoolean   powerSlopeState,
    ViReal64    powerLevel,
    ViReal64    powerSlope
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	if(!IS_E506x)
	{
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViBooleanRange(controlState),
					VI_ERROR_PARAMETER3);
	    CHECKPARAM( agena_invalidViBooleanRange(frequencyOffsetState),
					VI_ERROR_PARAMETER4);
		CHECKPARAM( agena_invalidViInt32Range(multiplier, -100, 100),
					VI_ERROR_PARAMETER5);
		CHECKPARAM( agena_invalidViInt32Range(divisor, 1, 100),
					VI_ERROR_PARAMETER6);
		CHECKPARAM( agena_invalidViReal64Range(offset, -1.0e+12, 1.0e+12),
					VI_ERROR_PARAMETER7);
		CHECKPARAM( agena_invalidViReal64Range(start, 0.0, 1.0e+12),
					VI_ERROR_PARAMETER8);
		CHECKPARAM( agena_invalidViReal64Range(stop, 0.0, 1.0e+12),
					VI_ERROR_INSTR_PARAMETER9);
		CHECKPARAM( agena_invalidViBooleanRange(powerSlopeState),
					VI_ERROR_INSTR_PARAMETER10);
		CHECKPARAM( agena_invalidViReal64Range(powerLevel, -150.0, 30.0),
					VI_ERROR_INSTR_PARAMETER11);
		CHECKPARAM( agena_invalidViReal64Range(powerSlope, -2.0, 2.0),
					VI_ERROR_INSTR_PARAMETER12);

	    p2buffer += sprintf(p2buffer, ":SENS%ld:OFFS:LOC:CONT %s;", channel,
	    					controlState ? "ON" : "OFF");
	   	p2buffer += sprintf(p2buffer, "STAT %s;", frequencyOffsetState ? "ON" : "OFF");
	   	p2buffer += sprintf(p2buffer, "MULT %ld;", multiplier);
	   	p2buffer += sprintf(p2buffer, "DIV %ld;", divisor);
	   	p2buffer += sprintf(p2buffer, "OFFS %lf;", offset);
	   	p2buffer += sprintf(p2buffer, "STAR %lf;", start);
	   	p2buffer += sprintf(p2buffer, "STOP %lf;", stop);
	   	p2buffer += sprintf(p2buffer, "POW %lf;", powerLevel);
	   	p2buffer += sprintf(p2buffer, ":SENS%ld:OFFS:LOC:POW:SLOP %lf;", channel, powerSlope);
	   	p2buffer += sprintf(p2buffer, ":SENS%ld:OFFS:LOC:POW:SLOP:STAT %s\n", channel,
	   						powerSlopeState ? "ON" : "OFF");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Frequency Offset
/* Purpose:  This function configure frequency offset parameters.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confFreqOffset (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     port,
    ViBoolean   state,
    ViInt32     multiplier,
    ViInt32     divisor,
    ViReal64    offset,
    ViReal64    start,
    ViReal64    stop,
    ViInt32     xAxisFreq,
	ViBoolean   avoidSpurious   
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32		model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
  	if(!IS_E506x)
  	{
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER3);
	    CHECKPARAM( agena_invalidViBooleanRange(state),
					VI_ERROR_PARAMETER4);
		CHECKPARAM( agena_invalidViInt32Range(multiplier, -100, 100),
					VI_ERROR_PARAMETER5);
		CHECKPARAM( agena_invalidViInt32Range(divisor, 1, 100),
					VI_ERROR_PARAMETER6);
		CHECKPARAM( agena_invalidViReal64Range(offset, -1.0e+12, 1.0e+12),
					VI_ERROR_PARAMETER7);
		CHECKPARAM( agena_invalidViReal64Range(start, 300.0e+3, 8.5e+9),
					VI_ERROR_PARAMETER8);
		CHECKPARAM( agena_invalidViReal64Range(stop, 300.0e+3, 8.5e+9),
					VI_ERROR_INSTR_PARAMETER9);
	    if (state)
		    CHECKPARAM( agena_invalidViInt32Range(xAxisFreq, 0, 6),
		    			VI_ERROR_INSTR_PARAMETER10); 
    
		CHECKPARAM( agena_invalidViBooleanRange(avoidSpurious),
					VI_ERROR_INSTR_PARAMETER11);
				
	    p2buffer += sprintf(p2buffer, ":SENS%ld:OFFS %s;", channel, state ? "ON" : "OFF");
	   	p2buffer += sprintf(p2buffer, ":SENS%ld:OFFS:PORT%ld:MULT %ld;", channel, port,
	   						multiplier);
	   	p2buffer += sprintf(p2buffer, "DIV %ld;", divisor);
	   	p2buffer += sprintf(p2buffer, "OFFS %lf;", offset);
	   	p2buffer += sprintf(p2buffer, "STAR %lf;", start);
	   	p2buffer += sprintf(p2buffer, "STOP %lf;", stop);

	 	p2buffer += sprintf(p2buffer, ":SENS%ld:OFFS:ASP %s;", channel, avoidSpurious ? "ON" : "OFF");
 		
	   	if (state)
	   		p2buffer += sprintf(p2buffer, ":CALC%ld:OFFS:XAX %s", channel,
	   						agena_xAxisFreq[xAxisFreq]);
	   	else
	   		p2buffer += sprintf(p2buffer, ":CALC%ld:MIX:XAX %s", channel,
	   						agena_xAxisFreq[xAxisFreq]);   							
	
		p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
  
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Layout
/* Purpose:  This function configure the graph layout for selected channel 
/*           or the layout of the windows on the LCD display.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confLayout (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     graphLayout
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;
	ViInt32		model_type;
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 0, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range( graphLayout, 0, 21), VI_ERROR_PARAMETER3);
	
	model_type = instrPtr->modelType;
	if(IS_E506x)
	{
		CHECKPARAM( (graphLayout >= 14 && graphLayout <= 21) , VI_ERROR_PARAMETER3);  	
	}
	
    p2buffer += sprintf(p2buffer, ":DISP:");
   	if (channel != 0)
   	{
   		p2buffer += sprintf(p2buffer, "WIND%ld:", channel);
   	}
   	p2buffer += sprintf(p2buffer, "SPL %s\n", agena_graphLayout[graphLayout]);
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Display
/* Purpose:  This function configure display paramters.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confDisplay (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   backlight,
    ViBoolean   displayUpdate,
    ViBoolean   graticuleLabel,  
    ViBoolean   clock,
    ViBoolean   frequency,
    ViBoolean   softkeyLabel,
	ViBoolean   title,
    ViString    titleText, 
	ViBoolean   table, 
    ViInt32     tableSelect, 
    ViInt32     displayType,
    ViBoolean   statisticAnalysisResult,
	ViBoolean   maximize
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViBooleanRange(backlight), VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViBooleanRange(displayUpdate), VI_ERROR_PARAMETER4);
    CHECKPARAM( agena_invalidViBooleanRange(graticuleLabel), VI_ERROR_PARAMETER5);
	CHECKPARAM( agena_invalidViBooleanRange(clock), VI_ERROR_PARAMETER6);
	CHECKPARAM( agena_invalidViBooleanRange(frequency), VI_ERROR_PARAMETER7);
	CHECKPARAM( agena_invalidViBooleanRange(softkeyLabel), VI_ERROR_PARAMETER8);
    CHECKPARAM( agena_invalidViBooleanRange(title), VI_ERROR_INSTR_PARAMETER9);
    CHECKPARAM( agena_invalidViBooleanRange(table), VI_ERROR_INSTR_PARAMETER11);
    if (table)
    	CHECKPARAM( agena_invalidViInt32Range(tableSelect, 0, 5), VI_ERROR_INSTR_PARAMETER12);
	
	CHECKPARAM( agena_invalidViInt32Range(displayType, 0, 1), VI_ERROR_INSTR_PARAMETER13);
	CHECKPARAM( agena_invalidViBooleanRange(statisticAnalysisResult), VI_ERROR_INSTR_PARAMETER14); 
	CHECKPARAM( agena_invalidViBooleanRange(maximize), VI_ERROR_INSTR_PARAMETER15);  

	
    p2buffer += sprintf(p2buffer, ":SYST:BACK %s;", backlight ? "ON" : "OFF");
	p2buffer += sprintf(p2buffer, ":DISP:ANN:FREQ %s;", frequency ? "ON" : "OFF");  
    p2buffer += sprintf(p2buffer, ":DISP:ENAB %s;", displayUpdate ? "ON" : "OFF");

    p2buffer += sprintf(p2buffer, "CLOC %s;", clock ? "ON" : "OFF");
    p2buffer += sprintf(p2buffer, "SKEY %s;", softkeyLabel ? "ON" : "OFF");
    p2buffer += sprintf(p2buffer, "IMAG %s;", agena_displayType[displayType]);

    p2buffer += sprintf(p2buffer, "TABL %s;", table ? "ON" : "OFF");
    if (table)
    	p2buffer += sprintf(p2buffer, "TABL:TYPE %s;", agena_dispTableType[tableSelect]);
    
    p2buffer += sprintf(p2buffer, ":DISP:WIND%ld:LAB %s;", channel,
    					graticuleLabel ? "ON" : "OFF");
    p2buffer += sprintf(p2buffer, "TITL %s;", title ? "ON" : "OFF");
    if (title)
    	p2buffer += sprintf(p2buffer, "TITL:DATA \"%s\";", titleText);
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:MST %s;", channel,
    					statisticAnalysisResult ? "ON" : "OFF");
    					
	p2buffer += sprintf(p2buffer, ":DISP:");
   		if (channel != 0)
   		{
   			p2buffer += sprintf(p2buffer, "WIND%ld:", channel);
   		}
   		p2buffer += sprintf(p2buffer, "MAX %s\n", maximize ? "ON" : "OFF");
   	

    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Trace Display
/* Purpose:  This function configure display of active trace.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confTraceDisplay (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     trace,
    ViInt32     traceDisplay,
    ViBoolean   displayData,
    ViBoolean   displayMemory
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(trace, 1, instrPtr->numTraces),
				VI_ERROR_PARAMETER3);
    CHECKPARAM( agena_invalidViInt32Range( traceDisplay, 0, 4), VI_ERROR_PARAMETER4);
    CHECKPARAM( agena_invalidViBooleanRange(displayData), VI_ERROR_PARAMETER5);
	CHECKPARAM( agena_invalidViBooleanRange(displayMemory), VI_ERROR_PARAMETER6);

    p2buffer += sprintf(p2buffer, ":CALC%ld:MATH:FUNC %s;", channel,
    					agena_dispTraceType[traceDisplay]);
    p2buffer += sprintf(p2buffer, ":DISP:WIND%ld:TRAC%ld:STAT %s;", channel, trace,
    					displayData ? "ON" : "OFF");
    p2buffer += sprintf(p2buffer, "MEM %s\n", displayMemory ? "ON" : "OFF");

    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Display Color
/* Purpose:  This function sets color of specific display item.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confColor (
    ViSession   instrumentHandle,
    ViInt32     displayType,
    ViInt32     trace,
    ViInt32     setting,
    ViInt32     r,
    ViInt32     g,
    ViInt32     b
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range( displayType, 0, 1), VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(trace, 1, instrPtr->numTraces),
				VI_ERROR_PARAMETER3);
    CHECKPARAM( agena_invalidViInt32Range( setting, 0, 6), VI_ERROR_PARAMETER4);
    CHECKPARAM( agena_invalidViInt32Range( r, 0, 5), VI_ERROR_PARAMETER5);
    CHECKPARAM( agena_invalidViInt32Range( g, 0, 5), VI_ERROR_PARAMETER6);
    CHECKPARAM( agena_invalidViInt32Range( b, 0, 5), VI_ERROR_PARAMETER7);
    
    p2buffer += sprintf(p2buffer, ":DISP:IMAG %s;", agena_displayType[displayType]); 
    
    p2buffer += sprintf(p2buffer, ":DISP:COL%ld:", displayType + 1);
    
    switch (setting)
    {
    case AGENA_DISPLAY_COLOR_DATA_TRACE:
    	p2buffer += sprintf(p2buffer, "TRAC%ld:DATA", trace);
		break;
	
	case AGENA_DISPLAY_COLOR_MEMORY_TRACE:
		p2buffer += sprintf(p2buffer, "TRAC%ld:MEM", trace);
		break;
		
	case AGENA_DISPLAY_COLOR_GRAPH_OUTER_FRAME:
		p2buffer += sprintf(p2buffer, "GRAT1");
		break;
	
	case AGENA_DISPLAY_COLOR_GRAPH_GRID_LINE:
		p2buffer += sprintf(p2buffer, "GRAT2");
		break;
		
	case AGENA_DISPLAY_COLOR_LIMIT_TEST_RESULT:
		p2buffer += sprintf(p2buffer, "LIM1");
		break;
		
	case AGENA_DISPLAY_COLOR_LIMIT_LINE:
		p2buffer += sprintf(p2buffer, "LIM2");
		break;
	
	case AGENA_DISPLAY_COLOR_BACKGROUND:
		p2buffer += sprintf(p2buffer, "BACK");
		break;
    }
    
    p2buffer += sprintf(p2buffer, " %ld,%ld,%ld\n", r, g, b);

    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure X Axis For Segment Sweep
/* Purpose:  This function selects the display method of the graph 
/*           horizontal axis of selected channel for segment sweep.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confXAxisSegmentSweep (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     displayMethod
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range( displayMethod, 0, 1), VI_ERROR_PARAMETER3);
    
    p2buffer += sprintf(p2buffer, ":DISP:WIND%ld:X:SPAC %s\n", channel,
    					agena_dispMethod[displayMethod]);
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Corrections
/* Purpose:  This function configure display corrections.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confDispCorr (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViReal64    electricalDelayTime,
    ViReal64    velocityFactor,
    ViReal64    phaseOffset
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViReal64Range(electricalDelayTime, -10.0, 10.0),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViReal64Range(velocityFactor, 0.0, 10.0),
				VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViReal64Range(phaseOffset, -360.0, 360.0),
				VI_ERROR_PARAMETER5);

    p2buffer += sprintf(p2buffer, ":CALC%ld:CORR:EDEL:TIME %lf;", channel,
    					electricalDelayTime);
    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:RVEL:COAX %lf;", channel,
    					velocityFactor);
    p2buffer += sprintf(p2buffer, ":CALC%ld:CORR:OFFS:PHAS %lf\n", channel,
    					phaseOffset);
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Scale
/* Purpose:  This function configure display scale.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confScale (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     trace,
    ViInt32     number_ofDivisions,
    ViReal64    scale_perDivision,
    ViInt32     referenceGraticuleLine,
    ViReal64    valueGraticuleLine
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(trace, 1, instrPtr->numTraces),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViInt32Range(number_ofDivisions, 4, 30),
				VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViReal64Range(scale_perDivision, 1.0e-18, 1.0e18),
				VI_ERROR_PARAMETER5);
	CHECKPARAM( agena_invalidViInt32Range(referenceGraticuleLine, 0, number_ofDivisions),
				VI_ERROR_PARAMETER6);
	CHECKPARAM( agena_invalidViInt32Range(valueGraticuleLine, -5.0e8, 5.0e8),
				VI_ERROR_PARAMETER7);
	
    p2buffer += sprintf(p2buffer, ":DISP:WIND%ld:Y:DIV %ld;", channel,
    					number_ofDivisions);
    p2buffer += sprintf(p2buffer, ":DISP:WIND%ld:TRAC%ld:Y:PDIV %lf;", channel, trace,
    					scale_perDivision);
    p2buffer += sprintf(p2buffer, "RLEV %ld;", referenceGraticuleLine);
    p2buffer += sprintf(p2buffer, "RPOS %lf\n", valueGraticuleLine);
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Calibration
/* Purpose:  This function configure calibration parameters.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confCal (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     calKit,
    ViInt32     calType,
    ViInt32     port1,
    ViInt32     port2,
    ViInt32     port3,
    ViBoolean   errorCorrectionState,
    ViBoolean   calibrationPropertyDisplay,
    ViReal64    velocityFactor,
    ViReal64    z0
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*    			p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
	model_type = instrPtr->modelType;

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(calKit, 1, 10), VI_ERROR_PARAMETER3);
    CHECKPARAM( agena_invalidViInt32Range(calType, 0, 6), VI_ERROR_PARAMETER4);
	if(IS_E506x)
	{
    	CHECKPARAM( (calType == AGENA_CALIBRATION_TYPE_3_PORT ||
					 calType == AGENA_CALIBRATION_TYPE_4_PORT), VI_ERROR_PARAMETER4);	 
	}
	else
	{
    	CHECKPARAM( (calType == AGENA_CALIBRATION_TYPE_EN_RESPONSE), VI_ERROR_PARAMETER4);	 
	}
	
    switch (calType)
    {
    case AGENA_CALIBRATION_TYPE_3_PORT:
		CHECKPARAM( agena_invalidViInt32Range(port3, 1, instrPtr->numPorts),
    			VI_ERROR_PARAMETER7);
	
	case AGENA_CALIBRATION_TYPE_THROUGH:
	case AGENA_CALIBRATION_TYPE_2_PORT:
	case AGENA_CALIBRATION_TYPE_EN_RESPONSE:
		CHECKPARAM( agena_invalidViInt32Range(port2, 1, instrPtr->numPorts),
    				VI_ERROR_PARAMETER6);

	case AGENA_CALIBRATION_TYPE_OPEN:
	case AGENA_CALIBRATION_TYPE_SHORT:
	case AGENA_CALIBRATION_TYPE_1_PORT:
		CHECKPARAM( agena_invalidViInt32Range(port1, 1, instrPtr->numPorts),
    				VI_ERROR_PARAMETER5);
	    break;

	case AGENA_CALIBRATION_TYPE_4_PORT:
	    break;
    }
    
    CHECKPARAM( agena_invalidViBooleanRange(errorCorrectionState), VI_ERROR_PARAMETER8);
    CHECKPARAM( agena_invalidViBooleanRange(calibrationPropertyDisplay),
    			VI_ERROR_INSTR_PARAMETER9);
    CHECKPARAM( agena_invalidViReal64Range(velocityFactor, 0.0, 10.0),
    			VI_ERROR_INSTR_PARAMETER10);
	CHECKPARAM( agena_invalidViReal64Range(z0, 1.0e-3, 1000.0),
    			VI_ERROR_INSTR_PARAMETER11);

    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:COLL:CKIT %ld;", channel, calKit);
    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:COLL:METH:", channel);
    
    switch (calType)
    {
    case AGENA_CALIBRATION_TYPE_OPEN:
	    p2buffer += sprintf(p2buffer, "OPEN %ld;", port1);
	    break;

	case AGENA_CALIBRATION_TYPE_SHORT:
		p2buffer += sprintf(p2buffer, "SHOR %ld;", port1);
	    break;

	case AGENA_CALIBRATION_TYPE_THROUGH:
		p2buffer += sprintf(p2buffer, "THRU %ld,%ld;", port1, port2);
	    break;

	case AGENA_CALIBRATION_TYPE_1_PORT:
		p2buffer += sprintf(p2buffer, "SOLT1 %ld;", port1);
	    break;

	case AGENA_CALIBRATION_TYPE_2_PORT:
		p2buffer += sprintf(p2buffer, "SOLT2 %ld,%ld;", port1, port2);
	    break;

	case AGENA_CALIBRATION_TYPE_3_PORT:
		p2buffer += sprintf(p2buffer, "SOLT3 %ld,%ld,%ld;", port1, port2,
							port3);
	    break;

	case AGENA_CALIBRATION_TYPE_4_PORT:
		p2buffer += sprintf(p2buffer, "SOLT4 1,2,3,4;");
	    break;
	    
	case AGENA_CALIBRATION_TYPE_EN_RESPONSE:
		p2buffer += sprintf(p2buffer, "ERES %ld,%ld;", port1, port2);
	    break;
    }
    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:STAT %s;", channel,
    					errorCorrectionState ? "ON" : "OFF");
    p2buffer += sprintf(p2buffer, "PROP %s;", calibrationPropertyDisplay ? "ON" : "OFF");
    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:RVEL:COAX %lf", channel,
    					velocityFactor);
	if(!IS_E506x)
	{
		p2buffer += sprintf(p2buffer, ";:SENS:CORR:IMP %lf", z0);
	}
	p2buffer += sprintf(p2buffer, "\n");
		
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Calibration Kit
/* Purpose:  This function configure calibration kit standard.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confCalKit (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     standard,
    ViString    label,
    ViInt32     type,
    ViReal64    c0,
    ViReal64    c1,
    ViReal64    c2,
    ViReal64    c3,
    ViReal64    l0,
    ViReal64    l1,
    ViReal64    l2,
    ViReal64    l3,
    ViReal64    arbitraryImpedance,
    ViString    calKitName
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*   	  		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
	
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(standard, 1, 21), VI_ERROR_PARAMETER3);
	model_type = instrPtr->modelType;
	if(IS_E506x)
	{
		CHECKPARAM( (standard > 4), VI_ERROR_PARAMETER3);	
	}
    CHECKPARAM( agena_invalidViInt32Range(type, 0, 5), VI_ERROR_PARAMETER5);
    CHECKPARAM( agena_invalidViReal64Range(c0, -1.0e18, 1.0e18), VI_ERROR_PARAMETER6);
    CHECKPARAM( agena_invalidViReal64Range(c1, -1.0e18, 1.0e18), VI_ERROR_PARAMETER7);
    CHECKPARAM( agena_invalidViReal64Range(c2, -1.0e18, 1.0e18), VI_ERROR_PARAMETER8);
    CHECKPARAM( agena_invalidViReal64Range(c3, -1.0e18, 1.0e18),
    			VI_ERROR_INSTR_PARAMETER9);
	CHECKPARAM( agena_invalidViReal64Range(l0, -1.0e18, 1.0e18),
    			VI_ERROR_INSTR_PARAMETER10);
	CHECKPARAM( agena_invalidViReal64Range(l1, -1.0e18, 1.0e18),
    			VI_ERROR_INSTR_PARAMETER11);
	CHECKPARAM( agena_invalidViReal64Range(l2, -1.0e18, 1.0e18),
    			VI_ERROR_INSTR_PARAMETER12);
	CHECKPARAM( agena_invalidViReal64Range(l3, -1.0e18, 1.0e18),
    			VI_ERROR_INSTR_PARAMETER13);
    CHECKPARAM( agena_invalidViReal64Range(arbitraryImpedance, -1.0e18, 1.0e18),
    			VI_ERROR_INSTR_PARAMETER14);

	p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:COLL:CKIT:LAB %s;", channel,
    				   calKitName);
    				   
    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:COLL:CKIT:STAN%ld:LAB %s;",
    					channel, standard, label);
    p2buffer += sprintf(p2buffer, "TYPE %s;", agena_calKitStandard[type]);
    p2buffer += sprintf(p2buffer, "C0 %lf;", c0);
    p2buffer += sprintf(p2buffer, "C1 %lf;", c1);
    p2buffer += sprintf(p2buffer, "C2 %lf;", c2);
    p2buffer += sprintf(p2buffer, "C3 %lf;", c3);
    p2buffer += sprintf(p2buffer, "L0 %lf;", l0);
    p2buffer += sprintf(p2buffer, "L1 %lf;", l1);
    p2buffer += sprintf(p2buffer, "L2 %lf;", l2);
    p2buffer += sprintf(p2buffer, "L3 %lf;", l3);
    p2buffer += sprintf(p2buffer, "ARB %lf\n", arbitraryImpedance);

    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Standard Offsets
/* Purpose:  This function configure calibration kit standard offset.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confCalKitStandardOffsets (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     standard,
    ViReal64    offsetDelay,
    ViReal64    offsetLoss,
    ViReal64    z0
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(standard, 1, 21),
				VI_ERROR_PARAMETER3);
	model_type = instrPtr->modelType;
	if(IS_E506x)
	{
		CHECKPARAM( (standard > 4), VI_ERROR_PARAMETER3);
	}
	CHECKPARAM( agena_invalidViReal64Range(offsetDelay, -1.0e18, 1.0e18),
				VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViReal64Range(offsetLoss, -1.0e18, 1.0e18),
				VI_ERROR_PARAMETER5);
	CHECKPARAM( agena_invalidViReal64Range(z0, -1.0e18, 1.0e18),
				VI_ERROR_PARAMETER6);

    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:COLL:CKIT:STAN%ld:DEL %lf;",
    					channel, standard, offsetDelay);
    p2buffer += sprintf(p2buffer, "LOSS %lf;", offsetLoss);
    p2buffer += sprintf(p2buffer, "Z0 %lf\n", z0);

    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Class
/* Purpose:  This function configure calibration kit class.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confCalKitClass (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     type,
    ViInt32     standard,
    ViInt32     port1,
    ViInt32     port2
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(type, 0, 3), VI_ERROR_PARAMETER3);
    CHECKPARAM( agena_invalidViInt32Range(standard, 1, 21), VI_ERROR_PARAMETER4);
    
    switch (type)
    {
    case AGENA_CALIB_STANDARD_THRU:
    	CHECKPARAM( agena_invalidViInt32Range(port2, 1, instrPtr->numPorts),
    				VI_ERROR_PARAMETER6);
    
    case AGENA_CALIB_STANDARD_OPEN:
    case AGENA_CALIB_STANDARD_SHORT:
    case AGENA_CALIB_STANDARD_LOAD:
    	CHECKPARAM( agena_invalidViInt32Range(port1, 1, instrPtr->numPorts),
    				VI_ERROR_PARAMETER5);
    	break;
    }
    
    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:COLL:CKIT:ORD:", channel);
    switch (type)
    {
    case AGENA_CALIB_STANDARD_OPEN:
    	p2buffer += sprintf(p2buffer, "OPEN %ld,", port1);
    	break;

    case AGENA_CALIB_STANDARD_SHORT:
    	p2buffer += sprintf(p2buffer, "SHOR %ld,", port1);
    	break;

    case AGENA_CALIB_STANDARD_LOAD:
    	p2buffer += sprintf(p2buffer, "LOAD %ld,", port1);
    	break;

    case AGENA_CALIB_STANDARD_THRU:
    	p2buffer += sprintf(p2buffer, "THRU %ld,%ld,", port1, port2);
    	break;
    }
    p2buffer += sprintf(p2buffer, "%ld\n", standard);

    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Port Extension
/* Purpose:  This function configure port extension settings.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confPortExtension (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   state,
    ViInt32     port1,
    ViReal64    correctionValue
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER3);
	if (state)
	{
		CHECKPARAM( agena_invalidViInt32Range(port1, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER4);
		CHECKPARAM( agena_invalidViReal64Range(correctionValue, -10.0, 10.0),
					VI_ERROR_PARAMETER5);
	}

    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:EXT %s", channel,
    					state ? "ON" : "OFF");
    if (state)
    	p2buffer += sprintf(p2buffer, ";:SENS%ld:CORR:EXT:PORT%ld %lf", channel,
    						port1, correctionValue);

	p2buffer += sprintf(p2buffer, "\n");

    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure ECal
/* Purpose:  This function configure electrical calibration.
/*           
/*           Notes:
/*           This function is available with the firmware version 3.50 or 
/*           greater.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confECal (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   isolationMeasurement,
    ViInt32     characterization
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViBooleanRange(isolationMeasurement), VI_ERROR_PARAMETER3);
    CHECKPARAM( agena_invalidViInt32Range(characterization, 0, 5), VI_ERROR_PARAMETER4);

    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:COLL:ECAL:ISOL %s", channel,
    					isolationMeasurement ? "ON" : "OFF");

    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		p2buffer += sprintf(p2buffer, ";:SENS%ld:CORR:COLL:ECAL:UCH %s", channel,
							agena_ECalCharacterization[characterization]);
	}
	p2buffer += sprintf(p2buffer, "\n");

    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Power Calibration
/* Purpose:  This function configure power calibration settings.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confPowCal (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     port,
    ViBoolean   state,
    ViInt32     averagingFactor,
    ViBoolean   lossCompensation,
    ViInt32     powerMeterAddress
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	if(!IS_E506x)
	{
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
	    CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER3);
		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER4);
		if (state)
		{
			CHECKPARAM( agena_invalidViInt32Range(averagingFactor, 1, 100),
						VI_ERROR_PARAMETER5);
			CHECKPARAM( agena_invalidViBooleanRange(lossCompensation),
						VI_ERROR_PARAMETER6);
			CHECKPARAM( agena_invalidViInt32Range(averagingFactor, 0, 30),
						VI_ERROR_PARAMETER7);
		}
	    p2buffer += sprintf(p2buffer, ":SOUR%ld:POW:PORT%ld:CORR %s", channel, port,
	    					state ? "ON" : "OFF");
	
		if (state)
		{
			p2buffer += sprintf(p2buffer, ";:SOUR%ld:POW:PORT%ld:CORR:COLL:AVER %ld;",
								channel, port, averagingFactor);
			p2buffer += sprintf(p2buffer, ":SOUR%ld:POW:PORT%ld:CORR:COLL:TABL:LOSS %s;",
								channel, port, lossCompensation ? "ON" : "OFF");
			p2buffer += sprintf(p2buffer, ":SYST:COMM:GPIB:PMET:ADDR %ld",
								powerMeterAddress);
		}
	
		p2buffer += sprintf(p2buffer, "\n");

	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Reference Calibration Factor
/* Purpose:  This function sets the reference calibration factor (the 
/*           calibration factor at 50 MHz) for selected power sensor.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confRefCalFactor (
    ViSession   instrumentHandle,
    ViInt32     powerSensor,
    ViReal64    referenceCalibrationFactor
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
	    CHECKPARAM( agena_invalidViInt32Range(powerSensor, 0, 1), VI_ERROR_PARAMETER2);
	    CHECKPARAM( agena_invalidViReal64Range(referenceCalibrationFactor, 1.0, 150.0),
	    			VI_ERROR_PARAMETER3);
    
	    p2buffer += sprintf(p2buffer, ":SOUR:POW:PORT:CORR:COLL:");
    
	    switch (powerSensor)
	    {
	    case AGENA_POWER_CALIBRATION_SENSOR_A:
	    	p2buffer += sprintf(p2buffer, "ASEN");
	    	break;
    	
		case AGENA_POWER_CALIBRATION_SENSOR_B:
			p2buffer += sprintf(p2buffer, "BSEN");
	    	break;
	    }
	
		p2buffer += sprintf(p2buffer, ":RCF %lf\n", referenceCalibrationFactor);
    	
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Calibration Factor Table
/* Purpose:  This function sets the calibration factor table for selected 
/*           power sensor.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confCalibrationFactorTable (
    ViSession   instrumentHandle,
    ViInt32     powerSensor,
    ViInt32     arraySize,
    ViReal64    frequencyArray[],
    ViReal64    calibrationFactorArray[]
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViInt32		buffer_size = 0,
    			i = 0;
    ViChar*		send_buffer = NULL;
    ViChar*     p2buffer;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
    
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
	    CHECKPARAM( agena_invalidViInt32Range( powerSensor, 0, 1), VI_ERROR_PARAMETER2);
	    CHECKPARAM( agena_invalidViInt32Range( arraySize, 0, 100), VI_ERROR_PARAMETER3);

		/* Allocate correct buffer size for send */
		/* 42 - command size                     */
		/* log(arraySize) + 1 - character count of array size                       */
		/* rest - size of arrays values                                             */
		buffer_size = 42 + log(arraySize) + 1 + arraySize * 2 * DOUBLE_BYTE_SIZE;
	    send_buffer = (char*) malloc (buffer_size * sizeof(char));
	    p2buffer = send_buffer;
    
	    p2buffer += sprintf(p2buffer, ":SOUR:POW:PORT:CORR:COLL:TABL:");
	    switch (powerSensor)
	    {
	    case AGENA_POWER_CALIBRATION_SENSOR_A:
	    	p2buffer += sprintf(p2buffer, "ASEN");
	    	break;
    	
		case AGENA_POWER_CALIBRATION_SENSOR_B:
			p2buffer += sprintf(p2buffer, "BSEN");
	    	break;
	    }
	    p2buffer += sprintf(p2buffer, ":DATA %ld", arraySize);
    
	    for (i = 0; i < arraySize; i++)
	    {
	    	p2buffer += sprintf(p2buffer, ",%le,%le", frequencyArray[i],
	    						calibrationFactorArray[i]);
		}
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
	if (send_buffer != NULL)
	{
		free(send_buffer);
		send_buffer = NULL;
	}
	
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Loss Compensation Table
/* Purpose:  This function sets the loss compensation table for selected 
/*           port of selected channel.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confLossCompensationTable (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     port,
    ViInt32     arraySize,
    ViReal64    frequencyArray[],
    ViReal64    lossCompensationArray[]
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViInt32				buffer_size = 0,
    					i = 0;
    ViChar*				send_buffer = NULL;
    ViChar*     		p2buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	if(!IS_E506x)
	{
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER3);
		CHECKPARAM( agena_invalidViInt32Range(arraySize, 1, 100),
					VI_ERROR_PARAMETER4);

	    /* Allocate correct buffer size for send */
		/* 46 - command size                     */
		/* log(arraySize) + 1 - character count of array size                       */
		/* rest - size of arrays values                                             */
		buffer_size = 46 + log(arraySize) + 1 + arraySize * 2 * DOUBLE_BYTE_SIZE;
	    send_buffer = (char*) malloc (buffer_size * sizeof(char));
	    p2buffer = send_buffer;
    
	    p2buffer += sprintf(p2buffer, ":SOUR%ld:POW:PORT%ld:CORR:COLL:TABL:LOSS:DATA %ld",
	    					channel, port, arraySize);
    
	    for (i = 0; i < arraySize; i++)
	    {
	    	p2buffer += sprintf(p2buffer, ",%le,%le", frequencyArray[i],
	    						lossCompensationArray[i]);
		}
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
	if (send_buffer != NULL)
	{
		free(send_buffer);
		send_buffer = NULL;
	}
	
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Scalar-Mixer Calibration
/* Purpose:  This function configure scalar-mixer calibration.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confScalarCal (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     method,
    ViInt32     port1,
    ViInt32     port2
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
	model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
	    CHECKPARAM( agena_invalidViInt32Range(method, 0, 1), VI_ERROR_PARAMETER3);
    
	    switch (method)
	    {
	    case AGENA_SCALAR_MIXER_CALIB_2_PORT:
	    	CHECKPARAM( agena_invalidViInt32Range(port2, 1, instrPtr->numPorts),
	    				VI_ERROR_PARAMETER5);
    	
		case AGENA_SCALAR_MIXER_CALIB_1_PORT:
			CHECKPARAM( agena_invalidViInt32Range(port1, 1, instrPtr->numPorts),
						VI_ERROR_PARAMETER4);
	    	break;
	    }
    
	    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:OFFS:COLL:METH:", channel);
    
	    switch (method)
	    {
	    case AGENA_SCALAR_MIXER_CALIB_1_PORT:
	    	p2buffer += sprintf(p2buffer, "SOLT1 %ld", port1);
	    	break;
    	
		case AGENA_SCALAR_MIXER_CALIB_2_PORT:
			p2buffer += sprintf(p2buffer, "SMIX2 %ld,%ld", port1, port2);
	    	break;
	    }
	
		p2buffer += sprintf(p2buffer, "\n");
    	
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
    }    

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Receiver Calibration
/* Purpose:  This function enables or disables receiver correction.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confRecCal (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     receiver,
    ViBoolean   state
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	if(!IS_E506x)
	{
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(receiver, 1, 4),
					VI_ERROR_PARAMETER3);
		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER4);

	    CHECKERR( viPrintf(instrumentHandle, ":SENS%ld:CORR:REC%ld %s\n", channel,
	    				   receiver, state ? "ON" : "OFF"));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Trigger
/* Purpose:  This function configure trigger.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confTrigger (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   continuousSweep,
    ViBoolean   pointTrigger,
    ViInt32     triggerSource
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViBooleanRange(continuousSweep), VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViBooleanRange(pointTrigger), VI_ERROR_PARAMETER4);
    CHECKPARAM( agena_invalidViInt32Range( triggerSource, 0, 3), VI_ERROR_PARAMETER5);
    
    if(!IS_E506x)
    {
    	p2buffer += sprintf(p2buffer, ":TRIG:POIN %s;", pointTrigger ? "ON" : "OFF");
    }
    p2buffer += sprintf(p2buffer, ":TRIG:SOUR %s;", agena_triggerSource[triggerSource]);
    p2buffer += sprintf(p2buffer, ":INIT%ld:CONT %s\n", channel,
    					continuousSweep ? "ON" : "OFF");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Limit Test
/* Purpose:  This function configure limit test parameters.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confLimitTest (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   limitTest,
    ViBoolean   limitLineDisplay,
    ViBoolean	limitLineClip,
    ViBoolean   limitFailDisplay
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViBooleanRange(limitTest), VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViBooleanRange(limitLineDisplay), VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViBooleanRange(limitFailDisplay), VI_ERROR_PARAMETER5);
	
    p2buffer += sprintf(p2buffer, ":CALC%ld:LIM %s;", channel, limitTest ? "ON" : "OFF");
    p2buffer += sprintf(p2buffer, ":CALC%ld:LIM:DISP %s;", channel,
    					limitLineDisplay ? "ON" : "OFF");
	if(IS_E506x)
	{
	    p2buffer += sprintf(p2buffer, ":CALC%ld:LIM:DISP:CLIP %s;", channel,
	    					limitLineClip ? "ON" : "OFF");
    }					
    p2buffer += sprintf(p2buffer, ":DISP:FSIG %s\n", limitFailDisplay ? "ON" : "OFF");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Limit Test Table
/* Purpose:  This function sets the limit table.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confLimitTestTable (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     number_ofLines,
    ViInt32     type_of_theLine[],
    ViReal64    startPointXValue[],
    ViReal64    endPointXValue[],
    ViReal64    startPointYValue[],
    ViReal64    endPointYValue[]
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViInt32		buffer_size = 0,
    			i = 0;
    ViChar*		send_buffer = NULL;
    ViChar*     p2buffer;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(number_ofLines, 0, 100),
				VI_ERROR_PARAMETER3);

    /* Allocate correct buffer size for send */
	/* 20 - command size                     */
	/* log(number_ofLines) + 1 - character count of array size                  */
	/* rest - size of arrays values                                             */
	buffer_size = 20 + log(number_ofLines) + 1 + number_ofLines * 5 * DOUBLE_BYTE_SIZE;
    send_buffer = (char*) malloc (buffer_size * sizeof(char));
    p2buffer = send_buffer;
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:LIM:DATA %ld", channel, number_ofLines);
    
    for (i = 0; i < number_ofLines; i++)
    {
    	p2buffer += sprintf(p2buffer, ",%ld,%le,%le,%le,%le", type_of_theLine[i],
    						startPointXValue[i], endPointXValue[i],
    						startPointYValue[i], endPointYValue[i]);
	}
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Marker
/* Purpose:  This function configure marker.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confMarker (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     marker,
    ViReal64    stimulus,
	ViBoolean   state
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(marker, 1, 10),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER5);

	if (state) 
    {
    	p2buffer += sprintf(p2buffer, ":CALC%ld:MARK%ld ON;", channel, marker);
	
    	p2buffer += sprintf(p2buffer, ":CALC%ld:MARK%ld:X %lf\n", channel, marker,
    					stimulus);
	}
	else
		p2buffer += sprintf(p2buffer, ":CALC%ld:MARK%ld OFF\n", channel, marker);
		
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Select Active Marker
/* Purpose:  For the active trace of selected channel, sets selected marker 
/*           to the active marker.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confActiveMarker (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     marker
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(marker, 1, 10),
				VI_ERROR_PARAMETER3);

    CHECKERR( viPrintf(instrumentHandle, ":CALC%ld:MARK%ld:ACT\n", channel, marker));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Marker Mode
/* Purpose:  This function configure marker mode.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confMarkerMode (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   coupled,
    ViBoolean   markerMode,
	ViBoolean   referenceMarkerMode
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

	CHECKPARAM( agena_invalidViBooleanRange(coupled), VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViBooleanRange(markerMode), VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViBooleanRange(referenceMarkerMode), VI_ERROR_PARAMETER5);
	
    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK:COUP %s;", channel,
    					coupled ? "ON" : "OFF");
    p2buffer += sprintf(p2buffer, "REF %s;", referenceMarkerMode ? "ON" : "OFF");
    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK:DISC %s\n", channel, 
    					markerMode ? "ON" : "OFF");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Marker Search
/* Purpose:  This function configure marker search.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confMarkerSearch (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     marker,
    ViBoolean   rangeCoupling,
    ViBoolean   tracking,
	ViReal64    peakExcursion,  
    ViInt32     peakPolarity,
    ViReal64    targetValue,
    ViInt32     targetPolarity,
	ViBoolean   partialMarkerState,
    ViReal64    start,
    ViReal64    stop
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(marker, 0, 10),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViBooleanRange(rangeCoupling), VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViBooleanRange(tracking), VI_ERROR_PARAMETER5);
	CHECKPARAM( agena_invalidViReal64Range(peakExcursion, 0.0, 5.0e8), VI_ERROR_PARAMETER6);
    CHECKPARAM( agena_invalidViInt32Range(peakPolarity, 0, 2), VI_ERROR_PARAMETER7);
    CHECKPARAM( agena_invalidViReal64Range(targetValue, -5.0e8, 5.0e8), VI_ERROR_PARAMETER8);
    CHECKPARAM( agena_invalidViInt32Range(targetPolarity, 0, 2), VI_ERROR_INSTR_PARAMETER9);
	CHECKPARAM( agena_invalidViBooleanRange(partialMarkerState), VI_ERROR_INSTR_PARAMETER10);       
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK:FUNC:DOM:COUP %s;", channel,
    					rangeCoupling ? "ON" : "OFF");
    if (marker > 0) 
    {
    	p2buffer += sprintf(p2buffer, ":CALC%ld:MARK%ld:FUNC:", channel, marker);
    }
    else
    {
    	p2buffer += sprintf(p2buffer, ":CALC%ld:MARK:FUNC:MULT:", channel);    
    }
    
    p2buffer += sprintf(p2buffer, "TRAC %s;", tracking ? "ON" : "OFF");
    p2buffer += sprintf(p2buffer, "PPOL %s;", agena_peakPolarity[peakPolarity]);
    p2buffer += sprintf(p2buffer, "PEXC %lf;", peakExcursion);
    p2buffer += sprintf(p2buffer, "TARG %lf;", targetValue);
    p2buffer += sprintf(p2buffer, "TTR %s;", agena_targetPolarity[targetPolarity]);
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK:FUNC:DOM %s", channel,
    					partialMarkerState ? "ON" : "OFF");
    
    if (partialMarkerState)
    {
    	p2buffer += sprintf(p2buffer, ";DOM:STAR %lf;", start);
    	p2buffer += sprintf(p2buffer, "STOP %lf", stop);
    }
    
    p2buffer += sprintf(p2buffer, "\n"); 
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Bandwidth Marker Search
/* Purpose:  This function configure bandwidth marker search.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confBandwidthSearch (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     marker,
    ViBoolean   state,
    ViReal64    bandwidthDefinitionValue
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(marker, 1, 10),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViInt32Range(bandwidthDefinitionValue, -5.0e8, 5.0e8),
				VI_ERROR_PARAMETER5);

    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK:BWID %s;", channel,
    					state ? "ON" : "OFF");
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK%ld:BWID:THR %lf\n", channel,
    					marker, bandwidthDefinitionValue);
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Marker Function
/* Purpose:  This function configure marker function.
/*          
/*			 Notes:
/*			 (1) This function is available only for ENA E5061A/E5062A. 
/*
/*===========================================================================*/
ViStatus _VI_FUNC agena_confMarkerFunction (
	ViSession instrumentHandle,
    ViInt32 channel,
    ViInt32 markerFunction,
    ViBoolean state
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	if(IS_E506x)
	{
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(markerFunction, 0, 2),
					VI_ERROR_PARAMETER3);
		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER4);

	    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK:MATH:", channel);
	    
		switch(markerFunction)
		{
		case AGENA_MARKER_MATH_FLAT:
			p2buffer += sprintf(p2buffer, "FLAT");
    		break;		
		case AGENA_MARKER_MATH_FST:
			p2buffer += sprintf(p2buffer, "FST");
    		break;		
		case AGENA_MARKER_MATH_STAT:
			p2buffer += sprintf(p2buffer, "STAT");
    		break;		
		}
		
		p2buffer += sprintf(p2buffer, "	%s\n", state ? "ON" : "OFF");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;    
}

/*===========================================================================*/
/* Function: Configure Notch Marker Search
/* Purpose:  This function configure notch marker search.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confNotchSearch (
	ViSession instrumentHandle,
    ViInt32 channel, 
    ViInt32 marker,
    ViBoolean state,
    ViReal64 notchDefinitionValue
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	if(IS_E506x)
	{
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(marker, 1, 10),
					VI_ERROR_PARAMETER3);
		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER4);
		CHECKPARAM( agena_invalidViInt32Range(notchDefinitionValue, -5.0e8, 5.0e8),
					VI_ERROR_PARAMETER5);

	    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK:NOTC %s;", channel,
	    					state ? "ON" : "OFF");
    
	    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK%ld:NOTC:THR %lf\n", channel,
	    					marker, notchDefinitionValue);
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;    
}

/*===========================================================================*/
/* Function: Configure Analysis
/* Purpose:  This function configure analysis parameters.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confAnalysis (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     analysisType,
    ViBoolean   rangeCoupling,
    ViReal64    peakExcursion,
    ViInt32     peakPolarity,
    ViReal64    targetValue,
    ViInt32     targetPolarity,
	ViBoolean   partialRangeAnalysisState,
    ViReal64    start,
    ViReal64    stop
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(analysisType, 0, 7), VI_ERROR_PARAMETER3);
    CHECKPARAM( agena_invalidViBooleanRange(rangeCoupling), VI_ERROR_PARAMETER4);
    CHECKPARAM( agena_invalidViReal64Range(targetValue, 0.0, 5.0e8),
    			VI_ERROR_PARAMETER5);
    CHECKPARAM( agena_invalidViInt32Range(peakPolarity, 0, 2), VI_ERROR_PARAMETER6);
    CHECKPARAM( agena_invalidViReal64Range(targetValue, -5.0e8, 5.0e8),
    			VI_ERROR_PARAMETER7);
    CHECKPARAM( agena_invalidViInt32Range(targetPolarity, 0, 2), VI_ERROR_PARAMETER8);
	CHECKPARAM( agena_invalidViBooleanRange(partialRangeAnalysisState), VI_ERROR_INSTR_PARAMETER9);
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:FUNC:TYPE %s;", channel,
    					agena_analysisType[analysisType]);
    p2buffer += sprintf(p2buffer, "PEXC %lf;", peakExcursion);
    p2buffer += sprintf(p2buffer, "PPOL %s;", agena_peakPolarity[peakPolarity]);
    p2buffer += sprintf(p2buffer, "TARG %lf;", targetValue);
    p2buffer += sprintf(p2buffer, "TTR %s;", agena_targetPolarity[targetPolarity]);
    p2buffer += sprintf(p2buffer, "DOM:COUP %s;", rangeCoupling ? "ON" : "OFF");

    p2buffer += sprintf(p2buffer, ":CALC%ld:FUNC:DOM %s",
    						channel, partialRangeAnalysisState ? "ON" : "OFF");
    if (partialRangeAnalysisState)
    {
    	p2buffer += sprintf(p2buffer, ";DOM:STAR %lf;", start);
    	p2buffer += sprintf(p2buffer, "STOP %lf", stop);
    }
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}


/*===========================================================================*/
/* Function: Configure Fixture Simulator
/* Purpose:  This function configure fixture simulator.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confFixSim (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   state,
    ViInt32     balanceDeviceType,
    ViBoolean   displayProperty,
    ViInt32     port1,
    ViInt32     port2,
    ViInt32     port3,
    ViInt32     port4
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32		model_type;
	
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	if (!IS_E506x) 
	{

		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER3);
	
		if (state)
		{
			CHECKPARAM( agena_invalidViInt32Range(balanceDeviceType, 0, 2),
		    			VI_ERROR_PARAMETER4);
			CHECKPARAM( agena_invalidViBooleanRange(displayProperty), VI_ERROR_PARAMETER5);
		
			switch (balanceDeviceType)
	    	{
	    	case AGENA_FIX_SIM_BALANCE_TYPE_BBAL:
	    	case AGENA_FIX_SIM_BALANCE_TYPE_SSBAL:
	    		CHECKPARAM( agena_invalidViInt32Range(port4, 1, instrPtr->numPorts),
		    				VI_ERROR_INSTR_PARAMETER9);
    		
	    	case AGENA_FIX_SIM_BALANCE_TYPE_SBAL:
	    		CHECKPARAM( agena_invalidViInt32Range(port1, 1, instrPtr->numPorts),
		    				VI_ERROR_PARAMETER6);
	    		CHECKPARAM( agena_invalidViInt32Range(port2, 1, instrPtr->numPorts),
		    				VI_ERROR_PARAMETER7);
		    	CHECKPARAM( agena_invalidViInt32Range(port3, 1, instrPtr->numPorts),
		    				VI_ERROR_PARAMETER8);
	    		break;
	    	}
	    }
    
	    p2buffer += sprintf(p2buffer, ":CALC%ld:FSIM:STAT %s", channel,
	    					state ? "ON" : "OFF");
	    if (state)
	    {
	    	p2buffer += sprintf(p2buffer, ";:CALC%ld:FSIM:BAL:DEV %s;", channel,
	    						agena_balanceDevType[balanceDeviceType]);
	    	p2buffer += sprintf(p2buffer, ":CALC%ld:FSIM:BAL:TOP:", channel);
	    	switch (balanceDeviceType)
	    	{
	    	case AGENA_FIX_SIM_BALANCE_TYPE_SBAL:
	    		p2buffer += sprintf(p2buffer, "SBAL %ld,%ld,%ld;", port1, port2, port3);
	    		break;
    		
			case AGENA_FIX_SIM_BALANCE_TYPE_BBAL:
				p2buffer += sprintf(p2buffer, "BBAL %ld,%ld,%ld,%ld;", port1, port2,
									port3, port4);
	    		break;
    		
			case AGENA_FIX_SIM_BALANCE_TYPE_SSBAL:
	    		p2buffer += sprintf(p2buffer, "SSB %ld,%ld,%ld,%ld;", port1, port2,
									port3, port4);
	    		break;
	    	}
	    	p2buffer += sprintf(p2buffer, ":CALC%ld:FSIM:BAL:TOP:PROP:STAT %s",
	    						channel, displayProperty ? "ON" : "OFF");
	    }
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
  	}
  
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Balance Unbalance Conversion
/* Purpose:  This function configure balance unbalance conversion.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confFixSimBalUnbalConv (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     trace,
    ViBoolean   state,
    ViInt32     balanceDeviceType,
    ViInt32     parameter,
	ViInt32     port1,
    ViInt32     port2
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32		model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
    if (!IS_E506x) 
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(trace, 1, instrPtr->numTraces),
					VI_ERROR_PARAMETER3);
	    CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER4);
    
	    if (state)
	    {
		    CHECKPARAM( agena_invalidViInt32Range( balanceDeviceType, 0, 2),
		    			VI_ERROR_PARAMETER5);
		    CHECKPARAM( agena_invalidViInt32Range( parameter, 0, 14),
		    			VI_ERROR_PARAMETER6);
	    }
    
		CHECKPARAM( agena_invalidViInt32Range(port1, 1, instrPtr->numPorts),
		    				VI_ERROR_PARAMETER7);
	    CHECKPARAM( agena_invalidViInt32Range(port2, 1, instrPtr->numPorts),
		    				VI_ERROR_PARAMETER8);
	    				
	    p2buffer += sprintf(p2buffer, ":CALC%ld:FSIM:BAL:PAR%ld:STAT %s", channel,
	    					trace, state ? "ON" : "OFF");
	    if (state)
	    {
	    	p2buffer += sprintf(p2buffer, ";:CALC%ld:FSIM:BAL:DEV %s;", channel,
	    						agena_balanceDevType[balanceDeviceType]);
	    	p2buffer += sprintf(p2buffer, ":CALC%ld:FSIM:BAL:PAR%ld:", channel, trace);
	    	switch (balanceDeviceType)
	    	{
	    	case AGENA_FIX_SIM_BALANCE_TYPE_SBAL:
	    		p2buffer += sprintf(p2buffer, "SBAL");
	    		break;
    		
			case AGENA_FIX_SIM_BALANCE_TYPE_BBAL:
				p2buffer += sprintf(p2buffer, "BBAL");
	    		break;
    		
			case AGENA_FIX_SIM_BALANCE_TYPE_SSBAL:
	    		p2buffer += sprintf(p2buffer, "SSB");
	    		break;
	    	}
    	
    	
	    	if (parameter == AGENA_BALANCE_PARAMETER_IMBALANCE1 &&
	    		balanceDeviceType == AGENA_FIX_SIM_BALANCE_TYPE_SBAL)
	    	{
	    		p2buffer += sprintf(p2buffer, " IMB");
	    	}
	    	else if (parameter == AGENA_BALANCE_PARAMETER_CMRR1 &&
	    		balanceDeviceType == AGENA_FIX_SIM_BALANCE_TYPE_SSBAL)
	    	{
	    		p2buffer += sprintf(p2buffer, " CMRR1");
	    	}
	    	else
	    	{
	    		if (parameter <= AGENA_BALANCE_PARAMETER_SCC) /* SSS,SDS,SSD,SCS,SSC,SDD,SCD,SDC,SCC */
	    			p2buffer += sprintf(p2buffer, " %s%ld%ld", agena_balanceParameter[parameter],port1, port2);
    	
	    		else  /* IMB1,IMB2,IMB3,IMB4,CMRR1,CMRR2 */
	    			p2buffer += sprintf(p2buffer, " %s", agena_balanceParameter[parameter]);
	    	}
	    }
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
    }
  
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Matching Circuit Embedding
/* Purpose:  This function configure matching circuit embedding.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confFixSimMatchingCircuitEmbedding (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     port,
    ViBoolean   state,
    ViInt32     circuitMode,
    ViInt32     circuitType,
    ViReal64    c,
    ViReal64    g,
    ViReal64    l,
    ViReal64    r,
    ViString    fileName
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32		model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
    if(!IS_E506x) 
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER4);
	    CHECKPARAM( agena_invalidViInt32Range(circuitMode, 0, 1), VI_ERROR_PARAMETER5);
    
	    if (state)
	    {
	    	CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
						VI_ERROR_PARAMETER3);
		    CHECKPARAM( agena_invalidViInt32Range(circuitType, 0, 6), VI_ERROR_PARAMETER6);
		    CHECKPARAM( agena_invalidViReal64Range(c, -1.0e18, 1.0e18), VI_ERROR_PARAMETER7);
		    CHECKPARAM( agena_invalidViReal64Range(g, -1.0e18, 1.0e18), VI_ERROR_PARAMETER8);
		    CHECKPARAM( agena_invalidViReal64Range(l, -1.0e18, 1.0e18),
		    			VI_ERROR_INSTR_PARAMETER9);
		    CHECKPARAM( agena_invalidViReal64Range(r, -1.0e18, 1.0e18),
		    			VI_ERROR_INSTR_PARAMETER10);
		}
    
	    p2buffer += sprintf(p2buffer, ":CALC%ld:FSIM:", channel);
	    switch (circuitMode)
		{
		case AGENA_CIRCUIT_MODE_NORMAL:
			p2buffer += sprintf(p2buffer, "SEND:PMC");
			break;
		
		case AGENA_CIRCUIT_MODE_DIFFERENTIAL:
			p2buffer += sprintf(p2buffer, "BAL:DMC");
			break;
		}
		p2buffer += sprintf(p2buffer, ":STAT %s", state ? "ON" : "OFF");
    	
	    if (state)
	    {
	    	p2buffer += sprintf(p2buffer, ";:CALC%ld:FSIM:", channel);
	    	switch (circuitMode)
	    	{
	    	case AGENA_CIRCUIT_MODE_NORMAL:
	    		p2buffer += sprintf(p2buffer, "SEND:PMC:PORT%ld", port);
	    		break;
    		
	    	case AGENA_CIRCUIT_MODE_DIFFERENTIAL:
	    		p2buffer += sprintf(p2buffer, "BAL:DMC:BPOR%ld", port);
	    		break;
	    	}
    	
	    	p2buffer += sprintf(p2buffer, ":TYPE %s;", agena_circuitType[circuitType]);
    	
	    	p2buffer += sprintf(p2buffer, "PAR:C %lf;", c);
	    	p2buffer += sprintf(p2buffer, "G %lf;", g);
	    	p2buffer += sprintf(p2buffer, "L %lf;", l);
	    	p2buffer += sprintf(p2buffer, "R %lf", r);
	    	if (circuitType == AGENA_CIRCUIT_TYPE_USER)
	    	{
	    		p2buffer += sprintf(p2buffer, ";:CALC%ld:FSIM:", channel);
		    	switch (circuitMode)
		    	{
		    	case AGENA_CIRCUIT_MODE_NORMAL:
		    		p2buffer += sprintf(p2buffer, "SEND:PMC:PORT%ld", port);
		    		break;
    		
		    	case AGENA_CIRCUIT_MODE_DIFFERENTIAL:
		    		p2buffer += sprintf(p2buffer, "BAL:DMC:BPOR%ld", port);
		    		break;
		    	}
    	
		    	p2buffer += sprintf(p2buffer, ":USER:FIL \"%s\"", fileName);
	    	}
	    }
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
    }
  
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Port Impedance Conversion
/* Purpose:  This function configure port impedance conversion.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confFixSimPortImpedanceConversion (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     port,
    ViBoolean   state,
	ViInt32     circuitMode,
    ViReal64    z0
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32		model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);

		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER4);  
		CHECKPARAM( agena_invalidViInt32Range( circuitMode, 0, 2), VI_ERROR_PARAMETER5);

		if (state)
		{
			CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
						VI_ERROR_PARAMETER3);
			CHECKPARAM( agena_invalidViReal64Range(z0, 1.0e-3, 1.0e7),
						VI_ERROR_PARAMETER6);
		}
    
	    p2buffer += sprintf(p2buffer, ":CALC%ld:FSIM:", channel);
	    switch (circuitMode)
		{
		case AGENA_CIRCUIT_MODE_NORMAL:
			p2buffer += sprintf(p2buffer, "SEND:ZCON");
			break;
		
		case AGENA_CIRCUIT_MODE_DIFFERENTIAL:
			p2buffer += sprintf(p2buffer, "BAL:DZC");
			break;
	
		case AGENA_CIRCUIT_MODE_COMMON:
			p2buffer += sprintf(p2buffer, "BAL:CZC");
			break;
		}
		p2buffer += sprintf(p2buffer, ":STAT %s", state ? "ON" : "OFF");
    	
	    if (state)
	    {
	    	p2buffer += sprintf(p2buffer, ";:CALC%ld:FSIM:", channel);
	    	switch (circuitMode)
	    	{
	    	case AGENA_CIRCUIT_MODE_NORMAL:
	    		p2buffer += sprintf(p2buffer, "SEND:ZCON:PORT%ld", port);
	    		break;
    		
	    	case AGENA_CIRCUIT_MODE_DIFFERENTIAL:
	    		p2buffer += sprintf(p2buffer, "BAL:DZC:BPOR%ld", port);
	    		break;

	    	case AGENA_CIRCUIT_MODE_COMMON:
	    		p2buffer += sprintf(p2buffer, "BAL:CZC:BPOR%ld", port);
	    		break;
	    	}
    	
	    	p2buffer += sprintf(p2buffer, ":Z0 %lf", z0);
	    }
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
    }
  
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Network De-embedding
/* Purpose:  This function configure network de-embedding.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confFixSimNetworkDeembedding (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     port,
    ViBoolean   state,
    ViInt32     circuitType,
    ViString    fileName
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32		model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER4);
	
		if (state)
		{
			CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
	    				VI_ERROR_PARAMETER3);
	    	CHECKPARAM( agena_invalidViInt32Range(circuitType, 0, 1),
	    				VI_ERROR_PARAMETER5);
	    }
    
	    p2buffer += sprintf(p2buffer, ":CALC%ld:FSIM:SEND:DEEM:STAT %s", channel,
	    					state ? "ON" : "OFF");
	    if (state)
	    {
	    	p2buffer += sprintf(p2buffer, ";:CALC%ld:FSIM:SEND:DEEM:PORT%ld %s", channel,
	    						port, agena_networkDeembedding[circuitType]);
    	
	    	if (circuitType == AGENA_NETWORK_DEEMBEDDING_USER)
	    	{
	    		p2buffer += sprintf(p2buffer, ";:CALC%ld:FSIM:SEND:DEEM:PORT%ld:USER:FIL \"%s\"",
	    							channel, port, fileName);
			}
	    }
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
    }
  
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure 4-port Network (De-)Embedding
/* Purpose:  This function configure 4-port network embedding/deembedding.
/*           
/*           Notes:
/*           This function is available with the firmware version 3.50 or 
/*           greater.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confFixSim4portNetworkDeEmbedding (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   state,
    ViInt32     topologyType,
    ViInt32     port1,
    ViInt32     port2,
    ViInt32     port3,
    ViInt32     port4,
    ViInt32     network,
    ViInt32     networkType,
    ViString    networkFile
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32		model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER3);
    
	    if (state)
	    {
		    CHECKPARAM( agena_invalidViInt32Range(topologyType, 0, 2),
		    			VI_ERROR_PARAMETER4);
	    
		    switch (topologyType)
	    	{
	    	case AGENA_TOPOLOGY_TYPE_C:
	    		CHECKPARAM( agena_invalidViInt32Range(port4, 1, instrPtr->numPorts),
		    				VI_ERROR_PARAMETER8);
    	
	    	case AGENA_TOPOLOGY_TYPE_B:
	    		CHECKPARAM( agena_invalidViInt32Range(port3, 1, instrPtr->numPorts),
		    				VI_ERROR_PARAMETER7);
    	
	    	case AGENA_TOPOLOGY_TYPE_A:
	    		CHECKPARAM( agena_invalidViInt32Range(port1, 1, instrPtr->numPorts),
		    				VI_ERROR_PARAMETER5);
				CHECKPARAM( agena_invalidViInt32Range(port2, 1, instrPtr->numPorts),
		    				VI_ERROR_PARAMETER6);
	    		break;
	    	}
	    
		    CHECKPARAM( agena_invalidViInt32Range(network, 1, 2),
		    			VI_ERROR_INSTR_PARAMETER9);
		    CHECKPARAM( agena_invalidViInt32Range(networkType, 0, 2),
		    			VI_ERROR_INSTR_PARAMETER10);
		}
    
	    p2buffer += sprintf(p2buffer, ":CALC%ld:FSIM:EMB:STAT %s", channel,
	    					state ? "ON" : "OFF");
	    if (state)
	    {
	    	p2buffer += sprintf(p2buffer, ";:CALC%ld:FSIM:EMB:TYPE %s;", channel,
	    						agena_topologyType[topologyType]);
	    	p2buffer += sprintf(p2buffer, ":CALC%ld:FSIM:EMB:TOP:%s:PORT %ld,%ld",
	    						channel, agena_topologyType[topologyType],
	    						port1, port2);
    	
	    	switch (topologyType)
	    	{
	    	case AGENA_TOPOLOGY_TYPE_A:
	    		break;
	    	case AGENA_TOPOLOGY_TYPE_B:
	    		p2buffer += sprintf(p2buffer, ",%ld", port3);
	    		break;
	    	case AGENA_TOPOLOGY_TYPE_C:
	    		p2buffer += sprintf(p2buffer, ",%ld,%ld", port3, port4);
	    		break;
	    	}
    	
	    	if (networkType != AGENA_NETWORK_TYPE_NONE)
	    	{
		    	p2buffer += sprintf(p2buffer, ";:CALC%ld:FSIM:EMB:NETW%ld:FIL \"%s\"",
		    						channel, network, networkFile);
	    	}
    	
	    	p2buffer += sprintf(p2buffer, ";:CALC%ld:FSIM:EMB:NETW%ld:TYPE %s",
	    						channel, network, agena_networkType[networkType]);
	    }
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
    }
  
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Time Domain Transform
/* Purpose:  This function configure time domain transformation.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confTDomTransform (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   state,
    ViInt32     transformationType,
    ViInt32     stimulusType,
    ViInt32     beta,
    ViReal64    impluseWidth,
    ViReal64    riseTime_ofStepSignal
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER3);
    
    if (state)
    {
	    CHECKPARAM( agena_invalidViInt32Range(transformationType, 0, 1),
	    			VI_ERROR_PARAMETER4);
	    CHECKPARAM( agena_invalidViInt32Range(stimulusType, 0, 1),
	    			VI_ERROR_PARAMETER5);
	    CHECKPARAM( agena_invalidViInt32Range(beta, 0, 13),
	    			VI_ERROR_PARAMETER6);
	}
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:TRAN:TIME:STAT %s", channel,
    					state ? "ON" : "OFF");
    if (state)
    {
    	p2buffer += sprintf(p2buffer, ";:CALC%ld:TRAN:TIME %s;", channel,
    						agena_transformationType[transformationType]);
    	p2buffer += sprintf(p2buffer, ":CALC%ld:TRAN:TIME:STIM %s;KBES %ld;",
    						channel, agena_stimulusType[stimulusType], beta);
    	p2buffer += sprintf(p2buffer, ":CALC%ld:TRAN:TIME:", channel);
    	
    	switch (stimulusType)
    	{
    	case AGENA_TRANSFORM_STIMULUS_TYPE_IMPULSE:
    		p2buffer += sprintf(p2buffer, "IMP:WIDT %lf", impluseWidth);
    		break;
    	
    	case AGENA_TRANSFORM_STIMULUS_TYPE_STEP:
    		p2buffer += sprintf(p2buffer, "STEP:RTIM %lf", riseTime_ofStepSignal);
    		break;
    	}
    }
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Time Domain Display Range
/* Purpose:  This function configure time domain display range.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confTDomDisplayRange (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     settingType,
    ViReal64    start,
    ViReal64    stop,
	ViReal64    center,
    ViReal64    span
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(settingType, 0, 1), VI_ERROR_PARAMETER3);
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:TRAN:TIME:", channel);
	
	switch (settingType)
	{
	case AGENA_TIME_DOMAIN_SET_TYPE_CENTER_SPAN:
		p2buffer += sprintf(p2buffer, "CENT %lf;SPAN %lf\n", center, span);
		break;
	
	case AGENA_TIME_DOMAIN_SET_TYPE_START_STOP:
		p2buffer += sprintf(p2buffer, "STAR %lf;STOP %lf\n", start, stop);
		break;
	}
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Time Domain Gating
/* Purpose:  This function configure time domain gating.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confTDomGating (
	ViSession instrumentHandle, ViInt32 channel,
	ViBoolean state, ViInt32 gateType,
	ViInt32 gateShape, ViInt32 settingType,
	ViReal64 start, ViReal64 stop,
	ViReal64 center, ViReal64 span
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32		model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER3);
	    if (state)
	    {
		    CHECKPARAM( agena_invalidViInt32Range(gateType, 0, 1), VI_ERROR_PARAMETER4);
		    CHECKPARAM( agena_invalidViInt32Range(gateShape, 0, 3), VI_ERROR_PARAMETER5);
		    CHECKPARAM( agena_invalidViInt32Range(settingType, 0, 1), VI_ERROR_PARAMETER6);
		}
    
	    p2buffer += sprintf(p2buffer, ":CALC%ld:FILT:TIME:STAT %s", channel,
	    					state ? "ON" : "OFF");
		if (state)
		{
			p2buffer += sprintf(p2buffer, ";:CALC%ld:FILT:TIME %s;", channel,
	    						agena_gateType[gateType]);
			p2buffer += sprintf(p2buffer, ":CALC%ld:FILT:TIME:SHAP %s;", channel,
	    						agena_shapeType[gateShape]);

			switch (settingType)
			{
			case AGENA_TIME_DOMAIN_SET_TYPE_CENTER_SPAN:
				p2buffer += sprintf(p2buffer, "CENT %lf;SPAN %lf", center, span);
				break;
	
			case AGENA_TIME_DOMAIN_SET_TYPE_START_STOP:
				p2buffer += sprintf(p2buffer, "STAR %lf;STOP %lf", start, stop);
				break;
			}
		}
		p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
    }
  
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Parameter Conversion
/* Purpose:  This function configure parameter conversion.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confParameterConversion (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean   state,
    ViInt32     parameter
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER3);
	if (state)CHECKPARAM( agena_invalidViInt32Range(parameter, 0, 7), VI_ERROR_PARAMETER4);
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:CONV %s", channel,
    					state ? "ON" : "OFF");
	if (state)
	{
		p2buffer += sprintf(p2buffer, ";:CALC%ld:CONV:FUNC %s", channel,
    						agena_parameter[parameter]);
	}
	p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Handler IO Control
/* Purpose:  This function configure handler IO control settings.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confHandlerIOControl (
    ViSession   instrumentHandle,
    ViInt32     portCDirection,
    ViInt32     portDDirection,
	ViInt32     OUTPUT1OUTPUT2Setting,  
    ViBoolean   INDEXSignalOutput,
    ViBoolean   READYFORTRIGGERSignalOutput,
    ViInt32     output
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;

    CHECKPARAM( agena_invalidViInt32Range(portCDirection, 0, 1), VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(portDDirection, 0, 1), VI_ERROR_PARAMETER3);
        
	CHECKPARAM( agena_invalidViInt32Range(OUTPUT1OUTPUT2Setting, 0, 1), VI_ERROR_PARAMETER4); 
    CHECKPARAM( agena_invalidViBooleanRange(INDEXSignalOutput), VI_ERROR_PARAMETER5);
    CHECKPARAM( agena_invalidViBooleanRange(READYFORTRIGGERSignalOutput), VI_ERROR_PARAMETER6);
    CHECKPARAM( agena_invalidViInt32Range(output, 1, 2), VI_ERROR_PARAMETER7);
    
    p2buffer += sprintf(p2buffer, ":CONT:HAND:C:MODE %s;", agena_portDirection[portCDirection]);
	p2buffer += sprintf(p2buffer, ":CONT:HAND:D:MODE %s;", agena_portDirection[portDDirection]);
	p2buffer += sprintf(p2buffer, ":CONT:HAND:OUTP%ld %ld;", output,
						OUTPUT1OUTPUT2Setting);
	p2buffer += sprintf(p2buffer, ":CONT:HAND:IND:STAT %s;",
						INDEXSignalOutput ? "ON" : "OFF");
	p2buffer += sprintf(p2buffer, ":CONT:HAND:RTR:STAT %s",
						READYFORTRIGGERSignalOutput ? "ON" : "OFF");
	p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Controlling E5091A
/* Purpose:  This function configure controlling of E5091A.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confE5091A (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     multiplexer,
    ViBoolean   state,
    ViInt32     port1,
    ViInt32     port2,
    ViInt32     port3,
    ViInt32     port4,
	ViBoolean   propertyDisplay, 
    ViInt32     controlLines
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
	model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
	    CHECKPARAM( agena_invalidViInt32Range(multiplexer, 1, 2),
					VI_ERROR_PARAMETER3);
	    CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER4);
    
	    if (state)
	    {
		    CHECKPARAM( agena_invalidViInt32Range(port1, 0, 1), VI_ERROR_PARAMETER5);
		    CHECKPARAM( agena_invalidViInt32Range(port2, 0, 1), VI_ERROR_PARAMETER6);
		    CHECKPARAM( agena_invalidViInt32Range(port3, 0, 2), VI_ERROR_PARAMETER7);
		    CHECKPARAM( agena_invalidViInt32Range(port4, 0, 2), VI_ERROR_PARAMETER8);
			CHECKPARAM( agena_invalidViBooleanRange(propertyDisplay), VI_ERROR_INSTR_PARAMETER9); 
		    CHECKPARAM( agena_invalidViInt32Range(controlLines, 0, 255), VI_ERROR_INSTR_PARAMETER10);
		}
    
	    p2buffer += sprintf(p2buffer, ":SENS:MULT%ld:STAT %s", multiplexer,
	    					state ? "ON" : "OFF");
		if (state)
		{
			p2buffer += sprintf(p2buffer, ";:SENS:MULT%ld:DISP %s;", multiplexer,
								propertyDisplay ? "ON" : "OFF");
			p2buffer += sprintf(p2buffer, ":SENS%ld:MULT%ld:TSET9:PORT1 %s;", channel,
								multiplexer, agena_port1E5091A[port1]);
			p2buffer += sprintf(p2buffer, "PORT2 %s;", agena_port2E5091A[port2]);
			p2buffer += sprintf(p2buffer, "PORT3 %s;", agena_port3E5091A[port3]);
			p2buffer += sprintf(p2buffer, "PORT4 %s;", agena_port4E5091A[port4]);
			p2buffer += sprintf(p2buffer, ":SENS%ld:MULT%ld:TSET9:OUTP %ld",
								channel, multiplexer, controlLines);
		}
		p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
    }
  
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Date And Time
/* Purpose:  This function setup date and time.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confDateTime (
    ViSession   instrumentHandle,
    ViBoolean   displayClock,
    ViInt32     year,
    ViInt32     month,
    ViInt32     day,
    ViInt32     hour,
    ViInt32     minute,
    ViInt32     second
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;

	CHECKPARAM( agena_invalidViBooleanRange(displayClock), VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(year, 1980, 2099), VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViInt32Range(month, 1, 12), VI_ERROR_PARAMETER4);
	CHECKPARAM( agena_invalidViInt32Range(day, 1, 31), VI_ERROR_PARAMETER5);
	CHECKPARAM( agena_invalidViInt32Range(hour, 0, 23), VI_ERROR_PARAMETER6);
	CHECKPARAM( agena_invalidViInt32Range(minute, 0, 59), VI_ERROR_PARAMETER7);
	CHECKPARAM( agena_invalidViInt32Range(second, 0, 59), VI_ERROR_PARAMETER8);

    p2buffer += sprintf(p2buffer, ":DISP:CLOC %s",
    					displayClock ? "ON" : "OFF");
    if (displayClock)
    {
	    p2buffer += sprintf(p2buffer, ";:SYST:TIME %ld,%ld,%ld;",
	    					hour, minute, second);
		p2buffer += sprintf(p2buffer, ":SYST:DATE %ld,%ld,%ld",
	    					year, month, day);
	}
	p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure External Signal Generator
/* Purpose:  This function configure external signal generator.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confExternalSigGen (
    ViSession   instrumentHandle,
    ViInt32     GPIBAddress,
    ViInt32     type,
    ViString    frequencySettingCommand,
    ViString    powerLevelSettingCommand,
    ViString    presetCommand,
    ViString    RFPowerONCommand,
    ViReal64    waitingTime
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(GPIBAddress, 0, 30), VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(type, 1, 3), VI_ERROR_PARAMETER3);
		CHECKPARAM( agena_invalidViReal64Range(waitingTime, 0.0, 1.0), VI_ERROR_PARAMETER8);
	
	    p2buffer += sprintf(p2buffer, ":SYST:COMM:GPIB:SGEN:ADDR %ld;", GPIBAddress);
	    p2buffer += sprintf(p2buffer, "TYPE %ld;", type);
	    p2buffer += sprintf(p2buffer, "DWEL %lf;", waitingTime);
	    p2buffer += sprintf(p2buffer, "CCOM:FREQ \"%s\";", frequencySettingCommand);
	    p2buffer += sprintf(p2buffer, "POW \"%s\";", powerLevelSettingCommand);
	    p2buffer += sprintf(p2buffer, "PRES \"%s\";", presetCommand);
	    p2buffer += sprintf(p2buffer, "RFON \"%s\"", RFPowerONCommand);
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Initial Source Port
/* Purpose:  This function configure initial source port.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confInitialSourcePort (
    ViSession   instrumentHandle,
    ViBoolean   state,
    ViInt32     port
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViBooleanRange(state), VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts), VI_ERROR_PARAMETER3);
	
	    p2buffer += sprintf(p2buffer, ":SYST:ISPC %s", state ? "ON" : "OFF");
	    if (state)
	    {
	    	p2buffer += sprintf(p2buffer, ";:SYST:ISPC:PORT %ld", port);
	    }
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Configure Correction and Temperature
/* Purpose:  This function configure correction and temperature.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_confCorrTemp (
    ViSession   instrumentHandle,
    ViBoolean   systemErrorCorrection,
    ViBoolean   highTemperatureMode
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViBooleanRange(systemErrorCorrection), VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViBooleanRange(highTemperatureMode), VI_ERROR_PARAMETER3);
	
	    p2buffer += sprintf(p2buffer, ":SYST:CORR %s;", systemErrorCorrection ? "ON" : "OFF");
	    p2buffer += sprintf(p2buffer, ":SYST:TEMP:HIGH %s\n", highTemperatureMode ? "ON" : "OFF");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Clear Averaging Data
/* Purpose:  This function clears the measurement data used for averaging of 
/*           selected channel. Measurement data before the execution of this 
/*           command is not used for averaging.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actClearAvgData (
    ViSession   instrumentHandle,
    ViInt32     channel
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    CHECKERR( viPrintf(instrumentHandle, ":SENS%ld:AVER:CLE\n", channel));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Copy Measurement Data To MEM
/* Purpose:  For the active trace of selected channel, copies the 
/*           measurement data at the execution of the command to the memory 
/*           trace.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actCopyMeasDataToMem (
    ViSession   instrumentHandle,
    ViInt32     channel
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    CHECKERR( viPrintf(instrumentHandle, ":CALC%ld:MATH:MEM\n", channel));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Autoscale Y Axis
/* Purpose:  For selected trace of selected channel, executes the auto scale 
/*           (function to automatically adjust the value of the reference 
/*           graticule line and the scale per division to display the trace 
/*           appropriately).
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actAutoscaleYAxis (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     trace
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(trace, 1, instrPtr->numTraces),
				VI_ERROR_PARAMETER3);

    CHECKERR( viPrintf(instrumentHandle, ":DISP:WIND%ld:TRAC%ld:Y:AUTO\n",
    				   channel, trace));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Reset Calibration Kit
/* Purpose:  This function resets the calibration kit selected for selected 
/*           channel to the factory setting state.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actResetCalKit (
    ViSession   instrumentHandle,
    ViInt32     channel
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    CHECKERR( viPrintf(instrumentHandle, ":SENS%ld:CORR:COLL:CKIT:RES\n", channel));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Measure Calibration Data
/* Purpose:  For selected channel, measures the calibration data of the 
/*           open, short, load, thru standard or isolation of the specified 
/*           ports.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actMeasureCalData (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     standard,
    ViInt32     port1_Response,
    ViInt32     port2_Stimulus
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(standard, 0, 4), VI_ERROR_PARAMETER3);
    CHECKPARAM( agena_invalidViInt32Range(port1_Response, 1, instrPtr->numPorts),
    			VI_ERROR_PARAMETER4);
    CHECKPARAM( agena_invalidViInt32Range(port2_Stimulus, 1, instrPtr->numPorts),
    			VI_ERROR_PARAMETER5);
    
    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:COLL:", channel);
    
    switch (standard)
    {
    case AGENA_MEASURE_CAL_DATA_STANDARD_OPEN:
    	p2buffer += sprintf(p2buffer, "OPEN %ld", port1_Response);
    	break;
    
    case AGENA_MEASURE_CAL_DATA_STANDARD_SHORT:
    	p2buffer += sprintf(p2buffer, "SHOR %ld", port1_Response);
    	break;

    case AGENA_MEASURE_CAL_DATA_STANDARD_LOAD:
    	p2buffer += sprintf(p2buffer, "LOAD %ld", port1_Response);
    	break;

	case AGENA_MEASURE_CAL_DATA_STANDARD_THRU:
    	p2buffer += sprintf(p2buffer, "THRU %ld,%ld", port1_Response,
    						port2_Stimulus);
    	break;
    
    case AGENA_MEASURE_CAL_DATA_STANDARD_ISOLATION:
    	p2buffer += sprintf(p2buffer, "ISOL %ld,%ld", port1_Response,
    						port2_Stimulus);
    	break;
    }
    
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Calculate Calibration Coefficients
/* Purpose:  From the measured calibration data, calculates the calibration 
/*           coefficients depending on the selected calibration type.
/*           Calculating the calibration coefficients clears all calibration 
/*           data whether or not used for the calculation and also clears the 
/*           calibration type selections.
/*           
/*           Notes:
/*           If you execute this function before all necessary calibration 
/*           data for calculating the calibration coefficients is measured, 
/*           an error occurs and the function is ignored.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actCalculateCalCoef (
    ViSession   instrumentHandle,
    ViInt32     channel
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    CHECKERR( viPrintf(instrumentHandle, ":SENS%ld:CORR:COLL:SAVE\n", channel));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Clear Calibration Data
/* Purpose:  Clears the error coefficient or the measurement value of the 
/*           Mechanical Cal kit for calibration when the frequency offset 
/*           mode is disabled for selected channel.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actClearCalData (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     clear
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(clear, 0, 1), VI_ERROR_PARAMETER3);
    
    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:", channel);
    
    switch (clear)
    {
    case AGENA_CALIBRATION_DATA_CLEAR_COEFFICIENT:
    	break;
    
    case AGENA_CALIBRATION_DATA_CLEAR_DATA:
    	p2buffer += sprintf(p2buffer, "COLL:");
    	break;
	}
    
    p2buffer += sprintf(p2buffer, "CLE\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Execute ECal
/* Purpose:  Executes 1-port, full 2-port, full 3-port, full 4-port, 
/*           response  calibration or the confidence check of the specified 
/*           ports of selected channel using the ECal (Electrical 
/*           Calibration) module.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actExecuteECal (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     calibration,
    ViInt32     port1,
    ViInt32     port2,
    ViInt32     port3
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(calibration, 0, 5), VI_ERROR_PARAMETER3);
	model_type = instrPtr->modelType;
	if(IS_E506x)
	{
    	CHECKPARAM( (calibration == AGENA_CALIBRATION_EXECUTE_3_PORT ||
    				 calibration == AGENA_CALIBRATION_EXECUTE_4_PORT ||
    				 calibration == AGENA_CALIBRATION_EXECUTE_CONF_CHECK), VI_ERROR_PARAMETER3);	
	}
	else
	{
    	CHECKPARAM( (calibration == AGENA_CALIBRATION_EXECUTE_EN_RESPONSE), VI_ERROR_PARAMETER3);	
	}
	
    switch (calibration)
    {
    case AGENA_CALIBRATION_EXECUTE_3_PORT:
    	CHECKPARAM( agena_invalidViInt32Range(port3, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER6);
    
    case AGENA_CALIBRATION_EXECUTE_2_PORT:
    case AGENA_CALIBRATION_EXECUTE_RESPONSE:
    case AGENA_CALIBRATION_EXECUTE_EN_RESPONSE:
    	CHECKPARAM( agena_invalidViInt32Range(port2, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER5);
	
	case AGENA_CALIBRATION_EXECUTE_1_PORT:
    	CHECKPARAM( agena_invalidViInt32Range(port1, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER4);
    	break;
	
	case AGENA_CALIBRATION_EXECUTE_4_PORT:
	case AGENA_CALIBRATION_EXECUTE_CONF_CHECK:
    	break;
	}

    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:COLL:ECAL:", channel);
    
    switch (calibration)
    {
    case AGENA_CALIBRATION_EXECUTE_1_PORT:
    	p2buffer += sprintf(p2buffer, "SOLT1 %ld", port1);
    	break;
    
    case AGENA_CALIBRATION_EXECUTE_2_PORT:
    	p2buffer += sprintf(p2buffer, "SOLT2 %ld,%ld", port1, port2);
    	break;
	
	case AGENA_CALIBRATION_EXECUTE_3_PORT:
    	p2buffer += sprintf(p2buffer, "SOLT3 %ld,%ld,%ld", port1, port2, port3);
    	break;
	
	case AGENA_CALIBRATION_EXECUTE_4_PORT:
    	p2buffer += sprintf(p2buffer, "SOLT4 1,2,3,4");
    	break;
	
	case AGENA_CALIBRATION_EXECUTE_RESPONSE:
    	p2buffer += sprintf(p2buffer, "THRU %ld,%ld", port1, port2);
    	break;
	
	case AGENA_CALIBRATION_EXECUTE_CONF_CHECK:
    	p2buffer += sprintf(p2buffer, "CCH");
    	break;
    case AGENA_CALIBRATION_EXECUTE_EN_RESPONSE:
    	p2buffer += sprintf(p2buffer, "ERES %ld,%ld", port1, port2);
    	break;
	}
    
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Measure Power Calibration Data
/* Purpose:  For selected port, measure the power calibration data using the 
/*           specified power sensor. When the measurement is complete 
/*           successfully, the power level error correction is automatically
/*           enabled.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actMeasurePowerCalData (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     port,
    ViInt32     sensor
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER3);
		CHECKPARAM( agena_invalidViInt32Range(sensor, 0, 1), VI_ERROR_PARAMETER4);

	    CHECKERR( viPrintf(instrumentHandle, ":SOUR%ld:POWer:PORT%ld:CORR:COLL %s\n",
	    				   channel, port, agena_sensorType[sensor]));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Calculate Scalar-Mixer Calibration Coefficients
/* Purpose:  From the measured calibration data, calculates the error 
/*           coefficient for the calibration type selected with 
/*           agena_confScalarCal function.
/*           
/*           After the error coefficient is calculated, the measured data 
/*           and the calibration type setting are cleared.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actCalculateScalarCalCoef (
    ViSession   instrumentHandle,
    ViInt32     channel
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

	model_type = instrPtr->modelType;
	if(!IS_E506x)
	{
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);

	    CHECKERR( viPrintf(instrumentHandle, ":SENS%ld:CORR:OFFS:COLL:SAVE\n", channel));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Clear Scalar-Mixer Calibration Data
/* Purpose:  Clears the error coefficient or the measurement value of the 
/*           Mechanical Cal kit for calibration when the frequency offset 
/*           mode is enabled for selected channel. This command also
/*           clears the measurement value of the power meter.
/*           
/*           To toggle the frequency offset mode, use agena_confFreqOffset 
/*           function.
/*           
/*           Notes:
/*           (1) Settings that have been temporarily changed due to 
/*           measurement for each standard (number of traces, measurement 
/*           parameter, and so on) return to their original values.
/*           
/*           (2) This function does not clear the error coefficient when the 
/*           frequency offset mode is disabled.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actClearScalarCalData (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     clear
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
	    CHECKPARAM( agena_invalidViInt32Range(clear, 0, 1), VI_ERROR_PARAMETER3);
    
	    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:OFFS:", channel);
    
	    switch (clear)
	    {
	    case AGENA_CALIBRATION_DATA_CLEAR_COEFFICIENT:
	    	break;
    
	    case AGENA_CALIBRATION_DATA_CLEAR_DATA:
	    	p2buffer += sprintf(p2buffer, "COLL:");
	    	break;
		}
    
	    p2buffer += sprintf(p2buffer, "CLE\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Measure Scalar-Mixed Calibration Data
/* Purpose:  For selected channel, measures the calibration data of the 
/*           open, short, load, thru or power calibration standard of the 
/*           specified port when the frequency offset mode is enabled.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actMeasureScalarCalData (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     standard,
    ViInt32     sensor,
    ViInt32     port1_Measurement,
    ViInt32     port2_SpecifiedFreq
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*    			p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
	    CHECKPARAM( agena_invalidViInt32Range(standard, 0, 4), VI_ERROR_PARAMETER3);
	    CHECKPARAM( agena_invalidViInt32Range(sensor, 0, 1), VI_ERROR_PARAMETER4);
	    CHECKPARAM( agena_invalidViInt32Range(port1_Measurement, 1, instrPtr->numPorts),
	    			VI_ERROR_PARAMETER5);
	    CHECKPARAM( agena_invalidViInt32Range(port2_SpecifiedFreq, 1, instrPtr->numPorts),
	    			VI_ERROR_PARAMETER6);
    
	    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:OFFS:COLL:", channel);
    
	    switch (standard)
	    {
	    case AGENA_MEASURE_CAL_SCALAR_STANDARD_OPEN:
	    	p2buffer += sprintf(p2buffer, "OPEN %ld,%ld", port1_Measurement,
	    						port2_SpecifiedFreq);
	    	break;
    
	    case AGENA_MEASURE_CAL_SCALAR_STANDARD_SHORT:
	    	p2buffer += sprintf(p2buffer, "SHOR %ld,%ld", port1_Measurement,
	    						port2_SpecifiedFreq);
	    	break;
	
		case AGENA_MEASURE_CAL_SCALAR_STANDARD_LOAD:
	    	p2buffer += sprintf(p2buffer, "LOAD %ld,%ld", port1_Measurement,
	    						port2_SpecifiedFreq);
	    	break;
	
		case AGENA_MEASURE_CAL_SCALAR_STANDARD_THRU:
	    	p2buffer += sprintf(p2buffer, "THRU %ld,%ld", port1_Measurement,
	    						port2_SpecifiedFreq);
	    	break;
	
		case AGENA_MEASURE_CAL_SCALAR_STANDARD_POWER:
	    	p2buffer += sprintf(p2buffer, "PMET %ld,%ld, %s", port1_Measurement,
	    						port2_SpecifiedFreq, agena_sensorType[sensor]);
	    	break;
		}
    
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Execute Scalar-Mixer ECal
/* Purpose:  For selected channel, performs 1-port or 2-port ECal module 
/*           measurement and error coefficient calculation (scalar-mixer 
/*           calibration) when the frequency offset mode is enabled.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actExecuteScalarECal (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     calibration,
    ViInt32     port1,
    ViInt32     port2
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
	agena_instrRange	instrPtr;
	ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
	    CHECKPARAM( agena_invalidViInt32Range(calibration, 0, 1), VI_ERROR_PARAMETER3);
    
	    switch (calibration)
	    {
	    case AGENA_SCALAR_MIXER_CALIB_2_PORT:
	    	CHECKPARAM( agena_invalidViInt32Range(port2, 1, instrPtr->numPorts),
	    				VI_ERROR_PARAMETER5);
    
	    case AGENA_SCALAR_MIXER_CALIB_1_PORT:
	    	CHECKPARAM( agena_invalidViInt32Range(port1, 1, instrPtr->numPorts),
	    				VI_ERROR_PARAMETER4);
	    	break;
		}
    
	    p2buffer += sprintf(p2buffer, ":SENS%ld:CORR:OFFS:COLL:ECAL:", channel);
    
	    switch (calibration)
	    {
	    case AGENA_SCALAR_MIXER_CALIB_1_PORT:
	    	p2buffer += sprintf(p2buffer, "SOLT1 %ld", port1);
	    	break;
    
	    case AGENA_SCALAR_MIXER_CALIB_2_PORT:
	    	p2buffer += sprintf(p2buffer, "SMIX2 %ld,%ld", port1, port2);
	    	break;
		}
    
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Calculate Receiver Calibration Coefficients
/* Purpose:  For selected channel, calculates the receiver calibration error
/*           coefficient for the specified port (executes receiver 
/*           calibration).
/*           
/*           The measurement port and the source port are THRU-connected for 
/*           execution. Therefore, if the same port number is specified for 
/*           the measurement port and the source port, an error occurs.
/*           
/*           Because information of power calibration for both the 
/*           measurement port and the source port is used for error 
/*           coefficient calculation, the precision of receiver calibration 
/*           is improved by executing power calibration for the both ports 
/*           before executing receiver calibration.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actCalculateRecCalCoef (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     receiver,
    ViInt32     port
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(receiver, 1, 4),
					VI_ERROR_PARAMETER3);
		CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER4);

	    CHECKERR( viPrintf(instrumentHandle, ":SENS%ld:CORR:REC%ld:COLL:ACQ %ld\n",
	    				   channel, receiver, port));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Send Trigger
/* Purpose:  This function send trigger.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actTrigger (
    ViSession   instrumentHandle,
    ViBoolean   ignoreTriggerSource,
    ViBoolean   waitForOPC
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar		trigger[1024] = "";
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;

	CHECKPARAM( agena_invalidViBooleanRange(ignoreTriggerSource),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViBooleanRange(waitForOPC),
				VI_ERROR_PARAMETER3);

    if (ignoreTriggerSource)
    {
    	if (waitForOPC)
    	{
    		p2buffer += sprintf(p2buffer, ":TRIG:SING");
    	}
    	else
    	{
    		p2buffer += sprintf(p2buffer, ":TRIG");
    	}
    }
    else
    {
    	ViInt32		trigger_source = -1;
    	
    	CHECKERR( viQueryf(instrumentHandle, ":TRIG:SOUR?\n", "%s", trigger));
    	RemoveSurroundingWhiteSpace(trigger);
    	trigger_source = agena_getValueIndex(trigger, agena_triggerSource);
    	if (trigger_source != AGENA_TRIGGER_SOURCE_BUS)
    	{
    		CHECKERR( AGENA_ERROR_INVALID_TRIGGER_SOURCE);
    	}
    	p2buffer += sprintf(p2buffer, "*TRG");
    }
    
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Start Sweep
/* Purpose:  Changes the state of each channel of selected channel to the 
/*           startup state in the trigger system.
/*           
/*           When this function is executed for a channel in the idle state, 
/*           it goes into the initiate state immediately. Then, after 
/*           measurement is executed once, it goes back to the idle state.
/*           
/*           If this function is executed for a channel that is not in the 
/*           idle state or for which the continuous initiation mode is 
/*           enabled, an error occurs.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actSweepStart (
    ViSession   instrumentHandle,
    ViInt32     channel
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    CHECKERR( viPrintf(instrumentHandle, ":INIT%ld\n", channel));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Abort Sweep
/* Purpose:  This function aborts the measurement and changes the trigger 
/*           sequence for all channels to idle state.
/*           
/*           After the change to the idle state, the channels for which the 
/*           continuous initiation mode is enabled change into the initiate 
/*           state.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actSweepAbort (
    ViSession   instrumentHandle
)
{
    ViStatus    agena_status = VI_SUCCESS;
    
    CHECKERR( viPrintf(instrumentHandle, ":ABOR\n"));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Restart Average
/* Purpose:  This function resets the result of the average function.
/*                     
/*===========================================================================*/
ViStatus _VI_FUNC agena_actSweAvgReset (
    ViSession   instrumentHandle,
    ViInt32     channel
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    CHECKERR( viPrintf(instrumentHandle, ":SENS%ld:AVER:CLE\n", channel));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Marker Search
/* Purpose:  This function search marker and returns position and value of 
/*           found marker.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actMarkerSearch (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     marker,
    ViInt32     function,
    ViReal64*   xValue,
    ViReal64*   yValue
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViReal64	y_value = 0.0,
    			x_value = 0.0;
    ViChar		trigger[1024] = "";
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(marker, 1, 10),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViInt32Range(function, 0, 7),
				VI_ERROR_PARAMETER4);

    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK%ld:FUNC:TYPE %s;EXEC\n", channel,
    					marker, agena_markerSearchFunc[function]);
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    
    CHECKERR( viQueryf( instrumentHandle, ":CALC%ld:MARK%ld:X?\n", "%lf", channel,
    					marker, &x_value));
    CHECKERR( viQueryf( instrumentHandle, ":CALC%ld:MARK%ld:Y?\n", "%lf", channel,
    					marker, &y_value));
	CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    if (xValue != NULL)
		*xValue = x_value;
	if (yValue != NULL)
		*yValue = y_value;
    
    return agena_status;
}

/*===========================================================================*/
/* Function: Marker To
/* Purpose:  For the active trace of selected channel, sets the value of the 
/*           specified item to the value of the position of selected marker.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actSetMarkerValues(
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     marker,
    ViInt32     markerTo
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViInt32Range(marker, 1, 10),
				VI_ERROR_PARAMETER3);
	CHECKPARAM( agena_invalidViInt32Range(markerTo, 0, 4),
				VI_ERROR_PARAMETER4);

    CHECKERR( viPrintf(instrumentHandle, ":CALC%ld:MARK%ld:SET %s\n", channel,
    				   marker, agena_markerTo[markerTo]));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Execute Analysis
/* Purpose:  For the active trace of selected channel, executes the analysis 
/*           specified with the agena_confAnalysis function.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actExecuteAnalysis (
    ViSession   instrumentHandle,
    ViInt32     channel
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    CHECKERR( viPrintf(instrumentHandle, ":CALC%ld:FUNC:EXEC\n", channel));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Match Frequency Range
/* Purpose:  For the active trace of selected channel, changes the frequency 
/*           range to match with the low-pass type transformation of the 
/*           transformation function of the time domain function.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actTDomMatchFreqRange (
    ViSession   instrumentHandle,
    ViInt32     channel
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    CHECKERR( viPrintf(instrumentHandle, ":CALC%ld:TRAN:TIME:LPFR\n", channel));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Store Instrument State
/* Purpose:  This function configure file handling.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actStoreInstrumentState (
    ViSession   instrumentHandle,
    ViInt32     items,
    ViBoolean   storeAllChannelsTraces
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;

    CHECKPARAM( agena_invalidViInt32Range(items, 0, 3), VI_ERROR_PARAMETER2);
    CHECKPARAM( agena_invalidViBooleanRange(storeAllChannelsTraces), VI_ERROR_PARAMETER3);
    
    p2buffer += sprintf(p2buffer, ":MMEM:STOR:STYP %s;", agena_fileHandlingItems[items]);
    p2buffer += sprintf(p2buffer, ":MMEM:STOR:SALL %s", storeAllChannelsTraces ? "ON" : "OFF");
	p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Store
/* Purpose:  This function saves specified instrument data into a file.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actStore (
    ViSession   instrumentHandle,
    ViInt32     dataType,
    ViString    fileName
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*  		    p2buffer = send_buffer;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

    CHECKPARAM( agena_invalidViInt32Range( dataType, 0, 11), VI_ERROR_PARAMETER2);
    
    model_type = instrPtr->modelType;
    if(IS_E506x)
    {
    	CHECKPARAM( (dataType == AGENA_FILE_DATA_TYPE_POWER_SENS_A || 
    				 dataType == AGENA_FILE_DATA_TYPE_POWER_SENS_B || 
    				 dataType >= AGENA_FILE_DATA_TYPE_LOSS_COM_1), VI_ERROR_PARAMETER2);    
    }
    
    p2buffer += sprintf(p2buffer, ":MMEM:STOR");
    
    switch (dataType)
    {
    case AGENA_FILE_DATA_TYPE_INSTR_STATE:
    	break;

    case AGENA_FILE_DATA_TYPE_FORMATTED:
    	p2buffer += sprintf(p2buffer, ":FDAT");
    	break;

    case AGENA_FILE_DATA_TYPE_IMAGE:
    	p2buffer += sprintf(p2buffer, ":IMAG");
    	break;
    
    case AGENA_FILE_DATA_TYPE_SEG_SWEEP_TABLE:
    	p2buffer += sprintf(p2buffer, ":SEGM");
    	break;
    
    case AGENA_FILE_DATA_TYPE_LIMIT_TABLE:
    	p2buffer += sprintf(p2buffer, ":LIM");
    	break;
    
    case AGENA_FILE_DATA_TYPE_POWER_SENS_A:
    	p2buffer += sprintf(p2buffer, ":ASCF");
    	break;
    
    case AGENA_FILE_DATA_TYPE_POWER_SENS_B:
    	p2buffer += sprintf(p2buffer, ":BSCF");
    	break;
    
    case AGENA_FILE_DATA_TYPE_VBA_PROJECT:
    	p2buffer += sprintf(p2buffer, ":PROG");
    	break;
    
    case AGENA_FILE_DATA_TYPE_LOSS_COM_1:
    	p2buffer += sprintf(p2buffer, ":PLOS1");
    	break;
    
    case AGENA_FILE_DATA_TYPE_LOSS_COM_2:
    	p2buffer += sprintf(p2buffer, ":PLOS2");
    	break;
    
    case AGENA_FILE_DATA_TYPE_LOSS_COM_3:
    	p2buffer += sprintf(p2buffer, ":PLOS3");
    	break;
    
    case AGENA_FILE_DATA_TYPE_LOSS_COM_4:
    	p2buffer += sprintf(p2buffer, ":PLOS4");
    	break;
    }
    p2buffer += sprintf(p2buffer, " \"%s\"\n", fileName);
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Recall
/* Purpose:  This function recalls specified instrument data into a file.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actRecall (
    ViSession   instrumentHandle,
    ViInt32     dataType,
    ViString    fileName
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

    CHECKPARAM( agena_invalidViInt32Range( dataType, 0, 11), VI_ERROR_PARAMETER2);
    
    model_type = instrPtr->modelType;
    if(IS_E506x)
    {
    	CHECKPARAM( (dataType == AGENA_FILE_DATA_TYPE_POWER_SENS_A || 
    				 dataType == AGENA_FILE_DATA_TYPE_POWER_SENS_B || 
    				 dataType >= AGENA_FILE_DATA_TYPE_LOSS_COM_1), VI_ERROR_PARAMETER2);    
    }
    
    p2buffer += sprintf(p2buffer, ":MMEM:LOAD");
    
    switch (dataType)
    {
    case AGENA_FILE_DATA_TYPE_INSTR_STATE:
    	break;

    case AGENA_FILE_DATA_TYPE_FORMATTED:
    	CHECKERR( VI_ERROR_PARAMETER2);
    	break;

    case AGENA_FILE_DATA_TYPE_IMAGE:
    	CHECKERR( VI_ERROR_PARAMETER2);
    	break;
    
    case AGENA_FILE_DATA_TYPE_SEG_SWEEP_TABLE:
    	p2buffer += sprintf(p2buffer, ":SEGM");
    	break;
    
    case AGENA_FILE_DATA_TYPE_LIMIT_TABLE:
    	p2buffer += sprintf(p2buffer, ":LIM");
    	break;
    
    case AGENA_FILE_DATA_TYPE_POWER_SENS_A:
    	p2buffer += sprintf(p2buffer, ":ASCF");
    	break;
    
    case AGENA_FILE_DATA_TYPE_POWER_SENS_B:
    	p2buffer += sprintf(p2buffer, ":BSCF");
    	break;
    
    case AGENA_FILE_DATA_TYPE_VBA_PROJECT:
    	p2buffer += sprintf(p2buffer, ":PROG");
    	break;
    
    case AGENA_FILE_DATA_TYPE_LOSS_COM_1:
    	p2buffer += sprintf(p2buffer, ":PLOS1");
    	break;
    
    case AGENA_FILE_DATA_TYPE_LOSS_COM_2:
    	p2buffer += sprintf(p2buffer, ":PLOS2");
    	break;
    
    case AGENA_FILE_DATA_TYPE_LOSS_COM_3:
    	p2buffer += sprintf(p2buffer, ":PLOS3");
    	break;
    
    case AGENA_FILE_DATA_TYPE_LOSS_COM_4:
    	p2buffer += sprintf(p2buffer, ":PLOS4");
    	break;
    }
    p2buffer += sprintf(p2buffer, " \"%s\"\n", fileName);
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Store Channel State
/* Purpose:  Saves the instrument state of the items set for the active 
/*           channel specific to that channel only into the specified 
/*           register (volatile memory).
/*           
/*           Notes:
/*           Notice that, if an instrument state has been saved already in 
/*           the specified register, its contents are overwritten.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actStoreChannelState (
    ViSession   instrumentHandle,
    ViInt32     memoryRegister
)
{
    ViStatus    agena_status = VI_SUCCESS;
    
    CHECKPARAM( agena_invalidViInt32Range( memoryRegister, 0, 3), VI_ERROR_PARAMETER2);
    
    CHECKERR( viPrintf(instrumentHandle, ":MMEM:STOR:CHAN %s\n",
    				   agena_memoryRegister[memoryRegister]));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Store Channel Coefficient
/* Purpose:  Saves the calibration coefficient of the active channel 
/*			into the specified register.
/*           
/*           Notes:
/*           (1) Notice that, if an instrument state has been saved already 
/*			 in the specified register, its contents are overwritten.
/*
/*			 (2) This function is available only for ENA E5061A/E5062A. 
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actStoreChannelCoefficient (
	ViSession instrumentHandle,
    ViInt32 memoryRegister
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(IS_E506x)
    {    
	    CHECKPARAM( agena_invalidViInt32Range( memoryRegister, 0, 3), VI_ERROR_PARAMETER2);
    
	    CHECKERR( viPrintf(instrumentHandle, ":MMEM:STOR:CHAN:COEF %s\n",
	    				   agena_memoryRegister[memoryRegister]));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;    
}

/*===========================================================================*/
/* Function: Recall Channel State
/* Purpose:  Recalls the instrument state for an individual channel from the 
/*           specified register as the setting of the active channel.
/*           
/*           Notes:
/*           It is possible to recall the register from a different channel 
/*           where it was saved.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actRecallChannelState (
    ViSession   instrumentHandle,
    ViInt32     memoryRegister
)
{
    ViStatus    agena_status = VI_SUCCESS;
    
    CHECKPARAM( agena_invalidViInt32Range( memoryRegister, 0, 3), VI_ERROR_PARAMETER2);
    
    CHECKERR( viPrintf(instrumentHandle, ":MMEM:LOAD:CHAN %s\n",
    				   agena_memoryRegister[memoryRegister]));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Recall Channel Coefficient
/* Purpose:  Recalls the calibration coefficient for an individual channel from the 
/*           specified register as the setting of the active channel.
/*           
/*           Notes:
/*           (1) It is possible to recall the register from a different channel 
/*           where it was saved.
/*
/*			 (2) This function is available only for ENA E5061A/E5062A. 
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actRecallChannelCoefficient (
	ViSession instrumentHandle,
    ViInt32 memoryRegister
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(IS_E506x)
    {
	    CHECKPARAM( agena_invalidViInt32Range( memoryRegister, 0, 3), VI_ERROR_PARAMETER2);
    
	    CHECKERR( viPrintf(instrumentHandle, ":MMEM:LOAD:CHAN:COEF %s\n",
	    				   agena_memoryRegister[memoryRegister]));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Clear Channel State
/* Purpose:  Deletes the instrument state for each channel in all the 
/*           registers.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actClearChannelState (ViSession instrumentHandle)
{
    ViStatus    agena_status = VI_SUCCESS;
    
    CHECKERR( viPrintf(instrumentHandle, ":MMEM:STOR:CHAN:CLE\n"));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: File Manager
/* Purpose:  This function creates, deletes directory or copies a file.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actFileManager (
    ViSession   instrumentHandle,
    ViInt32     operation,
    ViString    source,
    ViString    destination
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;

    CHECKPARAM( agena_invalidViInt32Range( operation, 0, 2), VI_ERROR_PARAMETER2);
    
    p2buffer += sprintf(p2buffer, ":MMEM:");
    
    switch (operation)
    {
    case AGENA_FILE_MANAGER_CREATE_DIR:
    	p2buffer += sprintf(p2buffer, "MDIR \"%s\"", source);
    	break;

    case AGENA_FILE_MANAGER_COPY_FILE:
    	p2buffer += sprintf(p2buffer, "COPY \"%s\",\"%s\"", source, destination);
    	break;
    
    case AGENA_FILE_MANAGER_DELETE_DIR:
    	p2buffer += sprintf(p2buffer, "DEL \"%s\"", source);
    	break;
    }
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: File Transfer To Storage Device
/* Purpose:  Writes data to a file on the built-in storage device of the 
/*           E5070B/E5071B.
/*           
/*           By reading out data with this function and writing it to a file 
/*           on the external controller, file transfer from the E5070B/E5071B 
/*           to the external controller can be realized. On the other hand, 
/*           by reading out data from the external controller and writing it 
/*           to a file on the E5070B/E5071B with this function, file transfer 
/*           from the external controller to the E5070B/E5071B can be 
/*           realized.
/*           
/*           Specify the file name with the extension. If you want to 
/*           specify a file on the floppy disk drive, you need to add "A:" at 
/*           the beginning of the file name. When you use directory names and 
/*           file name, separate them with "/" (slash) or "\" (backslash).
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actFileTransferToStorage (
    ViSession   instrumentHandle,
    ViString    fileName,
    ViInt32     dataBlockSize,
    ViChar      dataBlockArray[]
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar*     send_buffer = NULL;
    ViChar*     p2buffer;
	
	/* Allocate buffer for send           */
	/* dataBlockSize - size of data       */
	/* log(dataBlockSize) + 1 - number of character of data block size */
	/* strlen(fileName) - characters of file name */
	/* 15 - command size                  */
	send_buffer = malloc((dataBlockSize + log(dataBlockSize) + 1 + strlen(fileName) +
					 	 15) * sizeof(char));
    
    p2buffer = send_buffer;
    p2buffer += sprintf(p2buffer, ":MMEM:TRAN \"%s\",#%ld%ld", fileName, 
    					(ViInt32) log(dataBlockSize), dataBlockSize);
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, dataBlockArray, dataBlockSize, VI_NULL));
    CHECKERR( viPrintf(instrumentHandle, "\n"));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	if (send_buffer != NULL)
	{
		free(send_buffer);
		send_buffer = NULL;
	}
		
    return agena_status;
}

/*===========================================================================*/
/* Function: File Transfer From Storage Device
/* Purpose:  Reads data from a file on the built-in storage device of the 
/*           E5070B/E5071B.
/*           
/*           By reading out data with this function and writing it to a file 
/*           on the external controller, file transfer from the E5070B/E5071B 
/*           to the external controller can be realized. On the other hand, 
/*           by reading out data from the external controller and writing it 
/*           to a file on the E5070B/E5071B with this funcition, file 
/*           transfer from the external controller to the E5070B/E5071B can 
/*           be realized.
/*           
/*           Specify the file name with the extension. If you want to 
/*           specify 
/*           a file on the floppy disk
/*           drive, you need to add "A:" at the beginning of the file name. 
/*           When you use directory names and file name, separate them with 
/*           "/" (slash) or "\" (backslash).
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actFileTransferFromStorage (
    ViSession   instrumentHandle,
    ViString    fileName,
    ViInt32     bufferSize,
    ViChar      dataBlock[],
    ViInt32*	bytesRead
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar*		read_buffer = NULL;
    ViChar*		p2buffer;
    ViChar		buffer_read_size[10] = "";
    ViInt32		bytes_for_read = 0,
    			all_readed_bytes = 0,
    			readed_bytes = 0;
    
    CHECKERR( viPrintf(instrumentHandle, ":MMEM:TRAN? \"%s\"\n", fileName));
    CHECKERR( viRead(instrumentHandle, buffer_read_size, 2, VI_NULL));
    if (buffer_read_size[0] != '#')
    {
    	CHECKERR( VI_ERROR_INSTR_INTERPRETING_RESPONSE);
    }
    bytes_for_read = atol(buffer_read_size + 1);
    memset(buffer_read_size, 0, 10);
    CHECKERR( viRead(instrumentHandle, buffer_read_size, bytes_for_read, &readed_bytes));
    
    bytes_for_read = atol(buffer_read_size) + 1;
    read_buffer = malloc((bytes_for_read + 1) * sizeof(char));
    p2buffer = read_buffer;
    
    do
    {
    	CHECKERR( viRead(instrumentHandle, p2buffer, bytes_for_read, &readed_bytes));
    	p2buffer += readed_bytes;
    	all_readed_bytes += readed_bytes;
    } while (all_readed_bytes < bytes_for_read);
    
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	if (agena_status == VI_SUCCESS)
	{
		bytes_for_read = (bufferSize < all_readed_bytes) ? bufferSize : all_readed_bytes;
		/* Return correct buffer size if user pass smaller buffer */
		if (bufferSize < all_readed_bytes)
		{
			agena_status = all_readed_bytes;
		}
	
		if (dataBlock != NULL)
		{
			memcpy(dataBlock, read_buffer, bytes_for_read);
		}
	
		if (bytesRead != NULL)
			*bytesRead = bytes_for_read;
	}
	
	if (read_buffer != NULL)
	{
		free(read_buffer);
		read_buffer = NULL;
	}
		
    return agena_status;
}

/*===========================================================================*/
/* Function: Directory Contents
/* Purpose:  This function reads out the following information on the 
/*           built-in storage device of the E5070B/E5071B.
/*           
/*           To read out the information in the root directory (folder), 
/*           specify "\" (backslash). If you want to specify a directory on 
/*           the floppy disk drive, you need to add "A:" at the beginning of 
/*           the file name. Separate directory names with "/" (slash) or "\" 
/*           (backslash).
/*           
/*           - Space in use
/*           - Available space
/*           - Name and size of all files (including directories) in the 
/*           specified directory.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actDirContents (
    ViSession   instrumentHandle,
    ViString    directory,
    ViReal64*  	usedSize,
    ViReal64*  	freeSpace,
    ViInt32		bufferSize,
    ViChar      contents[]
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar*		read_buffer = NULL;
    ViChar*		p2size = NULL;
    ViInt32		readed_bytes = 0;
    ViReal64	used_bytes = 0,
    			free_space = 0;
    
    CHECKERR( viPrintf(instrumentHandle, ":MMEM:CAT? \"%s\"\n", directory));
    CHECKERR( agena_readDataUnknownLength(instrumentHandle, &read_buffer, &readed_bytes));
    
	p2size = read_buffer + 1;
    p2size = strtok(p2size, ",");
    if (p2size == NULL)
    {
    	CHECKERR( VI_ERROR_INSTR_INTERPRETING_RESPONSE);
    }
    used_bytes = atof(p2size);
    p2size = strtok(NULL, ",");
    if (p2size == NULL)
    {
    	CHECKERR( VI_ERROR_INSTR_INTERPRETING_RESPONSE);
    }
    free_space = atof(p2size);
    p2size = strtok(NULL, "\"");
    
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	if (agena_status == VI_SUCCESS)
	{
		if (usedSize != NULL)
		{
			*usedSize = used_bytes;
		}
	    if (freeSpace != NULL)
		{
			*freeSpace = free_space;
		}
	
		/* Return correct buffer size if user pass smaller buffer */
		if (contents != NULL)
		{
			*contents = '\0';
			
			if (p2size != NULL)
			{
				if (bufferSize < readed_bytes)
				{
					strncpy(contents, p2size, bufferSize - 1);
					contents[bufferSize - 1] = '\0';
					agena_status = readed_bytes;
				}
				else
				{
					strcpy(contents, p2size);
				}
			}
		}
		if (bufferSize == 0 && contents == NULL)
		{
			agena_status = readed_bytes;
		}
	}
	
	if (read_buffer != NULL)
	{
		free(read_buffer);
		read_buffer = NULL;
	}
	
    return agena_status;
}

/*===========================================================================*/
/* Function: Hardcopy
/* Purpose:  This function outputs the display image on the LCD display to 
/*           the printer connected to the E5070B/E5071B or abort the print 
/*           operation.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actHCopy (
    ViSession   instrumentHandle,
    ViInt32     operation
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;

    CHECKPARAM( agena_invalidViInt32Range( operation, 0, 1), VI_ERROR_PARAMETER2);
    
    p2buffer += sprintf(p2buffer, ":HCOP");
    
    switch (operation)
    {
    case AGENA_HARDCOPY_EXECUTE:
    	break;

    case AGENA_HARDCOPY_ABORT:
    	p2buffer += sprintf(p2buffer, ":ABOR");
    	break;
    }
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Read System Informations
/* Purpose:  This function reads system informations.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actSystemInfo (
    ViSession   instrumentHandle,
    ViInt32*    number_ofChannels,
    ViInt32*    number_ofTraces,
    ViInt32*    number_ofPorts,
    ViInt32*	systemVersion
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViInt32				channels = 0,
		    			traces = 0,
		    			ports = 0,
		    			version = 0;
	agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

    model_type = instrPtr->modelType;
    CHECKERR( viQueryf(instrumentHandle, ":SERV:CHAN:COUN?\n", "%ld", &channels));
    CHECKERR( viQueryf(instrumentHandle, ":SERV:CHAN:TRAC:COUN?\n", "%ld", &traces));
    CHECKERR( viQueryf(instrumentHandle, ":SERV:PORT:COUN?\n", "%ld", &ports));
    if(!IS_E506x)
	{ 
    	CHECKERR( viQueryf(instrumentHandle, ":SERV:SREV?\n", "%ld", &version));
    }
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	if (agena_status == VI_SUCCESS)
	{
		if (number_ofChannels != NULL)
			*number_ofChannels = channels;
		if (number_ofTraces != NULL)
			*number_ofTraces = traces;
		if (number_ofPorts != NULL)
			*number_ofPorts = ports;
		if (systemVersion != NULL)
			*systemVersion = version;
	}
    return agena_status;
}

/*===========================================================================*/
/* Function: Shutdown
/* Purpose:  Turns OFF the E5070B/E5071B.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actShutdown (ViSession instrumentHandle)
{
    ViStatus    agena_status = VI_SUCCESS;
	agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
	    CHECKERR( viPrintf(instrumentHandle, ":SYST:POFF\n"));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Security Level
/* Purpose:  Sets the security level.
/*
/*			 Notes:
/*			 (1) This function is available only for ENA E5061A/E5062A.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actSecurityLevel (
	ViSession instrumentHandle,
    ViInt32 securityLevel
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(IS_E506x)
    {
	    CHECKPARAM( agena_invalidViInt32Range( securityLevel, 0, 2), VI_ERROR_PARAMETER2);
    
	    p2buffer += sprintf(p2buffer, ":SYST:SEC:LEV ");
    
	    switch (securityLevel)
	    {
	    case AGENA_SECURITY_LEVEL_NONE:
	    	p2buffer += sprintf(p2buffer, "NON");    
	    	break;

	    case AGENA_SECURITY_LEVEL_LOW:
	    	p2buffer += sprintf(p2buffer, "LOW");
	    	break;

	    case AGENA_SECURITY_LEVEL_HIGH:
	    	p2buffer += sprintf(p2buffer, "HIGH");
	    	break;

	    }
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;    
}

/*===========================================================================*/
/* Function: Read Warmed-Up State
/* Purpose:  This function reads out whether warm-up to satisfy the 
/*           specifications of the E5070B/E5071B is enough.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actWarmedUp (
    ViSession   instrumentHandle,
    ViBoolean*  warmedUp
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViBoolean	warm_up = VI_FALSE;
    
    CHECKERR( viQueryf(instrumentHandle, ":SYST:TEMP?\n", "%hd", &warm_up));
	CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	if (warmedUp != NULL)
	{
		*warmedUp = warm_up;
	}
    return agena_status;
}

/*===========================================================================*/
/* Function: Read Service Mode State
/* Purpose:  Reads out whether to be in the service mode.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_actServMode (
    ViSession   instrumentHandle,
    ViBoolean*  serviceMode
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViBoolean	service = VI_FALSE;
    
    CHECKERR( viQueryf(instrumentHandle, ":SYST:SERV?\n", "%hd", &service));
	CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	if (serviceMode != NULL)
	{
		*serviceMode = service;
	}
    return agena_status;
}

/*===========================================================================*/
/* Function: Read Calibration Data Array
/* Purpose:  For selected port of selected channel, reads out the power 
/*           calibration data array.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataReadCalDataArr (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     port,
    ViInt32     arraySize,
    ViReal64    calData[]
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar*				read_buffer = NULL;
    ViChar*				p2value = NULL;
    ViInt32				readed_bytes = 0,
    					readed_values = 0;
    agena_instrRange	instrPtr;
    ViInt32				model_type;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER3);

	    if ((arraySize == 0 && calData != NULL) ||
	    	(arraySize != 0 && calData == NULL))
	    	CHECKERR( VI_ERROR_PARAMETER5);
    
	    CHECKERR( viPrintf(instrumentHandle, ":SOUR%ld:POW:PORT%ld:CORR:DATA?\n",
	    				   channel, port));
	    CHECKERR( agena_readDataUnknownLength(instrumentHandle, &read_buffer, &readed_bytes));
	    CHECKERR( agena_checkStatus( instrumentHandle));
    
	    p2value = strtok(read_buffer, ",");
	    while (p2value)
	    {
	    	if (readed_values < arraySize)
	    	{
	    		calData[readed_values] = atof(p2value);
	    	}
	    	readed_values++;
	    	p2value = strtok(NULL, ",");
	    }
	}
	
Error:
	if (agena_status == VI_SUCCESS)
	{
		if ((arraySize == 0 && calData == NULL) ||
			(readed_values > arraySize))
		{
			agena_status = readed_values;
		}
	}
	
	if (read_buffer != NULL)
	{
		free(read_buffer);
		read_buffer = NULL;
	}
	
    return agena_status;
}

/*===========================================================================*/
/* Function: Write Calibration Data Array
/* Purpose:  For selected port of selected channel, sets the power 
/*           calibration data array.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataWriteCalDataArr (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     port,
    ViInt32     arraySize,
    ViReal64    calData[]
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar*				send_buffer = NULL;
    ViChar*     		p2buffer;
    ViInt32				i = 0;
	agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(!IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(port, 1, instrPtr->numPorts),
					VI_ERROR_PARAMETER3);

		/* Allocate correct buffer size for send */
		/* 30 - command size                     */
		/* rest - array size in bytes            */
	    send_buffer = malloc((30 + arraySize * DOUBLE_BYTE_SIZE) * sizeof(char));
	    p2buffer = send_buffer;
    
	    p2buffer += sprintf(p2buffer, ":SOUR%ld:POW:PORT%ld:CORR:DATA ",
							channel, port);
    
	    for (i = 0; i < arraySize; i++)
	    {
	    	p2buffer += sprintf(p2buffer, "%le,", calData[i]);
	    }
    
	    /* Remove last comma separator */
	    *--p2buffer = '\0';
    
	    p2buffer += sprintf(p2buffer, "\n");
    
	    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Read Data and Memory Arrays
/* Purpose:  For the active trace of selected channel, reads out the 
/*           formated or corrected data or memory array.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataReadDataMemArr (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     source,
    ViInt32     correction,
    ViInt32     arraySize,
    ViReal64    primaryReal[],
    ViReal64    secondaryImaginary[]
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar		send_buffer[1024] = "";
    ViChar*		p2buffer = send_buffer;
    ViChar*		read_buffer = NULL;
    ViChar*		p2value = NULL;
    ViInt32		readed_bytes = 0,
    			readed_values = 0,
    			i = 0;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(source, 0, 1), VI_ERROR_PARAMETER3);
    CHECKPARAM( agena_invalidViInt32Range(correction, 0, 1), VI_ERROR_PARAMETER4);
    
    if ((arraySize == 0 && primaryReal != NULL) ||
    	(arraySize != 0 && primaryReal == NULL))
    	CHECKERR( VI_ERROR_PARAMETER6);
    	
    if ((arraySize == 0 && secondaryImaginary != NULL) ||
    	(arraySize != 0 && secondaryImaginary == NULL))
    	CHECKERR( VI_ERROR_PARAMETER7);
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:DATA:", channel);
    
    switch (correction)
    {
    case AGENA_DATA_CORRECTION_FORMATTED:
    	p2buffer += sprintf(p2buffer, "F");
    	break;
    
    case AGENA_DATA_CORRECTION_CORRECTED:
    	p2buffer += sprintf(p2buffer, "S");
    	break;
    }
    
    switch (source)
    {
    case AGENA_DATA_SOURCE_DATA:
    	p2buffer += sprintf(p2buffer, "DAT");
    	break;
    
    case AGENA_DATA_SOURCE_MEMORY:
    	p2buffer += sprintf(p2buffer, "MEM");
    	break;
    }
    p2buffer += sprintf(p2buffer, "?\n");
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_readDataUnknownLength(instrumentHandle, &read_buffer, &readed_bytes));
    CHECKERR( agena_checkStatus( instrumentHandle));
    
    p2value = strtok(read_buffer, ",");
    while (p2value)
    {
    	if (readed_values < arraySize)
    	{
    		if (i % 2)
    		{
    			secondaryImaginary[readed_values] = atof(p2value);
    		}
    		else
    		{
    			primaryReal[readed_values] = atof(p2value);
    		}
    	}
    	if (i % 2)
    		readed_values++;
    	
    	i++;
    	p2value = strtok(NULL, ",");
    }

Error:
	if (agena_status == VI_SUCCESS)
	{
		if ((arraySize == 0 && primaryReal == NULL) ||
			(readed_values > arraySize))
		{
			agena_status = readed_values;
		}
	}
	
	if (read_buffer != NULL)
	{
		free(read_buffer);
		read_buffer = NULL;
	}
	
    return agena_status;
}

/*===========================================================================*/
/* Function: Write Data and Memory Arrays
/* Purpose:  For the active trace of selected channel, sets the formated or 
/*           corrected data or memory array.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataWriteDataMemArr (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     source,
    ViInt32     correction,
    ViInt32     arraySize,
    ViReal64    primaryReal[],
    ViReal64    secondaryImaginary[]
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar*		send_buffer = NULL;
    ViChar*     p2buffer;
    ViInt32		i = 0;
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(source, 0, 1), VI_ERROR_PARAMETER3);
    CHECKPARAM( agena_invalidViInt32Range(correction, 0, 1), VI_ERROR_PARAMETER4);

	/* Allocate correct buffer size for send */
	/* 30 - command size                     */
	/* rest - array size in bytes            */
    send_buffer = malloc((20 + arraySize * 2 * DOUBLE_BYTE_SIZE) * sizeof(char));
    p2buffer = send_buffer;
    
    p2buffer += sprintf(p2buffer, ":CALC%ld:DATA:", channel);
    
    switch (correction)
    {
    case AGENA_DATA_CORRECTION_FORMATTED:
    	p2buffer += sprintf(p2buffer, "F");
    	break;
    
    case AGENA_DATA_CORRECTION_CORRECTED:
    	p2buffer += sprintf(p2buffer, "S");
    	break;
    }
    
    switch (source)
    {
    case AGENA_DATA_SOURCE_DATA:
    	p2buffer += sprintf(p2buffer, "DAT");
    	break;
    
    case AGENA_DATA_SOURCE_MEMORY:
    	p2buffer += sprintf(p2buffer, "MEM");
    	break;
    }
    p2buffer += sprintf(p2buffer, " ");
    
    for (i = 0; i < arraySize; i++)
    {
    	p2buffer += sprintf(p2buffer, "%le,%le,", primaryReal[i], secondaryImaginary[i]);
    }
    
    /* Remove last comma separator */
    *--p2buffer = '\0';
    
    p2buffer += sprintf(p2buffer, "\n");
    
    CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), VI_NULL));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Read Stimulus Array
/* Purpose:  For selected channel, reads out the frequencies of all 
/*           measurement point.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataReadStimulusArr (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     arraySize,
    ViReal64    stimulusData[]
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar*		read_buffer = NULL;
    ViChar*		p2value = NULL;
    ViInt32		readed_bytes = 0,
    			readed_values = 0;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    if ((arraySize == 0 && stimulusData != NULL) ||
    	(arraySize != 0 && stimulusData == NULL))
    	CHECKERR( VI_ERROR_PARAMETER4);
    
    CHECKERR( viPrintf(instrumentHandle, ":SENS%ld:FREQ:DATA?\n", channel));
    CHECKERR( agena_readDataUnknownLength(instrumentHandle, &read_buffer, &readed_bytes));
    CHECKERR( agena_checkStatus( instrumentHandle));
    
    p2value = strtok(read_buffer, ",");
    while (p2value)
    {
    	if (readed_values < arraySize)
    	{
    		stimulusData[readed_values] = atof(p2value);
    	}
    	readed_values++;
    	p2value = strtok(NULL, ",");
    }

Error:
	if (agena_status == VI_SUCCESS)
	{
		if ((arraySize == 0 && stimulusData == NULL) ||
			(readed_values > arraySize))
		{
			agena_status = readed_values;
		}
	}
	
	if (read_buffer != NULL)
	{
		free(read_buffer);
		read_buffer = NULL;
	}
	
    return agena_status;
}

/*===========================================================================*/
/* Function: Limit Fail
/* Purpose:  For the active trace of selected channel, reads out the limit 
/*           test result.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataLimitFail (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViBoolean*  fail
)
{
    ViStatus    agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    if (fail == NULL)
    	CHECKERR( VI_ERROR_PARAMETER3);
    
    CHECKERR( viQueryf(instrumentHandle, ":CALC%ld:LIM:FAIL?\n", "%hd", channel,
    				   fail));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	return agena_status;
}

/*===========================================================================*/
/* Function: Read Fail Meas Points
/* Purpose:  For the active trace of selected channel, reads out the number
/*			 of the measurement points and stimulus values (frequency, power
/*   		 level or time) at all the measurement point that failed the
/*			 limit test.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataReadFailMeasPoints (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     arraySize,
    ViInt32*    number_ofFailedPoints,    
    ViReal64    data[]
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar*		read_buffer = NULL;
    ViChar*		p2value = NULL;
    ViInt32		readed_bytes = 0,
    			readed_values = 0;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

 	if (number_ofFailedPoints == NULL)
    	CHECKERR( VI_ERROR_PARAMETER4);
    	
    if ((arraySize == 0 && data != NULL) ||
    	(arraySize != 0 && data == NULL))
    	CHECKERR( VI_ERROR_PARAMETER5);
  
  	CHECKERR( viQueryf(instrumentHandle, ":CALC%ld:LIM:REP:POIN?\n", "%ld", channel,
    				   number_ofFailedPoints));    	
    
    CHECKERR( viPrintf(instrumentHandle, ":CALC%ld:LIM:REP?\n", channel));
    CHECKERR( agena_readDataUnknownLength(instrumentHandle, &read_buffer, &readed_bytes));
    CHECKERR( agena_checkStatus( instrumentHandle));
    
    p2value = strtok(read_buffer, ",");
    while (p2value)
    {
    	if (readed_values < arraySize)
    	{
    		data[readed_values] = atof(p2value);
    	}
    	readed_values++;
    	p2value = strtok(NULL, ",");
    }

Error:
	if (agena_status == VI_SUCCESS)
	{
		if ((arraySize == 0 && data == NULL) ||
			(readed_values > arraySize))
		{
			agena_status = readed_values;
		}
	}
	
	if (read_buffer != NULL)
	{
		free(read_buffer);
		read_buffer = NULL;
	}
	
    return agena_status;
}

/*===========================================================================*/
/* Function: Marker Data
/* Purpose:  For the active trace of selected channel, reads out the 
/*           response value of selected marker.
/*           
/*           When the reference marker mode is enabled, the readout value is 
/*           the value relative to the reference marker.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataMarkerData (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     marker,
    ViReal64*   xValue,
    ViReal64*   realValue,
    ViReal64*   imaginaryValue
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViReal64	x_value = 0.0,
    			y_real_value = 0.0,
    			y_imaginary_value = 0.0;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(marker, 1, 10),
				VI_ERROR_PARAMETER3);

    CHECKERR( viQueryf(instrumentHandle, ":CALC%ld:MARK%ld:X?\n", "%lf",
    				   channel, marker, &x_value));
	CHECKERR( viQueryf(instrumentHandle, ":CALC%ld:MARK%ld:Y?\n", "%lf,%lf",
    				   channel, marker, &y_real_value, &y_imaginary_value));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	if (agena_status == VI_SUCCESS)
	{
		if (xValue != NULL)
			*xValue = x_value;
		if (realValue != NULL)
			*realValue = y_real_value;
		if (imaginaryValue != NULL)
			*imaginaryValue = y_imaginary_value;
	}
    return agena_status;
}

/*===========================================================================*/
/* Function: Math Marker Data
/* Purpose:  For the active trace of channel, returns marker flatness or
/*			 filter statistics or marker statistics data.
/*           
/*           Notes:
/*			 (1) This function is available only for ENA E5061A/E5062A.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataMathMarkerData (
	ViSession instrumentHandle,
    ViInt32 channel,
    ViInt32 markerFunction,
    ViReal64 *num1, 
    ViReal64 *num2,
    ViReal64 *num3, 
    ViReal64 *num4
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViChar      		send_buffer[1024] = "";
    ViChar*     		p2buffer = send_buffer;    
    ViReal64			num_1 = 0.0,
    					num_2 = 0.0,
    					num_3 = 0.0,
    					num_4 = 0.0;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(markerFunction, 0, 2),
					VI_ERROR_PARAMETER3);

	    p2buffer += sprintf(p2buffer, ":CALC%ld:MARK:MATH:", channel);
	    
		switch(markerFunction)
		{
		case AGENA_MARKER_MATH_FLAT:
			p2buffer += sprintf(p2buffer, "FLAT");
    		break;		
		case AGENA_MARKER_MATH_FST:
			p2buffer += sprintf(p2buffer, "FST");
    		break;		
		case AGENA_MARKER_MATH_STAT:
			p2buffer += sprintf(p2buffer, "STAT");
    		break;		
		}
		
		p2buffer += sprintf(p2buffer, ":DATA?\n");

        CHECKERR( viQueryf(instrumentHandle, p2buffer, "%lf,%lf,%lf,%lf",
    				   &num_1, &num_2, &num_3, &num_4));
    	CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
	if (agena_status == VI_SUCCESS)
	{
		if (num1 != NULL)
			*num1 = num_1;
		if (num2 != NULL)
			*num2 = num_2;
		if (num3 != NULL)
			*num3 = num_3;
		if (num4 != NULL)
			*num4 = num_4;
	}
    return agena_status;    
}

/*===========================================================================*/
/* Function: Marker Bandwidth Search Result
/* Purpose:  For the active trace of selected channel, reads out the 
/*           bandwidth search result of selected marker.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataMarkerBandwidthSearchResult (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     marker,
    ViReal64*   bandwidth,
    ViReal64*   centerFrequency,
    ViReal64*   qValue,
    ViReal64*   loss
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViReal64	b_width = 0.0,
    			center_freq = 0.0,
    			q_value = 0.0,
    			loss_value = 0.0;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);
	CHECKPARAM( agena_invalidViInt32Range(marker, 1, 10),
				VI_ERROR_PARAMETER3);

    CHECKERR( viQueryf(instrumentHandle, ":CALC%ld:MARK%ld:BWID:DATA?\n",
    				   "%lf,%lf,%lf,%lf",
    				   channel, marker,
    				   &b_width, &center_freq, &q_value, &loss_value));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	if (agena_status == VI_SUCCESS)
	{
		if (bandwidth != NULL)
			*bandwidth = b_width;
		if (centerFrequency != NULL)
			*centerFrequency = center_freq;
		if (qValue != NULL)
			*qValue = q_value;
		if (loss != NULL)
			*loss = loss_value;
	}
    return agena_status;
}

/*===========================================================================*/
/* Function: Marker Notch Search Result
/* Purpose:  For the active trace of selected channel, reads out the 
/*           notch search result of selected marker.
/*           
/*			 Notes:
/*
/*			 
/*
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataMarkerNotchSearchResult (
	ViSession instrumentHandle,
    ViReal64 *bandwidth,
    ViReal64 *centerFrequency,
    ViInt32 channel,
    ViInt32 marker,
    ViReal64 *qValue,
    ViReal64 *loss
)
{
    ViStatus    		agena_status = VI_SUCCESS;
    ViReal64			b_width = 0.0,
    					center_freq = 0.0,
    					q_value = 0.0,
    					loss_value = 0.0;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    model_type = instrPtr->modelType;
    if(IS_E506x)
    {
		CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
					VI_ERROR_PARAMETER2);
		CHECKPARAM( agena_invalidViInt32Range(marker, 1, 10),
					VI_ERROR_PARAMETER3);

	    CHECKERR( viQueryf(instrumentHandle, ":CALC%ld:MARK%ld:NOTC:DATA?\n",
	    				   "%lf,%lf,%lf,%lf", 
	    				   channel, marker,
	    				   &b_width, &center_freq, &q_value, &loss_value));
	    CHECKERR( agena_checkStatus( instrumentHandle));
	}
	
Error:
	if (agena_status == VI_SUCCESS)
	{
		if (bandwidth != NULL)
			*bandwidth = b_width;
		if (centerFrequency != NULL)
			*centerFrequency = center_freq;
		if (qValue != NULL)
			*qValue = q_value;
		if (loss != NULL)
			*loss = loss_value;
	}
    return agena_status;    
}

/*===========================================================================*/
/* Function: Read Analysis Result
/* Purpose:  For the active trace of selected channel, reads out the 
/*           analysis result of the agena_actExecuteAnalysis function.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataReadAnalysisResult (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViInt32     arraySize,
	ViInt32*    number_ofAnalysisResults,
    ViReal64    stimulus[],
    ViReal64    response[]
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar*		read_buffer = NULL;
    ViChar*		p2value = NULL;
    ViInt32		readed_bytes = 0,
    			readed_values = 0,
    			i = 0;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);


    if (number_ofAnalysisResults == NULL)
    	CHECKERR( VI_ERROR_PARAMETER4);
    	
    if ((arraySize == 0 && stimulus != NULL) ||
    	(arraySize != 0 && stimulus == NULL))
    	CHECKERR( VI_ERROR_PARAMETER5);
    	
    if ((arraySize == 0 && response != NULL) ||
    	(arraySize != 0 && response == NULL))
    	CHECKERR( VI_ERROR_PARAMETER6);
    
    CHECKERR( viQueryf(instrumentHandle, ":CALC%ld:FUNC:POIN?\n", "%ld",
    				   channel, number_ofAnalysisResults));
    				   
    CHECKERR( viPrintf(instrumentHandle, ":CALC%ld:FUNC:DATA?\n", channel));
    CHECKERR( agena_readDataUnknownLength(instrumentHandle, &read_buffer, &readed_bytes));
    CHECKERR( agena_checkStatus( instrumentHandle));
    
    p2value = strtok(read_buffer, ",");
    while (p2value)
    {
    	if (readed_values < arraySize)
    	{
    		if (i % 2)
    		{
    			stimulus[readed_values] = atof(p2value);
    		}
    		else
    		{
    			response[readed_values] = atof(p2value);
    		}
    	}
    	if (i % 2)
    		readed_values++;
    	
    	i++;
    	p2value = strtok(NULL, ",");
    }

Error:
	if (agena_status == VI_SUCCESS)
	{
		if ((arraySize == 0 && stimulus == NULL && response == NULL) ||
			(readed_values > arraySize))
		{
			agena_status = readed_values;
		}
	}
	
	if (read_buffer != NULL)
	{
		free(read_buffer);
		read_buffer = NULL;
	}
	
    return agena_status;
}

/*===========================================================================*/
/* Function: Read Handler Input Data
/* Purpose:  This function reads out data inputted to ports C, D or E (C0 to
/*           C3, D0 to D3 or C0 to D3).
/*           
/*           Notes:
/*           (1) Ports C or D must be set to input mode for read out from 
/*           the port C or D.
/*           
/*           (2) Ports C and D must be set to input mode for read out from 
/*           the port E.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataReadHandlerInput (
    ViSession   instrumentHandle,
    ViInt32     port,
    ViInt32*    data
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViChar      send_buffer[1024] = "";
    ViChar*     p2buffer = send_buffer;

    CHECKPARAM( agena_invalidViInt32Range(port, 2, 5), VI_ERROR_PARAMETER2);
    
    if (data == NULL)
    	CHECKERR( VI_ERROR_PARAMETER3);

    CHECKERR( viQueryf(instrumentHandle, ":CONT:HAND:%s?\n", "%ld", 
    				   agena_portName[port], data));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Write Handler Output Data
/* Purpose:  This function outputs data to output port A (A0 to A7), port B 
/*           (B0 to B7), port C (C0 to C3), port D (D0 to D3), port E (C0 to 
/*           D3) or port F (A0 to B7).
/*           
/*           Notes:
/*           (1) Ports C or D must be set to output mode for set to the port 
/*           C or D.
/*           
/*           (2) Ports C and D must be set to output mode for set to the 
/*           port E.
/*           
/*           (3) Data is outputted as 8-bit binary (for port A and B) using 
/*           x0 as LSB and x7 as MSB. Where x is port name.
/*           
/*           (4) Data is outputted as 4-bit binary (for port C and D) using 
/*           x0 as LSB and x3 as MSB. Where x is port name.
/*           
/*           (5) Data is outputted as 8-bit binary (for port E) using C0 as 
/*           LSB and D3 as MSB.
/*           
/*           (6) Data is outputted as 16-bit binary (for port F) using A0 as 
/*           LSB and B7 as MSB.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataWriteHandlerOutput (
    ViSession   instrumentHandle,
    ViInt32     port,
    ViInt32     data
)
{
    ViStatus    agena_status = VI_SUCCESS;
    
    CHECKPARAM( agena_invalidViInt32Range(port, 0, 5), VI_ERROR_PARAMETER2);
    
    CHECKERR( viPrintf(instrumentHandle, ":CONT:HAND:%s %ld\n", 
    				   agena_portName[port], data));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
    return agena_status;
}


/*===========================================================================*/
/* Function: Trace Statistic Analysis Result
/* Purpose:  For the active trace of selected channel, reads out the 
/*           statistics values (the mean vale, the standard deviation, and 
/*           the difference between the maximum value and the minimum value) 
/*           display.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_dataTraceStatisticAnalysisResult (
    ViSession   instrumentHandle,
    ViInt32     channel,
    ViReal64*   mean,
    ViReal64*   standardDeviation,
    ViReal64*   peak_toPeak
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViReal64	mean_value = 0.0,
    			std_deviation = 0.0,
    			peak2peak = 0.0;
    agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(channel, 1, instrPtr->numChannels),
				VI_ERROR_PARAMETER2);

    CHECKERR( viQueryf(instrumentHandle, ":CALC%ld:MST:DATA?\n", "%lf,%lf,%lf", 
    				   channel, &mean_value, &std_deviation, &peak2peak));
    CHECKERR( agena_checkStatus( instrumentHandle));

Error:
	if (agena_status == VI_SUCCESS)
	{
		if (mean != NULL)
			*mean = mean_value;
		if (standardDeviation != NULL)
			*standardDeviation = std_deviation;
		if (peak_toPeak != NULL)
			*peak_toPeak = peak2peak;
	}
    return agena_status;
}

/*****************************************************************************/
/*-------- INSERT USER-CALLABLE INSTRUMENT-DEPENDENT ROUTINES HERE ----------*/
/*****************************************************************************/

ViStatus _VI_FUNC agena_setStatusRegister (
	ViSession	instrumentHandle,
	ViInt32		registerOperation,
	ViInt32		questionableRegister,
	ViInt32		channel,
	ViInt32		enable,
	ViInt32		PTransition,
	ViInt32		NTransition
)
{
	ViStatus			agena_status = VI_SUCCESS;
	ViChar				send_buffer[512];
	ViChar*				p2buffer = send_buffer;
    agena_instrRange	instrPtr;
	ViInt32				model_type;
	
    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
	CHECKPARAM( agena_invalidViInt32Range(registerOperation, 0, 2), VI_ERROR_PARAMETER2);
	
	switch (registerOperation)
	{
	case AGENA_STATUS_REGISTER_PRESET:
		p2buffer += sprintf(p2buffer, ":STAT:PRES");
		break;
	
	case AGENA_STATUS_REGISTER_OPERATION:
		p2buffer += sprintf(p2buffer, ":STAT:OPER:ENAB %ld;NTR %ld;PTR %ld",
							enable, NTransition, PTransition);
		break;
	
	case AGENA_STATUS_REGISTER_QUESTIONABLE:
		p2buffer += sprintf(p2buffer, ":STAT:QUES");
							
		switch (questionableRegister)
		{
		case AGENA_QUESTIONABLE_REGISTER_MAIN:
			break;
		case AGENA_QUESTIONABLE_REGISTER_CHANNEL:
			p2buffer += sprintf(p2buffer, ":LIM:CHAN%ld", channel);
			break;
		case AGENA_QUESTIONABLE_REGISTER_CHANNEL_EXTRA:
			p2buffer += sprintf(p2buffer, ":LIM:CHAN%ld:ECH", channel);
			break;
		case AGENA_QUESTIONABLE_REGISTER_LIMIT:
			p2buffer += sprintf(p2buffer, ":LIM");
			break;
		case AGENA_QUESTIONABLE_REGISTER_LIMIT_EXTRA:
			p2buffer += sprintf(p2buffer, ":LIM:ELIM");
			break;
		}

		model_type = instrPtr->modelType;
		if (!IS_E506x || questionableRegister != AGENA_QUESTIONABLE_REGISTER_CHANNEL_EXTRA && 
						 questionableRegister != AGENA_QUESTIONABLE_REGISTER_LIMIT_EXTRA)
		{
			p2buffer += sprintf(p2buffer, ":ENAB %ld;NTR %ld;PTR %ld", enable,
								NTransition, PTransition);
		}
		break;
	}
	p2buffer += sprintf(p2buffer, "\n");
	
	CHECKERR( viWrite(instrumentHandle, send_buffer, strlen(send_buffer), NULL));
	CHECKERR( agena_checkStatus(instrumentHandle));
	
Error:
	return agena_status;
}

ViStatus _VI_FUNC agena_getStatusRegister (
	ViSession	instrumentHandle,
	ViInt32		statusRegistersQuery,
	ViInt32		channel,
	ViInt32*	registerValue
)
{
    ViStatus	agena_status = VI_SUCCESS;
    ViChar		send_buffer[512];
    ViChar*		p2buffer = send_buffer;
    ViInt32		value = 0;
    
    p2buffer += sprintf(p2buffer, ":STAT:");
    switch (statusRegistersQuery)
    {
    case AGENA_READ_STATUS_OPERATION:
    	p2buffer += sprintf(p2buffer, "OPER?");
    	break;
    
    case AGENA_READ_STATUS_OPERATION_CONDITION:
    	p2buffer += sprintf(p2buffer, "OPER:COND?");
    	break;
    
    case AGENA_READ_STATUS_QUES:
    	p2buffer += sprintf(p2buffer, "QUES?");
    	break;
    
    case AGENA_READ_STATUS_QUES_CONDITION:
    	p2buffer += sprintf(p2buffer, "QUES:COND?");
    	break;
    
    case AGENA_READ_STATUS_QUES_LIMIT:
    	p2buffer += sprintf(p2buffer, "QUES:LIM?");
    	break;
    
    case AGENA_READ_STATUS_QUES_LIMIT_CONDITION:
    	p2buffer += sprintf(p2buffer, "QUES:LIM:COND?");
    	break;
    
    case AGENA_READ_STATUS_QUES_LIMIT_EXTRA:
    	p2buffer += sprintf(p2buffer, "QUES:LIM:ELIM?");
    	break;
    
    case AGENA_READ_STATUS_QUES_LIMIT_EXTRA_COND:
    	p2buffer += sprintf(p2buffer, "QUES:LIM:ELIM:COND?");
    	break;
    
    case AGENA_READ_STATUS_QUES_LIMIT_CHANNEL:
    	p2buffer += sprintf(p2buffer, "QUES:LIM:CHAN%ld?", channel);
    	break;
    
    case AGENA_READ_STATUS_QUES_LIMIT_CHANNEL_COND:
    	p2buffer += sprintf(p2buffer, "QUES:LIM:CHAN%ld:COND?", channel);
    	break;
    
    case AGENA_READ_STATUS_QUES_LIMIT_CH_EXTRA:
    	p2buffer += sprintf(p2buffer, "QUES:LIM:CHAN%ld:ECH?", channel);
    	break;
    
    case AGENA_READ_STATUS_QUES_LIMIT_CH_EXTRA_COND:
    	p2buffer += sprintf(p2buffer, "QUES:LIM:CHAN%ld:ECH:COND?", channel);
    	break;
    
    }
    
Error:
	return agena_status;
}

ViStatus _VI_FUNC agena_setCheckStatus (
	ViSession	instrumentHandle,
	ViBoolean	checkStatus
)
{
    ViStatus			agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;

    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));

    instrPtr -> errorChecking = checkStatus;

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Set Time Out                                                    */
/* Purpose:  Sets a minimum timeout value for driver I/O transactions in     */
/*           milliseconds. The timeout period may vary on computer platforms.*/
/*===========================================================================*/
ViStatus _VI_FUNC agena_setTimeOut (ViSession instrumentHandle, ViInt32 timeout)
{
    ViStatus    agena_status = VI_SUCCESS;

    CHECKERR (viSetAttribute (instrumentHandle, VI_ATTR_TMO_VALUE, timeout));

Error:
	return agena_status;
}

/*===========================================================================*/
/* Function: Get Time Out                                                    */
/* Purpose:  Returns the timeout value for driver I/O transactions in        */
/*           milliseconds.                                                   */
/*                                                                           */
/*           The timeout period may vary on computer platforms.              */
/*===========================================================================*/
ViStatus _VI_FUNC agena_getTimeOut (ViSession instrumentHandle, ViPInt32 timeout)
{
    ViStatus    agena_status = VI_SUCCESS;
    
    if (timeout != NULL)  
	    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_TMO_VALUE, timeout));
Error:
	return agena_status;
}
 
/*===========================================================================*/
/* Function: Wait for OPC                                                    */
/* Purpose:  This function sends a command to the instrument and waits until */
/*           the instrument response is available (queries MAV in STB).      */
/*===========================================================================*/
ViStatus agena_waitOPC (ViSession instrumentHandle, ViPString command,
                ViPString instrResp, ViInt32 timeout)
{
    ViStatus agena_status = VI_SUCCESS;
    ViInt16 response = 0;
    ViInt32 counter = 0;
    ViInt32 oldTimeout = 0;
    ViUInt16 interface = VI_INTF_GPIB;

    CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_INTF_TYPE, &interface));

    /* Interface specific operations */
    switch (interface)
        {
        case VI_INTF_ASRL: /* Serial interface */
            CHECKERR (viGetAttribute (instrumentHandle, VI_ATTR_TMO_VALUE, &oldTimeout));
            CHECKERR (viSetAttribute (instrumentHandle, VI_ATTR_TMO_VALUE, timeout));
             /* "\n" is appended in the passed buffer, do not include it here */
            if ((agena_status = viQueryf (instrumentHandle, "%s", "%[^\r\n]", command, instrResp)) < 0)
                {
                viSetAttribute (instrumentHandle, VI_ATTR_TMO_VALUE, oldTimeout);
                return agena_status;
                }
            CHECKERR (viSetAttribute (instrumentHandle, VI_ATTR_TMO_VALUE, oldTimeout));
        break;
        default: /* Default case */

            /* "\n" is appended in the passed buffer, do not include it here */
            CHECKERR (viPrintf (instrumentHandle, "%s", command));

            while (!(response & 0x10)) /* (queries MAV in STB) */
                {

                CHECKERR (viReadSTB (instrumentHandle, &response));

                agena_delay (0.005);
                counter+= 5;
                if (counter >= timeout)
                    return VI_ERROR_TMO;
                }

            CHECKERR (viScanf (instrumentHandle, "%[^\r\n]", instrResp));
        break;
        }

Error:
	return agena_status;
}


/*===========================================================================*/
/* Function: Write To Instrument
/* Purpose:  This function writes commands and queries to the instrument to 
/*           modify parameters and query device settings.
/*===========================================================================*/
ViStatus _VI_FUNC agena_writeInstrData (
	ViSession	instrumentHandle,
	ViString	writeBuffer
)
{
    ViStatus	agena_status = VI_SUCCESS;

    CHECKERR (viPrintf (instrumentHandle, "%s\n", writeBuffer));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Read Instrument Data
/* Purpose:  This function reads data from the instrument's output buffer 
/*           and returns it to the specified variable in memory.
/*           
/*           Notes:
/*           
/*           (1) Because the instrument may return both numeric and text 
/*           data in response to queries this function returns the data in 
/*           string format.
/*           
/*           (2) If valid data is not available at the instrument's output 
/*           buffer when this function is called the instrument will hang up 
/*           and the function will not return until it times out.  If the 
/*           time-out is disabled this function will hang indefinitely and it 
/*           may be necessary to reboot the computer to break out.
/*===========================================================================*/
ViStatus _VI_FUNC agena_readInstrData (
	ViSession	instrumentHandle,
	ViInt32		numberBytesToRead,
	ViChar		readBuffer[],
	ViInt32*	numBytesRead
)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViUInt32    tmpCnt;

    if (numBytesRead)
        *numBytesRead = 0L;

    CHECKERR (viRead (instrumentHandle, (ViBuf)readBuffer, numberBytesToRead, &tmpCnt));

    if (numBytesRead)
        *numBytesRead = (ViInt32)tmpCnt;

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Reset
/* Purpose:  This function resets the instrument to a known state and sends 
/*           initialization commands to the instrument that set any necessary 
/*           programmatic variables such as Headers Off, Short Command form, 
/*           and Data Transfer Binary to the state necessary for the 
/*           operation of the instrument driver.
/*===========================================================================*/
ViStatus _VI_FUNC agena_reset (ViSession instrumentHandle)
{
	ViStatus	agena_status = VI_SUCCESS;
	
    /*  Initialize the instrument to a known state.  */
    CHECKERR (viPrintf (instrumentHandle, "*RST\n"));
    CHECKERR (agena_defaultInstrSetup (instrumentHandle));

Error:
	return agena_status;
}

/*===========================================================================*/
/* Function: Self-Test
/* Purpose:  This function runs the instrument's self test routine and 
/*           returns the test result(s).
/*           
/*           Note:
/*           
/*           (1) When is Self-Test Failed you read your manual.
/*===========================================================================*/
ViStatus _VI_FUNC agena_self_test (
	ViSession	instrumentHandle,
	ViInt16*	selfTestResult,
	ViChar		selfTestMessage[]
)
{
    *selfTestResult = 0;
    strcpy(selfTestMessage, "Passed");
    
    return VI_WARN_NSUP_SELF_TEST;
}

/*===========================================================================*/
/* Function: Error-Query
/* Purpose:  This function reads an error code from the instrument's error 
/*           queue.
/*===========================================================================*/
ViStatus _VI_FUNC agena_error_query (
	ViSession	instrumentHandle,
	ViInt32*	errorCode,
	ViChar		errorMessage[]
)
{
    ViStatus agena_status = VI_SUCCESS;

    CHECKERR (viPrintf (instrumentHandle, ":SYST:ERR?\n"));
    CHECKERR (viScanf (instrumentHandle, "%ld,\"%[^\"]", errorCode, errorMessage));

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Error Message
/* Purpose:  This function takes the Status Code returned by the instrument 
/*           driver functions, interprets it and returns it as a user 
/*           readable string. 
/*===========================================================================*/
ViStatus _VI_FUNC agena_error_message (
	ViSession	instrumentHandle,
	ViStatus	statusCode,
	ViChar		message[]
)
{
    ViStatus	agena_status = VI_SUCCESS;
    ViInt16		i;

    static agena_tStringValPair statusDescArray[] = {
        {VI_WARN_NSUP_ID_QUERY,     "WARNING: ID Query not supported"},
        {VI_WARN_NSUP_RESET,        "WARNING: Reset not supported"},
        {VI_WARN_NSUP_SELF_TEST,    "WARNING: Self-test not supported"},
        {VI_WARN_NSUP_ERROR_QUERY,  "WARNING: Error Query not supported"},
        {VI_WARN_NSUP_REV_QUERY,    "WARNING: Revision Query not supported"},
        {VI_ERROR_PARAMETER1,   "ERROR: Parameter 1 out of range"},
        {VI_ERROR_PARAMETER2,   "ERROR: Parameter 2 out of range"},
        {VI_ERROR_PARAMETER3,   "ERROR: Parameter 3 out of range"},
        {VI_ERROR_PARAMETER4,   "ERROR: Parameter 4 out of range"},
        {VI_ERROR_PARAMETER5,   "ERROR: Parameter 5 out of range"},
        {VI_ERROR_PARAMETER6,   "ERROR: Parameter 6 out of range"},
        {VI_ERROR_PARAMETER7,   "ERROR: Parameter 7 out of range"},
        {VI_ERROR_PARAMETER8,   "ERROR: Parameter 8 out of range"},
        {VI_ERROR_FAIL_ID_QUERY,"ERROR: Identification query failed"},
        {VI_ERROR_INV_RESPONSE, "ERROR: Interpreting instrument response"},
        {VI_ERROR_INSTR_FILE_OPEN,    "ERROR: Opening the specified file"},
        {VI_ERROR_INSTR_FILE_WRITE,   "ERROR: Writing to the specified file"},
        {VI_ERROR_INSTR_INTERPRETING_RESPONSE, "ERROR: Interpreting the instrument's response"},
        {VI_ERROR_INSTR_PARAMETER9 ,  "ERROR: Parameter 9 out of range"},
        {VI_ERROR_INSTR_PARAMETER10,  "ERROR: Parameter 10 out of range"},
        {VI_ERROR_INSTR_PARAMETER11,  "ERROR: Parameter 11 out of range"},
        {VI_ERROR_INSTR_PARAMETER12,  "ERROR: Parameter 12 out of range"},
        {VI_ERROR_INSTR_PARAMETER13,  "ERROR: Parameter 13 out of range"},
        {VI_ERROR_INSTR_PARAMETER14,  "ERROR: Parameter 14 out of range"},
        {VI_ERROR_INSTR_PARAMETER15,  "ERROR: Parameter 15 out of range"},

        {AGENA_ERROR_INSTRUMENT_ERROR,         "ERROR: Instrument status error"},
        {AGENA_ERROR_INSTRUMENT_OPTION,        "ERROR: Option not installed"},
        {AGENA_ERROR_INSTRUMENT_DATA_NOT_AVAILABLE, "ERROR: Data are not available."},
        {AGENA_ERROR_INSTRUMENT_CONFLICT,      "ERROR: Instrument settings conflict."},
        {AGENA_ERROR_INSTR_UNKNOWN_OPTION,     "ERROR: Unknown option."},
        {AGENA_ERROR_CALIBRATION_FAILED,       "ERROR: Calibration failed."},
        {AGENA_ERROR_COMPATIBILITY_ERROR,      "ERROR: Compatibility error."},
        {AGENA_ERROR_INSTRUMENT_IQ_OVERLOAD,   "ERROR: Instrument IQ overload."},
        {AGENA_ERROR_NSUP_FEATURE,      	   "ERROR: Non supported feature."},
        {AGENA_ERROR_INVALID_TRIGGER_SOURCE,   "ERROR: Invalid trigger source."},

        {VI_NULL, VI_NULL}
    };

    agena_status = viStatusDesc (instrumentHandle, statusCode, message);
    if (agena_status == VI_WARN_UNKNOWN_STATUS)
        {
        for (i = 0; statusDescArray[i].stringName; i++)
            {
            if (statusDescArray[i].stringVal == statusCode)
                {
                sprintf (message, "%s", statusDescArray[i].stringName);
                return (VI_SUCCESS);
                }
            }
        sprintf (message, "Unknown Error 0x%X", statusCode);
        return (VI_WARN_UNKNOWN_STATUS);
        }

    agena_status = VI_SUCCESS;
    return agena_status;
}

/*===========================================================================*/
/* Function: Revision Query
/* Purpose:  This function returns the revision numbers of the instrument 
/*           driver and instrument firmware, and tells the user with which  
/*           instrument firmware this revision of the driver is compatible. 
/*           
/*           This instrument driver's Revision Number is "Rev 1.0, 
/*           02/2005, CVI 7.0" and is compatible with Instrument Firmware 
/*           Revision "A.04.00" and higher.
/*           
/*===========================================================================*/
ViStatus _VI_FUNC agena_revision_query (
	ViSession	instrumentHandle,
	ViChar		instrumentDriverRevision[],
	ViChar		firmwareRevision[]
)
{
    ViStatus agena_status = VI_SUCCESS;

    CHECKERR (viPrintf (instrumentHandle, "*IDN?\n"));
    CHECKERR (viScanf (instrumentHandle, "%*[^,],%*[^,],%*[^,],%[^\r\n]",
    				   firmwareRevision));

    sprintf (instrumentDriverRevision, "%s", AGENA_REVISION);

Error:
    return agena_status;
}

/*===========================================================================*/
/* Function: Close
/* Purpose:  This function performs the following operations:
/*           viClose (instrSession) and viClose (rmSession).
/*           
/*           Notes:
/*           
/*           (1) The instrument must be reinitialized to use it again.
/*===========================================================================*/
ViStatus _VI_FUNC agena_close (ViSession instrumentHandle)
{
    ViStatus    		agena_status = VI_SUCCESS;
    agena_instrRange	instrPtr;
    
    viGetAttribute(instrumentHandle, VI_ATTR_USER_DATA, &instrPtr);
    
    if (instrPtr != NULL)
    	free(instrPtr);
    
    if (instrumentHandle != NULL)
    {
        CHECKERR( viClose(instrumentHandle));
    }

Error:
    return agena_status;
}


/*****************************************************************************/
/*= UTILITY ROUTINES (Non-Exportable Functions) =============================*/
/*****************************************************************************/

/*===========================================================================*/
/* Function: Boolean Value Out Of Range - ViBoolean                          */
/* Purpose:  This function checks a Boolean to see if it is equal to VI_TRUE */
/*           or VI_FALSE. If the value is out of range, the return value is  */
/*           VI_TRUE, otherwise the return value is VI_FALSE.                */
/*===========================================================================*/
ViBoolean agena_invalidViBooleanRange (ViBoolean val)
{
    return ((val != VI_FALSE && val != VI_TRUE) ? VI_TRUE : VI_FALSE);
}

/*===========================================================================*/
/* Function: Long Signed Integer Value Out Of Range - ViInt32                */
/* Purpose:  This function checks a long signed integer value to see if it   */
/*           lies between a minimum and maximum value.  If the value is out  */
/*           of range, the return value is VI_TRUE, otherwise the return     */
/*           value is VI_FALSE.                                              */
/*===========================================================================*/
ViBoolean agena_invalidViInt32Range (ViInt32 val, ViInt32 min, ViInt32 max)
{
    return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*===========================================================================*/
/* Function: Real (Double) Value Out Of Range - ViReal64                     */
/* Purpose:  This function checks a real (double) value to see if it lies    */
/*           between a minimum and maximum value.  If the value is out of    */
/*           range, the return value is VI_TRUE, otherwise the return value  */
/*           is VI_FALSE.                                                    */
/*===========================================================================*/
ViBoolean agena_invalidViReal64Range (ViReal64 val, ViReal64 min, ViReal64 max)
{
    return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*===========================================================================*/
/* Function: Check String                                                    */
/* Purpose:  This function checks a string value to see if it is             */
/*           of a defined length and initialized.                            */
/*===========================================================================*/
ViBoolean agena_invalidViString (ViString val, ViUInt32 maxLength)
{
    if (val)
        {
        if (strlen (val) > maxLength)
            return VI_TRUE;
        else
            return VI_FALSE;
        }

    return VI_TRUE;
}

/*===========================================================================*/
/* Function: Is In String Table                                              */
/* Purpose:  This function checks a string value to see if it is             */
/*           in specific string table.                                       */
/*===========================================================================*/
ViBoolean agena_isInStringTable (
    ViString            modelString,
    SStringTableEntry   stringTable[]
)
{
    SStringTableEntry*  table_entry = stringTable;
    
    while (table_entry->modelString != NULL)
    {
        if (!strcmp(modelString, table_entry->modelString))
            return VI_TRUE;

        table_entry++;
    }
    
    return VI_FALSE;
}

/*===========================================================================*/
/* Function: Get Model Index From String Table                               */
/* Purpose:  This function find model value in string table and return      */
/*           index of this value.                                            */
/*===========================================================================*/
ViInt32 agena_getModelIndex (
    ViString            modelString,
    SStringTableEntry   stringTable[]
)
{
	ViInt32		index = 0;
    SStringTableEntry*  table_entry = stringTable;
    
	while (table_entry->modelString != NULL)
	{
		if (!strcmp(modelString, table_entry->modelString))
		{
			return index;
		}
		table_entry++;
	}
	
	return -1;
}

/*===========================================================================*/
/* Function: Get Value Index From String Table                               */
/* Purpose:  This function find string value in string table and return      */
/*           index of this value.                                            */
/*===========================================================================*/
ViInt32 agena_getValueIndex (
    ViString            stringValue,
    ViString			stringTable[]
)
{
	ViInt32		index = 0;
	ViString	table_entry = stringTable[0];
	
	while (table_entry != NULL)
	{
		if (!strcmp(stringValue, table_entry))
		{
			return index;
		}
		table_entry = stringTable[++index];
	}
	
	return -1;
}

/*===========================================================================*/
/* Function: Read Data With Unknown length                                   */
/* Purpose:  This function allocates buffer and reads data from the          */
/*           instrument                                                      */
/* WARNING:  You must deallocate buffer, if any pointer has been returned.   */
/*           This function does not work correctly, when you read bin data   */
/*           via serial interface                                            */
/*===========================================================================*/
ViStatus agena_readDataUnknownLength(
	ViSession	instrSession,
	ViChar**	outBuffer,
	ViUInt32*	count
)
{
    ViStatus agena_status = VI_SUCCESS;
    ViUInt32 actSize, retCnt = 0;
    ViChar   *buffer = VI_NULL, *p2buffer;

    *outBuffer = VI_NULL;
    if (count) *count = 0;

    /* Allocate Buffer */
    actSize = BUFFER_SIZE;
    buffer = (ViChar *)calloc(actSize, sizeof(ViChar));
    if (buffer == VI_NULL) return VI_ERROR_ALLOC;

    p2buffer = buffer;
    do
        {
        if ((agena_status = viRead (instrSession, (ViPBuf)p2buffer, BUFFER_SIZE, &retCnt)) < 0)
            {
            free(buffer);
            *outBuffer = VI_NULL;
            return agena_status;
            }
        if (retCnt == BUFFER_SIZE) /* Buffer was small, reallocate it */
        {
            actSize += BUFFER_SIZE;
            buffer = (ViChar *)realloc(buffer, actSize);
            if (buffer == VI_NULL) return VI_ERROR_ALLOC;
            p2buffer = buffer + (actSize - BUFFER_SIZE); /* Set pointer to end of data in rallocated buffer */
        }
        else
        {
            *(p2buffer+retCnt) = '\0'; /* For sure set end of string at the end of data */
        }
       } while (agena_status == VI_SUCCESS_MAX_CNT); /* if buffer was small, continue with next read */

    *outBuffer = buffer;
    if (count) *count = (actSize - BUFFER_SIZE) + retCnt;

    return agena_status;
}

/*****************************************************************************
 * Function: RemoveSurroundingWhiteSpace
 * Purpose:  This function removes surrounding white space around a string
 *****************************************************************************/
static void RemoveSurroundingWhiteSpace(ViChar string[])
{
    ViChar  *start = string,
            *end;
    ViInt32 lengthWithoutLeadingWS;

    if (start)
        {
        while (*start && isspace((unsigned char)*start))
            start++;

        lengthWithoutLeadingWS = strlen( start);
        memmove( string, start, lengthWithoutLeadingWS);
        end = string + lengthWithoutLeadingWS;
        while (end > string && isspace((unsigned char)*(end-1)))
            end--;
        
        *end = '\0';
        }
}

/*===========================================================================*/
/* Function: Delay
/* Purpose : With a call to rsupv_delay, the current program is suspended
/*           from execution for the number of seconds specified by the
/*           argument seconds. rsupv_delay is accurate to a millisecond.
/*           This function is platform independent.
/*===========================================================================*/
void agena_delay (ViReal64 numberOfSeconds)
{
  clock_t StartTime = clock();

  while ((((double)(clock() - StartTime))/CLOCKS_PER_SEC) < (numberOfSeconds));

  return;
}

/*****************************************************************************/
/*------------------ INSTRUMENT-DEPENDENT UTILITY ROUTINES ------------------*/
/*****************************************************************************/

/*===========================================================================*/
/* Function: Default Instrument Setup                                        */
/* Purpose:  This function sends a default setup to the instrument.  This    */
/*           function is called by the agena_reset operation and by the      */
/*           agena_init function if the reset option has not been            */
/*           selected. This function is useful for configuring any           */
/*           instrument settings that are required by the rest of the        */
/*           instrument driver functions such as turning headers ON or OFF   */
/*           or using the long or short form for commands, queries, and data.*/
/*===========================================================================*/
ViStatus agena_defaultInstrSetup (ViSession instrSession)
{
    ViStatus			agena_status = VI_SUCCESS;
    ViChar				buffer[BUFFER_SIZE];
	agena_instrRange	instrPtr;

    /* Determine if the structure has been initialized for the current VISA  */
    /* Session and malloc if it has not.                                     */
    CHECKERR (viGetAttribute (instrSession, VI_ATTR_USER_DATA, &instrPtr));

    /*
        Following two ViInt32 variables are used to store information about
        currently connected instrument and its options. Each bit represents
        one instrument model or option.
    */
    
    instrPtr->numChannels = 0;
    instrPtr->numPorts = 0;
    instrPtr->numTraces = 0;
    /* --- */
    instrPtr -> errorChecking = VI_FALSE;
    strcpy (instrPtr -> instrDriverRevision, AGENA_REVISION);
    
    CHECKERR( agena_actSystemInfo(instrSession, &instrPtr->numChannels,
    							  &instrPtr->numTraces, &instrPtr->numPorts,
    							  &instrPtr->systemVersion));
    
    instrPtr -> errorChecking = VI_TRUE;

    /* Default Instrument Setup String - Data Format */
    /* If not under development CHANGE to ":SYST:DISP:UPD OFF" */

    CHECKERR (viPrintf (instrSession, "*CLS;:FORM:DATA ASC;*ESE 60;:DISP:ENAB OFF\n"));
    
Error:    
    return agena_status;
}

ViStatus agena_checkStatus(ViSession instrumentHandle)
{
    ViStatus    agena_status = VI_SUCCESS;
    ViInt32     esrByte;
    ViInt32     ret_cnt;
    ViChar      buffer[1024];
    agena_instrRange	instrPtr;
    
    CHECKERR( viGetAttribute(instrumentHandle, VI_ATTR_USER_DATA, &instrPtr));
    
    if (instrPtr -> errorChecking) { /* Is Error Checking Enabled? */
        /*--------------- Read the Standard Event Register --------------------*/
        CHECKERR (viQueryf (instrumentHandle, "*ESR?\n", "%ld", &esrByte));
        
        /*---------------- Check if any error or message bit was asserted -------*/
        if ((esrByte & 0x3C) != 0)
            agena_status = AGENA_ERROR_INSTRUMENT_ERROR;
        else
            agena_status = VI_SUCCESS;
    }
    
Error:
    return agena_status;
}
