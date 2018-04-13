#pragma once
#include "TraceControlEdit.h"
#include "CurrentlyScanning.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <iterator> //For split function
#include <Windows.h>
#include <cmath>
#include <chrono>
#include <ctime>
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visatype.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visaext.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visaext.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visa.h"

//Mention Visa connection string here.
#define DEFAULT_LOGICAL_ADDRESS "TCPIP0::192.168.100.5::inst0::INSTR"

//Function Prototypes
//
bool InitPort(HANDLE *hComm, char ComPortName[]); //open serial port, set parameters & timeouts
bool SetRxMask(HANDLE *hComm);
bool ClosePort(HANDLE *hComm, char ComPortName[]); //close serial port
bool WriteCmd(HANDLE *hComm, char lpBuffer[], char ComPortName[]);
bool ReadRsp(HANDLE *hComm, char ComPortName[]);
bool GoHome(HANDLE *hComm, char ComPortName[]);
bool SetAcelandVel(HANDLE *hComm, char ComPortName[]);
double ConvertCmtoSteps(double cm);
int ConvertStepstoSeconds(int steps);
bool GoToFirstPos(HANDLE *hComm, char ComPortName[], int xstart_steps, int ystart_steps);
bool GoToNextPos(HANDLE * hComm, char ComPortName[], int xstep_size, int ystep_size, int xPoints,
	int yPoints, int row_size, int x_index, int y_index, bool new_line, bool line_scan);

HANDLE hComm;                          // Handle to the Serial port	
char   ComPortName[] = "COM1";         // Name of the Serial port(May Change) to be opened
BOOL   Status;
DWORD dwEventMask, NoBytesRead;        // Event mask to trigger
char  TempChar, SerialBuffer[256];     // Buffer Containing Rxed Data, Bytes read by ReadFile()
int i = 0;
bool scan = 1;


//char instAdd[] = DEFAULT_LOGICAL_ADDRESS;

//Error checking constraights
#define FREQ_MAX 20000000000 //Set to 20GHz
#define FREQ_MIN 300000 //Set to 300kHz


//Global Strings for VISA lib. Change scope of these later
//this might no longer be needed. Should remove if possible
//char strResult[256] = { 0 };
//char noErrString[256] = { "+0,\"No error\"\n" };




namespace Design_Project {
	std::string folderPath;
	std::string experimentName;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			std::cout << "\nApplication Start Time: ";

			std::time_t AppStart = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::cout << std::ctime(&AppStart);
			std::cout << "\n\n";
			
			//Update NA info
			ViSession viDefaultRM, Instrument;
			ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
			ViUInt32 actual;
			viOpenDefaultRM(&viDefaultRM);
			viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);

			lbl_ipAdress->Text = DEFAULT_LOGICAL_ADDRESS;
			sendSCPI_String("*IDN?", &Instrument);
			lbl_IDN_resp->Text = convert_string_vcppString(readSCPI_Buffer(&Instrument));

			//Disable scan buttons
			SetCMDButton->Enabled = FALSE;
			btn_ecal->Enabled = FALSE;
			btn_StartScan->Enabled = FALSE;


		}
		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

		//int TrNumber, boolean enable, int TrType, int TrSParam

	private: int Tr1Type, Tr2Type, Tr3Type, Tr4Type;
	private: int Tr1Enable, Tr2Enable, Tr3Enable, Tr4Enable;
	private: int Tr1SParam, Tr2SParam, Tr3SParam, Tr4SParam;
		double xstart_cm, xstop_cm, ystart_cm, ystop_cm;
		int xstart_steps, xstop_steps, xPoints, xstep_size;
		int ystart_steps, ystop_steps, yPoints, ystep_size;
		int row_size; //need to know row size to return to start of the row
	
	TraceControlEdit^ trace1 = gcnew TraceControlEdit(this, 1);
	TraceControlEdit^ trace2 = gcnew TraceControlEdit(this, 2);
	TraceControlEdit^ trace3 = gcnew TraceControlEdit(this, 3);
	TraceControlEdit^ trace4 = gcnew TraceControlEdit(this, 4);
	private: System::Windows::Forms::Label^  lbl_ipAdress;

	private: System::Windows::Forms::Label^  lbl_IDN_resp;
	private: System::Windows::Forms::Label^  lbl_instIDN;
	private: System::Windows::Forms::GroupBox^  Group_Freq;
	private: System::Windows::Forms::TextBox^  SpanTextBox;
	private: System::Windows::Forms::TextBox^  CenterTextBox;
	private: System::Windows::Forms::TextBox^  StopTextBox;
	private: System::Windows::Forms::TextBox^  StartTextBox;
	private: System::Windows::Forms::Label^  SpanFreqLabel;
	private: System::Windows::Forms::Label^  CenterFreqLabel;
	private: System::Windows::Forms::Label^  StopFreqLabel;
	private: System::Windows::Forms::Label^  StartFreqLabel;
	private: System::Windows::Forms::RadioButton^  CenterSpanRadio;
	private: System::Windows::Forms::RadioButton^  StartStopRadio;
	private: System::Windows::Forms::Button^  SetCMDButton;
	private: System::Windows::Forms::GroupBox^  Start_Units;
	private: System::Windows::Forms::RadioButton^  Start_GHz;
	private: System::Windows::Forms::RadioButton^  Start_kHz;
	private: System::Windows::Forms::RadioButton^  Start_MHz;
	private: System::Windows::Forms::GroupBox^  Stop_Units;
	private: System::Windows::Forms::RadioButton^  Stop_kHz;
	private: System::Windows::Forms::RadioButton^  Stop_GHz;
	private: System::Windows::Forms::RadioButton^  Stop_MHz;
	private: System::Windows::Forms::GroupBox^  Span_Units;
	private: System::Windows::Forms::RadioButton^  Span_kHz;
	private: System::Windows::Forms::RadioButton^  Span_MHz;
	private: System::Windows::Forms::RadioButton^  Span_GHz;
	private: System::Windows::Forms::GroupBox^  Center_Units;
	private: System::Windows::Forms::RadioButton^  Center_kHz;
	private: System::Windows::Forms::RadioButton^  Center_MHz;
	private: System::Windows::Forms::RadioButton^  Center_GHz;
	private: System::Windows::Forms::GroupBox^  Group_Power;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::GroupBox^  Power_Units;
	private: System::Windows::Forms::TextBox^  PowerTextBox;
	private: System::Windows::Forms::RadioButton^  Power_dBm;
	private: System::Windows::Forms::GroupBox^  group_NAcomm;

	private: System::Windows::Forms::NumericUpDown^  numBox_Points;
	private: System::Windows::Forms::Label^  lbl_sweeppoints;

	private: System::Windows::Forms::GroupBox^  group_INITScan;

	private: System::Windows::Forms::Button^  btn_ecal;
	private: System::Windows::Forms::GroupBox^  group_foldername;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::Button^  btn_folder;
	private: System::Windows::Forms::Label^  lbl_folderPath;
	private: System::Windows::Forms::Label^  lbl_ExpName;
	private: System::Windows::Forms::Button^  btn_ExpName;
	private: System::Windows::Forms::TextBox^  txtbx_ExpName;
	private: System::Windows::Forms::Label^  lbl_name;
	private: System::Windows::Forms::Button^  btn_StartScan;

























	private: System::Windows::Forms::Button^  btn_LoadSettings;








	private: System::Windows::Forms::GroupBox^  group_Trace;
	private: System::Windows::Forms::Button^  btn_Tr1_Edit;
	private: System::Windows::Forms::Label^  lbl_Tr1_S;
	private: System::Windows::Forms::Label^  lbl_Tr1_Type;
	private: System::Windows::Forms::CheckBox^  chkbx_Tr1_Enable;
	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^  btn_Tr4_Edit;
	private: System::Windows::Forms::Label^  lbl_Tr4_S;
	private: System::Windows::Forms::Label^  lbl_Tr4_Type;
	private: System::Windows::Forms::CheckBox^  chkbx_Tr4_Enable;
	private: System::Windows::Forms::Button^  btn_Tr3_Edit;
	private: System::Windows::Forms::Label^  lbl_Tr3_S;
	private: System::Windows::Forms::Label^  lbl_Tr3_Type;
	private: System::Windows::Forms::CheckBox^  chkbx_Tr3_Enable;
	private: System::Windows::Forms::Button^  btn_Tr2_Edit;
	private: System::Windows::Forms::Label^  lbl_Tr2_S;
	private: System::Windows::Forms::Label^  lbl_Tr2_Type;
private: System::Windows::Forms::Label^  lbl_VisaAdressPropmt;
private: System::Windows::Forms::GroupBox^  group_AntennaPos;
private: System::Windows::Forms::GroupBox^  group_YDim;
private: System::Windows::Forms::NumericUpDown^  numbox_Ypoints;


private: System::Windows::Forms::Label^  lbl_YDim_Points;
private: System::Windows::Forms::TextBox^  txtbx_YStop;

private: System::Windows::Forms::TextBox^  txtbx_YStart;

private: System::Windows::Forms::Label^  lbl_YDim_Stop;
private: System::Windows::Forms::Label^  lbl_YDim_Start;
private: System::Windows::Forms::GroupBox^  group_XDim;
private: System::Windows::Forms::NumericUpDown^  numbox_Xpoints;
private: System::Windows::Forms::TextBox^  txtbx_XStop;


private: System::Windows::Forms::TextBox^  txtbx_XStart;

private: System::Windows::Forms::Label^  lbl_XDim_Points;
private: System::Windows::Forms::Label^  lbl_XDim_Stop;
private: System::Windows::Forms::Label^  lbl_XDim_Start;
private: System::Windows::Forms::GroupBox^  group_PreformScan;
private: System::Windows::Forms::Label^  lbl_loadSettings;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  lbl_initScan_steps;
private: System::Windows::Forms::Button^  btn_ScannerHome;
private: System::Windows::Forms::Button^  btnFirst_Pos;


	private: System::Windows::Forms::CheckBox^  chkbx_Tr2_Enable;


	#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lbl_ipAdress = (gcnew System::Windows::Forms::Label());
			this->lbl_IDN_resp = (gcnew System::Windows::Forms::Label());
			this->lbl_instIDN = (gcnew System::Windows::Forms::Label());
			this->Group_Freq = (gcnew System::Windows::Forms::GroupBox());
			this->numBox_Points = (gcnew System::Windows::Forms::NumericUpDown());
			this->Span_Units = (gcnew System::Windows::Forms::GroupBox());
			this->Span_kHz = (gcnew System::Windows::Forms::RadioButton());
			this->Span_MHz = (gcnew System::Windows::Forms::RadioButton());
			this->Span_GHz = (gcnew System::Windows::Forms::RadioButton());
			this->lbl_sweeppoints = (gcnew System::Windows::Forms::Label());
			this->Center_Units = (gcnew System::Windows::Forms::GroupBox());
			this->Center_kHz = (gcnew System::Windows::Forms::RadioButton());
			this->Center_MHz = (gcnew System::Windows::Forms::RadioButton());
			this->Center_GHz = (gcnew System::Windows::Forms::RadioButton());
			this->Stop_Units = (gcnew System::Windows::Forms::GroupBox());
			this->Stop_kHz = (gcnew System::Windows::Forms::RadioButton());
			this->Stop_GHz = (gcnew System::Windows::Forms::RadioButton());
			this->Stop_MHz = (gcnew System::Windows::Forms::RadioButton());
			this->Start_Units = (gcnew System::Windows::Forms::GroupBox());
			this->Start_kHz = (gcnew System::Windows::Forms::RadioButton());
			this->Start_MHz = (gcnew System::Windows::Forms::RadioButton());
			this->Start_GHz = (gcnew System::Windows::Forms::RadioButton());
			this->SpanTextBox = (gcnew System::Windows::Forms::TextBox());
			this->CenterTextBox = (gcnew System::Windows::Forms::TextBox());
			this->StopTextBox = (gcnew System::Windows::Forms::TextBox());
			this->StartTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SpanFreqLabel = (gcnew System::Windows::Forms::Label());
			this->CenterFreqLabel = (gcnew System::Windows::Forms::Label());
			this->StopFreqLabel = (gcnew System::Windows::Forms::Label());
			this->StartFreqLabel = (gcnew System::Windows::Forms::Label());
			this->CenterSpanRadio = (gcnew System::Windows::Forms::RadioButton());
			this->StartStopRadio = (gcnew System::Windows::Forms::RadioButton());
			this->SetCMDButton = (gcnew System::Windows::Forms::Button());
			this->Group_Power = (gcnew System::Windows::Forms::GroupBox());
			this->Power_Units = (gcnew System::Windows::Forms::GroupBox());
			this->Power_dBm = (gcnew System::Windows::Forms::RadioButton());
			this->PowerTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->group_NAcomm = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_VisaAdressPropmt = (gcnew System::Windows::Forms::Label());
			this->group_INITScan = (gcnew System::Windows::Forms::GroupBox());
			this->btn_StartScan = (gcnew System::Windows::Forms::Button());
			this->btn_ecal = (gcnew System::Windows::Forms::Button());
			this->group_foldername = (gcnew System::Windows::Forms::GroupBox());
			this->txtbx_ExpName = (gcnew System::Windows::Forms::TextBox());
			this->lbl_name = (gcnew System::Windows::Forms::Label());
			this->lbl_ExpName = (gcnew System::Windows::Forms::Label());
			this->btn_ExpName = (gcnew System::Windows::Forms::Button());
			this->lbl_folderPath = (gcnew System::Windows::Forms::Label());
			this->btn_folder = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->btn_LoadSettings = (gcnew System::Windows::Forms::Button());
			this->group_Trace = (gcnew System::Windows::Forms::GroupBox());
			this->btn_Tr4_Edit = (gcnew System::Windows::Forms::Button());
			this->lbl_Tr4_S = (gcnew System::Windows::Forms::Label());
			this->lbl_Tr4_Type = (gcnew System::Windows::Forms::Label());
			this->chkbx_Tr4_Enable = (gcnew System::Windows::Forms::CheckBox());
			this->btn_Tr3_Edit = (gcnew System::Windows::Forms::Button());
			this->lbl_Tr3_S = (gcnew System::Windows::Forms::Label());
			this->lbl_Tr3_Type = (gcnew System::Windows::Forms::Label());
			this->chkbx_Tr3_Enable = (gcnew System::Windows::Forms::CheckBox());
			this->btn_Tr2_Edit = (gcnew System::Windows::Forms::Button());
			this->lbl_Tr2_S = (gcnew System::Windows::Forms::Label());
			this->lbl_Tr2_Type = (gcnew System::Windows::Forms::Label());
			this->chkbx_Tr2_Enable = (gcnew System::Windows::Forms::CheckBox());
			this->btn_Tr1_Edit = (gcnew System::Windows::Forms::Button());
			this->lbl_Tr1_S = (gcnew System::Windows::Forms::Label());
			this->lbl_Tr1_Type = (gcnew System::Windows::Forms::Label());
			this->chkbx_Tr1_Enable = (gcnew System::Windows::Forms::CheckBox());
			this->group_AntennaPos = (gcnew System::Windows::Forms::GroupBox());
			this->btn_ScannerHome = (gcnew System::Windows::Forms::Button());
			this->group_YDim = (gcnew System::Windows::Forms::GroupBox());
			this->numbox_Ypoints = (gcnew System::Windows::Forms::NumericUpDown());
			this->lbl_YDim_Points = (gcnew System::Windows::Forms::Label());
			this->txtbx_YStop = (gcnew System::Windows::Forms::TextBox());
			this->txtbx_YStart = (gcnew System::Windows::Forms::TextBox());
			this->lbl_YDim_Stop = (gcnew System::Windows::Forms::Label());
			this->lbl_YDim_Start = (gcnew System::Windows::Forms::Label());
			this->group_XDim = (gcnew System::Windows::Forms::GroupBox());
			this->numbox_Xpoints = (gcnew System::Windows::Forms::NumericUpDown());
			this->txtbx_XStop = (gcnew System::Windows::Forms::TextBox());
			this->txtbx_XStart = (gcnew System::Windows::Forms::TextBox());
			this->lbl_XDim_Points = (gcnew System::Windows::Forms::Label());
			this->lbl_XDim_Stop = (gcnew System::Windows::Forms::Label());
			this->lbl_XDim_Start = (gcnew System::Windows::Forms::Label());
			this->group_PreformScan = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_initScan_steps = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lbl_loadSettings = (gcnew System::Windows::Forms::Label());
			this->btnFirst_Pos = (gcnew System::Windows::Forms::Button());
			this->Group_Freq->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numBox_Points))->BeginInit();
			this->Span_Units->SuspendLayout();
			this->Center_Units->SuspendLayout();
			this->Stop_Units->SuspendLayout();
			this->Start_Units->SuspendLayout();
			this->Group_Power->SuspendLayout();
			this->Power_Units->SuspendLayout();
			this->group_NAcomm->SuspendLayout();
			this->group_INITScan->SuspendLayout();
			this->group_foldername->SuspendLayout();
			this->group_Trace->SuspendLayout();
			this->group_AntennaPos->SuspendLayout();
			this->group_YDim->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numbox_Ypoints))->BeginInit();
			this->group_XDim->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numbox_Xpoints))->BeginInit();
			this->group_PreformScan->SuspendLayout();
			this->SuspendLayout();
			// 
			// lbl_ipAdress
			// 
			this->lbl_ipAdress->Location = System::Drawing::Point(5, 30);
			this->lbl_ipAdress->Name = L"lbl_ipAdress";
			this->lbl_ipAdress->Size = System::Drawing::Size(100, 12);
			this->lbl_ipAdress->TabIndex = 0;
			this->lbl_ipAdress->Text = L"-----IP----";
			// 
			// lbl_IDN_resp
			// 
			this->lbl_IDN_resp->AutoSize = true;
			this->lbl_IDN_resp->Location = System::Drawing::Point(6, 66);
			this->lbl_IDN_resp->Name = L"lbl_IDN_resp";
			this->lbl_IDN_resp->Size = System::Drawing::Size(40, 13);
			this->lbl_IDN_resp->TabIndex = 8;
			this->lbl_IDN_resp->Text = L"-----------";
			// 
			// lbl_instIDN
			// 
			this->lbl_instIDN->AutoSize = true;
			this->lbl_instIDN->Location = System::Drawing::Point(5, 53);
			this->lbl_instIDN->Name = L"lbl_instIDN";
			this->lbl_instIDN->Size = System::Drawing::Size(102, 13);
			this->lbl_instIDN->TabIndex = 9;
			this->lbl_instIDN->Text = L"Instrument Identifier:";
			this->lbl_instIDN->Click += gcnew System::EventHandler(this, &MainForm::label5_Click);
			// 
			// Group_Freq
			// 
			this->Group_Freq->Controls->Add(this->numBox_Points);
			this->Group_Freq->Controls->Add(this->Span_Units);
			this->Group_Freq->Controls->Add(this->lbl_sweeppoints);
			this->Group_Freq->Controls->Add(this->Center_Units);
			this->Group_Freq->Controls->Add(this->Stop_Units);
			this->Group_Freq->Controls->Add(this->Start_Units);
			this->Group_Freq->Controls->Add(this->SpanTextBox);
			this->Group_Freq->Controls->Add(this->CenterTextBox);
			this->Group_Freq->Controls->Add(this->StopTextBox);
			this->Group_Freq->Controls->Add(this->StartTextBox);
			this->Group_Freq->Controls->Add(this->SpanFreqLabel);
			this->Group_Freq->Controls->Add(this->CenterFreqLabel);
			this->Group_Freq->Controls->Add(this->StopFreqLabel);
			this->Group_Freq->Controls->Add(this->StartFreqLabel);
			this->Group_Freq->Controls->Add(this->CenterSpanRadio);
			this->Group_Freq->Controls->Add(this->StartStopRadio);
			this->Group_Freq->Location = System::Drawing::Point(23, 113);
			this->Group_Freq->Name = L"Group_Freq";
			this->Group_Freq->Size = System::Drawing::Size(373, 214);
			this->Group_Freq->TabIndex = 12;
			this->Group_Freq->TabStop = false;
			this->Group_Freq->Text = L"Frequency";
			// 
			// numBox_Points
			// 
			this->numBox_Points->Location = System::Drawing::Point(117, 181);
			this->numBox_Points->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20001, 0, 0, 0 });
			this->numBox_Points->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numBox_Points->Name = L"numBox_Points";
			this->numBox_Points->Size = System::Drawing::Size(64, 20);
			this->numBox_Points->TabIndex = 1;
			this->numBox_Points->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, 0 });
			// 
			// Span_Units
			// 
			this->Span_Units->Controls->Add(this->Span_kHz);
			this->Span_Units->Controls->Add(this->Span_MHz);
			this->Span_Units->Controls->Add(this->Span_GHz);
			this->Span_Units->Enabled = false;
			this->Span_Units->Location = System::Drawing::Point(188, 145);
			this->Span_Units->Name = L"Span_Units";
			this->Span_Units->Size = System::Drawing::Size(159, 35);
			this->Span_Units->TabIndex = 12;
			this->Span_Units->TabStop = false;
			// 
			// Span_kHz
			// 
			this->Span_kHz->AutoSize = true;
			this->Span_kHz->Location = System::Drawing::Point(109, 12);
			this->Span_kHz->Name = L"Span_kHz";
			this->Span_kHz->Size = System::Drawing::Size(44, 17);
			this->Span_kHz->TabIndex = 2;
			this->Span_kHz->Text = L"kHz";
			this->Span_kHz->UseVisualStyleBackColor = true;
			// 
			// Span_MHz
			// 
			this->Span_MHz->AutoSize = true;
			this->Span_MHz->Location = System::Drawing::Point(56, 12);
			this->Span_MHz->Name = L"Span_MHz";
			this->Span_MHz->Size = System::Drawing::Size(47, 17);
			this->Span_MHz->TabIndex = 1;
			this->Span_MHz->Text = L"MHz";
			this->Span_MHz->UseVisualStyleBackColor = true;
			// 
			// Span_GHz
			// 
			this->Span_GHz->AutoSize = true;
			this->Span_GHz->Checked = true;
			this->Span_GHz->Location = System::Drawing::Point(4, 12);
			this->Span_GHz->Name = L"Span_GHz";
			this->Span_GHz->Size = System::Drawing::Size(46, 17);
			this->Span_GHz->TabIndex = 0;
			this->Span_GHz->TabStop = true;
			this->Span_GHz->Text = L"GHz";
			this->Span_GHz->UseVisualStyleBackColor = true;
			// 
			// lbl_sweeppoints
			// 
			this->lbl_sweeppoints->AutoSize = true;
			this->lbl_sweeppoints->Location = System::Drawing::Point(10, 183);
			this->lbl_sweeppoints->Name = L"lbl_sweeppoints";
			this->lbl_sweeppoints->Size = System::Drawing::Size(75, 13);
			this->lbl_sweeppoints->TabIndex = 0;
			this->lbl_sweeppoints->Text = L"Sweep Points:";
			// 
			// Center_Units
			// 
			this->Center_Units->Controls->Add(this->Center_kHz);
			this->Center_Units->Controls->Add(this->Center_MHz);
			this->Center_Units->Controls->Add(this->Center_GHz);
			this->Center_Units->Enabled = false;
			this->Center_Units->Location = System::Drawing::Point(188, 113);
			this->Center_Units->Name = L"Center_Units";
			this->Center_Units->Size = System::Drawing::Size(157, 31);
			this->Center_Units->TabIndex = 11;
			this->Center_Units->TabStop = false;
			// 
			// Center_kHz
			// 
			this->Center_kHz->AutoSize = true;
			this->Center_kHz->Location = System::Drawing::Point(112, 9);
			this->Center_kHz->Name = L"Center_kHz";
			this->Center_kHz->Size = System::Drawing::Size(44, 17);
			this->Center_kHz->TabIndex = 2;
			this->Center_kHz->Text = L"kHz";
			this->Center_kHz->UseVisualStyleBackColor = true;
			// 
			// Center_MHz
			// 
			this->Center_MHz->AutoSize = true;
			this->Center_MHz->Location = System::Drawing::Point(59, 8);
			this->Center_MHz->Name = L"Center_MHz";
			this->Center_MHz->Size = System::Drawing::Size(47, 17);
			this->Center_MHz->TabIndex = 1;
			this->Center_MHz->Text = L"MHz";
			this->Center_MHz->UseVisualStyleBackColor = true;
			// 
			// Center_GHz
			// 
			this->Center_GHz->AutoSize = true;
			this->Center_GHz->Checked = true;
			this->Center_GHz->Location = System::Drawing::Point(6, 9);
			this->Center_GHz->Name = L"Center_GHz";
			this->Center_GHz->Size = System::Drawing::Size(46, 17);
			this->Center_GHz->TabIndex = 0;
			this->Center_GHz->TabStop = true;
			this->Center_GHz->Text = L"GHz";
			this->Center_GHz->UseVisualStyleBackColor = true;
			// 
			// Stop_Units
			// 
			this->Stop_Units->Controls->Add(this->Stop_kHz);
			this->Stop_Units->Controls->Add(this->Stop_GHz);
			this->Stop_Units->Controls->Add(this->Stop_MHz);
			this->Stop_Units->Location = System::Drawing::Point(188, 75);
			this->Stop_Units->Name = L"Stop_Units";
			this->Stop_Units->Size = System::Drawing::Size(157, 36);
			this->Stop_Units->TabIndex = 10;
			this->Stop_Units->TabStop = false;
			// 
			// Stop_kHz
			// 
			this->Stop_kHz->AutoSize = true;
			this->Stop_kHz->Location = System::Drawing::Point(109, 11);
			this->Stop_kHz->Name = L"Stop_kHz";
			this->Stop_kHz->Size = System::Drawing::Size(44, 17);
			this->Stop_kHz->TabIndex = 2;
			this->Stop_kHz->Text = L"kHz";
			this->Stop_kHz->UseVisualStyleBackColor = true;
			// 
			// Stop_GHz
			// 
			this->Stop_GHz->AutoSize = true;
			this->Stop_GHz->Checked = true;
			this->Stop_GHz->Location = System::Drawing::Point(4, 11);
			this->Stop_GHz->Name = L"Stop_GHz";
			this->Stop_GHz->Size = System::Drawing::Size(46, 17);
			this->Stop_GHz->TabIndex = 1;
			this->Stop_GHz->TabStop = true;
			this->Stop_GHz->Text = L"GHz";
			this->Stop_GHz->UseVisualStyleBackColor = true;
			// 
			// Stop_MHz
			// 
			this->Stop_MHz->AutoSize = true;
			this->Stop_MHz->Location = System::Drawing::Point(56, 11);
			this->Stop_MHz->Name = L"Stop_MHz";
			this->Stop_MHz->Size = System::Drawing::Size(47, 17);
			this->Stop_MHz->TabIndex = 0;
			this->Stop_MHz->Text = L"MHz";
			this->Stop_MHz->UseVisualStyleBackColor = true;
			// 
			// Start_Units
			// 
			this->Start_Units->Controls->Add(this->Start_kHz);
			this->Start_Units->Controls->Add(this->Start_MHz);
			this->Start_Units->Controls->Add(this->Start_GHz);
			this->Start_Units->Location = System::Drawing::Point(188, 39);
			this->Start_Units->Name = L"Start_Units";
			this->Start_Units->Size = System::Drawing::Size(159, 33);
			this->Start_Units->TabIndex = 0;
			this->Start_Units->TabStop = false;
			// 
			// Start_kHz
			// 
			this->Start_kHz->AutoSize = true;
			this->Start_kHz->Location = System::Drawing::Point(111, 14);
			this->Start_kHz->Name = L"Start_kHz";
			this->Start_kHz->Size = System::Drawing::Size(44, 17);
			this->Start_kHz->TabIndex = 11;
			this->Start_kHz->Text = L"kHz";
			this->Start_kHz->UseVisualStyleBackColor = true;
			// 
			// Start_MHz
			// 
			this->Start_MHz->AutoSize = true;
			this->Start_MHz->Location = System::Drawing::Point(58, 14);
			this->Start_MHz->Name = L"Start_MHz";
			this->Start_MHz->Size = System::Drawing::Size(47, 17);
			this->Start_MHz->TabIndex = 10;
			this->Start_MHz->Text = L"MHz";
			this->Start_MHz->UseVisualStyleBackColor = true;
			// 
			// Start_GHz
			// 
			this->Start_GHz->AutoSize = true;
			this->Start_GHz->Checked = true;
			this->Start_GHz->Location = System::Drawing::Point(6, 14);
			this->Start_GHz->Name = L"Start_GHz";
			this->Start_GHz->Size = System::Drawing::Size(46, 17);
			this->Start_GHz->TabIndex = 0;
			this->Start_GHz->TabStop = true;
			this->Start_GHz->Text = L"GHz";
			this->Start_GHz->UseVisualStyleBackColor = true;
			// 
			// SpanTextBox
			// 
			this->SpanTextBox->Enabled = false;
			this->SpanTextBox->Location = System::Drawing::Point(80, 151);
			this->SpanTextBox->Name = L"SpanTextBox";
			this->SpanTextBox->Size = System::Drawing::Size(100, 20);
			this->SpanTextBox->TabIndex = 9;
			this->SpanTextBox->Text = L"1";
			// 
			// CenterTextBox
			// 
			this->CenterTextBox->Enabled = false;
			this->CenterTextBox->Location = System::Drawing::Point(81, 118);
			this->CenterTextBox->Name = L"CenterTextBox";
			this->CenterTextBox->Size = System::Drawing::Size(100, 20);
			this->CenterTextBox->TabIndex = 8;
			this->CenterTextBox->Text = L"1.5";
			// 
			// StopTextBox
			// 
			this->StopTextBox->Location = System::Drawing::Point(80, 85);
			this->StopTextBox->Name = L"StopTextBox";
			this->StopTextBox->Size = System::Drawing::Size(100, 20);
			this->StopTextBox->TabIndex = 7;
			this->StopTextBox->Text = L"2";
			// 
			// StartTextBox
			// 
			this->StartTextBox->Location = System::Drawing::Point(80, 52);
			this->StartTextBox->Name = L"StartTextBox";
			this->StartTextBox->Size = System::Drawing::Size(100, 20);
			this->StartTextBox->TabIndex = 6;
			this->StartTextBox->Text = L"1";
			this->StartTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::StartTextBox_TextChanged);
			// 
			// SpanFreqLabel
			// 
			this->SpanFreqLabel->AutoSize = true;
			this->SpanFreqLabel->Location = System::Drawing::Point(7, 154);
			this->SpanFreqLabel->Name = L"SpanFreqLabel";
			this->SpanFreqLabel->Size = System::Drawing::Size(59, 13);
			this->SpanFreqLabel->TabIndex = 5;
			this->SpanFreqLabel->Text = L"Span Freq:";
			// 
			// CenterFreqLabel
			// 
			this->CenterFreqLabel->AutoSize = true;
			this->CenterFreqLabel->Location = System::Drawing::Point(7, 121);
			this->CenterFreqLabel->Name = L"CenterFreqLabel";
			this->CenterFreqLabel->Size = System::Drawing::Size(65, 13);
			this->CenterFreqLabel->TabIndex = 4;
			this->CenterFreqLabel->Text = L"Center Freq:";
			// 
			// StopFreqLabel
			// 
			this->StopFreqLabel->AutoSize = true;
			this->StopFreqLabel->Location = System::Drawing::Point(7, 88);
			this->StopFreqLabel->Name = L"StopFreqLabel";
			this->StopFreqLabel->Size = System::Drawing::Size(56, 13);
			this->StopFreqLabel->TabIndex = 3;
			this->StopFreqLabel->Text = L"Stop Freq:";
			// 
			// StartFreqLabel
			// 
			this->StartFreqLabel->AutoSize = true;
			this->StartFreqLabel->Location = System::Drawing::Point(6, 55);
			this->StartFreqLabel->Name = L"StartFreqLabel";
			this->StartFreqLabel->Size = System::Drawing::Size(56, 13);
			this->StartFreqLabel->TabIndex = 2;
			this->StartFreqLabel->Text = L"Start Freq:";
			// 
			// CenterSpanRadio
			// 
			this->CenterSpanRadio->AutoSize = true;
			this->CenterSpanRadio->Location = System::Drawing::Point(87, 20);
			this->CenterSpanRadio->Name = L"CenterSpanRadio";
			this->CenterSpanRadio->Size = System::Drawing::Size(86, 17);
			this->CenterSpanRadio->TabIndex = 1;
			this->CenterSpanRadio->Text = L"Center/Span";
			this->CenterSpanRadio->UseVisualStyleBackColor = true;
			this->CenterSpanRadio->CheckedChanged += gcnew System::EventHandler(this, &MainForm::CenterSpanRadio_CheckedChanged);
			// 
			// StartStopRadio
			// 
			this->StartStopRadio->AutoSize = true;
			this->StartStopRadio->Checked = true;
			this->StartStopRadio->Location = System::Drawing::Point(7, 20);
			this->StartStopRadio->Name = L"StartStopRadio";
			this->StartStopRadio->Size = System::Drawing::Size(74, 17);
			this->StartStopRadio->TabIndex = 0;
			this->StartStopRadio->TabStop = true;
			this->StartStopRadio->Text = L"Start/Stop";
			this->StartStopRadio->UseVisualStyleBackColor = true;
			this->StartStopRadio->CheckedChanged += gcnew System::EventHandler(this, &MainForm::StartStopRadio_CheckedChanged);
			// 
			// SetCMDButton
			// 
			this->SetCMDButton->Location = System::Drawing::Point(7, 18);
			this->SetCMDButton->Name = L"SetCMDButton";
			this->SetCMDButton->Size = System::Drawing::Size(108, 23);
			this->SetCMDButton->TabIndex = 13;
			this->SetCMDButton->Text = L"Set Commands";
			this->SetCMDButton->UseVisualStyleBackColor = true;
			this->SetCMDButton->Click += gcnew System::EventHandler(this, &MainForm::SetCMDButton_Click);
			// 
			// Group_Power
			// 
			this->Group_Power->Controls->Add(this->Power_Units);
			this->Group_Power->Controls->Add(this->PowerTextBox);
			this->Group_Power->Controls->Add(this->label6);
			this->Group_Power->Location = System::Drawing::Point(23, 333);
			this->Group_Power->Name = L"Group_Power";
			this->Group_Power->Size = System::Drawing::Size(373, 57);
			this->Group_Power->TabIndex = 14;
			this->Group_Power->TabStop = false;
			this->Group_Power->Text = L"Power";
			this->Group_Power->Enter += gcnew System::EventHandler(this, &MainForm::groupBox2_Enter);
			// 
			// Power_Units
			// 
			this->Power_Units->Controls->Add(this->Power_dBm);
			this->Power_Units->Location = System::Drawing::Point(194, 9);
			this->Power_Units->Name = L"Power_Units";
			this->Power_Units->Size = System::Drawing::Size(149, 33);
			this->Power_Units->TabIndex = 16;
			this->Power_Units->TabStop = false;
			this->Power_Units->Enter += gcnew System::EventHandler(this, &MainForm::groupBox1_Enter);
			// 
			// Power_dBm
			// 
			this->Power_dBm->AutoSize = true;
			this->Power_dBm->Checked = true;
			this->Power_dBm->Location = System::Drawing::Point(6, 10);
			this->Power_dBm->Name = L"Power_dBm";
			this->Power_dBm->Size = System::Drawing::Size(46, 17);
			this->Power_dBm->TabIndex = 0;
			this->Power_dBm->TabStop = true;
			this->Power_dBm->Text = L"dBm";
			this->Power_dBm->UseVisualStyleBackColor = true;
			// 
			// PowerTextBox
			// 
			this->PowerTextBox->Location = System::Drawing::Point(87, 17);
			this->PowerTextBox->Name = L"PowerTextBox";
			this->PowerTextBox->Size = System::Drawing::Size(100, 20);
			this->PowerTextBox->TabIndex = 15;
			this->PowerTextBox->Text = L"-15";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(10, 20);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(77, 13);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Trasmit Power:";
			this->label6->Click += gcnew System::EventHandler(this, &MainForm::label6_Click);
			// 
			// group_NAcomm
			// 
			this->group_NAcomm->Controls->Add(this->lbl_VisaAdressPropmt);
			this->group_NAcomm->Controls->Add(this->lbl_ipAdress);
			this->group_NAcomm->Controls->Add(this->lbl_instIDN);
			this->group_NAcomm->Controls->Add(this->lbl_IDN_resp);
			this->group_NAcomm->Location = System::Drawing::Point(25, 21);
			this->group_NAcomm->Name = L"group_NAcomm";
			this->group_NAcomm->Size = System::Drawing::Size(371, 86);
			this->group_NAcomm->TabIndex = 21;
			this->group_NAcomm->TabStop = false;
			this->group_NAcomm->Text = L"Network Analyzer";
			// 
			// lbl_VisaAdressPropmt
			// 
			this->lbl_VisaAdressPropmt->AutoSize = true;
			this->lbl_VisaAdressPropmt->Location = System::Drawing::Point(4, 16);
			this->lbl_VisaAdressPropmt->Name = L"lbl_VisaAdressPropmt";
			this->lbl_VisaAdressPropmt->Size = System::Drawing::Size(71, 13);
			this->lbl_VisaAdressPropmt->TabIndex = 10;
			this->lbl_VisaAdressPropmt->Text = L"Visa Address:";
			// 
			// group_INITScan
			// 
			this->group_INITScan->Controls->Add(this->btn_StartScan);
			this->group_INITScan->Controls->Add(this->SetCMDButton);
			this->group_INITScan->Controls->Add(this->btn_ecal);
			this->group_INITScan->Location = System::Drawing::Point(109, 222);
			this->group_INITScan->Name = L"group_INITScan";
			this->group_INITScan->Size = System::Drawing::Size(123, 108);
			this->group_INITScan->TabIndex = 27;
			this->group_INITScan->TabStop = false;
			this->group_INITScan->Text = L"Initiate Scan";
			// 
			// btn_StartScan
			// 
			this->btn_StartScan->Location = System::Drawing::Point(7, 74);
			this->btn_StartScan->Name = L"btn_StartScan";
			this->btn_StartScan->Size = System::Drawing::Size(108, 23);
			this->btn_StartScan->TabIndex = 31;
			this->btn_StartScan->Text = L"Start Scan";
			this->btn_StartScan->UseVisualStyleBackColor = true;
			this->btn_StartScan->Click += gcnew System::EventHandler(this, &MainForm::btn_StartScan_Click);
			// 
			// btn_ecal
			// 
			this->btn_ecal->Location = System::Drawing::Point(7, 45);
			this->btn_ecal->Name = L"btn_ecal";
			this->btn_ecal->Size = System::Drawing::Size(108, 23);
			this->btn_ecal->TabIndex = 29;
			this->btn_ecal->Text = L"Preform E-cal";
			this->btn_ecal->UseVisualStyleBackColor = true;
			this->btn_ecal->Click += gcnew System::EventHandler(this, &MainForm::btn_ecal_Click);
			// 
			// group_foldername
			// 
			this->group_foldername->Controls->Add(this->txtbx_ExpName);
			this->group_foldername->Controls->Add(this->lbl_name);
			this->group_foldername->Controls->Add(this->lbl_ExpName);
			this->group_foldername->Controls->Add(this->btn_ExpName);
			this->group_foldername->Controls->Add(this->lbl_folderPath);
			this->group_foldername->Controls->Add(this->btn_folder);
			this->group_foldername->Location = System::Drawing::Point(11, 89);
			this->group_foldername->Name = L"group_foldername";
			this->group_foldername->Size = System::Drawing::Size(221, 111);
			this->group_foldername->TabIndex = 30;
			this->group_foldername->TabStop = false;
			this->group_foldername->Text = L"Folder Path and Experiment Name";
			// 
			// txtbx_ExpName
			// 
			this->txtbx_ExpName->Location = System::Drawing::Point(43, 66);
			this->txtbx_ExpName->Name = L"txtbx_ExpName";
			this->txtbx_ExpName->Size = System::Drawing::Size(88, 20);
			this->txtbx_ExpName->TabIndex = 5;
			// 
			// lbl_name
			// 
			this->lbl_name->AutoSize = true;
			this->lbl_name->Location = System::Drawing::Point(6, 69);
			this->lbl_name->Name = L"lbl_name";
			this->lbl_name->Size = System::Drawing::Size(38, 13);
			this->lbl_name->TabIndex = 4;
			this->lbl_name->Text = L"Name:";
			// 
			// lbl_ExpName
			// 
			this->lbl_ExpName->AutoSize = true;
			this->lbl_ExpName->Location = System::Drawing::Point(6, 93);
			this->lbl_ExpName->Name = L"lbl_ExpName";
			this->lbl_ExpName->Size = System::Drawing::Size(161, 13);
			this->lbl_ExpName->TabIndex = 3;
			this->lbl_ExpName->Text = L"EXPERIMENT NAME NOT SET";
			// 
			// btn_ExpName
			// 
			this->btn_ExpName->Enabled = false;
			this->btn_ExpName->Location = System::Drawing::Point(137, 64);
			this->btn_ExpName->Name = L"btn_ExpName";
			this->btn_ExpName->Size = System::Drawing::Size(75, 23);
			this->btn_ExpName->TabIndex = 2;
			this->btn_ExpName->Text = L"Set";
			this->btn_ExpName->UseVisualStyleBackColor = true;
			this->btn_ExpName->Click += gcnew System::EventHandler(this, &MainForm::btn_ExpName_Click);
			// 
			// lbl_folderPath
			// 
			this->lbl_folderPath->AutoSize = true;
			this->lbl_folderPath->Location = System::Drawing::Point(6, 45);
			this->lbl_folderPath->Name = L"lbl_folderPath";
			this->lbl_folderPath->Size = System::Drawing::Size(128, 13);
			this->lbl_folderPath->TabIndex = 1;
			this->lbl_folderPath->Text = L"NO FOLDER SELECTED";
			// 
			// btn_folder
			// 
			this->btn_folder->Location = System::Drawing::Point(6, 19);
			this->btn_folder->Name = L"btn_folder";
			this->btn_folder->Size = System::Drawing::Size(206, 23);
			this->btn_folder->TabIndex = 0;
			this->btn_folder->Text = L"Select Folder";
			this->btn_folder->UseVisualStyleBackColor = true;
			this->btn_folder->Click += gcnew System::EventHandler(this, &MainForm::btn_folder_Click);
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->HelpRequest += gcnew System::EventHandler(this, &MainForm::folderBrowserDialog1_HelpRequest_1);
			// 
			// btn_LoadSettings
			// 
			this->btn_LoadSettings->Location = System::Drawing::Point(138, 19);
			this->btn_LoadSettings->Name = L"btn_LoadSettings";
			this->btn_LoadSettings->Size = System::Drawing::Size(84, 23);
			this->btn_LoadSettings->TabIndex = 31;
			this->btn_LoadSettings->Text = L"Load Settings";
			this->btn_LoadSettings->UseVisualStyleBackColor = true;
			this->btn_LoadSettings->Click += gcnew System::EventHandler(this, &MainForm::btn_LoadSettings_Click);
			// 
			// group_Trace
			// 
			this->group_Trace->Controls->Add(this->btn_Tr4_Edit);
			this->group_Trace->Controls->Add(this->lbl_Tr4_S);
			this->group_Trace->Controls->Add(this->lbl_Tr4_Type);
			this->group_Trace->Controls->Add(this->chkbx_Tr4_Enable);
			this->group_Trace->Controls->Add(this->btn_Tr3_Edit);
			this->group_Trace->Controls->Add(this->lbl_Tr3_S);
			this->group_Trace->Controls->Add(this->lbl_Tr3_Type);
			this->group_Trace->Controls->Add(this->chkbx_Tr3_Enable);
			this->group_Trace->Controls->Add(this->btn_Tr2_Edit);
			this->group_Trace->Controls->Add(this->lbl_Tr2_S);
			this->group_Trace->Controls->Add(this->lbl_Tr2_Type);
			this->group_Trace->Controls->Add(this->chkbx_Tr2_Enable);
			this->group_Trace->Controls->Add(this->btn_Tr1_Edit);
			this->group_Trace->Controls->Add(this->lbl_Tr1_S);
			this->group_Trace->Controls->Add(this->lbl_Tr1_Type);
			this->group_Trace->Controls->Add(this->chkbx_Tr1_Enable);
			this->group_Trace->Location = System::Drawing::Point(23, 396);
			this->group_Trace->Name = L"group_Trace";
			this->group_Trace->Size = System::Drawing::Size(373, 126);
			this->group_Trace->TabIndex = 32;
			this->group_Trace->TabStop = false;
			this->group_Trace->Text = L"Trace Controls";
			// 
			// btn_Tr4_Edit
			// 
			this->btn_Tr4_Edit->Location = System::Drawing::Point(270, 95);
			this->btn_Tr4_Edit->Name = L"btn_Tr4_Edit";
			this->btn_Tr4_Edit->Size = System::Drawing::Size(75, 21);
			this->btn_Tr4_Edit->TabIndex = 15;
			this->btn_Tr4_Edit->Text = L"Edit Trace";
			this->btn_Tr4_Edit->UseVisualStyleBackColor = true;
			this->btn_Tr4_Edit->Click += gcnew System::EventHandler(this, &MainForm::btn_Tr4_Edit_Click);
			// 
			// lbl_Tr4_S
			// 
			this->lbl_Tr4_S->AutoSize = true;
			this->lbl_Tr4_S->Location = System::Drawing::Point(231, 100);
			this->lbl_Tr4_S->Name = L"lbl_Tr4_S";
			this->lbl_Tr4_S->Size = System::Drawing::Size(26, 13);
			this->lbl_Tr4_S->TabIndex = 14;
			this->lbl_Tr4_S->Text = L"S11";
			// 
			// lbl_Tr4_Type
			// 
			this->lbl_Tr4_Type->AutoSize = true;
			this->lbl_Tr4_Type->Location = System::Drawing::Point(75, 100);
			this->lbl_Tr4_Type->Name = L"lbl_Tr4_Type";
			this->lbl_Tr4_Type->Size = System::Drawing::Size(71, 13);
			this->lbl_Tr4_Type->TabIndex = 13;
			this->lbl_Tr4_Type->Text = L"Type: M LOG";
			// 
			// chkbx_Tr4_Enable
			// 
			this->chkbx_Tr4_Enable->AutoSize = true;
			this->chkbx_Tr4_Enable->Location = System::Drawing::Point(9, 100);
			this->chkbx_Tr4_Enable->Name = L"chkbx_Tr4_Enable";
			this->chkbx_Tr4_Enable->Size = System::Drawing::Size(63, 17);
			this->chkbx_Tr4_Enable->TabIndex = 12;
			this->chkbx_Tr4_Enable->Text = L"Trace 4";
			this->chkbx_Tr4_Enable->UseVisualStyleBackColor = true;
			this->chkbx_Tr4_Enable->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chkbx_Tr4_Enable_CheckedChanged);
			// 
			// btn_Tr3_Edit
			// 
			this->btn_Tr3_Edit->Location = System::Drawing::Point(270, 69);
			this->btn_Tr3_Edit->Name = L"btn_Tr3_Edit";
			this->btn_Tr3_Edit->Size = System::Drawing::Size(75, 21);
			this->btn_Tr3_Edit->TabIndex = 11;
			this->btn_Tr3_Edit->Text = L"Edit Trace";
			this->btn_Tr3_Edit->UseVisualStyleBackColor = true;
			this->btn_Tr3_Edit->Click += gcnew System::EventHandler(this, &MainForm::btn_Tr3_Edit_Click);
			// 
			// lbl_Tr3_S
			// 
			this->lbl_Tr3_S->AutoSize = true;
			this->lbl_Tr3_S->Location = System::Drawing::Point(231, 74);
			this->lbl_Tr3_S->Name = L"lbl_Tr3_S";
			this->lbl_Tr3_S->Size = System::Drawing::Size(26, 13);
			this->lbl_Tr3_S->TabIndex = 10;
			this->lbl_Tr3_S->Text = L"S11";
			// 
			// lbl_Tr3_Type
			// 
			this->lbl_Tr3_Type->AutoSize = true;
			this->lbl_Tr3_Type->Location = System::Drawing::Point(75, 74);
			this->lbl_Tr3_Type->Name = L"lbl_Tr3_Type";
			this->lbl_Tr3_Type->Size = System::Drawing::Size(71, 13);
			this->lbl_Tr3_Type->TabIndex = 9;
			this->lbl_Tr3_Type->Text = L"Type: M LOG";
			// 
			// chkbx_Tr3_Enable
			// 
			this->chkbx_Tr3_Enable->AutoSize = true;
			this->chkbx_Tr3_Enable->Location = System::Drawing::Point(9, 74);
			this->chkbx_Tr3_Enable->Name = L"chkbx_Tr3_Enable";
			this->chkbx_Tr3_Enable->Size = System::Drawing::Size(63, 17);
			this->chkbx_Tr3_Enable->TabIndex = 8;
			this->chkbx_Tr3_Enable->Text = L"Trace 3";
			this->chkbx_Tr3_Enable->UseVisualStyleBackColor = true;
			this->chkbx_Tr3_Enable->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chkbx_Tr3_Enable_CheckedChanged);
			// 
			// btn_Tr2_Edit
			// 
			this->btn_Tr2_Edit->Location = System::Drawing::Point(270, 42);
			this->btn_Tr2_Edit->Name = L"btn_Tr2_Edit";
			this->btn_Tr2_Edit->Size = System::Drawing::Size(75, 21);
			this->btn_Tr2_Edit->TabIndex = 7;
			this->btn_Tr2_Edit->Text = L"Edit Trace";
			this->btn_Tr2_Edit->UseVisualStyleBackColor = true;
			this->btn_Tr2_Edit->Click += gcnew System::EventHandler(this, &MainForm::btn_Tr2_Edit_Click);
			// 
			// lbl_Tr2_S
			// 
			this->lbl_Tr2_S->AutoSize = true;
			this->lbl_Tr2_S->Location = System::Drawing::Point(231, 47);
			this->lbl_Tr2_S->Name = L"lbl_Tr2_S";
			this->lbl_Tr2_S->Size = System::Drawing::Size(26, 13);
			this->lbl_Tr2_S->TabIndex = 6;
			this->lbl_Tr2_S->Text = L"S11";
			// 
			// lbl_Tr2_Type
			// 
			this->lbl_Tr2_Type->AutoSize = true;
			this->lbl_Tr2_Type->Location = System::Drawing::Point(75, 47);
			this->lbl_Tr2_Type->Name = L"lbl_Tr2_Type";
			this->lbl_Tr2_Type->Size = System::Drawing::Size(71, 13);
			this->lbl_Tr2_Type->TabIndex = 5;
			this->lbl_Tr2_Type->Text = L"Type: M LOG";
			// 
			// chkbx_Tr2_Enable
			// 
			this->chkbx_Tr2_Enable->AutoSize = true;
			this->chkbx_Tr2_Enable->Location = System::Drawing::Point(9, 47);
			this->chkbx_Tr2_Enable->Name = L"chkbx_Tr2_Enable";
			this->chkbx_Tr2_Enable->Size = System::Drawing::Size(63, 17);
			this->chkbx_Tr2_Enable->TabIndex = 4;
			this->chkbx_Tr2_Enable->Text = L"Trace 2";
			this->chkbx_Tr2_Enable->UseVisualStyleBackColor = true;
			this->chkbx_Tr2_Enable->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chkbx_Tr2_Enable_CheckedChanged);
			// 
			// btn_Tr1_Edit
			// 
			this->btn_Tr1_Edit->Location = System::Drawing::Point(270, 15);
			this->btn_Tr1_Edit->Name = L"btn_Tr1_Edit";
			this->btn_Tr1_Edit->Size = System::Drawing::Size(75, 21);
			this->btn_Tr1_Edit->TabIndex = 3;
			this->btn_Tr1_Edit->Text = L"Edit Trace";
			this->btn_Tr1_Edit->UseVisualStyleBackColor = true;
			this->btn_Tr1_Edit->Click += gcnew System::EventHandler(this, &MainForm::btn_Tr1_Edit_Click);
			// 
			// lbl_Tr1_S
			// 
			this->lbl_Tr1_S->AutoSize = true;
			this->lbl_Tr1_S->Location = System::Drawing::Point(231, 20);
			this->lbl_Tr1_S->Name = L"lbl_Tr1_S";
			this->lbl_Tr1_S->Size = System::Drawing::Size(26, 13);
			this->lbl_Tr1_S->TabIndex = 2;
			this->lbl_Tr1_S->Text = L"S11";
			// 
			// lbl_Tr1_Type
			// 
			this->lbl_Tr1_Type->AutoSize = true;
			this->lbl_Tr1_Type->Location = System::Drawing::Point(75, 20);
			this->lbl_Tr1_Type->Name = L"lbl_Tr1_Type";
			this->lbl_Tr1_Type->Size = System::Drawing::Size(71, 13);
			this->lbl_Tr1_Type->TabIndex = 1;
			this->lbl_Tr1_Type->Text = L"Type: M LOG";
			// 
			// chkbx_Tr1_Enable
			// 
			this->chkbx_Tr1_Enable->AutoSize = true;
			this->chkbx_Tr1_Enable->Location = System::Drawing::Point(9, 19);
			this->chkbx_Tr1_Enable->Name = L"chkbx_Tr1_Enable";
			this->chkbx_Tr1_Enable->Size = System::Drawing::Size(63, 17);
			this->chkbx_Tr1_Enable->TabIndex = 0;
			this->chkbx_Tr1_Enable->Text = L"Trace 1";
			this->chkbx_Tr1_Enable->UseVisualStyleBackColor = true;
			this->chkbx_Tr1_Enable->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chkbx_Tr1_Enable_CheckedChanged);
			// 
			// group_AntennaPos
			// 
			this->group_AntennaPos->Controls->Add(this->btnFirst_Pos);
			this->group_AntennaPos->Controls->Add(this->btn_ScannerHome);
			this->group_AntennaPos->Controls->Add(this->group_YDim);
			this->group_AntennaPos->Controls->Add(this->group_XDim);
			this->group_AntennaPos->Location = System::Drawing::Point(403, 21);
			this->group_AntennaPos->Name = L"group_AntennaPos";
			this->group_AntennaPos->Size = System::Drawing::Size(288, 266);
			this->group_AntennaPos->TabIndex = 33;
			this->group_AntennaPos->TabStop = false;
			this->group_AntennaPos->Text = L"Antenna Positions";
			this->group_AntennaPos->Enter += gcnew System::EventHandler(this, &MainForm::group_AntennaPos_Enter);
			// 
			// btn_ScannerHome
			// 
			this->btn_ScannerHome->Location = System::Drawing::Point(10, 233);
			this->btn_ScannerHome->Name = L"btn_ScannerHome";
			this->btn_ScannerHome->Size = System::Drawing::Size(104, 23);
			this->btn_ScannerHome->TabIndex = 2;
			this->btn_ScannerHome->Text = L"Move to Home";
			this->btn_ScannerHome->UseVisualStyleBackColor = true;
			this->btn_ScannerHome->Click += gcnew System::EventHandler(this, &MainForm::btn_ScannerHome_Click);
			// 
			// group_YDim
			// 
			this->group_YDim->Controls->Add(this->numbox_Ypoints);
			this->group_YDim->Controls->Add(this->lbl_YDim_Points);
			this->group_YDim->Controls->Add(this->txtbx_YStop);
			this->group_YDim->Controls->Add(this->txtbx_YStart);
			this->group_YDim->Controls->Add(this->lbl_YDim_Stop);
			this->group_YDim->Controls->Add(this->lbl_YDim_Start);
			this->group_YDim->Location = System::Drawing::Point(10, 127);
			this->group_YDim->Name = L"group_YDim";
			this->group_YDim->Size = System::Drawing::Size(264, 100);
			this->group_YDim->TabIndex = 1;
			this->group_YDim->TabStop = false;
			this->group_YDim->Text = L"Y Dimension";
			// 
			// numbox_Ypoints
			// 
			this->numbox_Ypoints->Location = System::Drawing::Point(102, 70);
			this->numbox_Ypoints->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numbox_Ypoints->Name = L"numbox_Ypoints";
			this->numbox_Ypoints->Size = System::Drawing::Size(100, 20);
			this->numbox_Ypoints->TabIndex = 6;
			this->numbox_Ypoints->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// lbl_YDim_Points
			// 
			this->lbl_YDim_Points->AutoSize = true;
			this->lbl_YDim_Points->Location = System::Drawing::Point(7, 72);
			this->lbl_YDim_Points->Name = L"lbl_YDim_Points";
			this->lbl_YDim_Points->Size = System::Drawing::Size(88, 13);
			this->lbl_YDim_Points->TabIndex = 5;
			this->lbl_YDim_Points->Text = L"Number of Points";
			// 
			// txtbx_YStop
			// 
			this->txtbx_YStop->Location = System::Drawing::Point(102, 43);
			this->txtbx_YStop->Name = L"txtbx_YStop";
			this->txtbx_YStop->Size = System::Drawing::Size(100, 20);
			this->txtbx_YStop->TabIndex = 7;
			// 
			// txtbx_YStart
			// 
			this->txtbx_YStart->Location = System::Drawing::Point(102, 17);
			this->txtbx_YStart->Name = L"txtbx_YStart";
			this->txtbx_YStart->Size = System::Drawing::Size(100, 20);
			this->txtbx_YStart->TabIndex = 6;
			// 
			// lbl_YDim_Stop
			// 
			this->lbl_YDim_Stop->AutoSize = true;
			this->lbl_YDim_Stop->Location = System::Drawing::Point(7, 46);
			this->lbl_YDim_Stop->Name = L"lbl_YDim_Stop";
			this->lbl_YDim_Stop->Size = System::Drawing::Size(32, 13);
			this->lbl_YDim_Stop->TabIndex = 4;
			this->lbl_YDim_Stop->Text = L"Stop:";
			// 
			// lbl_YDim_Start
			// 
			this->lbl_YDim_Start->AutoSize = true;
			this->lbl_YDim_Start->Location = System::Drawing::Point(7, 22);
			this->lbl_YDim_Start->Name = L"lbl_YDim_Start";
			this->lbl_YDim_Start->Size = System::Drawing::Size(32, 13);
			this->lbl_YDim_Start->TabIndex = 3;
			this->lbl_YDim_Start->Text = L"Start:";
			// 
			// group_XDim
			// 
			this->group_XDim->Controls->Add(this->numbox_Xpoints);
			this->group_XDim->Controls->Add(this->txtbx_XStop);
			this->group_XDim->Controls->Add(this->txtbx_XStart);
			this->group_XDim->Controls->Add(this->lbl_XDim_Points);
			this->group_XDim->Controls->Add(this->lbl_XDim_Stop);
			this->group_XDim->Controls->Add(this->lbl_XDim_Start);
			this->group_XDim->Location = System::Drawing::Point(10, 20);
			this->group_XDim->Name = L"group_XDim";
			this->group_XDim->Size = System::Drawing::Size(264, 100);
			this->group_XDim->TabIndex = 0;
			this->group_XDim->TabStop = false;
			this->group_XDim->Text = L"X Dimension";
			// 
			// numbox_Xpoints
			// 
			this->numbox_Xpoints->Location = System::Drawing::Point(102, 68);
			this->numbox_Xpoints->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numbox_Xpoints->Name = L"numbox_Xpoints";
			this->numbox_Xpoints->Size = System::Drawing::Size(100, 20);
			this->numbox_Xpoints->TabIndex = 5;
			this->numbox_Xpoints->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// txtbx_XStop
			// 
			this->txtbx_XStop->Location = System::Drawing::Point(102, 43);
			this->txtbx_XStop->Name = L"txtbx_XStop";
			this->txtbx_XStop->Size = System::Drawing::Size(100, 20);
			this->txtbx_XStop->TabIndex = 4;
			// 
			// txtbx_XStart
			// 
			this->txtbx_XStart->Location = System::Drawing::Point(102, 17);
			this->txtbx_XStart->Name = L"txtbx_XStart";
			this->txtbx_XStart->Size = System::Drawing::Size(100, 20);
			this->txtbx_XStart->TabIndex = 3;
			// 
			// lbl_XDim_Points
			// 
			this->lbl_XDim_Points->AutoSize = true;
			this->lbl_XDim_Points->Location = System::Drawing::Point(7, 70);
			this->lbl_XDim_Points->Name = L"lbl_XDim_Points";
			this->lbl_XDim_Points->Size = System::Drawing::Size(88, 13);
			this->lbl_XDim_Points->TabIndex = 2;
			this->lbl_XDim_Points->Text = L"Number of Points";
			// 
			// lbl_XDim_Stop
			// 
			this->lbl_XDim_Stop->AutoSize = true;
			this->lbl_XDim_Stop->Location = System::Drawing::Point(7, 44);
			this->lbl_XDim_Stop->Name = L"lbl_XDim_Stop";
			this->lbl_XDim_Stop->Size = System::Drawing::Size(32, 13);
			this->lbl_XDim_Stop->TabIndex = 1;
			this->lbl_XDim_Stop->Text = L"Stop:";
			// 
			// lbl_XDim_Start
			// 
			this->lbl_XDim_Start->AutoSize = true;
			this->lbl_XDim_Start->Location = System::Drawing::Point(7, 20);
			this->lbl_XDim_Start->Name = L"lbl_XDim_Start";
			this->lbl_XDim_Start->Size = System::Drawing::Size(32, 13);
			this->lbl_XDim_Start->TabIndex = 0;
			this->lbl_XDim_Start->Text = L"Start:";
			// 
			// group_PreformScan
			// 
			this->group_PreformScan->Controls->Add(this->lbl_initScan_steps);
			this->group_PreformScan->Controls->Add(this->label1);
			this->group_PreformScan->Controls->Add(this->lbl_loadSettings);
			this->group_PreformScan->Controls->Add(this->group_foldername);
			this->group_PreformScan->Controls->Add(this->group_INITScan);
			this->group_PreformScan->Controls->Add(this->btn_LoadSettings);
			this->group_PreformScan->Location = System::Drawing::Point(787, 24);
			this->group_PreformScan->Name = L"group_PreformScan";
			this->group_PreformScan->Size = System::Drawing::Size(239, 375);
			this->group_PreformScan->TabIndex = 34;
			this->group_PreformScan->TabStop = false;
			this->group_PreformScan->Text = L"Preform Scan";
			// 
			// lbl_initScan_steps
			// 
			this->lbl_initScan_steps->AutoSize = true;
			this->lbl_initScan_steps->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl_initScan_steps->Location = System::Drawing::Point(43, 246);
			this->lbl_initScan_steps->Name = L"lbl_initScan_steps";
			this->lbl_initScan_steps->Size = System::Drawing::Size(60, 60);
			this->lbl_initScan_steps->TabIndex = 34;
			this->lbl_initScan_steps->Text = L"Step 2:\r\nStep 3:\r\nStep 4:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(13, 66);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 20);
			this->label1->TabIndex = 33;
			this->label1->Text = L"Step 1:";
			// 
			// lbl_loadSettings
			// 
			this->lbl_loadSettings->AutoSize = true;
			this->lbl_loadSettings->Location = System::Drawing::Point(7, 24);
			this->lbl_loadSettings->Name = L"lbl_loadSettings";
			this->lbl_loadSettings->Size = System::Drawing::Size(129, 13);
			this->lbl_loadSettings->TabIndex = 32;
			this->lbl_loadSettings->Text = L"Load previous settings file";
			// 
			// btnFirst_Pos
			// 
			this->btnFirst_Pos->Location = System::Drawing::Point(170, 233);
			this->btnFirst_Pos->Name = L"btnFirst_Pos";
			this->btnFirst_Pos->Size = System::Drawing::Size(104, 23);
			this->btnFirst_Pos->TabIndex = 3;
			this->btnFirst_Pos->Text = L"Move to Start";
			this->btnFirst_Pos->UseVisualStyleBackColor = true;
			this->btnFirst_Pos->Click += gcnew System::EventHandler(this, &MainForm::btnFirst_Pos_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1031, 535);
			this->Controls->Add(this->group_PreformScan);
			this->Controls->Add(this->group_AntennaPos);
			this->Controls->Add(this->group_Trace);
			this->Controls->Add(this->group_NAcomm);
			this->Controls->Add(this->Group_Power);
			this->Controls->Add(this->Group_Freq);
			this->Name = L"MainForm";
			this->Text = L"Team Zero Impedance";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->Group_Freq->ResumeLayout(false);
			this->Group_Freq->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numBox_Points))->EndInit();
			this->Span_Units->ResumeLayout(false);
			this->Span_Units->PerformLayout();
			this->Center_Units->ResumeLayout(false);
			this->Center_Units->PerformLayout();
			this->Stop_Units->ResumeLayout(false);
			this->Stop_Units->PerformLayout();
			this->Start_Units->ResumeLayout(false);
			this->Start_Units->PerformLayout();
			this->Group_Power->ResumeLayout(false);
			this->Group_Power->PerformLayout();
			this->Power_Units->ResumeLayout(false);
			this->Power_Units->PerformLayout();
			this->group_NAcomm->ResumeLayout(false);
			this->group_NAcomm->PerformLayout();
			this->group_INITScan->ResumeLayout(false);
			this->group_foldername->ResumeLayout(false);
			this->group_foldername->PerformLayout();
			this->group_Trace->ResumeLayout(false);
			this->group_Trace->PerformLayout();
			this->group_AntennaPos->ResumeLayout(false);
			this->group_YDim->ResumeLayout(false);
			this->group_YDim->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numbox_Ypoints))->EndInit();
			this->group_XDim->ResumeLayout(false);
			this->group_XDim->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numbox_Xpoints))->EndInit();
			this->group_PreformScan->ResumeLayout(false);
			this->group_PreformScan->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		



private: System::Void StartStopRadio_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (StartStopRadio->Checked == 1) {
		StartTextBox->Enabled = 1;
		Start_Units->Enabled = 1;
		StopTextBox->Enabled = 1;
		Stop_Units->Enabled = 1;
		SpanTextBox->Enabled = 0;
		Span_Units->Enabled = 0;
		CenterTextBox->Enabled = 0;
		Center_Units->Enabled = 0;
	}
}
private: System::Void CenterSpanRadio_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (CenterSpanRadio->Checked == 1) {
		StartTextBox->Enabled = 0;
		Start_Units->Enabled = 0;
		StopTextBox->Enabled = 0;
		Stop_Units->Enabled = 0;
		SpanTextBox->Enabled = 1;
		Span_Units->Enabled = 1;
		CenterTextBox->Enabled = 1;
		Center_Units->Enabled = 1;
	}
}

private: System::Void SetCMDButton_Click(System::Object^  sender, System::EventArgs^  e) {
	std::string returnStatus; //used to catch the what the functions return

	ViSession viDefaultRM, Instrument;
	ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
	viOpenDefaultRM(&viDefaultRM);
	viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);


	std::cout << "The BUTTON SetCMDButton was pressed \n";
	returnStatus = Controls_Frequency(&Instrument);
	std::cout << returnStatus;
	std::cout << "\n";
	returnStatus = Controls_Power(&Instrument);
	std::cout << returnStatus;
	std::cout << "\n";
	returnStatus = Controls_Channel_Trace(&Instrument);
	std::cout << returnStatus;
	std::cout << "\n";
	returnStatus = Controls_Points(&Instrument);
	std::cout << returnStatus;
	std::cout << "\n";
	Controls_Scanner();
	std::cout << "\n";

	saveSettings2File("Settings");

	//enable ecal btn
	btn_ecal->Enabled = TRUE;
	
}

private: bool is_number(String^ testString){
	/**
	*   \brief Checks passed String^ for "-.0123456789"
	*   \param String^ to be checked.
	*   \return Returns a boolean.
	**/

	//Next 4 lines are string conversion
	IntPtr ptrToNativeString; //Pointer for String to Char conversion
	ptrToNativeString = Marshal::StringToHGlobalAnsi(testString); //PTR TO NATIVE STRING
	std::string s = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR

	return(strspn(s.c_str(), "-.0123456789") == s.size()); //Check for valid chars
}

private: std::string Controls_Channel_Trace(ViSession* Instrument) {
	/**
	*   \brief Sends Trace Controls to NA.
	*
	*   \param NO INPUT PARAMETERS.
	*   \return Returns a Status String.
	*
	**/
	std::string returnStatus;
	std::string linkedList[] = { "MLOG", "MLIN", "REAL", "IMAG", "GDEL", "SWR", "PHAS", "UPH", "PPH", "SLIN", "SLOG" , "SCOM" , "SMIT" , "SADM" , "PLIN", "PLOG", "POL" };

	//Disable all traces before turning them back on again
	sendSCPI_String(":DISP:WIND1:TRAC1:STAT OFF", Instrument);
	sendSCPI_String(":DISP:WIND1:TRAC2:STAT OFF", Instrument);
	sendSCPI_String(":DISP:WIND1:TRAC3:STAT OFF", Instrument);
	sendSCPI_String(":DISP:WIND1:TRAC4:STAT OFF", Instrument);



	String^ traceCMD = ":CALC1:TRAC1:FORM ";
	String^ tempSelection1 = gcnew String(linkedList[Tr1Type].c_str()); //convert string to String^
	traceCMD = traceCMD + tempSelection1;
	if (Tr1Enable == 1) {
		sendSCPI_String(traceCMD, Instrument);
		sendSCPI_String(":DISP:WIND1:TRAC1:STAT ON", Instrument);
	}
	

	traceCMD = ":CALC1:TRAC2:FORM ";
	String^ tempSelection2 = gcnew String(linkedList[Tr2Type].c_str());
	traceCMD = traceCMD + tempSelection2;
	if (Tr2Enable == 1) {
		sendSCPI_String(traceCMD, Instrument);
		sendSCPI_String(":DISP:WIND1:TRAC2:STAT ON", Instrument);
	}

	traceCMD = ":CALC1:TRAC3:FORM ";
	String^ tempSelection3 = gcnew String(linkedList[Tr3Type].c_str());
	traceCMD = traceCMD + tempSelection3;
	if (Tr3Enable == 1) {
		sendSCPI_String(traceCMD, Instrument);
		sendSCPI_String(":DISP:WIND1:TRAC3:STAT ON", Instrument);
	}

	traceCMD = ":CALC1:TRAC4:FORM ";
	String^ tempSelection4 = gcnew String(linkedList[Tr4Type].c_str());
	traceCMD = traceCMD + tempSelection4;
	if (Tr4Enable == 1) {
		sendSCPI_String(traceCMD, Instrument);
		sendSCPI_String(":DISP:WIND1:TRAC4:STAT ON", Instrument);
	}

	//Check if no traces are selected
	if (Tr1Enable == 0 && Tr2Enable == 0 && Tr3Enable == 0 && Tr4Enable == 0) {
		MessageBox::Show("Please check the trace controls.\nNo traces are selected.", "No trace controls set", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}


	//NO ERROR CHECKING HERE
	returnStatus = "Trace Controls were not checked";
	return returnStatus;
	//sendSCPI_String(":CALC1:TRAC2:FORM?");
	//std::string returnMessage = readSCPI_Buffer();
	//if (convert_vcppString_string(tempSelection1 + "\n") == returnMessage) {
	//	if (Tr2Enable == 1) {
	//		if (convert_vcppString_string(tempSelection2 + "\n") == returnMessage) {
	//			returnStatus = "Trace Controls Matched! \n";
	//			return returnStatus;
	//		}
	//		else {
	//			//did not match
	//			returnStatus = "Trace Controls DID NOT Match \n";
	//			return returnStatus;
	//		}
	//	}
	//	else {
	//		returnStatus = "Trace Controls Matched! \n";
	//		return returnStatus;
	//	}
	//}
	//else {
	//	//did not match
	//	returnStatus = "Trace Controls DID NOT Match \n";
	//	return returnStatus;
	//}

	
}

private: std::string Controls_Power(ViSession* Instrument) {
	/**
	*   \brief Forms, checks and sends Power Controls to NA.
	*
	*   This function is responsiable for converting the user input for the power controls
	*   into a string. It also sends the string, and checks the set value on the NA.
	*   A status string is returned. saying if the operation was successful or failed.
	*
	*   \param NO INPUT PARAMETERS.
	*   \return Returns a Status String.
	*
	**/

	String^ powerCMD = ":SOUR:POW:LEV:IMM:AMPL "; 
	std::string returnStatus;
	double powerNum;

	std::cout << "The Function  \"Controls_Power\" has been called\n";

	if (is_number(PowerTextBox->Text)) { //check user input as number
		std::cout << "Power is a number\n";
		//Convert user input into double
		std::string tempString = convert_vcppString_string(PowerTextBox->Text); //Using Cpp Strings
		powerNum = string_to_double(tempString); //Convert to double. This is might cause errors... Needs testing
	}
	else {
		returnStatus = "Power is not a number\n";
		std::cout << returnStatus;
		MessageBox::Show("Please check the transmit power.\nParameter not set.", "Transmit power is not valid", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return returnStatus;
	}

	powerCMD = powerCMD + powerNum;
	sendSCPI_String(powerCMD, Instrument);
	
	//INCOMPLETE CODE BELOW!!!!!!

	//Power should be checked now
	sendSCPI_String(":SOUR:POW:LEV:IMM:AMPL?", Instrument);
	std::string returnMessage = readSCPI_Buffer(Instrument);
	double retPower = string_science_to_double(returnMessage);
	if (retPower == powerNum) {
		returnMessage = "Power Control Matched! \n";
		return returnMessage;
	}
	else {
		returnStatus = "Power Control DID NOT match. \n";
		return returnStatus;
	}
	
}

private: std::string Controls_Points(ViSession* Instrument) {
	/**
	*   \brief Forms, checks and sends number of points in sweep to NA.
	*
	*
	*   \param NO INPUT PARAMETERS.
	*   \return Returns a Status String.
	*
	**/
	String^ pointsCMD = ":SENS1:SWE:POIN ";
	pointsCMD = pointsCMD + numBox_Points->Value;
	sendSCPI_String(pointsCMD, Instrument);

	//error checking
	pointsCMD = ":SENS1:SWE:POIN?";
	sendSCPI_String(pointsCMD, Instrument);
	std::string tempReturn = readSCPI_Buffer(Instrument);
	if (string_to_double(tempReturn) == ((double)numBox_Points->Value)) {
		return "Points Control Matched! \n";
	}
	return "Points did not match on NA. \n";

}


private: std::string Controls_Frequency(ViSession* Instrument) {
	/**
	*   \brief Forms, checks and sends Frequency Controls to NA.
	*
	*   This function is responsiable for converting the user input for the frequency controls
	*   into a string. It also sends the string, and checks the set value on the NA. 
	*   A status string is returned. saying if the operation was successful or failed.
	*
	*   \param NO INPUT PARAMETERS.
	*   \return Returns a Status String.
	*
	**/

	int exponent; //String used to add zeros based on GHz, Mhz, and kHz selection
	
	String^ frequencyStartCMD = ":SENS1:FREQ:STAR ";
	String^ frequencyStopCMD = ":SENS1:FREQ:STOP ";
	String^ frequencyCenterCMD = ":SENS1:FREQ:CENT ";
	String^ frequencySpanCMD = ":SENS1:FREQ:SPAN ";

	double frequencyStartNum;
	double frequencyStopNum;
	double frequencyCenterNum;
	double frequencySpanNum;
	std::string returnStatus;

	std::cout << "The Function  \"Controls_FreqStartStop\" has been called\n";

	if (StartStopRadio->Checked == 1) { 
		//If in start/stop mode, the ":SENS1:FREQ:STAR " and ":SENS1:FREQ:STOP " cmds need to be formed


		//Start Controls
		if (Start_GHz->Checked) {
			exponent = 1000000000;
		}
		if (Start_MHz->Checked) {
			exponent = 1000000;
		}
		if (Start_kHz->Checked) {
			exponent = 1000;
		}

		if (is_number(StartTextBox->Text)) { //check user input as number
			std::cout << "Start freq is a number\n";
			//Convert user input into double
			std::string tempString = convert_vcppString_string(StartTextBox->Text); //Using Cpp Strings
			frequencyStartNum = string_to_double(tempString); //Convert to double. This is might cause errors... Needs testing
			frequencyStartNum = frequencyStartNum * exponent; //Mutiply unit scaler with user input
		}
		else {
			returnStatus = "Start freq is not a number\n";
			std::cout << returnStatus;
			MessageBox::Show("Please check start frequency.\nParameter not set.", "Start Frequency is not valid", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return returnStatus;
		}

	
		//Stop Controls
		if (Stop_GHz->Checked) {
			exponent = 1000000000;
		}
		if (Stop_MHz->Checked) {
			exponent = 1000000;
		}
		if (Stop_kHz->Checked) {
			exponent = 1000;
		}

		if (is_number(StopTextBox->Text)) { //check user input as number
			std::cout << "Stop freq is a number\n";
			//Convert user input into double
			std::string tempString = convert_vcppString_string(StopTextBox->Text); //Using Cpp Strings
			frequencyStopNum = string_to_double(tempString); //Convert to double. This is might cause errors... Needs testing
			frequencyStopNum = frequencyStopNum * exponent; //Mutiply unit scaler with user input	
		}
		else {
			returnStatus = "Stop freq is not a number\n";
			std::cout << returnStatus;
			MessageBox::Show("Please check stop frequency.\nParameter not set.", "Stop Frequency is not valid", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return returnStatus;
		}


		//Error checking.
		//Check if start<stop, start<max, start>min, 
		//Check if stop<max, stop>min
		if ((frequencyStartNum < frequencyStopNum) && (frequencyStartNum <= FREQ_MAX) && (frequencyStartNum >= FREQ_MIN) && (frequencyStopNum <= FREQ_MAX) && (frequencyStopNum >= FREQ_MIN)) {
			returnStatus = "Start and Stop Frequencies are in range\n";
			std::cout << returnStatus;
			frequencyStartCMD = frequencyStartCMD + frequencyStartNum;
			sendSCPI_String(frequencyStartCMD, Instrument);
			frequencyStopCMD = frequencyStopCMD + frequencyStopNum;
			sendSCPI_String(frequencyStopCMD, Instrument);

			//start and stop parameters should be checked now
			sendSCPI_String(":SENS1:FREQ:STAR?", Instrument);
			std::string returnMessage = readSCPI_Buffer(Instrument);
			double retStartFreq = string_science_to_double(returnMessage);

			sendSCPI_String(":SENS1:FREQ:STOP?", Instrument);
			returnMessage = readSCPI_Buffer(Instrument);
			double retStopFreq = string_science_to_double(returnMessage);

			if ((retStartFreq == frequencyStartNum)&&(retStopFreq == frequencyStopNum)) {
				returnStatus = "Frequency Controls Matched! \n";
				return returnStatus;
			}
			else
			{
				MessageBox::Show("Please check the input frequencies.\nParameters are not in range.\nParameter not set.", "Start/Stop Frequency did not match", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				returnStatus = "Frequency Controls DID NOT Match \n";
				return returnStatus;
			}
		}
		else {
			returnStatus = "Start and Stop Frequencies are NOT in range\n";
			std::cout << returnStatus;
			MessageBox::Show("Please check the input frequencies.\nParameters are not in range.\nParameter not set.", "Start/Stop Frequency is not valid", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return returnStatus;
		}
	}
	
	if (CenterSpanRadio->Checked == 1) {
		//If in center/span mode, the ":SENS1:FREQ:CENT " and ":SENS1:FREQ:SPAN " cmds need to be formed

		//Center Controls
		if (Center_GHz->Checked) {
			exponent = 1000000000;
		}
		if (Center_MHz->Checked) {
			exponent = 1000000;
		}
		if (Center_kHz->Checked) {
			exponent = 1000;
		}
		if (is_number(CenterTextBox->Text)) { //check user input as number
			std::cout << "Center freq is a number\n";
			//Convert user input into double
			std::string tempString = convert_vcppString_string(CenterTextBox->Text); //Using Cpp Strings
			frequencyCenterNum = string_to_double(tempString); //Convert to double. This is might cause errors... Needs testing
			frequencyCenterNum = frequencyCenterNum * exponent; //Mutiply unit scaler with user input
		}
		else {
			returnStatus = "Center freq is not a number\n";
			std::cout << returnStatus;
			MessageBox::Show("Please check center frequency.\nParameter not set.", "Center Frequency is not valid", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return returnStatus;
		}

		//Span Controls
		if (Span_GHz->Checked) {
			exponent = 1000000000;
		}
		if (Span_MHz->Checked) {
			exponent = 1000000;
		}
		if (Span_kHz->Checked) {
			exponent = 1000;
		}
		if (is_number(SpanTextBox->Text)) { //check user input as number
			std::cout << "Span freq is a number\n";
			//Convert user input into double
			std::string tempString = convert_vcppString_string(SpanTextBox->Text); //Using Cpp Strings
			frequencySpanNum = string_to_double(tempString); //Convert to double. This is might cause errors... Needs testing
			frequencySpanNum = frequencySpanNum * exponent; //Mutiply unit scaler with user input
		}
		else {
			returnStatus = "Span freq is not a number\n";
			std::cout << returnStatus;
			MessageBox::Show("Please check span frequency.\nParameter not set.", "Span Frequency is not valid", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return returnStatus;
		}

		//Error checking.
		//Check if start<stop, start<max, start>min, 
		//Check if stop<max, stop>min
		frequencyStartNum = frequencyCenterNum - (frequencySpanNum / 2);
		frequencyStopNum = frequencyCenterNum + (frequencySpanNum / 2);
		if ((frequencyStartNum < frequencyStopNum) && (frequencyStartNum <= FREQ_MAX) && (frequencyStartNum >= FREQ_MIN) && (frequencyStopNum <= FREQ_MAX) && (frequencyStopNum >= FREQ_MIN)) {
			returnStatus = "Center and Span Frequencies are in range\n";
			std::cout << returnStatus;
			frequencyCenterCMD = frequencyCenterCMD + frequencyCenterNum;
			sendSCPI_String(frequencyCenterCMD, Instrument);
			frequencySpanCMD = frequencySpanCMD + frequencySpanNum;
			sendSCPI_String(frequencySpanCMD, Instrument);

			//start and stop parameters should be checked now
			sendSCPI_String(":SENS1:FREQ:CENT?", Instrument);
			std::string returnMessage = readSCPI_Buffer(Instrument);
			double retCenterFreq = string_science_to_double(returnMessage);

			sendSCPI_String(":SENS1:FREQ:SPAN?", Instrument);
			returnMessage = readSCPI_Buffer(Instrument);
			double retSpanFreq = string_science_to_double(returnMessage);

			if ((retCenterFreq == frequencyCenterNum) && (retSpanFreq == frequencySpanNum)) {
				returnStatus = "Frequency Controls Matched! \n";
				return returnStatus;
			}
			else
			{
				MessageBox::Show("Please check the input frequencies.\nParameters are not in range.\nParameter not set.", "Center/Span Frequency did not match", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				returnStatus = "Frequency Controls DID NOT Match \n";
				return returnStatus;
			}
		}
		else {
			returnStatus = "Center and Span Frequencies are NOT in range\n";
			std::cout << returnStatus;
			MessageBox::Show("Please check the input frequencies.\nParameters are not in range.\nParameter not set.", "Cener/Span Frequency is not valid", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return returnStatus;
		}
	}

	//Return statement
	//returnStatus = "Maybe it worked...";
	return returnStatus;
}

private: System::Void Controls_Scanner() {
	//X Information
	//
	String^ xstart_native = txtbx_XStart->Text; //obtain user input for first X Position
	const std::string xstart_norm = convert_vcppString_string(xstart_native); //convert to normal string
	xstart_cm = string_to_double(xstart_norm); //convert string to double
	xstart_steps = ConvertCmtoSteps(xstart_cm); //convert user input of CM to Steps
	std::cout << xstart_steps;
	std::cout << "\n";

	String^ xstop_native = txtbx_XStop->Text; //obtain user input for Last X Position
	const std::string xstop_norm = convert_vcppString_string(xstop_native); //convert to normal string
	xstop_cm = string_to_double(xstop_norm); //convert string to double
	xstop_steps = ConvertCmtoSteps(xstop_cm); //convert user input of CM to Steps 

	String^ xPoints_native = numbox_Xpoints->Text; //obtain user input for number of columns
	const std::string xPoints_norm = convert_vcppString_string(xPoints_native); //convert to normal string
	xPoints = string_to_double(xPoints_norm); //convert string to double

											  //Y Information
											  //
	String^ ystart_native = txtbx_YStart->Text; //obtain user input for first Y Position
	const std::string ystart_norm = convert_vcppString_string(ystart_native); //convert to normal string
	ystart_cm = string_to_double(ystart_norm); //convert string to double
	ystart_steps = ConvertCmtoSteps(ystart_cm); //convert user input of CM to Steps

	String^ ystop_native = txtbx_YStop->Text; //obtain user input for Last Y Position
	const std::string ystop_norm = convert_vcppString_string(ystop_native); //convert to normal string
	ystop_cm = string_to_double(ystop_norm); //convert string to double
	ystop_steps = ConvertCmtoSteps(ystop_cm); //convert user input of CM to Steps

	String^ yPoints_native = numbox_Ypoints->Text; //obtain user input for number of rows
	const std::string yPoints_norm = convert_vcppString_string(yPoints_native); //convert to normal string
	yPoints = string_to_double(yPoints_norm); //convert string to double

	xstep_size = (xstop_steps - xstart_steps) / xPoints; //obtain the number of steps between each column
	ystep_size = (ystop_steps - ystart_steps) / yPoints; //obtain the number of steps between each row
	row_size = xstep_size*(xPoints - 1);

	std::cout << "\nX step size: " << xstep_size << "\nY step size: " << ystep_size;

	if (yPoints == 1) {
		std::cout << "\n\nThis will be a line scan.\n";
	}
}

private: double string_to_double(const std::string& s) {
	/**
	*   \brief converts a cpp string to a double.
	*   Function found online... doesnt throw proper errors. This issue needs to be documented
	**/

	std::istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
}

private: double string_science_to_double(const std::string& s){
	/**
	*   \brief converts a cpp string to a double.
	*   Function found online... doesnt throw proper errors. This issue needs to be documented
	**/
	std::string delimiter = "E+";
	std::string coeff = s.substr(0, s.find(delimiter)-1);
	std::string power = s.substr(s.find(delimiter)+2, s.length());

	std::istringstream i(coeff);
	std::istringstream j(power);
	double dbl_coeff;
	double dbl_power;
	if (!(i >> dbl_coeff))
		return 0;
	if (!(j >> dbl_power))
		return 0;

	double returnValue =  dbl_coeff * pow(10,(int)dbl_power);

	return returnValue;
}

private: std::string convert_vcppString_string(String^ vcppString) {
	/**
	*   \brief converts a visual C++ string to a normal C string
	**/
	char charBuffer[50000]; //Char Array Buffer
	IntPtr ptrToNativeString; //Pointer for String to Char conversion
	char* nativeString; // Static Char used in conversion process

	ptrToNativeString = Marshal::StringToHGlobalAnsi(vcppString); //PTR TO NATIVE STRING
	nativeString = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR
	strcpy(charBuffer, nativeString); //COPY CHAR ARRAY TO SCPIcmd Char buffer
	return (std::string)charBuffer;
}

private: String^ convert_string_vcppString(std::string in_string) {
	String^ nativeVISAREAD = gcnew String(in_string.c_str());
	return nativeVISAREAD;
}

private: std::string readSCPI_Buffer(ViSession* Instrument) {
	/**
	*   \brief Reads the SCPI buffer
	*
	*   This function is responsiable reading commands sent by the NA
	*
	*   \param void
	*   \return Returns a std c string.
	**/

	//Open COM
	/*ViSession viDefaultRM, Instrument;
	ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
	viOpenDefaultRM(&viDefaultRM);
	viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);*/
	char buf[50000]; //Reduce buffer size once issue is found

	viScanf(*Instrument, "%t", &buf); //Read buffer into memory

	std::cout << "The visa buffer was read:  \n";
	std::cout << buf;
	std::cout << "\n";
	//viClose(Instrument); //Close COM

	String^ nativeVISAREAD;
	nativeVISAREAD = Marshal::PtrToStringAnsi((IntPtr)buf); //Convert to native string
	std::string VisaMessage = convert_vcppString_string(nativeVISAREAD);
	return VisaMessage;

}

private: System::Void sendSCPI_String(String^ sendString, ViSession* Instrument) {
	/**
	*   \brief Sends the passed String^ over the SCPI interface 
	*
	*   This function is responsiable for converting the passed String^ into a const static char array
	*   It opens the comm, converts the string, sends the string, then closes the comm
	*
	*   \param Command to be sent, as String^ type.
	*   \return NO RETURN VALUE.
	**/

	//Next 5 lines initialize the Instrument communications
	//This process needs to occur before sending a command. This function will open and close the comm for every cmd sent

	//End of communications opening
	ViPUInt32 actual;
	std::string temp = convert_vcppString_string(sendString);
	const char *SCPIcmd = temp.c_str();								   
	viWrite(*Instrument, (ViBuf)SCPIcmd, (ViUInt32)strlen(SCPIcmd), actual); //Send cmd on SPCI interface
	//viClose(Instrument); //Close the comm

	//Next three lines makes entry in console log
	std::cout << "The command:  \"";
	std::cout << SCPIcmd;
	std::cout << "\"   was sent. \n";
}

private: System::Void saveSettings2File(std::string name_extension) {

	std::cout << "\n======SAVE SETTING TO FILE CODE WAS CALLED======\n";


	//VARIABLES
	char SCPIcmd[50000]; //Char Array for CMD 
	String^ buildString;
	String^ exponent_temp;
	String^ s_param_temp;
	std::string linkedList[] = { "MLOG", "MLIN", "REAL", "IMAG", "GDEL", "SWR", "PHAS", "UPH", "PPH", "SLIN", "SLOG" , "SCOM" , "SMIT" , "SADM" , "PLIN", "PLOG", "POL" };


	//Frequency controls
	buildString = buildString + "Frequency Control(True=Start_False=Center)," + StartStopRadio->Checked + ",\n";

	if (Start_GHz->Checked) {
		exponent_temp = "GHz";
	}
	if (Start_MHz->Checked) {
		exponent_temp = "MHz";
	}
	if (Start_kHz->Checked) {
		exponent_temp = "kHz";
	}
	buildString = buildString + "Frequency Start," + StartTextBox->Text + "," + exponent_temp + ",\n";

	if (Stop_GHz->Checked) {
		exponent_temp = "GHz";
	}
	if (Stop_MHz->Checked) {
		exponent_temp = "MHz";
	}
	if (Stop_kHz->Checked) {
		exponent_temp = "kHz";
	}
	buildString = buildString + "Frequency Stop," + StopTextBox->Text + "," + exponent_temp + ",\n";

	if (Center_GHz->Checked) {
		exponent_temp = "GHz";
	}
	if (Center_MHz->Checked) {
		exponent_temp = "MHz";
	}
	if (Center_kHz->Checked) {
		exponent_temp = "kHz";
	}
	buildString = buildString + "Frequency Center," + CenterTextBox->Text + "," + exponent_temp + ",\n";

	if (Span_GHz->Checked) {
		exponent_temp = "GHz";
	}
	if (Span_MHz->Checked) {
		exponent_temp = "MHz";
	}
	if (Span_kHz->Checked) {
		exponent_temp = "kHz";
	}
	buildString = buildString + "Frequency Span," + SpanTextBox->Text + "," + exponent_temp + ",\n";

	buildString = buildString + "Frequency Points," + numBox_Points->Text + ",\n";

	//Power
	buildString = buildString + "Power," + PowerTextBox->Text + ",\n";
	
	//Trace 1
	buildString = buildString + "Trace 1 Enable," + Tr1Enable + ",\n";

	buildString = buildString + "Trace 1 Type," + Tr1Type + "," + convert_string_vcppString(linkedList[Tr1Type]) + ",\n";

	if (Tr1SParam == 1) {
		s_param_temp = "S11";
	}
	if (Tr1SParam == 2) {
		s_param_temp = "S12";
	}
	if (Tr1SParam == 3) {
		s_param_temp = "S21";
	}
	if (Tr1SParam == 4) {
		s_param_temp = "S22";
	}
	buildString = buildString + "Trace 1 S parameter," + Tr1SParam + "," + s_param_temp + ",\n";

	//Trace 2
	buildString = buildString + "Trace 2 Enable," + Tr2Enable + ",\n";

	buildString = buildString + "Trace 2 Type," + Tr2Type + "," + convert_string_vcppString(linkedList[Tr2Type]) + ",\n";

	if (Tr2SParam == 1) {
		s_param_temp = "S11";
	}
	if (Tr2SParam == 2) {
		s_param_temp = "S12";
	}
	if (Tr2SParam == 3) {
		s_param_temp = "S21";
	}
	if (Tr2SParam == 4) {
		s_param_temp = "S22";
	}
	buildString = buildString + "Trace 2 S parameter," + Tr2SParam + "," + s_param_temp + ",\n";

	//Trace 3
	buildString = buildString + "Trace 3 Enable," + Tr3Enable + ",\n";

	buildString = buildString + "Trace 3 Type," + Tr3Type + "," + convert_string_vcppString(linkedList[Tr3Type]) + ",\n";

	if (Tr3SParam == 1) {
		s_param_temp = "S11";
	}
	if (Tr3SParam == 2) {
		s_param_temp = "S12";
	}
	if (Tr3SParam == 3) {
		s_param_temp = "S21";
	}
	if (Tr3SParam == 4) {
		s_param_temp = "S22";
	}
	buildString = buildString + "Trace 3 S parameter," + Tr3SParam + "," + s_param_temp + ",\n";


	//Trace 4
	buildString = buildString + "Trace 4 Enable," + Tr4Enable + ",\n";

	buildString = buildString + "Trace 4 Type," + Tr4Type + "," + convert_string_vcppString(linkedList[Tr4Type]) + ",\n";

	if (Tr4SParam == 1) {
		s_param_temp = "S11";
	}
	if (Tr4SParam == 2) {
		s_param_temp = "S12";
	}
	if (Tr4SParam == 3) {
		s_param_temp = "S21";
	}
	if (Tr4SParam == 4) {
		s_param_temp = "S22";
	}
	buildString = buildString + "Trace 4 S parameter," + Tr4SParam + "," + s_param_temp + ",\n";


	buildString = buildString + "X Antenna Start ," + txtbx_XStart->Text + ",\n";
	buildString = buildString + "X Antenna Stop ," + txtbx_XStop->Text + ",\n";
	buildString = buildString + "X Antenna Points ," + numbox_Xpoints->Text + ",\n";

	buildString = buildString + "Y Antenna Start ," + txtbx_YStart->Text + ",\n";
	buildString = buildString + "Y Antenna Stop ," + txtbx_YStop->Text + ",\n";
	buildString = buildString + "Y Antenna Points ," + numbox_Ypoints->Text + ",\n";

	//CHANGE DATA TYPES
	IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(buildString); //PTR TO NATIVE STRING
	char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR
	strcpy(SCPIcmd, nativeString); //COPY CHAR ARRAY TO SCPIcmd 



	//OPEN FILE
	std::string csv_file_string = folderPath + "\\" + experimentName + "\\" + experimentName + "_" + name_extension + ".csv";
	const char *csv_file_const_char = csv_file_string.c_str();
	FILE *fp = fopen(csv_file_const_char, "w");


	//WRITE FILE
	int buildStringLength = buildString->Length;
	fwrite(SCPIcmd, sizeof(char), buildStringLength, fp);
	fclose(fp);

}

private: System::Void saveFrequencyList(ViSession* Instrument) {
	
	std::string csv_file_string_Freq = folderPath + "\\" + experimentName + "\\" + experimentName + "_Frequency" + ".csv";
	const char *csv_file_const_char_Freq = csv_file_string_Freq.c_str();
	FILE *fp_Freq = fopen(csv_file_const_char_Freq, "w");

	char SCPIcmd_Freq[50000]; //Char Array for CMD 
	String^ buildString_Freq;

	//start, stop, points parameters will be read from machine, not UI
	sendSCPI_String(":SENS1:FREQ:STAR?", Instrument);
	std::string returnMessage = readSCPI_Buffer(Instrument);
	double retStartFreq = string_science_to_double(returnMessage);

	sendSCPI_String(":SENS1:FREQ:STOP?", Instrument);
	returnMessage = readSCPI_Buffer(Instrument);
	double retStopFreq = string_science_to_double(returnMessage);

	sendSCPI_String(":SENS1:SWE:POIN?", Instrument);
	returnMessage = readSCPI_Buffer(Instrument);
	int retPointsNum = string_to_double(returnMessage);

	double frequencyPoints;
	double delta = (retStopFreq - retStartFreq) / (retPointsNum);
	for (int l = 0; l < retPointsNum; l++) {
		frequencyPoints = retStartFreq + delta*l; //Compute frequency

		buildString_Freq = buildString_Freq + frequencyPoints + "\n"; //Convert into string
	}

	//Convert Data Types
	IntPtr ptrToNativeString_Freq = Marshal::StringToHGlobalAnsi(buildString_Freq); //PTR TO NATIVE STRING
	char* nativeString_Freq = static_cast<char*>(ptrToNativeString_Freq.ToPointer()); //CAST POINT AS STATIC CHAR
	strcpy(SCPIcmd_Freq, nativeString_Freq); //COPY CHAR ARRAY TO SCPIcmd 

												//Write File
	int buildStringLength_Freq = buildString_Freq->Length;
	fwrite(SCPIcmd_Freq, sizeof(char), buildStringLength_Freq, fp_Freq);
	fclose(fp_Freq);
}

private: int saveData2File(String^ dataString, int traceNumber, int fileNumber) {
	/**
	*   \brief writes passed string to a CSV file
	*	
	*   \return NO RETURN VALUE.
	**/
	std::cout << "\n======SAVE DATA TO FILE CODE WAS CALLED======\n";
	std::cout << "\n======TRACENUMBER ";
	std::cout << traceNumber;
	std::cout << "       FILENUMBER ";
	std::cout << fileNumber;
	std::cout << " ======\n";
	

	//First CREATE and open the CSV File
	std::string fileNum_string = std::to_string(fileNumber + 1);
	std::string traceNumber_string = std::to_string(traceNumber);
	//Creates folder of experiment name
	std::string csv_file_string = folderPath + "\\" + experimentName + "\\" + "Trace" + traceNumber_string + "_Location_" + fileNum_string + ".csv";
	const char *csv_file_const_char = csv_file_string.c_str();
	FILE *fp = fopen(csv_file_const_char, "w");
	
	char SCPIcmd[50000]; //Char Array for CMD 
	String^ buildString;
	



	//format dataStrig below
	std::vector<std::string> x = split(convert_vcppString_string(dataString), ',');

	//Header for CSV file
	std::string linkedList[] = { "MLOG", "MLIN", "REAL", "IMAG", "GDEL", "SWR", "PHAS", "UPH", "PPH", "SLIN", "SLOG" , "SCOM" , "SMIT" , "SADM" , "PLIN", "PLOG", "POL" };
	if (traceNumber == 1) {
		buildString = convert_string_vcppString(linkedList[Tr1Type]) + convert_string_vcppString((std::string)"_ComponentA_Pos_") + convert_string_vcppString(fileNum_string) + convert_string_vcppString((std::string)",") + convert_string_vcppString(linkedList[Tr1Type]) + convert_string_vcppString((std::string)"_ComponentB_Pos_") + convert_string_vcppString(fileNum_string) + convert_string_vcppString((std::string)",\n");
	}
	if (traceNumber == 2) {
		buildString = convert_string_vcppString(linkedList[Tr2Type]) + convert_string_vcppString((std::string)"_ComponentA_Pos_") + convert_string_vcppString(fileNum_string) + convert_string_vcppString((std::string)",") + convert_string_vcppString(linkedList[Tr2Type]) + convert_string_vcppString((std::string)"_ComponentB_Pos_") + convert_string_vcppString(fileNum_string) + convert_string_vcppString((std::string)",\n");
	}
	if (traceNumber == 3) {
		buildString = convert_string_vcppString(linkedList[Tr3Type]) + convert_string_vcppString((std::string)"_ComponentA_Pos_") + convert_string_vcppString(fileNum_string) + convert_string_vcppString((std::string)",") + convert_string_vcppString(linkedList[Tr3Type]) + convert_string_vcppString((std::string)"_ComponentB_Pos_") + convert_string_vcppString(fileNum_string) + convert_string_vcppString((std::string)",\n");
	}
	if (traceNumber == 4) {
		buildString = convert_string_vcppString(linkedList[Tr4Type]) + convert_string_vcppString((std::string)"_ComponentA_Pos_") + convert_string_vcppString(fileNum_string) + convert_string_vcppString((std::string)",") + convert_string_vcppString(linkedList[Tr4Type]) + convert_string_vcppString((std::string)"_ComponentB_Pos_") + convert_string_vcppString(fileNum_string) + convert_string_vcppString((std::string)",\n");
	}

	for (int i = 0; i <= (x.size())-1; i= i + 2) 
	{
		buildString = buildString + string_science_to_double(x[i]) + "," + string_science_to_double(x[i + 1]) + "\n";
	}

	IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(buildString); //PTR TO NATIVE STRING
	char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR
	strcpy(SCPIcmd, nativeString); //COPY CHAR ARRAY TO SCPIcmd 

	int buildStringLength = buildString->Length; 
	fwrite(SCPIcmd, sizeof(char), buildStringLength, fp);
	fclose(fp);

	return 1;
	
}

//split function
std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}
template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}
//end of split

private: System::Void groupBox2_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
}
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
}
private: System::Void folderBrowserDialog1_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
}


private: System::Void btn_ecal_Click(System::Object^  sender, System::EventArgs^  e) {
	std::cout << "E-CAL Button Pressed\n";
	MessageBox::Show("Please perform E-CAL\nClick Enter after calibration", "E-CAL", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);	
	btn_StartScan->Enabled = TRUE;
}
private: System::Void folderBrowserDialog1_HelpRequest_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void btn_folder_Click(System::Object^  sender, System::EventArgs^  e) {

	FolderBrowserDialog ^dlg = gcnew FolderBrowserDialog();
	if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String ^folderName = dlg->SelectedPath;
		folderPath = convert_vcppString_string(folderName);
		lbl_folderPath->Text = folderName;
		std::cout << "Folder path set to: ";
		std::cout << folderPath;
		std::cout << "\n";
	}
	btn_ExpName->Enabled = TRUE;
}
private: System::Void btn_ExpName_Click(System::Object^  sender, System::EventArgs^  e) {

	experimentName = convert_vcppString_string(txtbx_ExpName->Text);
	lbl_ExpName->Text = "Experiment is named\"" + txtbx_ExpName->Text + "\" ";
	std::string temp_directory = folderPath + "\\" + experimentName;
	CreateDirectoryA(temp_directory.c_str(),NULL);
	//Enable Set scans btn
	SetCMDButton->Enabled = TRUE;

}
private: System::Void btn_StartScan_Click(System::Object^  sender, System::EventArgs^  e) {

	ViSession viDefaultRM, Instrument;
	ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
	ViUInt32 actual;
	viOpenDefaultRM(&viDefaultRM);
	viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);

	if ((folderPath == "")||(experimentName == ""))
	{
		std::cout << "Not valid folder / Experiment Name";
		MessageBox::Show("Please enter a valid folder and experiment name", "Folder/Name Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
	else
	{
		//check for continuous mesurement and disable
		sendSCPI_String(":INIT:CONT? ", &Instrument);
		std::string returnMessage = readSCPI_Buffer(&Instrument);
		if (returnMessage == "1\n") {
			sendSCPI_String(":INIT:CONT OFF", &Instrument);
		}

		sendSCPI_String(":DISP:WIND1:ACT", &Instrument);
		sendSCPI_String(":DISP:WIND1:TRAC1:STAT ON", &Instrument);
		sendSCPI_String(":DISP:WIND1:TRAC2:STAT ON", &Instrument);
		sendSCPI_String(":DISP:WIND1:TRAC3:STAT ON", &Instrument);
		sendSCPI_String(":DISP:WIND1:TRAC4:STAT ON", &Instrument);
		sendSCPI_String(":CALC1:PAR:COUNT 4", &Instrument); //Enable 4 traces

		sendSCPI_String(":DISP:WIND1:MAX ON", &Instrument);

		//Save Numbox Points to interger
		int numbox_X = string_to_double(convert_vcppString_string(numbox_Xpoints->Text));
		int numbox_Y = string_to_double(convert_vcppString_string(numbox_Ypoints->Text));

		//Create new object for scan form
		CurrentlyScanning^ ScanForm = gcnew CurrentlyScanning(this, numbox_X, numbox_Y);
		ScanForm->Show();
		ScanForm->setStartTime();
		//Make CSV File of freqs
		saveFrequencyList(&Instrument);

		bool new_line = false;
		bool line_scan;


		//determine whether this is a line scan or not
		//
		if (yPoints == 1) {
			line_scan = true;
		}
		else {
			line_scan = false;
		}

		for (int y = 0; y < numbox_Y; y++) {
			for (int x = 0; x < numbox_X; x++) {
				//take Single Shot
				InitPort(&hComm, ComPortName);           //Initialize Serial Port
				SetRxMask(&hComm);					      //Set Receive Mask
				SetAcelandVel(&hComm, ComPortName);

				Sleep(100);

				takeSingleShotAndSave((y*numbox_Y) + x, &Instrument);
				
				ScanForm->updateVisuals(x, y);
				Sleep(100);

				if (x == xPoints - 1) {
					new_line = true;
				}
				else
					new_line = false;
				GoToNextPos(&hComm, ComPortName, xstep_size, ystep_size, xPoints,
					yPoints, row_size, x, y, new_line, line_scan);
				ClosePort(&hComm, ComPortName);
			}
		}
		ScanForm->Hide();

	}

}

private: System::Void takeSingleShotAndSave(int position, ViSession* Instrument) {
	sendSCPI_String(":INIT:IMM1", Instrument);
	int delayTime = 100;
	std::string tempReturn;
	String^ nativeVISAREAD;

	if (Tr1Enable == 1) {

		//Enable trace
		sendSCPI_String(":CALC1:PAR1:SEL", Instrument);

		//Set S-param
		if (Tr1SParam == 1) {
			sendSCPI_String(":CALC:PAR1:DEF S11", Instrument);
		}
		if (Tr1SParam == 2) {
			sendSCPI_String(":CALC:PAR1:DEF S12", Instrument);
		}
		if (Tr1SParam == 3) {
			sendSCPI_String(":CALC:PAR1:DEF S21", Instrument);
		}
		if (Tr1SParam == 4) {
			sendSCPI_String(":CALC:PAR1:DEF S22", Instrument);
		}

		sendSCPI_String(":CALC1:DATA:FDAT?", Instrument);
		Sleep(delayTime);
		tempReturn = readSCPI_Buffer(Instrument);
		if (tempReturn.length() == 0) {
			MessageBox::Show("ERROR IN SCAN!\Click Okay to try again", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			sendSCPI_String(":CALC1:DATA:FDAT?", Instrument);
			tempReturn = readSCPI_Buffer(Instrument);
			if (tempReturn.length() == 0) {
				MessageBox::Show("ERROR IN SCAN, AGAIN", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
		}
		nativeVISAREAD = gcnew String(tempReturn.c_str());
		saveData2File(nativeVISAREAD, 1, position);
	}
	if (Tr2Enable == 1) {
		sendSCPI_String(":CALC1:PAR2:SEL", Instrument);

		//Set S-param
		if (Tr2SParam == 1) {
			sendSCPI_String(":CALC:PAR2:DEF S11", Instrument);
		}
		if (Tr2SParam == 2) {
			sendSCPI_String(":CALC:PAR2:DEF S12", Instrument);
		}
		if (Tr2SParam == 3) {
			sendSCPI_String(":CALC:PAR2:DEF S21", Instrument);
		}
		if (Tr2SParam == 4) {
			sendSCPI_String(":CALC:PAR2:DEF S22", Instrument);
		}

		sendSCPI_String(":CALC1:DATA:FDAT?", Instrument);
		Sleep(delayTime);
		tempReturn = readSCPI_Buffer(Instrument);
		if (tempReturn.length() == 0) {
			MessageBox::Show("ERROR IN SCAN!\Click Okay to try again", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			sendSCPI_String(":CALC1:DATA:FDAT?", Instrument);
			tempReturn = readSCPI_Buffer(Instrument);
			if (tempReturn.length() == 0) {
				MessageBox::Show("ERROR IN SCAN, AGAIN", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
		}
		nativeVISAREAD = gcnew String(tempReturn.c_str());
		saveData2File(nativeVISAREAD, 2, position);
	}
	if (Tr3Enable == 1) {
		sendSCPI_String(":CALC1:PAR3:SEL", Instrument);

		//Set S-param
		if (Tr3SParam == 1) {
			sendSCPI_String(":CALC:PAR3:DEF S11", Instrument);
		}
		if (Tr3SParam == 2) {
			sendSCPI_String(":CALC:PAR3:DEF S12", Instrument);
		}
		if (Tr3SParam == 3) {
			sendSCPI_String(":CALC:PAR3:DEF S21", Instrument);
		}
		if (Tr3SParam == 4) {
			sendSCPI_String(":CALC:PAR3:DEF S22", Instrument);
		}

		sendSCPI_String(":CALC1:DATA:FDAT?", Instrument);
		Sleep(delayTime);
		tempReturn = readSCPI_Buffer(Instrument);
		if (tempReturn.length() == 0) {
			MessageBox::Show("ERROR IN SCAN!\Click Okay to try again", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			sendSCPI_String(":CALC1:DATA:FDAT?", Instrument);
			tempReturn = readSCPI_Buffer(Instrument);
			if (tempReturn.length() == 0) {
				MessageBox::Show("ERROR IN SCAN, AGAIN", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
		}
		nativeVISAREAD = gcnew String(tempReturn.c_str());
		saveData2File(nativeVISAREAD, 3, position);
	}
	if (Tr4Enable == 1) {
		sendSCPI_String(":CALC1:PAR4:SEL", Instrument);

		//Set S-param
		if (Tr4SParam == 1) {
			sendSCPI_String(":CALC:PAR4:DEF S11", Instrument);
		}
		if (Tr4SParam == 2) {
			sendSCPI_String(":CALC:PAR4:DEF S12", Instrument);
		}
		if (Tr4SParam == 3) {
			sendSCPI_String(":CALC:PAR4:DEF S21", Instrument);
		}
		if (Tr4SParam == 4) {
			sendSCPI_String(":CALC:PAR4:DEF S22", Instrument);
		}

		sendSCPI_String(":CALC1:DATA:FDAT?", Instrument);
		Sleep(delayTime);
		tempReturn = readSCPI_Buffer(Instrument);
		if (tempReturn.length() == 0) {
			MessageBox::Show("ERROR IN SCAN!\Click Okay to try again", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			sendSCPI_String(":CALC1:DATA:FDAT?", Instrument);
			tempReturn = readSCPI_Buffer(Instrument);
			if (tempReturn.length() == 0) {
				MessageBox::Show("ERROR IN SCAN, AGAIN", "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
		}
		nativeVISAREAD = gcnew String(tempReturn.c_str());
		saveData2File(nativeVISAREAD, 4, position);
	}
}


private: System::Void Group_Channel1_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void rTBX_Trace3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void StartTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void btn_LoadSettings_Click(System::Object^  sender, System::EventArgs^  e) {


	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

	openFileDialog1->InitialDirectory = "%systemdrive%\\users\\%username%\\Desktop\\Scanner_Data";
	openFileDialog1->Filter = "csv files (*.csv)|*.csv";
	openFileDialog1->FilterIndex = 1;
	openFileDialog1->RestoreDirectory = true;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		//print file selection to console
		std::cout << "The following CSV file was attempted to be laoded: \n";
		std::cout << convert_vcppString_string( openFileDialog1->FileName);
		std::cout << "\n";


		//std::ifstream classFile());

		std::ifstream in;
		in.open(convert_vcppString_string(openFileDialog1->FileName));
		std::vector<char*> values;

		const int MAXSIZE = 126;

		char thisVal[MAXSIZE];

		while (in.getline(thisVal, MAXSIZE, ',')) {
			values.resize(values.size() + 1);
			values.back() = new char[MAXSIZE];
			strcpy(values.back(), thisVal);
		}
		in.close();

		if (convert_string_vcppString((std::string)values[1])->Equals("True"))
		{
			StartStopRadio->Checked = TRUE;
			CenterSpanRadio->Checked = FALSE;
		}
		else {
			StartStopRadio->Checked = FALSE;
			CenterSpanRadio->Checked = TRUE;
		}

		

		//Start controls
		StartTextBox->Text = convert_string_vcppString(values[3]);
		if (convert_string_vcppString((std::string)values[4])->Equals("GHz")) {
			Start_GHz->Checked = TRUE;
			Start_MHz->Checked = FALSE;
			Start_kHz->Checked = FALSE;
		}
		else if(convert_string_vcppString((std::string)values[4])->Equals("MHz"))
		{
			Start_GHz->Checked = FALSE;
			Start_MHz->Checked = TRUE;
			Start_kHz->Checked = FALSE;
		}
		else if (convert_string_vcppString((std::string)values[4])->Equals("kHz"))
		{
			Start_GHz->Checked = FALSE;
			Start_MHz->Checked = FALSE;
			Start_kHz->Checked = TRUE;
		}
		//Stop Controls
		StopTextBox->Text = convert_string_vcppString(values[6]);
		if (convert_string_vcppString((std::string)values[7])->Equals("GHz")) {
			Stop_GHz->Checked = TRUE;
			Stop_MHz->Checked = FALSE;
			Stop_kHz->Checked = FALSE;
		}
		else if (convert_string_vcppString((std::string)values[7])->Equals("MHz"))
		{
			Stop_GHz->Checked = FALSE;
			Stop_MHz->Checked = TRUE;
			Stop_kHz->Checked = FALSE;
		}
		else if (convert_string_vcppString((std::string)values[7])->Equals("kHz"))
		{
			Stop_GHz->Checked = FALSE;
			Stop_MHz->Checked = FALSE;
			Stop_kHz->Checked = TRUE;
		}
		//Center Controls
		CenterTextBox->Text = convert_string_vcppString(values[9]);
		if (convert_string_vcppString((std::string)values[10])->Equals("GHz")) {
			Center_GHz->Checked = TRUE;
			Center_MHz->Checked = FALSE;
			Center_kHz->Checked = FALSE;
		}
		else if (convert_string_vcppString((std::string)values[10])->Equals("MHz"))
		{
			Center_GHz->Checked = FALSE;
			Center_MHz->Checked = TRUE;
			Center_kHz->Checked = FALSE;
		}
		else if (convert_string_vcppString((std::string)values[10])->Equals("kHz"))
		{
			Center_GHz->Checked = FALSE;
			Center_MHz->Checked = FALSE;
			Center_kHz->Checked = TRUE;
		}
		//Span Controls
		SpanTextBox->Text = convert_string_vcppString(values[12]);
		if (convert_string_vcppString((std::string)values[13])->Equals("GHz")) {
			Span_GHz->Checked = TRUE;
			Span_MHz->Checked = FALSE;
			Span_kHz->Checked = FALSE;
		}
		else if (convert_string_vcppString((std::string)values[13])->Equals("MHz"))
		{
			Span_GHz->Checked = FALSE;
			Span_MHz->Checked = TRUE;
			Span_kHz->Checked = FALSE;
		}
		else if (convert_string_vcppString((std::string)values[13])->Equals("kHz"))
		{
			Span_GHz->Checked = FALSE;
			Span_MHz->Checked = FALSE;
			Span_kHz->Checked = TRUE;
		}
		//Points controls
		numBox_Points->Text = convert_string_vcppString(values[15]);
		//Power
		PowerTextBox->Text = convert_string_vcppString(values[17]);

		//Trace
		Tr1Enable = string_to_double(values[19]);
		Tr1Type = string_to_double(values[21]);
		Tr1SParam = string_to_double(values[24]);

		Tr2Enable = string_to_double(values[27]);
		Tr2Type = string_to_double(values[29]);
		Tr2SParam = string_to_double(values[32]);

		Tr3Enable = string_to_double(values[35]);
		Tr3Type = string_to_double(values[37]);
		Tr3SParam = string_to_double(values[40]);

		Tr4Enable = string_to_double(values[43]);
		Tr4Type = string_to_double(values[45]);
		Tr4SParam = string_to_double(values[48]);

		txtbx_XStart->Text = convert_string_vcppString(values[51]);
		txtbx_XStop->Text = convert_string_vcppString(values[53]);
		numbox_Xpoints->Text = convert_string_vcppString(values[55]);

		txtbx_YStart->Text = convert_string_vcppString(values[57]);
		txtbx_YStop->Text = convert_string_vcppString(values[59]);
		numbox_Ypoints->Text = convert_string_vcppString(values[61]);

		this->Hide();
		this->Show();
	}
}
private: System::Void btn_Tr1_Edit_Click(System::Object^  sender, System::EventArgs^  e) {
	set_TraceWindow_pointers();
	trace1->Show();
	this->Hide();
}
private: System::Void btn_Tr2_Edit_Click(System::Object^  sender, System::EventArgs^  e) {
	set_TraceWindow_pointers();
	trace2->Show();
	this->Hide();
}
private: System::Void btn_Tr3_Edit_Click(System::Object^  sender, System::EventArgs^  e) {
	set_TraceWindow_pointers();
	trace3->Show();
	this->Hide();
}
private: System::Void btn_Tr4_Edit_Click(System::Object^  sender, System::EventArgs^  e) {
	set_TraceWindow_pointers();
	trace4->Show();
	this->Hide();
}

protected: virtual void OnVisibleChanged(EventArgs^ e) override
{
	//Update Trace 1
	
	if (Tr1Enable) {
		chkbx_Tr1_Enable->Checked = TRUE;
	}
	else {
		chkbx_Tr1_Enable->Checked = FALSE;
	}

	if (Tr1Type == 0) {
		lbl_Tr1_Type->Text = "Type: Magnitude Logarithmic";
	}
	if (Tr1Type == 1) {
		lbl_Tr1_Type->Text = "Type: Magnitude Linear";
	}
	if (Tr1Type == 2) {
		lbl_Tr1_Type->Text = "Type: Real";
	}
	if (Tr1Type == 3) {
		lbl_Tr1_Type->Text = "Type: Imaginary";
	}
	if (Tr1Type == 4) {
		lbl_Tr1_Type->Text = "Type: Group Delay";
	}
	if (Tr1Type == 5) {
		lbl_Tr1_Type->Text = "Type: SWR";
	}
	if (Tr1Type == 6) {
		lbl_Tr1_Type->Text = "Type: Phase";
	}
	if (Tr1Type == 7) {
		lbl_Tr1_Type->Text = "Type: Unwrapped Phase";
	}
	if (Tr1Type == 8) {
		lbl_Tr1_Type->Text = "Type: P Phase";
	}
	if (Tr1Type == 9) {
		lbl_Tr1_Type->Text = "Type: S Linear";
	}
	if (Tr1Type == 10) {
		lbl_Tr1_Type->Text = "Type: S Logarithmic";
	}
	if (Tr1Type == 11) {
		lbl_Tr1_Type->Text = "Type: S Complex";
	}
	if (Tr1Type == 12) {
		lbl_Tr1_Type->Text = "Type: Smith";
	}
	if (Tr1Type == 13) {
		lbl_Tr1_Type->Text = "Type: S Admittance";
	}
	if (Tr1Type == 14) {
		lbl_Tr1_Type->Text = "Type: S P Linear";
	}
	if (Tr1Type == 15) {
		lbl_Tr1_Type->Text = "Type: P Logarithmic";
	}
	if (Tr1Type == 16) {
		lbl_Tr1_Type->Text = "Type: Polar";
	}

	if (Tr1SParam == 1 | Tr1SParam == 0) {
		lbl_Tr1_S->Text = "S11";
	}
	if (Tr1SParam == 2) {
		lbl_Tr1_S->Text = "S12";
	}
	if (Tr1SParam == 3) {
		lbl_Tr1_S->Text = "S21";
	}
	if (Tr1SParam == 4) {
		lbl_Tr1_S->Text = "S22";
	}
	
	//Update Trace 2
	if (Tr2Enable) {
		chkbx_Tr2_Enable->Checked = TRUE;
	}
	else {
		chkbx_Tr2_Enable->Checked = FALSE;
	}

	if (Tr2Type == 0) {
		lbl_Tr2_Type->Text = "Type: Magnitude Logarithmic";
	}
	if (Tr2Type == 1) {
		lbl_Tr2_Type->Text = "Type: Magnitude Linear";
	}
	if (Tr2Type == 2) {
		lbl_Tr2_Type->Text = "Type: Real";
	}
	if (Tr2Type == 3) {
		lbl_Tr2_Type->Text = "Type: Imaginary";
	}
	if (Tr2Type == 4) {
		lbl_Tr2_Type->Text = "Type: Group Delay";
	}
	if (Tr2Type == 5) {
		lbl_Tr2_Type->Text = "Type: SWR";
	}
	if (Tr2Type == 6) {
		lbl_Tr2_Type->Text = "Type: Phase";
	}
	if (Tr2Type == 7) {
		lbl_Tr2_Type->Text = "Type: Unwrapped Phase";
	}
	if (Tr2Type == 8) {
		lbl_Tr2_Type->Text = "Type: P Phase";
	}
	if (Tr2Type == 9) {
		lbl_Tr2_Type->Text = "Type: S Linear";
	}
	if (Tr2Type == 10) {
		lbl_Tr2_Type->Text = "Type: S Logarithmic";
	}
	if (Tr2Type == 11) {
		lbl_Tr2_Type->Text = "Type: S Complex";
	}
	if (Tr2Type == 12) {
		lbl_Tr2_Type->Text = "Type: Smith";
	}
	if (Tr2Type == 13) {
		lbl_Tr2_Type->Text = "Type: S Admittance";
	}
	if (Tr2Type == 14) {
		lbl_Tr2_Type->Text = "Type: S P Linear";
	}
	if (Tr2Type == 15) {
		lbl_Tr2_Type->Text = "Type: P Logarithmic";
	}
	if (Tr2Type == 16) {
		lbl_Tr2_Type->Text = "Type: Polar";
	}

	if (Tr2SParam == 1 | Tr2SParam == 0) {
		lbl_Tr2_S->Text = "S11";
	}
	if (Tr2SParam == 2) {
		lbl_Tr2_S->Text = "S12";
	}
	if (Tr2SParam == 3) {
		lbl_Tr2_S->Text = "S21";
	}
	if (Tr2SParam == 4) {
		lbl_Tr2_S->Text = "S22";
	}

	//Update Trace 3
	if (Tr3Enable) {
		chkbx_Tr3_Enable->Checked = TRUE;
	}
	else {
		chkbx_Tr3_Enable->Checked = FALSE;
	}
	
	if (Tr3Type == 0) {
		lbl_Tr3_Type->Text = "Type: Magnitude Logarithmic";
	}
	if (Tr3Type == 1) {
		lbl_Tr3_Type->Text = "Type: Magnitude Linear";
	}
	if (Tr3Type == 2) {
		lbl_Tr3_Type->Text = "Type: Real";
	}
	if (Tr3Type == 3) {
		lbl_Tr3_Type->Text = "Type: Imaginary";
	}
	if (Tr3Type == 4) {
		lbl_Tr3_Type->Text = "Type: Group Delay";
	}
	if (Tr3Type == 5) {
		lbl_Tr3_Type->Text = "Type: SWR";
	}
	if (Tr3Type == 6) {
		lbl_Tr3_Type->Text = "Type: Phase";
	}
	if (Tr3Type == 7) {
		lbl_Tr3_Type->Text = "Type: Unwrapped Phase";
	}
	if (Tr3Type == 8) {
		lbl_Tr3_Type->Text = "Type: P Phase";
	}
	if (Tr3Type == 9) {
		lbl_Tr3_Type->Text = "Type: S Linear";
	}
	if (Tr3Type == 10) {
		lbl_Tr3_Type->Text = "Type: S Logarithmic";
	}
	if (Tr3Type == 11) {
		lbl_Tr3_Type->Text = "Type: S Complex";
	}
	if (Tr3Type == 12) {
		lbl_Tr3_Type->Text = "Type: Smith";
	}
	if (Tr3Type == 13) {
		lbl_Tr3_Type->Text = "Type: S Admittance";
	}
	if (Tr3Type == 14) {
		lbl_Tr3_Type->Text = "Type: S P Linear";
	}
	if (Tr3Type == 15) {
		lbl_Tr3_Type->Text = "Type: P Logarithmic";
	}
	if (Tr3Type == 16) {
		lbl_Tr3_Type->Text = "Type: Polar";
	}


	if (Tr3SParam == 1 | Tr3SParam == 0) {
		lbl_Tr3_S->Text = "S11";
	}
	if (Tr3SParam == 2) {
		lbl_Tr3_S->Text = "S12";
	}
	if (Tr3SParam == 3) {
		lbl_Tr3_S->Text = "S21";
	}
	if (Tr3SParam == 4) {
		lbl_Tr3_S->Text = "S22";
	}

	//Update Trace 4
	if (Tr4Enable) {
		chkbx_Tr4_Enable->Checked = TRUE;
	}
	else {
		chkbx_Tr4_Enable->Checked = FALSE;
	}
	

	if (Tr4Type == 0) {
		lbl_Tr4_Type->Text = "Type: Magnitude Logarithmic";
	}
	if (Tr4Type == 1) {
		lbl_Tr4_Type->Text = "Type: Magnitude Linear";
	}
	if (Tr4Type == 2) {
		lbl_Tr4_Type->Text = "Type: Real";
	}
	if (Tr4Type == 3) {
		lbl_Tr4_Type->Text = "Type: Imaginary";
	}
	if (Tr4Type == 4) {
		lbl_Tr4_Type->Text = "Type: Group Delay";
	}
	if (Tr4Type == 5) {
		lbl_Tr4_Type->Text = "Type: SWR";
	}
	if (Tr4Type == 6) {
		lbl_Tr4_Type->Text = "Type: Phase";
	}
	if (Tr4Type == 7) {
		lbl_Tr4_Type->Text = "Type: Unwrapped Phase";
	}
	if (Tr4Type == 8) {
		lbl_Tr4_Type->Text = "Type: P Phase";
	}
	if (Tr4Type == 9) {
		lbl_Tr4_Type->Text = "Type: S Linear";
	}
	if (Tr4Type == 10) {
		lbl_Tr4_Type->Text = "Type: S Logarithmic";
	}
	if (Tr4Type == 11) {
		lbl_Tr4_Type->Text = "Type: S Complex";
	}
	if (Tr4Type == 12) {
		lbl_Tr4_Type->Text = "Type: Smith";
	}
	if (Tr4Type == 13) {
		lbl_Tr4_Type->Text = "Type: S Admittance";
	}
	if (Tr4Type == 14) {
		lbl_Tr4_Type->Text = "Type: S P Linear";
	}
	if (Tr4Type == 15) {
		lbl_Tr4_Type->Text = "Type: P Logarithmic";
	}
	if (Tr4Type == 16) {
		lbl_Tr4_Type->Text = "Type: Polar";
	}


	if (Tr4SParam == 1 | Tr4SParam == 0) {
		lbl_Tr4_S->Text = "S11";
	}
	if (Tr4SParam == 2) {
		lbl_Tr4_S->Text = "S12";
	}
	if (Tr4SParam == 3) {
		lbl_Tr4_S->Text = "S21";
	}
	if (Tr4SParam == 4) {
		lbl_Tr4_S->Text = "S22";
	}
}

private: System::Void set_TraceWindow_pointers() {
	pin_ptr<int> temp_Tr1Type = &Tr1Type;
	pin_ptr<int> temp_Tr2Type = &Tr2Type;
	pin_ptr<int> temp_Tr3Type = &Tr3Type;
	pin_ptr<int> temp_Tr4Type = &Tr4Type;

	pin_ptr<int> temp_Tr1SParam = &Tr1SParam;
	pin_ptr<int> temp_Tr2SParam = &Tr2SParam;
	pin_ptr<int> temp_Tr3SParam = &Tr3SParam;
	pin_ptr<int> temp_Tr4SParam = &Tr4SParam;

	pin_ptr<int> temp_Tr1Enable = &Tr1Enable;
	pin_ptr<int> temp_Tr2Enable = &Tr2Enable;
	pin_ptr<int> temp_Tr3Enable = &Tr3Enable;
	pin_ptr<int> temp_Tr4Enable = &Tr4Enable;

	trace1->set_memory_address(temp_Tr1Enable, temp_Tr1Type, temp_Tr1SParam);
	trace2->set_memory_address(temp_Tr2Enable, temp_Tr2Type, temp_Tr2SParam);
	trace3->set_memory_address(temp_Tr3Enable, temp_Tr3Type, temp_Tr3SParam);
	trace4->set_memory_address(temp_Tr4Enable, temp_Tr4Type, temp_Tr4SParam);
}



private: System::Void chkbx_Tr1_Enable_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (chkbx_Tr1_Enable->Checked == TRUE) {
		Tr1Enable = 1;
	}
	else {
		Tr1Enable = 0;
	}
}
private: System::Void chkbx_Tr2_Enable_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (chkbx_Tr2_Enable->Checked == TRUE) {
		Tr2Enable = 1;
	}
	else {
		Tr2Enable = 0;
	}
}
private: System::Void chkbx_Tr3_Enable_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (chkbx_Tr3_Enable->Checked == TRUE) {
		Tr3Enable = 1;
	}
	else {
		Tr3Enable = 0;
	}
}
private: System::Void chkbx_Tr4_Enable_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (chkbx_Tr4_Enable->Checked == TRUE) {
		Tr4Enable = 1;
	}
	else {
		Tr4Enable = 0;
	}
}
private: System::Void group_AntennaPos_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void btn_ScannerHome_Click(System::Object^  sender, System::EventArgs^  e) {
	InitPort(&hComm, ComPortName);           //Initialize Serial Port
	SetRxMask(&hComm);					      //Set Receive Mask
	SetAcelandVel(&hComm, ComPortName);
	GoHome(&hComm, ComPortName);
	ClosePort(&hComm, ComPortName);
}
private: System::Void btnFirst_Pos_Click(System::Object^  sender, System::EventArgs^  e) {
	InitPort(&hComm, ComPortName);           //Initialize Serial Port
	SetRxMask(&hComm);					      //Set Receive Mask
	SetAcelandVel(&hComm, ComPortName);
	GoToFirstPos(&hComm, ComPortName, xstart_steps, ystart_steps);
	ClosePort(&hComm, ComPortName);
}
};
}
