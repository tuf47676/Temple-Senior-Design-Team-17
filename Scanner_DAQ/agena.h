#include <cvidef.h>

#include <vpptype.h>

/*****************************************************************************/
/*= Instrument Driver Specific Error/Warning Codes ==========================*/
/*****************************************************************************/
#define VI_ERROR_INSTR_FILE_OPEN                (_VI_ERROR+0x3FFC0800L)
#define VI_ERROR_INSTR_FILE_WRITE               (_VI_ERROR+0x3FFC0801L)
#define VI_ERROR_INSTR_INTERPRETING_RESPONSE    (_VI_ERROR+0x3FFC0803L)
#define VI_ERROR_INSTR_PARAMETER9               (_VI_ERROR+0x3FFC0809L)
#define VI_ERROR_INSTR_PARAMETER10              (_VI_ERROR+0x3FFC080AL)
#define VI_ERROR_INSTR_PARAMETER11              (_VI_ERROR+0x3FFC080BL)
#define VI_ERROR_INSTR_PARAMETER12              (_VI_ERROR+0x3FFC080CL)
#define VI_ERROR_INSTR_PARAMETER13              (_VI_ERROR+0x3FFC080DL)
#define VI_ERROR_INSTR_PARAMETER14              (_VI_ERROR+0x3FFC080EL)
#define VI_ERROR_INSTR_PARAMETER15              (_VI_ERROR+0x3FFC080FL)
#define VI_ERROR_INSTR_PARAMETER16              (_VI_ERROR+0x3FFC0810L)
#define VI_ERROR_INSTR_PARAMETER17              (_VI_ERROR+0x3FFC0811L)
#define VI_ERROR_INSTR_PARAMETER18              (_VI_ERROR+0x3FFC0812L)
#define AGENA_WARNING_SMALL_BUFFER

/*****************************************************************************/
/*======== Instrument Specific Error/Warning Codes ==========================*/
/*****************************************************************************/
#define VI_WARNING_INSTR_OFFSET                           (0x3FFC0900L)
#define VI_ERROR_INSTR_OFFSET                   (_VI_ERROR+0x3FFC0900L)

#define AGENA_ERROR_INSTRUMENT_ERROR            (VI_ERROR_INSTR_OFFSET + 0xF0L)
#define AGENA_ERROR_INSTRUMENT_OPTION           (VI_ERROR_INSTR_OFFSET + 0xF1L)
#define AGENA_ERROR_INSTRUMENT_CONFLICT         (VI_ERROR_INSTR_OFFSET + 0xF2L)
#define AGENA_ERROR_INSTRUMENT_DATA_NOT_AVAILABLE   (VI_ERROR_INSTR_OFFSET + 0xF3L)
#define AGENA_ERROR_INSTR_UNKNOWN_OPTION        (VI_ERROR_INSTR_OFFSET + 0xF4L)
#define AGENA_ERROR_CALIBRATION_FAILED          (VI_ERROR_INSTR_OFFSET + 0xF5L)
#define AGENA_ERROR_COMPATIBILITY_ERROR         (VI_ERROR_INSTR_OFFSET + 0xF6L)
#define AGENA_ERROR_INSTRUMENT_IQ_OVERLOAD      (VI_ERROR_INSTR_OFFSET + 0xF7L)
#define AGENA_ERROR_NSUP_FEATURE                (VI_ERROR_INSTR_OFFSET + 0xF8L)
#define AGENA_ERROR_INVALID_TRIGGER_SOURCE      (VI_ERROR_INSTR_OFFSET + 0xF9L)

/*****************************************************************************/
/*= INSTRUMENT CONSTANT =====================================================*/
/*****************************************************************************/

/*- fuction agena_confChannelTrace control Measurement Parameter -*/
#define AGENA_MEASUREMENT_PARAMETER_S11             0
#define AGENA_MEASUREMENT_PARAMETER_S21             1
#define AGENA_MEASUREMENT_PARAMETER_S31             2
#define AGENA_MEASUREMENT_PARAMETER_S41             3
#define AGENA_MEASUREMENT_PARAMETER_S12             4
#define AGENA_MEASUREMENT_PARAMETER_S22             5
#define AGENA_MEASUREMENT_PARAMETER_S32             6
#define AGENA_MEASUREMENT_PARAMETER_S42             7
#define AGENA_MEASUREMENT_PARAMETER_S13             8
#define AGENA_MEASUREMENT_PARAMETER_S23             9
#define AGENA_MEASUREMENT_PARAMETER_S33             10
#define AGENA_MEASUREMENT_PARAMETER_S43             11
#define AGENA_MEASUREMENT_PARAMETER_S14             12
#define AGENA_MEASUREMENT_PARAMETER_S24             13
#define AGENA_MEASUREMENT_PARAMETER_S34             14
#define AGENA_MEASUREMENT_PARAMETER_S44             15
#define AGENA_MEASUREMENT_PARAMETER_A               16
#define AGENA_MEASUREMENT_PARAMETER_B               17
#define AGENA_MEASUREMENT_PARAMETER_C               18
#define AGENA_MEASUREMENT_PARAMETER_D               19
#define AGENA_MEASUREMENT_PARAMETER_R1              20
#define AGENA_MEASUREMENT_PARAMETER_R2              21
#define AGENA_MEASUREMENT_PARAMETER_R3              22
#define AGENA_MEASUREMENT_PARAMETER_R4              23

/*- fuction agena_confChannelTrace control Data Format -*/
#define AGENA_FORMAT_LOG_MAGNITUDE                  0
#define AGENA_FORMAT_PHASE                          1
#define AGENA_FORMAT_GROUP_DELAY                    2
#define AGENA_FORMAT_SMITH_LINEAR                   3
#define AGENA_FORMAT_SMITH_LOGARITHMIC              4
#define AGENA_FORMAT_SMITH_COMPLEX                  5
#define AGENA_FORMAT_SMITH_IMPEDANCE                6
#define AGENA_FORMAT_SMITH_ADMITTANCE               7
#define AGENA_FORMAT_POLAR_LINEAR                   8
#define AGENA_FORMAT_POLAR_LOGARITHMIC              9
#define AGENA_FORMAT_POLAR_COMPLEX                  10
#define AGENA_FORMAT_LINEAR_MAGNITUDE               11
#define AGENA_FORMAT_SWR                            12
#define AGENA_FORMAT_REAL                           13
#define AGENA_FORMAT_IMAGINARY                      14
#define AGENA_FORMAT_EXPANDED_PHASE                 15
#define AGENA_FORMAT_POSITIVE_PHASE                 16

/*- fuction agena_confStimulus control Stimulus -*/
#define AGENA_STIMULUS_START                        0
#define AGENA_STIMULUS_STOP                         1
#define AGENA_STIMULUS_CENTER                       2
#define AGENA_STIMULUS_SPAN                         3

/*- fuction agena_confStimulus control Parameter -*/
#define AGENA_STIMULUS_PARAMETER_TIME_AUTO          (-1)

/*- fuction agena_confStimulus control Parameter -*/
#define AGENA_STIMULUS_UNITS_HZ                     0
#define AGENA_STIMULUS_UNITS_KHZ                    1
#define AGENA_STIMULUS_UNITS_MHZ                    2
#define AGENA_STIMULUS_UNITS_GHZ                    3
#define AGENA_STIMULUS_UNITS_DBM                    4
#define AGENA_STIMULUS_UNITS_DB                     5
#define AGENA_STIMULUS_UNITS_S                      6   

/*- fuction agena_confSweep control Sweep Mode -*/
#define AGENA_SWEEP_MODE_STEPPED                    0
#define AGENA_SWEEP_MODE_ANALOG                     1
#define AGENA_SWEEP_MODE_FSTEPPED                   2
#define AGENA_SWEEP_MODE_FANALOG                    3

/*- fuction agena_confSweep control Sweep Mode -*/
#define AGENA_SWEEP_TYPE_LINEAR                     0
#define AGENA_SWEEP_TYPE_LOGARITHMIC                1
#define AGENA_SWEEP_TYPE_SEGMENT                    2
#define AGENA_SWEEP_TYPE_POWER                      3

/*- fuction agena_confSweepSegments control Stimulus Mode -*/
#define AGENA_SWEEP_SEGMENT_MODE_START              0
#define AGENA_SWEEP_SEGMENT_MODE_CENTER             1

/*- fuction agena_confXAxisFreq control X Axis Freq -*/
/*- fuction agena_confFreqOffset control X Axis Freq -*/
#define AGENA_XAXIS_FREQUENCY_NORMAL                0
#define AGENA_XAXIS_FREQUENCY_RF_PLUS_LO            1
#define AGENA_XAXIS_FREQUENCY_RF_MINUS_LO           2
#define AGENA_XAXIS_FREQUENCY_LO_MINUS_RF           3
#define AGENA_XAXIS_FREQUENCY_BASE                  4
#define AGENA_XAXIS_FREQUENCY_STIMULUS              5
#define AGENA_XAXIS_FREQUENCY_RESPONSE              6

/*- fuction agena_confDisplayLayout control Graph Layout -*/
#define AGENA_DISPLAY_LAYOUT_D1                     0
#define AGENA_DISPLAY_LAYOUT_D12                    1
#define AGENA_DISPLAY_LAYOUT_D1_2                   2
#define AGENA_DISPLAY_LAYOUT_D112                   3
#define AGENA_DISPLAY_LAYOUT_D1_1_2                 4
#define AGENA_DISPLAY_LAYOUT_D123                   5
#define AGENA_DISPLAY_LAYOUT_D1_2_3                 6
#define AGENA_DISPLAY_LAYOUT_D12_33                 7
#define AGENA_DISPLAY_LAYOUT_D11_23                 8
#define AGENA_DISPLAY_LAYOUT_D13_23                 9
#define AGENA_DISPLAY_LAYOUT_D12_13                 10
#define AGENA_DISPLAY_LAYOUT_D1234                  11
#define AGENA_DISPLAY_LAYOUT_D1_2_3_4               12
#define AGENA_DISPLAY_LAYOUT_D12_34                 13
#define AGENA_DISPLAY_LAYOUT_D123_456               14
#define AGENA_DISPLAY_LAYOUT_D12_34_56              15
#define AGENA_DISPLAY_LAYOUT_D1234_5678             16
#define AGENA_DISPLAY_LAYOUT_D12_34_56_78           17
#define AGENA_DISPLAY_LAYOUT_D123_456_789           18
#define AGENA_DISPLAY_LAYOUT_D123__ABC              19
#define AGENA_DISPLAY_LAYOUT_D1234__9ABC            20
#define AGENA_DISPLAY_LAYOUT_D1234__CDEF            21

/*- fuction agena_confDisplay control Display Type -*/
/*- fuction agena_confDisplayColor control Display Type -*/
#define AGENA_DISPLAY_TYPE_NORMAL                   0
#define AGENA_DISPLAY_TYPE_INVERT                   1

/*- fuction agena_confDisplay control Table Type -*/
#define AGENA_DISPLAY_TABLE_TYPE_MARKER             0
#define AGENA_DISPLAY_TABLE_TYPE_LIMIT              1
#define AGENA_DISPLAY_TABLE_TYPE_SEGMENT            2
#define AGENA_DISPLAY_TABLE_TYPE_ECHO               3
#define AGENA_DISPLAY_TABLE_TYPE_PLOSS              4
#define AGENA_DISPLAY_TABLE_TYPE_SCFACTOR           5

/*- fuction agena_confTraceDisplay control Trace Display -*/
#define AGENA_DISPLAY_TRACE_NORMAL                  0
#define AGENA_DISPLAY_TRACE_ADD                     1
#define AGENA_DISPLAY_TRACE_SUBTRACT                2
#define AGENA_DISPLAY_TRACE_MULTIPLY                3
#define AGENA_DISPLAY_TRACE_DIVIDE                  4

/*- fuction agena_confXAxisSegmentSweep control Display Method -*/
#define AGENA_DISPLAY_XAXIS_LINEAR                  0
#define AGENA_DISPLAY_XAXIS_ORDER_BASE              1

/*- fuction agena_confDisplayColor control Setting -*/
#define AGENA_DISPLAY_COLOR_DATA_TRACE				0
#define AGENA_DISPLAY_COLOR_MEMORY_TRACE			1
#define AGENA_DISPLAY_COLOR_GRAPH_OUTER_FRAME		2
#define AGENA_DISPLAY_COLOR_GRAPH_GRID_LINE			3
#define AGENA_DISPLAY_COLOR_LIMIT_TEST_RESULT		4
#define AGENA_DISPLAY_COLOR_LIMIT_LINE				5
#define AGENA_DISPLAY_COLOR_BACKGROUND				6

/*- fuction agena_confCal control Cal Type -*/
#define AGENA_CALIBRATION_TYPE_OPEN                 0
#define AGENA_CALIBRATION_TYPE_SHORT                1
#define AGENA_CALIBRATION_TYPE_THROUGH              2
#define AGENA_CALIBRATION_TYPE_1_PORT               3
#define AGENA_CALIBRATION_TYPE_2_PORT               4
#define AGENA_CALIBRATION_TYPE_3_PORT               5
#define AGENA_CALIBRATION_TYPE_4_PORT               6
#define AGENA_CALIBRATION_TYPE_EN_RESPONSE			7

/*- fuction agena_confCalKitStandard control Type -*/
/*- fuction agena_confCalKitClass control Type -*/
#define AGENA_CALIB_STANDARD_OPEN                   0
#define AGENA_CALIB_STANDARD_SHORT                  1
#define AGENA_CALIB_STANDARD_LOAD                   2
#define AGENA_CALIB_STANDARD_THRU                   3
#define AGENA_CALIB_STANDARD_ARBI                   4
#define AGENA_CALIB_STANDARD_NONE                   5

/*- fuction agena_confECal control Characterization -*/
#define AGENA_ECAL_CHARACTERIZATION_CHAR0           0
#define AGENA_ECAL_CHARACTERIZATION_CHAR1           1
#define AGENA_ECAL_CHARACTERIZATION_CHAR2           2
#define AGENA_ECAL_CHARACTERIZATION_CHAR3           3
#define AGENA_ECAL_CHARACTERIZATION_CHAR4           4
#define AGENA_ECAL_CHARACTERIZATION_CHAR5           5

/*- fuction agena_confPowCal control Power Sensor -*/
/*- fuction agena_actMeasurePowerCalData control Sensor -*/
/*- fuction agena_actMeasureScalarCalData control Sensor -*/
#define AGENA_POWER_CALIBRATION_SENSOR_A            0
#define AGENA_POWER_CALIBRATION_SENSOR_B            1

/*- fuction agena_confScalarCal control Method -*/
#define AGENA_SCALAR_MIXER_CALIB_1_PORT             0
#define AGENA_SCALAR_MIXER_CALIB_2_PORT             1

/*- fuction agena_confTrigger control Trigger Source -*/
#define AGENA_TRIGGER_SOURCE_INTERNAL				0
#define AGENA_TRIGGER_SOURCE_EXTERNAL				1
#define AGENA_TRIGGER_SOURCE_MANUAL					2
#define AGENA_TRIGGER_SOURCE_BUS					3

/*- fuction agena_confLimitTestTable control Type of the Line -*/
#define AGENA_LIMIT_LINE_TYPE_OFF					0
#define AGENA_LIMIT_LINE_TYPE_UPPER					1
#define AGENA_LIMIT_LINE_TYPE_LOWER					2

/*- fuction agena_confMarkerSearch control Peak Polarity -*/
#define AGENA_MARKER_PEAK_POLARITY_POSITIVE         0
#define AGENA_MARKER_PEAK_POLARITY_NEGATIVE         1
#define AGENA_MARKER_PEAK_POLARITY_BOTH             2

/*- fuction agena_confMarkerSearch control Target Polarity -*/
#define AGENA_MARKER_TARGET_POLARITY_POSITIVE       0
#define AGENA_MARKER_TARGET_POLARITY_NEGATIVE       1
#define AGENA_MARKER_TARGET_POLARITY_BOTH           2

/*- fuction agena_confMarkerFunction control Marker Function -*/
#define AGENA_MARKER_MATH_FLAT       				0
#define AGENA_MARKER_MATH_FST       				1
#define AGENA_MARKER_MATH_STAT			            2

/*- fuction agena_confAnalysis control Analysis Type -*/
#define AGENA_ANALYSIS_TYPE_PEAK_2_PEAK             0
#define AGENA_ANALYSIS_TYPE_STD_DEV                 1
#define AGENA_ANALYSIS_TYPE_MEAN                    2
#define AGENA_ANALYSIS_TYPE_MAXIMUM                 3
#define AGENA_ANALYSIS_TYPE_MINIMUM                 4
#define AGENA_ANALYSIS_TYPE_PEAK                    5
#define AGENA_ANALYSIS_TYPE_ALL_PEAK                6
#define AGENA_ANALYSIS_TYPE_ALL_TARGET              7

/*- fuction agena_confAnalysis control Peak Polarity -*/
#define AGENA_ANALYSIS_PEAK_POLARITY_POSITIVE       0
#define AGENA_ANALYSIS_PEAK_POLARITY_NEGATIVE       1
#define AGENA_ANALYSIS_PEAK_POLARITY_BOTH           2

/*- fuction agena_confAnalysis control Target Polarity -*/
#define AGENA_ANALYSIS_TARGET_POLARITY_POSITIVE     0
#define AGENA_ANALYSIS_TARGET_POLARITY_NEGATIVE     1
#define AGENA_ANALYSIS_TARGET_POLARITY_BOTH         2

/*- fuction agena_confFixSim control Balance Device Type -*/
#define AGENA_FIX_SIM_BALANCE_TYPE_SBAL             0
#define AGENA_FIX_SIM_BALANCE_TYPE_BBAL             1
#define AGENA_FIX_SIM_BALANCE_TYPE_SSBAL            2

/*- fuction agena_confFixSimBalUnbalConv control Parameter -*/
/*
#define AGENA_BALANCE_PARAMETER_SSS11               0
#define AGENA_BALANCE_PARAMETER_SSS21               1
#define AGENA_BALANCE_PARAMETER_SSS12               2
#define AGENA_BALANCE_PARAMETER_SSS22               3
#define AGENA_BALANCE_PARAMETER_SDS21               4
#define AGENA_BALANCE_PARAMETER_SDS31               5
#define AGENA_BALANCE_PARAMETER_SDS32               6
#define AGENA_BALANCE_PARAMETER_SSD12               7
#define AGENA_BALANCE_PARAMETER_SSD13               8
#define AGENA_BALANCE_PARAMETER_SSD23               9
#define AGENA_BALANCE_PARAMETER_SCS21               10
#define AGENA_BALANCE_PARAMETER_SCS31               11
#define AGENA_BALANCE_PARAMETER_SCS32               12
#define AGENA_BALANCE_PARAMETER_SSC12               13
#define AGENA_BALANCE_PARAMETER_SSC13               14
#define AGENA_BALANCE_PARAMETER_SSC23               15
#define AGENA_BALANCE_PARAMETER_SDD11               16
#define AGENA_BALANCE_PARAMETER_SDD21               17
#define AGENA_BALANCE_PARAMETER_SDD12               18
#define AGENA_BALANCE_PARAMETER_SDD22               19
#define AGENA_BALANCE_PARAMETER_SDD33               20
#define AGENA_BALANCE_PARAMETER_SCD11               21
#define AGENA_BALANCE_PARAMETER_SCD21               22
#define AGENA_BALANCE_PARAMETER_SCD12               23
#define AGENA_BALANCE_PARAMETER_SCD22               24
#define AGENA_BALANCE_PARAMETER_SCD33               25
#define AGENA_BALANCE_PARAMETER_SDC11               26
#define AGENA_BALANCE_PARAMETER_SDC21               27
#define AGENA_BALANCE_PARAMETER_SDC12               28
#define AGENA_BALANCE_PARAMETER_SDC22               29
#define AGENA_BALANCE_PARAMETER_SDC33               30
#define AGENA_BALANCE_PARAMETER_SCC11               31
#define AGENA_BALANCE_PARAMETER_SCC21               32
#define AGENA_BALANCE_PARAMETER_SCC12               33
#define AGENA_BALANCE_PARAMETER_SCC22               34
#define AGENA_BALANCE_PARAMETER_SCC33               35
#define AGENA_BALANCE_PARAMETER_IMBALANCE1          36
#define AGENA_BALANCE_PARAMETER_IMBALANCE2          37
#define AGENA_BALANCE_PARAMETER_IMBALANCE3          38
#define AGENA_BALANCE_PARAMETER_IMBALANCE4          39
#define AGENA_BALANCE_PARAMETER_CMRR1               40
#define AGENA_BALANCE_PARAMETER_CMRR2               41
*/
#define AGENA_BALANCE_PARAMETER_SSS        			0
#define AGENA_BALANCE_PARAMETER_SDS        			1
#define AGENA_BALANCE_PARAMETER_SSD        			2
#define AGENA_BALANCE_PARAMETER_SCS        			3
#define AGENA_BALANCE_PARAMETER_SSC        			4
#define AGENA_BALANCE_PARAMETER_SDD        			5
#define AGENA_BALANCE_PARAMETER_SCD        			6
#define AGENA_BALANCE_PARAMETER_SDC        			7
#define AGENA_BALANCE_PARAMETER_SCC        			8
#define AGENA_BALANCE_PARAMETER_IMBALANCE1 			9
#define AGENA_BALANCE_PARAMETER_IMBALANCE2 			10
#define AGENA_BALANCE_PARAMETER_IMBALANCE3 			11
#define AGENA_BALANCE_PARAMETER_IMBALANCE4 			12
#define AGENA_BALANCE_PARAMETER_CMRR1      			13
#define AGENA_BALANCE_PARAMETER_CMRR2      			14



/*- fuction agena_confFixSimMatchingCircuitEmbedding control Circuit Mode -*/
#define AGENA_CIRCUIT_MODE_NORMAL                   0  
#define AGENA_CIRCUIT_MODE_DIFFERENTIAL             1
#define AGENA_CIRCUIT_MODE_COMMON                   2



/*- fuction agena_confFixSimMatchingCircuitEmbedding control Circuit Type -*/
#define AGENA_CIRCUIT_TYPE_NONE                     0
#define AGENA_CIRCUIT_TYPE_SLPC                     1
#define AGENA_CIRCUIT_TYPE_PCSL                     2
#define AGENA_CIRCUIT_TYPE_PLSC                     3
#define AGENA_CIRCUIT_TYPE_SCPL                     4
#define AGENA_CIRCUIT_TYPE_PLPC                     5
#define AGENA_CIRCUIT_TYPE_USER                     6

/*- fuction agena_confFixSimNetworkDeembedding control Circuit Type -*/
#define AGENA_NETWORK_DEEMBEDDING_NONE              0
#define AGENA_NETWORK_DEEMBEDDING_USER              1

/*- fuction agena_confFixSim4portNetworkDeEmbedding control Topology Type -*/
#define AGENA_TOPOLOGY_TYPE_A                       0
#define AGENA_TOPOLOGY_TYPE_B                       1
#define AGENA_TOPOLOGY_TYPE_C                       2

/*- fuction agena_confFixSim4portNetworkDeEmbedding control Network Type -*/
#define AGENA_NETWORK_TYPE_NONE                     0
#define AGENA_NETWORK_TYPE_EMBED                    1
#define AGENA_NETWORK_TYPE_DEEMBED                  2

/*- fuction agena_confTDomTransform control Transformation Type -*/
#define AGENA_TRANSFORMATION_TYPE_BPASS             0
#define AGENA_TRANSFORMATION_TYPE_LPASS             1

/*- fuction agena_confTDomTransform control Stimulus Type -*/
#define AGENA_TRANSFORM_STIMULUS_TYPE_IMPULSE       0
#define AGENA_TRANSFORM_STIMULUS_TYPE_STEP          1

/*- fuction agena_confTDomDisplayRange control Setting Type -*/
/*- fuction agena_confTDomGating control Setting Type -*/
#define AGENA_TIME_DOMAIN_SET_TYPE_CENTER_SPAN      0
#define AGENA_TIME_DOMAIN_SET_TYPE_START_STOP       1

/*- fuction agena_confTDomGating control Gate Shape -*/
#define AGENA_TIME_DOMAIN_GATE_SHAPE_MAX            0
#define AGENA_TIME_DOMAIN_GATE_SHAPE_WIDE           1
#define AGENA_TIME_DOMAIN_GATE_SHAPE_NORMAL         2
#define AGENA_TIME_DOMAIN_GATE_SHAPE_MIN            3

/*- fuction agena_confTDomGating control Gate Type -*/
#define AGENA_TIME_DOMAIN_GATE_TYPE_BPASS           0
#define AGENA_TIME_DOMAIN_GATE_TYPE_NOTCH           1

/*- fuction agena_confParameterConversion control Parameter -*/
#define AGENA_PARAMETER_CONVERSION_ZREFLECT         0
#define AGENA_PARAMETER_CONVERSION_ZTRANSMIT        1
#define AGENA_PARAMETER_CONVERSION_YREFLECT         2
#define AGENA_PARAMETER_CONVERSION_YTRANSMIT        3
#define AGENA_PARAMETER_CONVERSION_INVERSION        4
#define AGENA_PARAMETER_CONVERSION_ZTSHUNT          5
#define AGENA_PARAMETER_CONVERSION_YTSHUNT          6
#define AGENA_PARAMETER_CONVERSION_CONJUGATE        7

/*- fuction agena_confHandlerIOControl control Port C Direction -*/
#define AGENA_IO_HANDLER_DIR_PORT_C_INPUT           0
#define AGENA_IO_HANDLER_DIR_PORT_C_OUTPUT          1

/*- fuction agena_confHandlerIOControl control Port D Direction -*/
#define AGENA_IO_HANDLER_DIR_PORT_D_INPUT           0
#define AGENA_IO_HANDLER_DIR_PORT_D_OUTPUT          1

/*- fuction agena_confHandlerIOControl control OUTPUT1/OUTPUT2 Setting -*/
#define AGENA_HANDLER_IO_OUTPUT_HIGH                0
#define AGENA_HANDLER_IO_OUTPUT_LOW                 1

/*- fuction agena_confE5091A control Port 1 -*/
#define AGENA_CONTROL_E5091A_PORT1_A                0
#define AGENA_CONTROL_E5091A_PORT1_T1               1

/*- fuction agena_confE5091A control Port 2 -*/
#define AGENA_CONTROL_E5091A_PORT2_T1               0
#define AGENA_CONTROL_E5091A_PORT2_T2               1

/*- fuction agena_confE5091A control Port 3 -*/
#define AGENA_CONTROL_E5091A_PORT3_R1               0
#define AGENA_CONTROL_E5091A_PORT3_R2               1
#define AGENA_CONTROL_E5091A_PORT3_R3               2

/*- fuction agena_confE5091A control Port 4 -*/
#define AGENA_CONTROL_E5091A_PORT4_R1               0
#define AGENA_CONTROL_E5091A_PORT4_R2               1
#define AGENA_CONTROL_E5091A_PORT4_R3               2

/*- fuction agena_confFileHandling control Items -*/
#define AGENA_FILE_HANDLING_ITEM_STATE              0
#define AGENA_FILE_HANDLING_ITEM_CSTATE             1
#define AGENA_FILE_HANDLING_ITEM_DSTATE             2
#define AGENA_FILE_HANDLING_ITEM_CDSTATE            3

/*- fuction agena_confPrintColor control Color -*/
#define AGENA_PRINT_COLOR_NORMAL                    0
#define AGENA_PRINT_COLOR_INVERT                    1

/*- fuction agena_actMeasureCalData control Standard -*/
#define AGENA_MEASURE_CAL_DATA_STANDARD_OPEN        0
#define AGENA_MEASURE_CAL_DATA_STANDARD_SHORT       1
#define AGENA_MEASURE_CAL_DATA_STANDARD_LOAD        2
#define AGENA_MEASURE_CAL_DATA_STANDARD_THRU        3
#define AGENA_MEASURE_CAL_DATA_STANDARD_ISOLATION   4

/*- fuction agena_actClearCalData control Clear -*/
/*- fuction agena_actClearScalarCalData control Clear -*/
#define AGENA_CALIBRATION_DATA_CLEAR_COEFFICIENT    0
#define AGENA_CALIBRATION_DATA_CLEAR_DATA           1

/*- fuction agena_actExecuteECal control Calibration -*/
#define AGENA_CALIBRATION_EXECUTE_1_PORT            0
#define AGENA_CALIBRATION_EXECUTE_2_PORT            1
#define AGENA_CALIBRATION_EXECUTE_3_PORT            2
#define AGENA_CALIBRATION_EXECUTE_4_PORT            3
#define AGENA_CALIBRATION_EXECUTE_RESPONSE          4
#define AGENA_CALIBRATION_EXECUTE_CONF_CHECK        5
#define AGENA_CALIBRATION_EXECUTE_EN_RESPONSE		6

/*- fuction agena_actMeasureScalarCalData control Standard -*/
#define AGENA_MEASURE_CAL_SCALAR_STANDARD_OPEN      0
#define AGENA_MEASURE_CAL_SCALAR_STANDARD_SHORT     1
#define AGENA_MEASURE_CAL_SCALAR_STANDARD_LOAD      2
#define AGENA_MEASURE_CAL_SCALAR_STANDARD_THRU      3
#define AGENA_MEASURE_CAL_SCALAR_STANDARD_POWER     4

/*- fuction agena_actMarkerSearch control Function -*/
#define AGENA_MARKER_SEARCH_MAXIMUM                 0
#define AGENA_MARKER_SEARCH_MINIMUM                 1
#define AGENA_MARKER_SEARCH_PEAK                    2
#define AGENA_MARKER_SEARCH_LPEAK                   3
#define AGENA_MARKER_SEARCH_RPEAK                   4
#define AGENA_MARKER_SEARCH_TARGET                  5
#define AGENA_MARKER_SEARCH_LTARGET                 6
#define AGENA_MARKER_SEARCH_RTARGET                 7

/*- fuction agena_actMarkerTo control Marker To -*/
#define AGENA_MARKER_SET_TO_START                   0
#define AGENA_MARKER_SET_TO_STOP                    1
#define AGENA_MARKER_SET_TO_CENTER                  2
#define AGENA_MARKER_SET_TO_RLEVEL                  3
#define AGENA_MARKER_SET_TO_DELAY                   4

/*- fuction agena_actStore control Data Type -*/
/*- fuction agena_actRecall control Data Type -*/
#define AGENA_FILE_DATA_TYPE_INSTR_STATE            0
#define AGENA_FILE_DATA_TYPE_FORMATTED              1
#define AGENA_FILE_DATA_TYPE_IMAGE                  2
#define AGENA_FILE_DATA_TYPE_SEG_SWEEP_TABLE        3
#define AGENA_FILE_DATA_TYPE_LIMIT_TABLE            4
#define AGENA_FILE_DATA_TYPE_POWER_SENS_A           5
#define AGENA_FILE_DATA_TYPE_POWER_SENS_B           6
#define AGENA_FILE_DATA_TYPE_VBA_PROJECT            7
#define AGENA_FILE_DATA_TYPE_LOSS_COM_1             8
#define AGENA_FILE_DATA_TYPE_LOSS_COM_2             9
#define AGENA_FILE_DATA_TYPE_LOSS_COM_3             10
#define AGENA_FILE_DATA_TYPE_LOSS_COM_4             11

/*- fuction agena_actStoreChannelState control Memory Register -*/
/*- fuction agena_actRecallChannelState control Memory Register -*/
#define AGENA_MEMORY_REGISTER_A						0
#define AGENA_MEMORY_REGISTER_B						1
#define AGENA_MEMORY_REGISTER_C						2
#define AGENA_MEMORY_REGISTER_D						3

/*- fuction agena_actFileManager control Operation -*/
#define AGENA_FILE_MANAGER_CREATE_DIR				0
#define AGENA_FILE_MANAGER_COPY_FILE				1
#define AGENA_FILE_MANAGER_DELETE_DIR				2

/*- fuction agena_actHCopy control Operation -*/
#define AGENA_HARDCOPY_EXECUTE                      0
#define AGENA_HARDCOPY_ABORT                        1

/*- fuction agena_actSecurityLevel control Operation -*/
#define AGENA_SECURITY_LEVEL_NONE					0
#define AGENA_SECURITY_LEVEL_LOW 					1
#define AGENA_SECURITY_LEVEL_HIGH					2

/*- fuction agena_actBeep control Beep Type -*/
#define AGENA_BEEP_TYPE_COMPLETE					0
#define AGENA_BEEP_TYPE_WARNING						1

/*- fuction agena_actControlMacro control Operation -*/
#define AGENA_CONTROL_MACRO_OPERATION_RUN           0
#define AGENA_CONTROL_MACRO_OPERATION_STOP          1

/*- fuction agena_dataReadArr control Source -*/
/*- fuction agena_dataWriteArr control Source -*/
#define AGENA_DATA_SOURCE_DATA                      0
#define AGENA_DATA_SOURCE_MEMORY                    1

/*- fuction agena_dataReadArr control Correction -*/
/*- fuction agena_dataWriteArr control Correction -*/
#define AGENA_DATA_CORRECTION_FORMATTED             0
#define AGENA_DATA_CORRECTION_CORRECTED             1

/*- fuction agena_dataWriteArr control Correction -*/
#define AGENA_HANDLER_PORT_A                        0
#define AGENA_HANDLER_PORT_B                        1
#define AGENA_HANDLER_PORT_C                        2
#define AGENA_HANDLER_PORT_D                        3
#define AGENA_HANDLER_PORT_E                        4
#define AGENA_HANDLER_PORT_F                        5


/*- Status registers constants -*/
#define AGENA_STATUS_REGISTER_PRESET				0
#define AGENA_STATUS_REGISTER_OPERATION				1
#define AGENA_STATUS_REGISTER_QUESTIONABLE			2

#define AGENA_QUESTIONABLE_REGISTER_MAIN			0
#define AGENA_QUESTIONABLE_REGISTER_CHANNEL			1
#define AGENA_QUESTIONABLE_REGISTER_CHANNEL_EXTRA	2
#define AGENA_QUESTIONABLE_REGISTER_LIMIT			3
#define AGENA_QUESTIONABLE_REGISTER_LIMIT_EXTRA		4

#define AGENA_READ_STATUS_OPERATION					0
#define AGENA_READ_STATUS_OPERATION_CONDITION		1
#define AGENA_READ_STATUS_QUES						2
#define AGENA_READ_STATUS_QUES_CONDITION			3
#define AGENA_READ_STATUS_QUES_LIMIT				4
#define AGENA_READ_STATUS_QUES_LIMIT_CONDITION		5
#define AGENA_READ_STATUS_QUES_LIMIT_EXTRA			6
#define AGENA_READ_STATUS_QUES_LIMIT_EXTRA_COND		7
#define AGENA_READ_STATUS_QUES_LIMIT_CHANNEL		8
#define AGENA_READ_STATUS_QUES_LIMIT_CHANNEL_COND	9
#define AGENA_READ_STATUS_QUES_LIMIT_CH_EXTRA		10
#define AGENA_READ_STATUS_QUES_LIMIT_CH_EXTRA_COND	11

/*- Configure Marker -*/
#define AGENA_MARKER_UNIT_HZ    0
#define AGENA_MARKER_UNIT_S     1
#define AGENA_MARKER_UNIT_DBM   2


/*****************************************************************************/
/*= GLOBAL USER-CALLABLE FUNCTION DECLARATIONS (Exportable Functions) =======*/
/*****************************************************************************/

ViStatus _VI_FUNC agena_init (ViRsrc resourceName, ViBoolean IDQuery,
                              ViBoolean resetDevice, ViPSession instrumentHandle);
ViStatus _VI_FUNC agena_configureAppExample (ViRsrc resourceName, ViBoolean IDQuery,
                                             ViBoolean resetDevice,
                                             ViReal64 centerFrequencyHz,
                                             ViReal64 spanFrequencyHz,
                                             ViReal64 IFBandwidthHz,
                                             ViReal64 powerdBm);
ViStatus _VI_FUNC agena_openCalibrationExample (ViRsrc resourceName,
                                                ViBoolean IDQuery,
                                                ViBoolean resetDevice);
ViStatus _VI_FUNC agena_shortCalibrationExample (ViRsrc resourceName,
                                                 ViBoolean IDQuery,
                                                 ViBoolean resetDevice);
ViStatus _VI_FUNC agena_loadCalibrationExample (ViRsrc resourceName,
                                                ViBoolean IDQuery,
                                                ViBoolean resetDevice);
ViStatus _VI_FUNC agena_thru12CalibrationExample (ViRsrc resourceName,
                                                  ViBoolean IDQuery,
                                                  ViBoolean resetDevice);
ViStatus _VI_FUNC agena_thru21CalibrationExample (ViRsrc resourceName,
                                                  ViBoolean IDQuery,
                                                  ViBoolean resetDevice);
ViStatus _VI_FUNC agena_appExample (ViRsrc resourceName, ViBoolean IDQuery,
                                    ViBoolean resetDevice, ViPReal64 bandwidth,
                                    ViPReal64 center, ViPReal64 low, ViPReal64 high,
                                    ViPReal64 q, ViPReal64 loss);
ViStatus _VI_FUNC agena_confChannelTrace (ViSession instrumentHandle,
                                          ViInt32 activeChannel,
                                          ViInt32 activeTrace,
                                          ViInt32 numberOfTraces,
                                          ViInt32 measurementParameter,
                                          ViInt32 dataFormat);
ViStatus _VI_FUNC agena_confPower (ViSession instrumentHandle, ViInt32 channel,
                                   ViInt32 port, ViBoolean portCoupling,
                                   ViBoolean autoPowerRange, ViReal64 powerRange,
                                   ViBoolean powerSlope,
                                   ViReal64 powerSlopeCoefficient,
                                   ViReal64 powerLevel);
ViStatus _VI_FUNC agena_confFixedFreq (ViSession instrumentHandle, ViInt32 channel,
                                       ViReal64 fixedFrequency);
ViStatus _VI_FUNC agena_confSweep (ViSession instrumentHandle, ViInt32 channel,
                                   ViInt32 numberOfMeasurementPoints,
                                   ViReal64 delayTime, ViInt32 sweepType,
                                   ViInt32 sweepMode, ViInt32 autoSweepTime,
                                   ViReal64 sweepTime, ViBoolean spuriousAvoidMode);
ViStatus _VI_FUNC agena_confSweepStimulus (ViSession instrumentHandle,
                                           ViInt32 channel, ViBoolean signalOutput,
                                           ViInt32 stimulus, ViReal64 parameter,
                                           ViInt32 unit);
ViStatus _VI_FUNC agena_confSweepSegments (ViSession instrumentHandle,
                                           ViInt32 channel,
                                           ViInt32 stimulusSettingMode,
                                           ViBoolean eachSegmentIFBwidSetting,
                                           ViBoolean eachSegmentPowerSetting,
                                           ViBoolean eachSegmentSwDelaySetting,
                                           ViBoolean eachSegmentSwModeSetting,
                                           ViBoolean eachSegmentSwTimeSetting,
                                           ViInt32 number_ofSegments,
                                           ViReal64 _VI_FAR startCenterValues[],
                                           ViReal64 _VI_FAR stopSpanValues[],
                                           ViInt32 _VI_FAR numbers_ofMeasPoints[],
                                           ViReal64 _VI_FAR IFBandwidths[],
                                           ViReal64 _VI_FAR powers[],
                                           ViReal64 _VI_FAR sweepDelayTimes[],
                                           ViReal64 _VI_FAR sweepModes[],
                                           ViReal64 _VI_FAR sweepTimes[]);
ViStatus _VI_FUNC agena_confIFBwid (ViSession instrumentHandle, ViInt32 channel,
                                    ViReal64 IFBandwidth);
ViStatus _VI_FUNC agena_confAveraging (ViSession instrumentHandle, ViInt32 channel,
                                       ViBoolean state, ViInt32 factor);
ViStatus _VI_FUNC agena_confSmoothing (ViSession instrumentHandle, ViInt32 channel,
                                       ViBoolean state, ViReal64 smoothingAperture);
ViStatus _VI_FUNC agena_confAbsoluteMeasurement (ViSession instrumentHandle,
                                                 ViInt32 channel, ViInt32 port,
                                                 ViInt32 trace,
                                                 ViInt32 measurementParameter);
ViStatus _VI_FUNC agena_confExtSignalSource (ViSession instrumentHandle,
                                             ViInt32 channel,
                                             ViBoolean controlState,
                                             ViBoolean frequencyOffsetState,
                                             ViInt32 multiplier, ViInt32 divisor,
                                             ViReal64 offset, ViReal64 start,
                                             ViReal64 stop,
                                             ViBoolean powerSlopeState,
                                             ViReal64 powerLevel,
                                             ViReal64 powerSlope);
ViStatus _VI_FUNC agena_confFreqOffset (ViSession instrumentHandle, ViInt32 channel,
                                        ViInt32 port, ViBoolean state,
                                        ViInt32 multiplier, ViInt32 divisor,
                                        ViReal64 offset, ViReal64 start,
                                        ViReal64 stop, ViInt32 xAxisFreq,
                                        ViBoolean avoidSpurious);
ViStatus _VI_FUNC agena_confLayout (ViSession instrumentHandle, ViInt32 channel,
                                    ViInt32 graphLayout);
ViStatus _VI_FUNC agena_confDisplay (ViSession instrumentHandle, ViInt32 channel,
                                     ViBoolean backlight, ViBoolean displayUpdate,
                                     ViBoolean graticuleLabel, ViBoolean clock,
                                     ViBoolean frequency, ViBoolean softkeyLabel,
                                     ViBoolean title, ViString titleText,
                                     ViBoolean table, ViInt32 tableSelect,
                                     ViInt32 displayType,
                                     ViBoolean statisticAnalysisResult,
                                     ViBoolean maximize);
ViStatus _VI_FUNC agena_confTraceDisplay (ViSession instrumentHandle,
                                          ViInt32 channel, ViInt32 trace,
                                          ViInt32 traceDisplay,
                                          ViBoolean displayData,
                                          ViBoolean displayMemory);
ViStatus _VI_FUNC agena_confColor (ViSession instrumentHandle, ViInt32 displayType,
                                   ViInt32 trace, ViInt32 setting, ViInt32 r,
                                   ViInt32 g, ViInt32 b);
ViStatus _VI_FUNC agena_confXAxisSegmentSweep (ViSession instrumentHandle,
                                               ViInt32 channel,
                                               ViInt32 displayMethod);
ViStatus _VI_FUNC agena_confDispCorr (ViSession instrumentHandle, ViInt32 channel,
                                      ViReal64 electricalDelayTime,
                                      ViReal64 velocityFactor,
                                      ViReal64 phaseOffset);
ViStatus _VI_FUNC agena_confScale (ViSession instrumentHandle, ViInt32 channel,
                                   ViInt32 trace, ViInt32 number_ofDivisions,
                                   ViReal64 scale_perDivision,
                                   ViInt32 referenceGraticuleLine,
                                   ViReal64 valueGraticuleLine);
ViStatus _VI_FUNC agena_confCal (ViSession instrumentHandle, ViInt32 channel,
                                 ViInt32 calKit, ViInt32 calType, ViInt32 port1,
                                 ViInt32 port2, ViInt32 port3,
                                 ViBoolean errorCorrectionState,
                                 ViBoolean calibrationPropertyDisplay,
                                 ViReal64 velocityFactor, ViReal64 z0);
ViStatus _VI_FUNC agena_confCalKit (ViSession instrumentHandle, ViInt32 channel,
                                    ViInt32 standard, ViString label, ViInt32 type,
                                    ViReal64 c0, ViReal64 c1, ViReal64 c2,
                                    ViReal64 c3, ViReal64 l0, ViReal64 l1,
                                    ViReal64 l2, ViReal64 l3,
                                    ViReal64 arbitraryImpedance,
                                    ViString calKitName);
ViStatus _VI_FUNC agena_confCalKitStandardOffsets (ViSession instrumentHandle,
                                                   ViInt32 channel,
                                                   ViInt32 standard,
                                                   ViReal64 offsetDelay,
                                                   ViReal64 offsetLoss,
                                                   ViReal64 z0);
ViStatus _VI_FUNC agena_confCalKitClass (ViSession instrumentHandle,
                                         ViInt32 channel, ViInt32 type,
                                         ViInt32 standard, ViInt32 port1,
                                         ViInt32 port2);
ViStatus _VI_FUNC agena_confPortExtension (ViSession instrumentHandle,
                                           ViInt32 channel, ViBoolean state,
                                           ViInt32 port1, ViReal64 correctionValue);
ViStatus _VI_FUNC agena_confECal (ViSession instrumentHandle, ViInt32 channel,
                                  ViBoolean isolationMeasurement,
                                  ViInt32 characterization);
ViStatus _VI_FUNC agena_confPowCal (ViSession instrumentHandle, ViInt32 channel,
                                    ViInt32 port, ViBoolean state,
                                    ViInt32 averagingFactor,
                                    ViBoolean lossCompensation,
                                    ViInt32 powerMeterAddress);
ViStatus _VI_FUNC agena_confRefCalFactor (ViSession instrumentHandle,
                                          ViInt32 powerSensor,
                                          ViReal64 referenceCalibrationFactor);
ViStatus _VI_FUNC agena_confCalibrationFactorTable (ViSession instrumentHandle,
                                                    ViInt32 powerSensor,
                                                    ViInt32 arraySize,
                                                    ViReal64 _VI_FAR frequencyArray[],
                                                    ViReal64 _VI_FAR calibrationFactorArray[]);
ViStatus _VI_FUNC agena_confLossCompensationTable (ViSession instrumentHandle,
                                                   ViInt32 channel, ViInt32 port,
                                                   ViInt32 arraySize,
                                                   ViReal64 _VI_FAR frequencyArray[],
                                                   ViReal64 _VI_FAR lossCompensationArray[]);
ViStatus _VI_FUNC agena_confScalarCal (ViSession instrumentHandle, ViInt32 channel,
                                       ViInt32 method, ViInt32 port1,
                                       ViInt32 port2);
ViStatus _VI_FUNC agena_confRecCal (ViSession instrumentHandle, ViInt32 channel,
                                    ViInt32 receiver, ViBoolean state);
ViStatus _VI_FUNC agena_confTrigger (ViSession instrumentHandle, ViInt32 channel,
                                     ViBoolean continuousSweep,
                                     ViBoolean pointTrigger, ViInt32 triggerSource);
ViStatus _VI_FUNC agena_confLimitTest (ViSession instrumentHandle, ViInt32 channel,
                                       ViBoolean limitTest,
                                       ViBoolean limitLineDisplay,
                                       ViBoolean limitLineClip,
                                       ViBoolean limitFailDisplay);
ViStatus _VI_FUNC agena_confLimitTestTable (ViSession instrumentHandle,
                                            ViInt32 channel, ViInt32 number_ofLines,
                                            ViInt32 _VI_FAR type_of_theLine[],
                                            ViReal64 _VI_FAR startPointXValue[],
                                            ViReal64 _VI_FAR endPointXValue[],
                                            ViReal64 _VI_FAR startPointYValue[],
                                            ViReal64 _VI_FAR endPointYValue[]);
ViStatus _VI_FUNC agena_confMarker (ViSession instrumentHandle, ViInt32 channel,
                                    ViInt32 marker, ViReal64 stimulus, ViBoolean state);
ViStatus _VI_FUNC agena_confActiveMarker (ViSession instrumentHandle,
                                          ViInt32 channel, ViInt32 marker);
ViStatus _VI_FUNC agena_confMarkerMode (ViSession instrumentHandle, ViInt32 channel,
                                        ViBoolean coupled, ViBoolean markerMode,
                                        ViBoolean referenceMarkerMode);
ViStatus _VI_FUNC agena_confMarkerSearch (ViSession instrumentHandle,
                                          ViInt32 channel, ViInt32 marker,
                                          ViBoolean rangeCoupling,
                                          ViBoolean tracking,
                                          ViReal64 peakExcursion,
                                          ViInt32 peakPolarity,
                                          ViReal64 targetValue,
                                          ViInt32 targetPolarity,
                                          ViBoolean partialMarkerState,
                                          ViReal64 start, ViReal64 stop);
ViStatus _VI_FUNC agena_confBandwidthSearch (ViSession instrumentHandle,
                                             ViInt32 channel, ViInt32 marker,
                                             ViBoolean state,
                                             ViReal64 bandwidthDefinitionValue);
ViStatus _VI_FUNC agena_confMarkerFunction (ViSession instrumentHandle,
                                            ViInt32 channel,
                                            ViInt32 markerFunction,
                                            ViBoolean state);
ViStatus _VI_FUNC agena_confNotchSearch (ViSession instrumentHandle,
                                         ViInt32 channel, ViInt32 marker,
                                         ViBoolean state,
                                         ViReal64 notchDefinitionValue);
ViStatus _VI_FUNC agena_confAnalysis (ViSession instrumentHandle, ViInt32 channel,
                                      ViInt32 analysisType, ViBoolean rangeCoupling,
                                      ViReal64 peakExcursion, ViInt32 peakPolarity,
                                      ViReal64 targetValue, ViInt32 targetPolarity,
                                      ViBoolean partialRangeAnalysisState,
                                      ViReal64 start, ViReal64 stop);
ViStatus _VI_FUNC agena_confFixSim (ViSession instrumentHandle, ViInt32 channel,
                                    ViBoolean state, ViInt32 balanceDeviceType,
                                    ViBoolean displayProperty, ViInt32 port1,
                                    ViInt32 port2, ViInt32 port3, ViInt32 port4);
ViStatus _VI_FUNC agena_confFixSimBalUnbalConv (ViSession instrumentHandle,
                                                ViInt32 channel, ViInt32 trace,
                                                ViBoolean state,
                                                ViInt32 balanceDeviceType,
                                                ViInt32 parameter, ViInt32 port1,
                                                ViInt32 port2);
ViStatus _VI_FUNC agena_confFixSimMatchingCircuitEmbedding
             (ViSession instrumentHandle, ViInt32 channel, ViInt32 port,
              ViBoolean state, ViInt32 circuitMode, ViInt32 circuitType, ViReal64 c,
              ViReal64 g, ViReal64 l, ViReal64 r, ViString fileName);
ViStatus _VI_FUNC agena_confFixSimPortImpedanceConversion
             (ViSession instrumentHandle, ViInt32 channel, ViInt32 port,
              ViBoolean state, ViInt32 circuitMode, ViReal64 z0);
ViStatus _VI_FUNC agena_confFixSimNetworkDeembedding (ViSession instrumentHandle,
                                                      ViInt32 channel, ViInt32 port,
                                                      ViBoolean state,
                                                      ViInt32 circuitType,
                                                      ViString fileName);
ViStatus _VI_FUNC agena_confFixSim4portNetworkDeEmbedding
             (ViSession instrumentHandle, ViInt32 channel, ViBoolean state,
              ViInt32 topologyType, ViInt32 port1, ViInt32 port2, ViInt32 port3,
              ViInt32 port4, ViInt32 network, ViInt32 networkType,
              ViString networkFile);
ViStatus _VI_FUNC agena_confTDomTransform (ViSession instrumentHandle,
                                           ViInt32 channel, ViBoolean state,
                                           ViInt32 transformationType,
                                           ViInt32 stimulusType, ViInt32 beta,
                                           ViReal64 impluseWidth,
                                           ViReal64 riseTime_ofStepSignal);
ViStatus _VI_FUNC agena_confTDomDisplayRange (ViSession instrumentHandle,
                                              ViInt32 channel, ViInt32 settingType,
                                              ViReal64 start, ViReal64 stop,
                                              ViReal64 center, ViReal64 span);
ViStatus _VI_FUNC agena_confTDomGating (ViSession instrumentHandle, ViInt32 channel,
                                        ViBoolean state, ViInt32 gateType,
                                        ViInt32 gateShape, ViInt32 settingType,
                                        ViReal64 start, ViReal64 stop,
                                        ViReal64 center, ViReal64 span);
ViStatus _VI_FUNC agena_confParameterConversion (ViSession instrumentHandle,
                                                 ViInt32 channel, ViBoolean state,
                                                 ViInt32 parameter);
ViStatus _VI_FUNC agena_confHandlerIOControl (ViSession instrumentHandle,
                                              ViInt32 portCDirection,
                                              ViInt32 portDDirection,
                                              ViInt32 OUTPUT1OUTPUT2Setting,
                                              ViBoolean INDEXSignalOutput,
                                              ViBoolean READYFORTRIGGERSignalOutput,
                                              ViInt32 output);
ViStatus _VI_FUNC agena_confE5091A (ViSession instrumentHandle, ViInt32 channel,
                                    ViInt32 multiplexer, ViBoolean state,
                                    ViInt32 port1, ViInt32 port2, ViInt32 port3,
                                    ViInt32 port4, ViBoolean propertyDisplay,
                                    ViInt32 controlLines);
ViStatus _VI_FUNC agena_confDateTime (ViSession instrumentHandle,
                                      ViBoolean displayClock, ViInt32 year,
                                      ViInt32 month, ViInt32 day, ViInt32 hour,
                                      ViInt32 minute, ViInt32 second);
ViStatus _VI_FUNC agena_confExternalSigGen (ViSession instrumentHandle,
                                            ViInt32 GPIBAddress, ViInt32 type,
                                            ViString frequencySettingCommand,
                                            ViString powerLevelSettingCommand,
                                            ViString presetCommand,
                                            ViString RFPowerONCommand,
                                            ViReal64 waitingTime);
ViStatus _VI_FUNC agena_confInitialSourcePort (ViSession instrumentHandle,
                                               ViBoolean state, ViInt32 port);
ViStatus _VI_FUNC agena_confCorrTemp (ViSession instrumentHandle,
                                      ViBoolean systemErrorCorrection,
                                      ViBoolean highTemperatureMode);
ViStatus _VI_FUNC agena_actClearAvgData (ViSession instrumentHandle,
                                         ViInt32 channel);
ViStatus _VI_FUNC agena_actCopyMeasDataToMem (ViSession instrumentHandle,
                                              ViInt32 channel);
ViStatus _VI_FUNC agena_actAutoscaleYAxis (ViSession instrumentHandle,
                                           ViInt32 channel, ViInt32 trace);
ViStatus _VI_FUNC agena_actResetCalKit (ViSession instrumentHandle,
                                        ViInt32 channel);
ViStatus _VI_FUNC agena_actMeasureCalData (ViSession instrumentHandle,
                                           ViInt32 channel, ViInt32 standard,
                                           ViInt32 port1_Response,
                                           ViInt32 port2_Stimulus);
ViStatus _VI_FUNC agena_actCalculateCalCoef (ViSession instrumentHandle,
                                             ViInt32 channel);
ViStatus _VI_FUNC agena_actClearCalData (ViSession instrumentHandle,
                                         ViInt32 channel, ViInt32 clear);
ViStatus _VI_FUNC agena_actExecuteECal (ViSession instrumentHandle, ViInt32 channel,
                                        ViInt32 calibration, ViInt32 port1,
                                        ViInt32 port2, ViInt32 port3);
ViStatus _VI_FUNC agena_actMeasurePowerCalData (ViSession instrumentHandle,
                                                ViInt32 channel, ViInt32 port,
                                                ViInt32 sensor);
ViStatus _VI_FUNC agena_actCalculateScalarCalCoef (ViSession instrumentHandle,
                                                   ViInt32 channel);
ViStatus _VI_FUNC agena_actClearScalarCalData (ViSession instrumentHandle,
                                               ViInt32 channel, ViInt32 clear);
ViStatus _VI_FUNC agena_actMeasureScalarCalData (ViSession instrumentHandle,
                                                 ViInt32 channel, ViInt32 standard,
                                                 ViInt32 sensor,
                                                 ViInt32 port1_Measurement,
                                                 ViInt32 port2_SpecifiedFreq);
ViStatus _VI_FUNC agena_actExecuteScalarECal (ViSession instrumentHandle,
                                              ViInt32 channel, ViInt32 calibration,
                                              ViInt32 port1, ViInt32 port2);
ViStatus _VI_FUNC agena_actCalculateRecCalCoef (ViSession instrumentHandle,
                                                ViInt32 channel, ViInt32 receiver,
                                                ViInt32 port);
ViStatus _VI_FUNC agena_actTrigger (ViSession instrumentHandle,
                                    ViBoolean ignoreTriggerSource,
                                    ViBoolean waitForOPC);
ViStatus _VI_FUNC agena_actSweepStart (ViSession instrumentHandle, ViInt32 channel);
ViStatus _VI_FUNC agena_actSweepAbort (ViSession instrumentHandle);
ViStatus _VI_FUNC agena_actSweAvgReset (ViSession instrumentHandle,
                                        ViInt32 channel);
ViStatus _VI_FUNC agena_actMarkerSearch (ViSession instrumentHandle,
                                         ViInt32 channel, ViInt32 marker,
                                         ViInt32 function, ViPReal64 xValue,
                                         ViPReal64 yValue);
ViStatus _VI_FUNC agena_actSetMarkerValues (ViSession instrumentHandle,
                                            ViInt32 channel, ViInt32 marker,
                                            ViInt32 markerTo);
ViStatus _VI_FUNC agena_actExecuteAnalysis (ViSession instrumentHandle,
                                            ViInt32 channel);
ViStatus _VI_FUNC agena_actTDomMatchFreqRange (ViSession instrumentHandle,
                                               ViInt32 channel);
ViStatus _VI_FUNC agena_actStoreInstrumentState (ViSession instrumentHandle,
                                                 ViInt32 items,
                                                 ViBoolean storeAllChannelsTraces);
ViStatus _VI_FUNC agena_actStore (ViSession instrumentHandle, ViInt32 dataType,
                                  ViString fileName);
ViStatus _VI_FUNC agena_actRecall (ViSession instrumentHandle, ViInt32 dataType,
                                   ViString fileName);
ViStatus _VI_FUNC agena_actStoreChannelState (ViSession instrumentHandle,
                                              ViInt32 memoryRegister);
ViStatus _VI_FUNC agena_actStoreChannelCoefficient (ViSession instrumentHandle,
                                                    ViInt32 memoryRegister);
ViStatus _VI_FUNC agena_actRecallChannelState (ViSession instrumentHandle,
                                               ViInt32 memoryRegister);
ViStatus _VI_FUNC agena_actRecallChannelCoefficient (ViSession instrumentHandle,
                                                     ViInt32 memoryRegister);
ViStatus _VI_FUNC agena_actClearChannelState (ViSession instrumentHandle);
ViStatus _VI_FUNC agena_actFileManager (ViSession instrumentHandle,
                                        ViInt32 operation, ViString source,
                                        ViString destination);
ViStatus _VI_FUNC agena_actFileTransferToStorage (ViSession instrumentHandle,
                                                  ViString fileName,
                                                  ViInt32 dataBlockSize,
                                                  ViChar _VI_FAR dataBlockArray[]);
ViStatus _VI_FUNC agena_actFileTransferFromStorage (ViSession instrumentHandle,
                                                    ViString fileName,
                                                    ViInt32 bufferSize,
                                                    ViChar _VI_FAR dataBlock[],
                                                    ViPInt32 bytesRead);
ViStatus _VI_FUNC agena_actDirContents (ViSession instrumentHandle,
                                        ViString directory, ViPReal64 usedSize,
                                        ViPReal64 freeSpace, ViInt32 bufferSize,
                                        ViChar _VI_FAR contents[]);
ViStatus _VI_FUNC agena_actHCopy (ViSession instrumentHandle, ViInt32 operation);
ViStatus _VI_FUNC agena_actSystemInfo (ViSession instrumentHandle,
                                       ViPInt32 number_ofChannels,
                                       ViPInt32 number_ofTraces,
                                       ViPInt32 number_ofPorts,
                                       ViPInt32 systemVersion);
ViStatus _VI_FUNC agena_actShutdown (ViSession instrumentHandle);
ViStatus _VI_FUNC agena_actSecurityLevel (ViSession instrumentHandle,
                                          ViInt32 securityLevel);
ViStatus _VI_FUNC agena_actWarmedUp (ViSession instrumentHandle,
                                     ViPBoolean warmedUp);
ViStatus _VI_FUNC agena_actServMode (ViSession instrumentHandle,
                                     ViPBoolean serviceMode);
ViStatus _VI_FUNC agena_dataReadCalDataArr (ViSession instrumentHandle,
                                            ViInt32 channel, ViInt32 port,
                                            ViInt32 arraySize,
                                            ViReal64 _VI_FAR calData[]);
ViStatus _VI_FUNC agena_dataWriteCalDataArr (ViSession instrumentHandle,
                                             ViInt32 channel, ViInt32 port,
                                             ViInt32 arraySize,
                                             ViReal64 _VI_FAR calData[]);
ViStatus _VI_FUNC agena_dataReadDataMemArr (ViSession instrumentHandle,
                                            ViInt32 channel, ViInt32 source,
                                            ViInt32 correction, ViInt32 arraySize,
                                            ViReal64 _VI_FAR primaryReal[],
                                            ViReal64 _VI_FAR secondaryImaginary[]);
ViStatus _VI_FUNC agena_dataWriteDataMemArr (ViSession instrumentHandle,
                                             ViInt32 channel, ViInt32 source,
                                             ViInt32 correction, ViInt32 arraySize,
                                             ViReal64 _VI_FAR primaryReal[],
                                             ViReal64 _VI_FAR secondaryImaginary[]);
ViStatus _VI_FUNC agena_dataReadStimulusArr (ViSession instrumentHandle,
                                             ViInt32 channel, ViInt32 arraySize,
                                             ViReal64 _VI_FAR stimulusData[]);
ViStatus _VI_FUNC agena_dataLimitFail (ViSession instrumentHandle, ViInt32 channel,
                                       ViPBoolean fail);
ViStatus _VI_FUNC agena_dataReadFailMeasPoints (ViSession instrumentHandle,
                                                ViInt32 channel, ViInt32 arraySize,
                                                ViPInt32 number_ofFailedPoints,
                                                ViReal64 _VI_FAR data[]);
ViStatus _VI_FUNC agena_dataMarkerData (ViSession instrumentHandle, ViInt32 channel,
                                        ViInt32 marker, ViPReal64 xValue,
                                        ViPReal64 realValue,
                                        ViPReal64 imaginaryValue);
ViStatus _VI_FUNC agena_dataMathMarkerData (ViSession instrumentHandle,
                                            ViInt32 channel,
                                            ViInt32 markerFunction,
                                            ViReal64 *num1, ViReal64 *num2,
                                            ViReal64 *num3, ViReal64 *num4);
ViStatus _VI_FUNC agena_dataMarkerBandwidthSearchResult (ViSession instrumentHandle,
                                                         ViInt32 channel,
                                                         ViInt32 marker,
                                                         ViPReal64 bandwidth,
                                                         ViPReal64 centerFrequency,
                                                         ViPReal64 qValue,
                                                         ViPReal64 loss);
ViStatus _VI_FUNC agena_dataMarkerNotchSearchResult (ViSession instrumentHandle,
                                                     ViReal64 *bandwidth,
                                                     ViReal64 *centerFrequency,
                                                     ViInt32 channel,
                                                     ViInt32 marker,
                                                     ViReal64 *qValue,
                                                     ViReal64 *loss);
ViStatus _VI_FUNC agena_dataReadAnalysisResult (ViSession instrumentHandle,
                                                ViInt32 channel, ViInt32 arraySize,
                                                ViPInt32 number_ofAnalysisResults,
                                                ViReal64 _VI_FAR stimulus[],
                                                ViReal64 _VI_FAR response[]);
ViStatus _VI_FUNC agena_dataReadHandlerInput (ViSession instrumentHandle,
                                              ViInt32 port, ViPInt32 data);
ViStatus _VI_FUNC agena_dataWriteHandlerOutput (ViSession instrumentHandle,
                                                ViInt32 port, ViInt32 data);
ViStatus _VI_FUNC agena_dataTraceStatisticAnalysisResult (ViSession instrumentHandle,
                                                          ViInt32 channel,
                                                          ViPReal64 mean,
                                                          ViPReal64 standardDeviation,
                                                          ViPReal64 peak_toPeak);
ViStatus _VI_FUNC agena_reset (ViSession instrumentHandle);
ViStatus _VI_FUNC agena_self_test (ViSession instrumentHandle,
                                   ViPInt16 selfTestResult,
                                   ViChar _VI_FAR selfTestMessage[]);
ViStatus _VI_FUNC agena_error_query (ViSession instrumentHandle, ViPInt32 errorCode,
                                     ViChar _VI_FAR errorMessage[]);
ViStatus _VI_FUNC agena_error_message (ViSession instrumentHandle,
                                       ViStatus statusCode,
                                       ViChar _VI_FAR message[]);
ViStatus _VI_FUNC agena_revision_query (ViSession instrumentHandle,
                                        ViChar _VI_FAR instrumentDriverRevision[],
                                        ViChar _VI_FAR firmwareRevision[]);
ViStatus _VI_FUNC agena_close (ViSession instrumentHandle);
