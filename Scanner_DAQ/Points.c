/******************************************************************************
*																			  *
*	Filename:	Points.c							     					  *
*	Date:		11 March 2007												  *
*																			  *
******************************************************************************/

#include <utility.h>
#include "inifile.h"
#include <ansi_c.h>
#include <userint.h>
#include "Defines.h"
#include "Setup.h"
#include "Points.h"


//*****************************************************************************
//	Variable Declarations
//

extern int hPanelMain;

extern struct FPPosGen {
	int iNumCol;
	double dPosFirstCol;
	double dPosLastCol;
	int iNumRow;
	double dPosFirstRow;
	double dPosLastRow;
}FPPosGenNums;

extern struct FP2PosGen {				
	int iNumCol;
	double dPosCol[1000];
	int iNumRow;
	double dPosRow[1000];
}FP2PosGenNums;


extern struct FPPoint {
	double x;   //width
	double y;   //height
}theFPPoints[100000];

extern int iNumFPPoints;

extern int iCurrentFPPoint;

static double dColDisplayScaling = 100.0 / 84.0;
static double dRowDisplayScaling = 100.0 / 82.0;


extern double posXInInches;
extern double posYInInches;

extern iFPPosValid;


//*****************************************************************************
//	Functions
//

void calcFPPositions(void)
// Fixed Delta Panel
// loads the final x & y values into theFPPoints structure array that is used during the experiment
{
int iCol;
int iRow;
int iPointNum;
double dColSpacing;
double dColPos;
double dRowSpacing;
double dRowPos;
char strPointNum[64];

	iCurrentFPPoint = -1;

	iNumFPPoints = FPPosGenNums.iNumCol * FPPosGenNums.iNumRow;
	DebugPrintf("iNumFPPoints = %d", iNumFPPoints);
	
	
	if( FPPosGenNums.iNumCol == 1 ) {
		dColSpacing = 0.0;
	}
	else {
		dColSpacing = ( FPPosGenNums.dPosLastCol - FPPosGenNums.dPosFirstCol ) / (double)( FPPosGenNums.iNumCol - 1 ); 
	}
	
	
	if( FPPosGenNums.iNumRow == 1 ) {
		dRowSpacing = 0.0;
	}
	else {
		dRowSpacing = ( FPPosGenNums.dPosLastRow - FPPosGenNums.dPosFirstRow ) / (double)( FPPosGenNums.iNumRow - 1 ); 
	}
	
	ClearListCtrl (hPanelMain, FIELDPROBE_RING_GOTO_POS);
	
	dRowPos = FPPosGenNums.dPosFirstRow;
	
	iPointNum = 0;
	for( iRow = 1; iRow <= FPPosGenNums.iNumRow; iRow++ ) {
	
		dColPos = FPPosGenNums.dPosFirstCol;
	
		for( iCol = 1; iCol <= FPPosGenNums.iNumCol; iCol++ ) {
	
			theFPPoints[iPointNum].x = dColPos;
			theFPPoints[iPointNum].y = dRowPos;
			
			sprintf( strPointNum, "%d", iPointNum + 1 );
			InsertListItem (hPanelMain, FIELDPROBE_RING_GOTO_POS, -1, strPointNum, iPointNum);
			
			iPointNum++;
			dColPos += dColSpacing;
		}
		
		dRowPos += dRowSpacing;

	}
	
	
	SetCtrlVal (hPanelMain, FIELDPROBE_NUM_COL_SPACING, dColSpacing);
	SetCtrlVal (hPanelMain, FIELDPROBE_NUM_ROW_SPACING, dRowSpacing);
	
	
//	SetCtrlVal (hPanelMain, FIELDPROBE_TEXTMSG_FILE, "File = None");
	

}


void calcFP2Positions(void)
// Random Delta Panel
// loads the final x & y values into theFPPoints structure array that is used during the experiment
{
//int iCol;
//int iRow;
int iPointNum;
//double dColSpacing;
//double dColPos;
//double dRowSpacing;
//double dRowPos;
char strPointNum[64];
int index_x, index_y;

	iCurrentFPPoint = -1;

	iNumFPPoints = FP2PosGenNums.iNumCol * FP2PosGenNums.iNumRow;
	
	
	
//	if( FP2PosGenNums.iNumCol == 1 ) {
//		dColSpacing = 0.0;
//	}
//	else {
//		dColSpacing = ( FPPosGenNums.dPosLastCol - FPPosGenNums.dPosFirstCol ) / (double)( FPPosGenNums.iNumCol - 1 ); 
//	}
	
	
//	if( FPPosGenNums.iNumRow == 1 ) {
//		dRowSpacing = 0.0;
//	}
//	else {
//		dRowSpacing = ( FPPosGenNums.dPosLastRow - FPPosGenNums.dPosFirstRow ) / (double)( FPPosGenNums.iNumRow - 1 ); 
//	}
	
	ClearListCtrl (hPanelMain, FIELDPROBE_RING_GOTO_POS);
	
//	dRowPos = FPPosGenNums.dPosFirstRow;
	
	iPointNum = 0;
	for( index_y = 1; index_y <= FP2PosGenNums.iNumRow; index_y++ )
	{
		
		for( index_x = 1; index_x <= FP2PosGenNums.iNumCol; index_x++ )
		{
	
			theFPPoints[iPointNum].x = FP2PosGenNums.dPosCol[index_x];
			theFPPoints[iPointNum].y = FP2PosGenNums.dPosRow[index_y];
			
			DebugPrintf("%f, %f\n", theFPPoints[iPointNum].x, theFPPoints[iPointNum].y);
			sprintf( strPointNum, "%d", iPointNum + 1 );
			InsertListItem (hPanelMain, FIELDPROBE_RING_GOTO_POS, -1, strPointNum, iPointNum);
			
			iPointNum++;
		}

	}
	
	
//	SetCtrlVal (hPanelMain, FIELDPROBE_TEXTMSG_FILE_2, "File = None");
	

}



// ********************************************************************************************************

void displayFPPositions(void)
{
int iCount1;
char strNum[64];




	SetCtrlAttribute (hPanelMain, FIELDPROBE_GRAPH_FP, ATTR_SHIFT_TEXT_PLOTS, 0);

	DeleteGraphPlot (hPanelMain, FIELDPROBE_GRAPH_FP, -1, VAL_IMMEDIATE_DRAW);
	
	
	
	PlotLine (hPanelMain, FIELDPROBE_GRAPH_FP, 0, 0, 0, 100, VAL_GRAY);
	PlotLine (hPanelMain, FIELDPROBE_GRAPH_FP, 0, 0, 100, 0, VAL_GRAY);
	PlotLine (hPanelMain, FIELDPROBE_GRAPH_FP, 100, 0, 100, 100, VAL_GRAY);
	PlotLine (hPanelMain, FIELDPROBE_GRAPH_FP, 0, 100, 100, 100, VAL_GRAY);
	
	
	
	for( iCount1 = 0; iCount1 < iNumFPPoints; iCount1++ ){
	
		sprintf( strNum, "%d", iCount1 + 1 );

		PlotPoint (hPanelMain, FIELDPROBE_GRAPH_FP, dColDisplayScaling * theFPPoints[iCount1].x,
				   dRowDisplayScaling * theFPPoints[iCount1].y, VAL_EMPTY_CIRCLE, VAL_WHITE);
	
	
	
		PlotText (hPanelMain, FIELDPROBE_GRAPH_FP, dColDisplayScaling * theFPPoints[iCount1].x,
				  dRowDisplayScaling * theFPPoints[iCount1].y, strNum, VAL_APP_META_FONT, VAL_GRAY,
				  VAL_TRANSPARENT);
	
	
	}
	
	displayPos( );

}

// ********************************************************************************************************

void displayPos( void )
{
static int hPos;
char msg[64];
int iStatus;

//	DeleteGraphPlot (hPanelMain, FIELDPROBE_GRAPH_FP, hPos, VAL_IMMEDIATE_DRAW);
	

	hPos = PlotPoint (hPanelMain, FIELDPROBE_GRAPH_FP,
			   		  dColDisplayScaling * posXInInches,
			   		  dRowDisplayScaling * posYInInches, VAL_SOLID_CIRCLE,
			   		  VAL_YELLOW);




	SetCtrlVal (hPanelMain, FIELDPROBE_NUM_CUR_POS_HORZ, posXInInches);
	SetCtrlVal (hPanelMain, FIELDPROBE_NUM_CUR_POS_VERT, posYInInches);
	
	if( iCurrentFPPoint == -1 ) 
	{
		sprintf( msg, "Changed" );
	}
	else {
		sprintf( msg, "%d of %d", iCurrentFPPoint + 1, iNumFPPoints );
	}
	iStatus = SetCtrlVal (hPanelMain, FIELDPROBE_TM_SCAN_POS, msg);
	

}

							   
// ********************************************************************************************************

int saveFPPosFile( void )
{
char strPath[MAX_PATHNAME_LEN];
IniText hTheData;
int iStatus;
char strMsg[1024];
char strFile[1024];

	iStatus = FileSelectPopup ("", "*.fpp", "*.fpp", "Enter File Name To Save To",
							   VAL_SAVE_BUTTON, 0, 1, 1, 1, strPath);
							   
	if( ( iStatus == VAL_EXISTING_FILE_SELECTED ) || ( iStatus == VAL_NEW_FILE_SELECTED ) ) {
	
		hTheData = Ini_New (1);
		
		iStatus = Ini_PutInt    (hTheData, "POINT_ARRAY", "NUMBER_COL",    FPPosGenNums.iNumCol);
		iStatus = Ini_PutDouble (hTheData, "POINT_ARRAY", "POS_FIRST_COL", FPPosGenNums.dPosFirstCol );
		iStatus = Ini_PutDouble (hTheData, "POINT_ARRAY", "POS_LAST_COL",  FPPosGenNums.dPosLastCol );

		iStatus = Ini_PutInt    (hTheData, "POINT_ARRAY", "NUMBER_ROW",    FPPosGenNums.iNumRow);
		iStatus = Ini_PutDouble (hTheData, "POINT_ARRAY", "POS_FIRST_ROW", FPPosGenNums.dPosFirstRow );
		iStatus = Ini_PutDouble (hTheData, "POINT_ARRAY", "POS_LAST_ROW",  FPPosGenNums.dPosLastRow );
		
		Ini_WriteToFile( hTheData, strPath );
		
		Ini_Dispose( hTheData );
		
		
		SplitPath (strPath, NULL, NULL, strFile);
		sprintf( strMsg, "File = %s", strFile );
		SetCtrlVal (hPanelMain, FIELDPROBE_TEXTMSG_FILE, strMsg);

		
	}
		

	return 0;
}  

// ********************************************************************************************************

int loadFPPosFile( void )
{
char strPath[MAX_PATHNAME_LEN];
IniText hTheData;
int iStatus;
struct FPPosGen tempNums;
struct FP2PosGen temp2Nums;   
char strMsg[512];
char strFile[512];
int index;
int temp;

	GetCtrlAttribute (hPanelMain, FIELDPROBE_BINARYSWITCH, ATTR_CTRL_VAL , &temp);
	if (temp == 0)
	{
		iStatus = FileSelectPopup ("", "*.fpp", "*.fpp", "Enter File Name To Load From",
								   VAL_LOAD_BUTTON, 0, 1, 1, 0, strPath);
							   
		if( iStatus == VAL_EXISTING_FILE_SELECTED )
		{
			hTheData = Ini_New (1);
		
			iStatus = Ini_ReadFromFile( hTheData, strPath );
			if( iStatus != 0 ) {
				sprintf( strMsg, "Could Not Open %s.", strPath );
				MessagePopup ("Error", strMsg);
				return( -1 );
			}

		
			iStatus = Ini_GetInt(hTheData, "POINT_ARRAY", "NUMBER_COL",    &tempNums.iNumCol);
			if( iStatus <= 0 ) {
				sprintf( strMsg, "Could Not Load %s.\nFile Corrupted Or Missing Required Entries", strPath );
				MessagePopup ("Error", strMsg);
				return( -1 );
			}
			iStatus = Ini_GetDouble (hTheData, "POINT_ARRAY", "POS_FIRST_COL", &tempNums.dPosFirstCol );
			if( iStatus <= 0 ) {
				sprintf( strMsg, "Could Not Load %s.\nFile Corrupted Or Missing Required Entries", strPath );
				MessagePopup ("Error", strMsg);
				return( -1 );
			}
			iStatus = Ini_GetDouble (hTheData, "POINT_ARRAY", "POS_LAST_COL",  &tempNums.dPosLastCol );
			if( iStatus <= 0 ) {
				sprintf( strMsg, "Could Not Load %s.\nFile Corrupted Or Missing Required Entries", strPath );
				MessagePopup ("Error", strMsg);
				return( -1 );
			}

			iStatus = Ini_GetInt(hTheData, "POINT_ARRAY", "NUMBER_ROW",    &tempNums.iNumRow);
			if( iStatus <= 0 ) {
				sprintf( strMsg, "Could Not Load %s.\nFile Corrupted Or Missing Required Entries", strPath );
				MessagePopup ("Error", strMsg);
				return( -1 );
			}
			iStatus = Ini_GetDouble (hTheData, "POINT_ARRAY", "POS_FIRST_ROW", &tempNums.dPosFirstRow );
			if( iStatus <= 0 ) {
				sprintf( strMsg, "Could Not Load %s.\nFile Corrupted Or Missing Required Entries", strPath );
				MessagePopup ("Error", strMsg);
				return( -1 );
			}
			iStatus = Ini_GetDouble (hTheData, "POINT_ARRAY", "POS_LAST_ROW",  &tempNums.dPosLastRow );
			if( iStatus <= 0 ) {
				sprintf( strMsg, "Could Not Load %s.\nFile Corrupted Or Missing Required Entries", strPath );
				MessagePopup ("Error", strMsg);
				return( -1 );
			}
		
		
			Ini_Dispose( hTheData );
		
			SetCtrlVal (hPanelMain, FIELDPROBE_NUM_NUM_COL, 		 tempNums.iNumCol);
			SetCtrlVal (hPanelMain, FIELDPROBE_NUM_START_COL_POS, tempNums.dPosFirstCol);
			SetCtrlVal (hPanelMain, FIELDPROBE_NUM_LAST_COL_POS,  tempNums.dPosLastCol);
	

			SetCtrlVal (hPanelMain, FIELDPROBE_NUM_NUM_ROWS, 	 tempNums.iNumRow);
			SetCtrlVal (hPanelMain, FIELDPROBE_NUM_START_ROW_POS, tempNums.dPosFirstRow);
			SetCtrlVal (hPanelMain, FIELDPROBE_NUM_LAST_ROW_POS,  tempNums.dPosLastRow);
		
			calcFP_Points (hPanelMain, FIELDPROBE_NUM_NUM_COL, EVENT_COMMIT, NULL, 0, 0);
		
		
			SplitPath (strPath, NULL, NULL, strFile);
			sprintf( strMsg, "File = %s", strFile );
			SetCtrlVal (hPanelMain, FIELDPROBE_TEXTMSG_FILE, strMsg);
		}		
		
	}
	else
	{

		iStatus = FileSelectPopup ("", "*.fp2", "*.fp2", "Enter File Name To Load From",
								   VAL_LOAD_BUTTON, 0, 1, 1, 0, strPath);

		if( iStatus == VAL_EXISTING_FILE_SELECTED )
		{
			hTheData = Ini_New (1);
			iStatus = Ini_ReadFromFile( hTheData, strPath );
			if( iStatus != 0 )
			{
				sprintf( strMsg, "Could Not Open %s.", strPath );
				MessagePopup ("Error", strMsg);
				return( -1 );
			}

			iStatus = Ini_GetInt(hTheData, "POINT_ARRAY2", "COLUMNS", &temp2Nums.iNumCol);
			if( iStatus <= 0 )
			{
				sprintf( strMsg, "Could Not Load %s.\nFile Corrupted Or Missing Required Entries", strPath );
				MessagePopup ("Error", strMsg);
				return( -1 );
			}

			for (index = 1; index <= temp2Nums.iNumCol; index++)
			{
				sprintf( strMsg, "POS_COL_%d", index);
				iStatus = Ini_GetDouble (hTheData, "POINT_ARRAY2", strMsg, &temp2Nums.dPosCol[index] );
				if( iStatus <= 0 )
				{
					sprintf( strMsg, "Could Not Load %s.\nFile Corrupted Or Missing Required Entries", strPath );
					MessagePopup ("Error", strMsg);
					return( -1 );
				}
			}

			iStatus = Ini_GetInt(hTheData, "POINT_ARRAY2", "ROWS", &temp2Nums.iNumRow);
			if( iStatus <= 0 )
			{
				sprintf( strMsg, "Could Not Load %s.\nFile Corrupted Or Missing Required Entries", strPath );
				MessagePopup ("Error", strMsg);
				return( -1 );
			}
			for (index = 1; index <= temp2Nums.iNumRow; index++)
			{
				sprintf( strMsg, "POS_ROW_%d", index);
				iStatus = Ini_GetDouble (hTheData, "POINT_ARRAY2", strMsg, &temp2Nums.dPosRow[index] );
				if( iStatus <= 0 )
				{
					sprintf( strMsg, "Could Not Load %s.\nFile Corrupted Or Missing Required Entries", strPath );
					MessagePopup ("Error", strMsg);
					return( -1 );
				}
			}
		
		
			Ini_Dispose( hTheData );
		
			SetCtrlVal (hPanelMain, FIELDPROBE_NUM_NUM_COL_2, temp2Nums.iNumCol);

			SetCtrlVal (hPanelMain, FIELDPROBE_NUM_NUM_ROWS_2, temp2Nums.iNumRow);

			
			SetCtrlVal (hPanelMain, FIELDPROBE_TEXTMSG_FILE_2, "File = None");
		
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

	
			calcFP2Positions( );
			displayFPPositions( ); 
			displayPos();

			SplitPath (strPath, NULL, NULL, strFile);
			sprintf( strMsg, "File = %s", strFile );
			SetCtrlVal (hPanelMain, FIELDPROBE_TEXTMSG_FILE_2, strMsg);
		
		
		}

	}

	return 0;
}

// ********************************************************************************************************



