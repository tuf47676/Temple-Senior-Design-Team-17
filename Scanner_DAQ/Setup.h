/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2008. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  FIELDPROBE                      1
#define  FIELDPROBE_CB_EMERG_STOP        2       /* callback function: emergencyStop */
#define  FIELDPROBE_GRAPH_FP             3
#define  FIELDPROBE_NUM_START_COL_POS    4       /* callback function: calcFP_Points */
#define  FIELDPROBE_NUM_LAST_COL_POS     5       /* callback function: calcFP_Points */
#define  FIELDPROBE_NUM_LAST_ROW_POS     6       /* callback function: calcFP_Points */
#define  FIELDPROBE_NUM_START_ROW_POS    7       /* callback function: calcFP_Points */
#define  FIELDPROBE_NUM_NUM_ROWS_2       8
#define  FIELDPROBE_NUM_NUM_ROWS         9       /* callback function: calcFP_Points */
#define  FIELDPROBE_NUM_NUM_COL_2        10
#define  FIELDPROBE_NUM_NUM_COL          11      /* callback function: calcFP_Points */
#define  FIELDPROBE_CB_SAVE_FP_POS_FILE  12      /* callback function: saveFile */
#define  FIELDPROBE_CB_GO_FIRST_POS      13      /* callback function: goFirstPosition */
#define  FIELDPROBE_CB_GO_NEXT_POS       14      /* callback function: goNextPosition */
#define  FIELDPROBE_DECORATION_5         15
#define  FIELDPROBE_RING_GOTO_POS        16      /* callback function: gotoSelectedPosition */
#define  FIELDPROBE_DECORATION_4         17
#define  FIELDPROBE_DECORATION_6         18
#define  FIELDPROBE_DECORATION_3         19
#define  FIELDPROBE_NUM_CUR_POS_VERT     20
#define  FIELDPROBE_NUM_ROW_SPACING      21
#define  FIELDPROBE_NUM_CUR_POS_HORZ     22
#define  FIELDPROBE_NUM_COL_SPACING      23
#define  FIELDPROBE_CB_LOAD_FP_POS_FILE_2 24     /* callback function: loadFile2 */
#define  FIELDPROBE_CB_LOAD_FP_POS_FILE  25      /* callback function: loadFile */
#define  FIELDPROBE_TEXTMSG_FILE_2       26
#define  FIELDPROBE_TEXTMSG_FILE         27
#define  FIELDPROBE_TM_SCAN_POS          28
#define  FIELDPROBE_TEXTMSG              29
#define  FIELDPROBE_GRID_NA_SETTINGS     30
#define  FIELDPROBE_CB_netsetup          31      /* callback function: network_setup */
#define  FIELDPROBE_CB_STOP_EXP          32      /* callback function: stopExperiment */
#define  FIELDPROBE_CB_BEGIN_EXP         33      /* callback function: beginExperiment */
#define  FIELDPROBE_CB_quit              34      /* callback function: quit */
#define  FIELDPROBE_TIMER1               35      /* callback function: collectAndDisplay */
#define  FIELDPROBE_BINARYSWITCH         36      /* callback function: position_data_type */
#define  FIELDPROBE_TEXTMSG_EXP          37

#define  NETSETUP                        2
#define  NETSETUP_NUMERIC_stopfreq       2
#define  NETSETUP_NUMERIC_startfreq      3
#define  NETSETUP_DECORATION_1           4
#define  NETSETUP_DECORATION_18          5
#define  NETSETUP_DECORATION_2           6
#define  NETSETUP_NUMERIC_ifbandwidth2   7
#define  NETSETUP_NUMERIC_aver2          8
#define  NETSETUP_NUMERIC_numpoints2     9
#define  NETSETUP_SPLITTER               10
#define  NETSETUP_RING_meas2_16          11
#define  NETSETUP_RING_meas2_12          12
#define  NETSETUP_RING_meas2_15          13
#define  NETSETUP_RING_meas2_8           14
#define  NETSETUP_RADIO_active2_16       15      /* callback function: active2_16 */
#define  NETSETUP_DECORATION_2_16        16
#define  NETSETUP_RING_meas2_13          17
#define  NETSETUP_RING_meas2_14          18
#define  NETSETUP_TEXTMSG_2_16           19
#define  NETSETUP_RING_meas2_11          20
#define  NETSETUP_RADIO_active2_15       21      /* callback function: active2_15 */
#define  NETSETUP_DECORATION_2_15        22
#define  NETSETUP_RADIO_active2_13       23      /* callback function: active2_13 */
#define  NETSETUP_DECORATION_2_13        24
#define  NETSETUP_TEXTMSG_2_13           25
#define  NETSETUP_TEXTMSG_2_15           26
#define  NETSETUP_RADIO_active2_14       27      /* callback function: active2_14 */
#define  NETSETUP_DECORATION_2_14        28
#define  NETSETUP_TEXTMSG_2_14           29
#define  NETSETUP_RING_meas2_4           30
#define  NETSETUP_RADIO_active2_12       31      /* callback function: active2_12 */
#define  NETSETUP_DECORATION_2_12        32
#define  NETSETUP_RING_meas2_9           33
#define  NETSETUP_RING_meas2_10          34
#define  NETSETUP_TEXTMSG_2_12           35
#define  NETSETUP_RING_meas2_7           36
#define  NETSETUP_RADIO_active2_11       37      /* callback function: active2_11 */
#define  NETSETUP_DECORATION_2_11        38
#define  NETSETUP_RADIO_active2_9        39      /* callback function: active2_9 */
#define  NETSETUP_DECORATION_2_9         40
#define  NETSETUP_TEXTMSG_2_9            41
#define  NETSETUP_TEXTMSG_2_11           42
#define  NETSETUP_RADIO_active2_10       43      /* callback function: active2_10 */
#define  NETSETUP_DECORATION_2_10        44
#define  NETSETUP_TEXTMSG_2_10           45
#define  NETSETUP_TEXTMSG_28             46
#define  NETSETUP_RADIO_active2_8        47      /* callback function: active2_8 */
#define  NETSETUP_DECORATION_2_8         48
#define  NETSETUP_RING_meas2_5           49
#define  NETSETUP_RING_meas2_6           50
#define  NETSETUP_TEXTMSG_2_8            51
#define  NETSETUP_RING_meas2_3           52
#define  NETSETUP_RADIO_active2_7        53      /* callback function: active2_7 */
#define  NETSETUP_DECORATION_2_7         54
#define  NETSETUP_RADIO_active2_5        55      /* callback function: active2_5 */
#define  NETSETUP_DECORATION_2_5         56
#define  NETSETUP_TEXTMSG_2_5            57
#define  NETSETUP_TEXTMSG_2_7            58
#define  NETSETUP_RADIO_active2_6        59      /* callback function: active2_6 */
#define  NETSETUP_DECORATION_2_6         60
#define  NETSETUP_TEXTMSG_2_6            61
#define  NETSETUP_RADIO_active2_4        62      /* callback function: active2_4 */
#define  NETSETUP_DECORATION_2_4         63
#define  NETSETUP_RING_meas2_2           64
#define  NETSETUP_TEXTMSG_2_4            65
#define  NETSETUP_SPLITTER_3             66
#define  NETSETUP_RADIO_active2_3        67      /* callback function: active2_3 */
#define  NETSETUP_DECORATION_2_3         68
#define  NETSETUP_RING_meas2_1           69
#define  NETSETUP_TEXTMSG_2_3            70
#define  NETSETUP_DECORATION_2_1         71
#define  NETSETUP_RADIO_active2_1        72      /* callback function: active2_1 */
#define  NETSETUP_RADIO_active2_2        73      /* callback function: active2_2 */
#define  NETSETUP_DECORATION_2_2         74
#define  NETSETUP_TEXTMSG_2_1            75
#define  NETSETUP_TEXTMSG_2_2            76
#define  NETSETUP_RING_sweepmode2        77
#define  NETSETUP_RING_sweeptype2        78
#define  NETSETUP_NUMERIC_ifbandwidth1   79
#define  NETSETUP_NUMERIC_aver1          80
#define  NETSETUP_NUMERIC_numpoints1     81
#define  NETSETUP_NUMERIC_powerlevel     82
#define  NETSETUP_RING_meas1_16          83
#define  NETSETUP_RING_meas1_12          84
#define  NETSETUP_RING_meas1_15          85
#define  NETSETUP_RING_meas1_8           86
#define  NETSETUP_RADIO_active1_16       87      /* callback function: active1_16 */
#define  NETSETUP_DECORATION_1_16        88
#define  NETSETUP_RING_meas1_13          89
#define  NETSETUP_RING_meas1_14          90
#define  NETSETUP_TEXTMSG_1_16           91
#define  NETSETUP_RING_meas1_11          92
#define  NETSETUP_RADIO_active1_15       93      /* callback function: active1_15 */
#define  NETSETUP_DECORATION_1_15        94
#define  NETSETUP_RADIO_active1_13       95      /* callback function: active1_13 */
#define  NETSETUP_DECORATION_1_13        96
#define  NETSETUP_TEXTMSG_1_13           97
#define  NETSETUP_TEXTMSG_1_15           98
#define  NETSETUP_RADIO_active1_14       99      /* callback function: active1_14 */
#define  NETSETUP_DECORATION_1_14        100
#define  NETSETUP_TEXTMSG_1_14           101
#define  NETSETUP_RING_meas1_4           102
#define  NETSETUP_RADIO_active1_12       103     /* callback function: active1_12 */
#define  NETSETUP_DECORATION_1_12        104
#define  NETSETUP_RING_meas1_9           105
#define  NETSETUP_RING_meas1_10          106
#define  NETSETUP_TEXTMSG_1_12           107
#define  NETSETUP_RING_meas1_7           108
#define  NETSETUP_RADIO_active1_11       109     /* callback function: active1_11 */
#define  NETSETUP_DECORATION_1_11        110
#define  NETSETUP_RADIO_active1_9        111     /* callback function: active1_9 */
#define  NETSETUP_DECORATION_1_9         112
#define  NETSETUP_TEXTMSG_1_9            113
#define  NETSETUP_TEXTMSG_1_11           114
#define  NETSETUP_RADIO_active1_10       115     /* callback function: active1_10 */
#define  NETSETUP_DECORATION_1_10        116
#define  NETSETUP_TEXTMSG_1_10           117
#define  NETSETUP_TEXTMSG                118
#define  NETSETUP_RADIO_active1_8        119     /* callback function: active1_8 */
#define  NETSETUP_DECORATION_1_8         120
#define  NETSETUP_RING_meas1_5           121
#define  NETSETUP_RING_meas1_6           122
#define  NETSETUP_TEXTMSG_1_8            123
#define  NETSETUP_RING_meas1_3           124
#define  NETSETUP_RADIO_active1_7        125     /* callback function: active1_7 */
#define  NETSETUP_DECORATION_1_7         126
#define  NETSETUP_RADIO_active1_5        127     /* callback function: active1_5 */
#define  NETSETUP_DECORATION_1_5         128
#define  NETSETUP_TEXTMSG_1_5            129
#define  NETSETUP_TEXTMSG_1_7            130
#define  NETSETUP_RADIO_active1_6        131     /* callback function: active1_6 */
#define  NETSETUP_DECORATION_1_6         132
#define  NETSETUP_TEXTMSG_1_6            133
#define  NETSETUP_RADIO_active1_4        134     /* callback function: active1_4 */
#define  NETSETUP_DECORATION_1_4         135
#define  NETSETUP_RING_meas1_2           136
#define  NETSETUP_TEXTMSG_1_4            137
#define  NETSETUP_SPLITTER_2             138
#define  NETSETUP_RADIO_active1_3        139     /* callback function: active1_3 */
#define  NETSETUP_DECORATION_1_3         140
#define  NETSETUP_RING_format1_5         141
#define  NETSETUP_RING_format1_9         142
#define  NETSETUP_RING_format1_13        143
#define  NETSETUP_RING_format1_2         144
#define  NETSETUP_RING_format1_6         145
#define  NETSETUP_RING_format1_10        146
#define  NETSETUP_RING_format1_14        147
#define  NETSETUP_RING_format1_3         148
#define  NETSETUP_RING_format1_7         149
#define  NETSETUP_RING_format1_11        150
#define  NETSETUP_RING_format1_15        151
#define  NETSETUP_RING_format1_4         152
#define  NETSETUP_RING_format1_8         153
#define  NETSETUP_RING_format1_12        154
#define  NETSETUP_RING_format1_16        155
#define  NETSETUP_RING_format2_5         156
#define  NETSETUP_RING_format2_9         157
#define  NETSETUP_RING_format2_13        158
#define  NETSETUP_RING_format2_2         159
#define  NETSETUP_RING_format2_6         160
#define  NETSETUP_RING_format2_10        161
#define  NETSETUP_RING_format2_14        162
#define  NETSETUP_RING_format2_3         163
#define  NETSETUP_RING_format2_7         164
#define  NETSETUP_RING_format2_11        165
#define  NETSETUP_RING_format2_15        166
#define  NETSETUP_RING_format2_4         167
#define  NETSETUP_RING_format2_8         168
#define  NETSETUP_RING_format2_12        169
#define  NETSETUP_RING_format2_16        170
#define  NETSETUP_RING_format2_1         171
#define  NETSETUP_RING_format1_1         172
#define  NETSETUP_RING_meas1_1           173
#define  NETSETUP_TEXTMSG_1_3            174
#define  NETSETUP_DECORATION_1_1         175
#define  NETSETUP_RADIO_active1_2        176     /* callback function: active1_2 */
#define  NETSETUP_DECORATION_1_2         177
#define  NETSETUP_TEXTMSG_1_1            178
#define  NETSETUP_TEXTMSG_1_2            179
#define  NETSETUP_RING_sweepmode1        180
#define  NETSETUP_RING_sweeptype1        181
#define  NETSETUP_RADIO_average_on2      182     /* callback function: average_on2 */
#define  NETSETUP_RADIO_average_on1      183     /* callback function: average_on1 */
#define  NETSETUP_COMMAND_load           184     /* callback function: load_setup */
#define  NETSETUP_COMMAND_save           185     /* callback function: save_setup */
#define  NETSETUP_CB_netsetup_OK         186     /* callback function: netsetup_OK */

#define  PNL_INIT                        3
#define  PNL_INIT_CB_EMERG_STOP          2       /* callback function: emergencyStop */
#define  PNL_INIT_CB_INIT                3       /* callback function: init */
#define  PNL_INIT_TEXTMSG                4


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                         1
#define  MENUBAR_File                    2
#define  MENUBAR_File_New                3
#define  MENUBAR_File_Open               4

#define  MENUBAR_2                       2
#define  MENUBAR_2_File                  2
#define  MENUBAR_2_File_New              3
#define  MENUBAR_2_File_Open             4
#define  MENUBAR_2_File_Save             5


     /* Callback Prototypes: */ 

int  CVICALLBACK active1_10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_11(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_12(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_13(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_14(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_15(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_16(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active1_9(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_11(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_12(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_13(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_14(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_15(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_16(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK active2_9(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK average_on1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK average_on2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK beginExperiment(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK calcFP_Points(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK collectAndDisplay(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK emergencyStop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK goFirstPosition(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK goNextPosition(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK gotoSelectedPosition(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK init(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK load_setup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK loadFile(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK loadFile2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK netsetup_OK(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK network_setup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK position_data_type(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK save_setup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK saveFile(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stopExperiment(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
