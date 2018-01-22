#pragma once
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visatype.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visaext.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visaext.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visa.h"

//Mention Visa connection string here.
#define DEFAULT_LOGICAL_ADDRESS "TCPIP0::192.168.100.5::inst0::INSTR"
#define CSV_FILE_NAME "commandList.csv"
char instAdd[] = DEFAULT_LOGICAL_ADDRESS;

//Error checking constraights
#define FREQ_MAX 10000000000 //Set to 10ghz for now. Dont know a proper limit
#define FREQ_MIN 250000 //Set to 250khz for now. Dont know a proper limit


//Global Strings for VISA lib. Change scope of these later
//this might no longer be needed. Should remove if possible
char strResult[256] = { 0 };
char noErrString[256] = { "+0,\"No error\"\n" };


namespace Design_Project {

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
			//
			//TODO: Add the constructor code here
			//
			
			//Update LABEL2 with address for display 
			label2->Text = DEFAULT_LOGICAL_ADDRESS;

			//default list box selection
			ListBox_Trace1->SelectedIndex = 0;
			ListBox_Trace2->SelectedIndex = 0;
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
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

	private: System::Windows::Forms::Button^  button1;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  readCSVfile;
	private: System::Windows::Forms::Button^  Append_CSV;
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
	private: System::Windows::Forms::GroupBox^  Group_Trace;

	private: System::Windows::Forms::Label^  labelTrace1;
	private: System::Windows::Forms::ListBox^  ListBox_Trace1;
	private: System::Windows::Forms::ListBox^  ListBox_Trace2;
	private: System::Windows::Forms::Label^  LabelTrace2;
	private: System::Windows::Forms::Label^  label_SetCommands;
	private: System::Windows::Forms::CheckBox^  chkbx_Tr2Enable;

	private: System::Windows::Forms::CheckBox^  chkbx_Tr1Enable;
	private: System::Windows::Forms::Button^  btn_IMM;
	private: System::Windows::Forms::GroupBox^  Group_Sparam;
	private: System::Windows::Forms::RadioButton^  rad_S22;
	private: System::Windows::Forms::RadioButton^  rad_S21;
	private: System::Windows::Forms::RadioButton^  rad_S12;
	private: System::Windows::Forms::RadioButton^  rad_S11;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Button^  btn_Data;





	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->readCSVfile = (gcnew System::Windows::Forms::Button());
			this->Append_CSV = (gcnew System::Windows::Forms::Button());
			this->Group_Freq = (gcnew System::Windows::Forms::GroupBox());
			this->Span_Units = (gcnew System::Windows::Forms::GroupBox());
			this->Span_kHz = (gcnew System::Windows::Forms::RadioButton());
			this->Span_MHz = (gcnew System::Windows::Forms::RadioButton());
			this->Span_GHz = (gcnew System::Windows::Forms::RadioButton());
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
			this->Group_Trace = (gcnew System::Windows::Forms::GroupBox());
			this->chkbx_Tr2Enable = (gcnew System::Windows::Forms::CheckBox());
			this->chkbx_Tr1Enable = (gcnew System::Windows::Forms::CheckBox());
			this->ListBox_Trace2 = (gcnew System::Windows::Forms::ListBox());
			this->LabelTrace2 = (gcnew System::Windows::Forms::Label());
			this->labelTrace1 = (gcnew System::Windows::Forms::Label());
			this->ListBox_Trace1 = (gcnew System::Windows::Forms::ListBox());
			this->label_SetCommands = (gcnew System::Windows::Forms::Label());
			this->btn_IMM = (gcnew System::Windows::Forms::Button());
			this->Group_Sparam = (gcnew System::Windows::Forms::GroupBox());
			this->rad_S22 = (gcnew System::Windows::Forms::RadioButton());
			this->rad_S21 = (gcnew System::Windows::Forms::RadioButton());
			this->rad_S12 = (gcnew System::Windows::Forms::RadioButton());
			this->rad_S11 = (gcnew System::Windows::Forms::RadioButton());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->btn_Data = (gcnew System::Windows::Forms::Button());
			this->Group_Freq->SuspendLayout();
			this->Span_Units->SuspendLayout();
			this->Center_Units->SuspendLayout();
			this->Stop_Units->SuspendLayout();
			this->Start_Units->SuspendLayout();
			this->Group_Power->SuspendLayout();
			this->Power_Units->SuspendLayout();
			this->Group_Trace->SuspendLayout();
			this->Group_Sparam->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(118, 61);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Send CMD";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 86);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(34, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"---------";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(118, 90);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Read VISA";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 63);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 5;
			this->textBox1->Text = L"*IDN\?";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox1_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"label2";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 25);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(89, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"VISA ADDRESS:";
			this->label3->Click += gcnew System::EventHandler(this, &MainForm::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 113);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(40, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"-----------";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(13, 100);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(101, 13);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Recieved message:";
			this->label5->Click += gcnew System::EventHandler(this, &MainForm::label5_Click);
			// 
			// readCSVfile
			// 
			this->readCSVfile->Location = System::Drawing::Point(199, 63);
			this->readCSVfile->Name = L"readCSVfile";
			this->readCSVfile->Size = System::Drawing::Size(75, 23);
			this->readCSVfile->TabIndex = 10;
			this->readCSVfile->Text = L"Read CSV";
			this->readCSVfile->UseVisualStyleBackColor = true;
			this->readCSVfile->Click += gcnew System::EventHandler(this, &MainForm::readCSVfile_Click);
			// 
			// Append_CSV
			// 
			this->Append_CSV->Location = System::Drawing::Point(199, 92);
			this->Append_CSV->Name = L"Append_CSV";
			this->Append_CSV->Size = System::Drawing::Size(75, 23);
			this->Append_CSV->TabIndex = 11;
			this->Append_CSV->Text = L"Append CSV";
			this->Append_CSV->UseVisualStyleBackColor = true;
			this->Append_CSV->Click += gcnew System::EventHandler(this, &MainForm::Append_CSV_Click);
			// 
			// Group_Freq
			// 
			this->Group_Freq->Controls->Add(this->Span_Units);
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
			this->Group_Freq->Location = System::Drawing::Point(450, 12);
			this->Group_Freq->Name = L"Group_Freq";
			this->Group_Freq->Size = System::Drawing::Size(373, 194);
			this->Group_Freq->TabIndex = 12;
			this->Group_Freq->TabStop = false;
			this->Group_Freq->Text = L"Frequency";
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
			this->SetCMDButton->Location = System::Drawing::Point(332, 141);
			this->SetCMDButton->Name = L"SetCMDButton";
			this->SetCMDButton->Size = System::Drawing::Size(112, 23);
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
			this->Group_Power->Location = System::Drawing::Point(450, 212);
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
			// Group_Trace
			// 
			this->Group_Trace->Controls->Add(this->chkbx_Tr2Enable);
			this->Group_Trace->Controls->Add(this->chkbx_Tr1Enable);
			this->Group_Trace->Controls->Add(this->ListBox_Trace2);
			this->Group_Trace->Controls->Add(this->LabelTrace2);
			this->Group_Trace->Controls->Add(this->labelTrace1);
			this->Group_Trace->Location = System::Drawing::Point(450, 275);
			this->Group_Trace->Name = L"Group_Trace";
			this->Group_Trace->Size = System::Drawing::Size(373, 94);
			this->Group_Trace->TabIndex = 15;
			this->Group_Trace->TabStop = false;
			this->Group_Trace->Text = L"Trace";
			// 
			// chkbx_Tr2Enable
			// 
			this->chkbx_Tr2Enable->AutoSize = true;
			this->chkbx_Tr2Enable->Location = System::Drawing::Point(242, 19);
			this->chkbx_Tr2Enable->Name = L"chkbx_Tr2Enable";
			this->chkbx_Tr2Enable->Size = System::Drawing::Size(59, 17);
			this->chkbx_Tr2Enable->TabIndex = 4;
			this->chkbx_Tr2Enable->Text = L"Enable";
			this->chkbx_Tr2Enable->UseVisualStyleBackColor = true;
			// 
			// chkbx_Tr1Enable
			// 
			this->chkbx_Tr1Enable->AutoSize = true;
			this->chkbx_Tr1Enable->Checked = true;
			this->chkbx_Tr1Enable->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkbx_Tr1Enable->Location = System::Drawing::Point(66, 18);
			this->chkbx_Tr1Enable->Name = L"chkbx_Tr1Enable";
			this->chkbx_Tr1Enable->Size = System::Drawing::Size(59, 17);
			this->chkbx_Tr1Enable->TabIndex = 3;
			this->chkbx_Tr1Enable->Text = L"Enable";
			this->chkbx_Tr1Enable->UseVisualStyleBackColor = true;
			// 
			// ListBox_Trace2
			// 
			this->ListBox_Trace2->FormattingEnabled = true;
			this->ListBox_Trace2->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"Mag Log", L"Smith", L"Phase", L"Polar",
					L"Lin Mag", L"SWR", L"Real", L"Imaginary", L"Expanded Phase", L"Positive Phase"
			});
			this->ListBox_Trace2->Location = System::Drawing::Point(194, 36);
			this->ListBox_Trace2->Name = L"ListBox_Trace2";
			this->ListBox_Trace2->Size = System::Drawing::Size(120, 43);
			this->ListBox_Trace2->TabIndex = 2;
			// 
			// LabelTrace2
			// 
			this->LabelTrace2->AutoSize = true;
			this->LabelTrace2->Location = System::Drawing::Point(188, 19);
			this->LabelTrace2->Name = L"LabelTrace2";
			this->LabelTrace2->Size = System::Drawing::Size(47, 13);
			this->LabelTrace2->TabIndex = 1;
			this->LabelTrace2->Text = L"Trace 2:";
			// 
			// labelTrace1
			// 
			this->labelTrace1->AutoSize = true;
			this->labelTrace1->Location = System::Drawing::Point(13, 20);
			this->labelTrace1->Name = L"labelTrace1";
			this->labelTrace1->Size = System::Drawing::Size(47, 13);
			this->labelTrace1->TabIndex = 0;
			this->labelTrace1->Text = L"Trace 1:";
			// 
			// ListBox_Trace1
			// 
			this->ListBox_Trace1->FormattingEnabled = true;
			this->ListBox_Trace1->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"Mag Log", L"Smith", L"Phase", L"Polar",
					L"Lin Mag", L"SWR", L"Real", L"Imaginary", L"Expanded Phase", L"Positive Phase"
			});
			this->ListBox_Trace1->Location = System::Drawing::Point(466, 311);
			this->ListBox_Trace1->Name = L"ListBox_Trace1";
			this->ListBox_Trace1->Size = System::Drawing::Size(120, 43);
			this->ListBox_Trace1->TabIndex = 1;
			// 
			// label_SetCommands
			// 
			this->label_SetCommands->AutoSize = true;
			this->label_SetCommands->Location = System::Drawing::Point(106, 146);
			this->label_SetCommands->Name = L"label_SetCommands";
			this->label_SetCommands->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->label_SetCommands->Size = System::Drawing::Size(220, 13);
			this->label_SetCommands->TabIndex = 16;
			this->label_SetCommands->Text = L"This button will set the parameters to the right";
			// 
			// btn_IMM
			// 
			this->btn_IMM->Location = System::Drawing::Point(332, 170);
			this->btn_IMM->Name = L"btn_IMM";
			this->btn_IMM->Size = System::Drawing::Size(112, 23);
			this->btn_IMM->TabIndex = 17;
			this->btn_IMM->Text = L"Immediate Scan";
			this->btn_IMM->UseVisualStyleBackColor = true;
			this->btn_IMM->Click += gcnew System::EventHandler(this, &MainForm::btn_IMM_Click);
			// 
			// Group_Sparam
			// 
			this->Group_Sparam->Controls->Add(this->rad_S22);
			this->Group_Sparam->Controls->Add(this->rad_S21);
			this->Group_Sparam->Controls->Add(this->rad_S12);
			this->Group_Sparam->Controls->Add(this->rad_S11);
			this->Group_Sparam->Location = System::Drawing::Point(450, 376);
			this->Group_Sparam->Name = L"Group_Sparam";
			this->Group_Sparam->Size = System::Drawing::Size(173, 69);
			this->Group_Sparam->TabIndex = 18;
			this->Group_Sparam->TabStop = false;
			this->Group_Sparam->Text = L"S Parameter";
			// 
			// rad_S22
			// 
			this->rad_S22->AutoSize = true;
			this->rad_S22->Location = System::Drawing::Point(66, 42);
			this->rad_S22->Name = L"rad_S22";
			this->rad_S22->Size = System::Drawing::Size(44, 17);
			this->rad_S22->TabIndex = 3;
			this->rad_S22->TabStop = true;
			this->rad_S22->Text = L"S22";
			this->rad_S22->UseVisualStyleBackColor = true;
			// 
			// rad_S21
			// 
			this->rad_S21->AutoSize = true;
			this->rad_S21->Location = System::Drawing::Point(16, 42);
			this->rad_S21->Name = L"rad_S21";
			this->rad_S21->Size = System::Drawing::Size(44, 17);
			this->rad_S21->TabIndex = 2;
			this->rad_S21->TabStop = true;
			this->rad_S21->Text = L"S21";
			this->rad_S21->UseVisualStyleBackColor = true;
			// 
			// rad_S12
			// 
			this->rad_S12->AutoSize = true;
			this->rad_S12->Location = System::Drawing::Point(66, 19);
			this->rad_S12->Name = L"rad_S12";
			this->rad_S12->Size = System::Drawing::Size(44, 17);
			this->rad_S12->TabIndex = 1;
			this->rad_S12->Text = L"S12";
			this->rad_S12->UseVisualStyleBackColor = true;
			// 
			// rad_S11
			// 
			this->rad_S11->AutoSize = true;
			this->rad_S11->Checked = true;
			this->rad_S11->Location = System::Drawing::Point(16, 19);
			this->rad_S11->Name = L"rad_S11";
			this->rad_S11->Size = System::Drawing::Size(44, 17);
			this->rad_S11->TabIndex = 0;
			this->rad_S11->TabStop = true;
			this->rad_S11->Text = L"S11";
			this->rad_S11->UseVisualStyleBackColor = true;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(118, 25);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(156, 13);
			this->label7->TabIndex = 19;
			this->label7->Text = L"These controls will be removed.";
			// 
			// btn_Data
			// 
			this->btn_Data->Location = System::Drawing::Point(332, 200);
			this->btn_Data->Name = L"btn_Data";
			this->btn_Data->Size = System::Drawing::Size(112, 23);
			this->btn_Data->TabIndex = 20;
			this->btn_Data->Text = L"Get Raw Data";
			this->btn_Data->UseVisualStyleBackColor = true;
			this->btn_Data->Click += gcnew System::EventHandler(this, &MainForm::btn_Data_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(923, 457);
			this->Controls->Add(this->btn_Data);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->Group_Sparam);
			this->Controls->Add(this->btn_IMM);
			this->Controls->Add(this->label_SetCommands);
			this->Controls->Add(this->ListBox_Trace1);
			this->Controls->Add(this->Group_Trace);
			this->Controls->Add(this->Group_Power);
			this->Controls->Add(this->SetCMDButton);
			this->Controls->Add(this->Group_Freq);
			this->Controls->Add(this->Append_CSV);
			this->Controls->Add(this->readCSVfile);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"MainForm";
			this->Text = L"Team Zero Impedance";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->Group_Freq->ResumeLayout(false);
			this->Group_Freq->PerformLayout();
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
			this->Group_Trace->ResumeLayout(false);
			this->Group_Trace->PerformLayout();
			this->Group_Sparam->ResumeLayout(false);
			this->Group_Sparam->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

//button for send a the textbox on comm. This has not been cleaned up yet.
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		
		//Opening COM
		ViSession viDefaultRM, Instrument; 
		ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
		ViUInt32 actual;
		viOpenDefaultRM(&viDefaultRM);
		viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);

		//sending a cmd
		char SCPIcmd[256]; //Char Array for CMD [FINAL DATA TYPE BEFORE TRANS]

		String^ test = (textBox1->Text); //NATIVE STRING
		IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(test); //PTR TO NATIVE STRING
		char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR
		strcpy(SCPIcmd, nativeString); //COPY CHAR ARRAY TO SCPIcmd 

		viWrite(Instrument, (ViBuf)SCPIcmd, (ViUInt32)strlen(SCPIcmd), &actual);
		label1->Text = "Command Sent"; //INFORM USER THAT CMD WAS SENT
		std::cout << "The command: ";
		std::cout << SCPIcmd;
		std::cout << " was sent. \n";
		viClose(Instrument);

	}

 //button for reading the comm. Still needs to be cleaned up.
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		//Open COM

		std::string tempString = readSCPI_Buffer();
		//String^ nativeVISAREAD = gcnew String(tempString.c_str());
		//label4->Text = nativeVISAREAD;
	}

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

	std::cout << "The BUTTON SetCMDButton was pressed \n";
	returnStatus = Controls_Frequency();
	returnStatus = Controls_Power();
	returnStatus = Controls_Trace();
	std::cout << "\n";

}

private: bool is_number(String^ testString){
	/**
	*   \brief Checks passed String^ for "-.0123456789"
	*   \param String^ to be checked.
	*   \return Returns a boolean.
	**/

	//Next 4 lines are string conversion
	IntPtr ptrToNativeString; //Pointer for String to Char conversion
	char* nativeString; // Static Char used in conversion process
	ptrToNativeString = Marshal::StringToHGlobalAnsi(testString); //PTR TO NATIVE STRING
	std::string s = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR

	return(strspn(s.c_str(), "-.0123456789") == s.size()); //Check for valid chars
}

private: std::string Controls_Trace(void) {
	/**
	*   \brief Sends Trace Controls to NA.
	*
	*   \param NO INPUT PARAMETERS.
	*   \return Returns a Status String.
	*
	**/
	std::string returnStatus;
	std::string linkedList[] = { "MLOG", "SMIT", "PHAS", "POL", "LMAG", "SWR", "REAL", "IMAG", "UPH", "PPH" };

	String^ traceCMD = ":CALC1:TRAC1:FORM ";
	String^ tempSelection = gcnew String(linkedList[ListBox_Trace1->SelectedIndex].c_str()); //convert string to String^
	traceCMD = traceCMD + tempSelection;
	if (chkbx_Tr1Enable->Checked == true) {
		sendSCPI_String(traceCMD);
	}
	

	traceCMD = ":CALC1:TRAC2:FORM ";
	tempSelection = gcnew String(linkedList[ListBox_Trace2->SelectedIndex].c_str());
	traceCMD = traceCMD + tempSelection;
	if (chkbx_Tr2Enable->Checked == true) {
		sendSCPI_String(traceCMD);
	}

	//Return statement
	returnStatus = "Maybe it worked...";
	return returnStatus;
}

private: std::string Controls_Power(void) {
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
	sendSCPI_String(powerCMD);
	
	//INCOMPLETE CODE BELOW!!!!!!

	//Power should be checked now
	sendSCPI_String(":SOUR:POW:LEV:IMM:AMPL?");
	std::string returnMessage = readSCPI_Buffer();
	//now convert "+5.000000000E+009" string into a double
	//Check numbers
	
	//Return statement
	returnStatus = "Maybe it worked...";
	return returnStatus;
}


private: std::string Controls_Frequency(void) {
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
	String^ frequencyCMD; //Working variable for forming the string .... TO BE DELETED
	
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
			sendSCPI_String(frequencyStartCMD);
			frequencyStopCMD = frequencyStopCMD + frequencyStopNum;
			sendSCPI_String(frequencyStopCMD);

			//INCOMPLETE CODE BELOW!!!!!!

			//start and stop parameters should be checked now
			sendSCPI_String(":SENS1:FREQ:STAR?");
			std::string returnMessage = readSCPI_Buffer();
			//now convert "+5.000000000E+009" string into a double
			//Then compare number, and repeat for stop command. Copy code for center span.


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
			sendSCPI_String(frequencyCenterCMD);
			frequencySpanCMD = frequencySpanCMD + frequencySpanNum;
			sendSCPI_String(frequencySpanCMD);
		}
		else {
			returnStatus = "Center and Span Frequencies are NOT in range\n";
			std::cout << returnStatus;
			MessageBox::Show("Please check the input frequencies.\nParameters are not in range.\nParameter not set.", "Cener/Span Frequency is not valid", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return returnStatus;
		}
	}

	//Return statement
	returnStatus = "Maybe it worked...";
	return returnStatus;
}


private: double string_to_double(const std::string& s){
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

private: std::string convert_vcppString_string(String^ vcppString) {
	/**
	*   \brief converts a visual C++ string to a normal C string
	**/
	char charBuffer[256]; //Char Array Buffer
	IntPtr ptrToNativeString; //Pointer for String to Char conversion
	char* nativeString; // Static Char used in conversion process

	ptrToNativeString = Marshal::StringToHGlobalAnsi(vcppString); //PTR TO NATIVE STRING
	nativeString = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR
	strcpy(charBuffer, nativeString); //COPY CHAR ARRAY TO SCPIcmd Char buffer
	return (std::string)charBuffer;
}

private: std::string readSCPI_Buffer(System::Void) {
	/**
	*   \brief Reads the SCPI buffer
	*
	*   This function is responsiable reading commands sent by the NA
	*
	*   \param void
	*   \return Returns a std c string.
	**/

	//Open COM
		ViSession viDefaultRM, Instrument;
		ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
		viOpenDefaultRM(&viDefaultRM);
		viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);
	char buf[1000000];


		viScanf(Instrument, "%t", &buf); //Read buffer into memory


	std::cout << "The visa buffer was read:  \"";
	std::cout << buf;
	std::cout << "\" \n";
		viClose(Instrument); //Close COM

	String^ nativeVISAREAD;
	nativeVISAREAD = Marshal::PtrToStringAnsi((IntPtr)buf); //Convert to native string
	std::string VisaMessage = convert_vcppString_string(nativeVISAREAD);
	return VisaMessage;

}

private: System::Void sendSCPI_String(String^ sendString) {
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
		ViSession viDefaultRM, Instrument;
		ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
		ViUInt32 actual;
		viOpenDefaultRM(&viDefaultRM);
		viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);
	//End of communications opening

	std::string temp = convert_vcppString_string(sendString);
	const char *SCPIcmd = temp.c_str();
	
								   
		viWrite(Instrument, (ViBuf)SCPIcmd, (ViUInt32)strlen(SCPIcmd), &actual); //Send cmd on SPCI interface
		viClose(Instrument); //Close the comm


	label1->Text = "Command Sent"; //Update the a label on the form
	//Next three lines makes entry in console log
	std::cout << "The command:  \"";
	std::cout << SCPIcmd;
	std::cout << "\"   was sent. \n";
}
private: System::Void btn_IMM_Click(System::Object^  sender, System::EventArgs^  e) {
	//Need to select channel some how...
	sendSCPI_String(":INIT:IMM1");



}

private: System::Void btn_Data_Click(System::Object^  sender, System::EventArgs^  e) {

	String^ tempString;

	if (rad_S11->Checked == true) {
		tempString = ":SENS:DATA:RAWD? S11";
	}
	if (rad_S12->Checked == true) {
		tempString = ":SENS:DATA:RAWD? S12";
	}
	if (rad_S21->Checked == true) {
		tempString = ":SENS:DATA:RAWD? S21";
	}
	if (rad_S22->Checked == true) {
		tempString = ":SENS:DATA:RAWD? S22";
	}
	sendSCPI_String(tempString);

	//_sleep(50);
	//std::string tempReturn = readSCPI_Buffer();


}


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



		 //Below is some CSV shit code. This will be ripped out later
private: System::Void readCSVfile_Click(System::Object^  sender, System::EventArgs^  e) {
	std::cout << "\n======CVS READ CODE WAS CALLED======\n";
	std::ifstream csv_fileStream;
	csv_fileStream.open(CSV_FILE_NAME);

	if (csv_fileStream.is_open()) {

		std::cout << "The CSV File";
		std::cout << CSV_FILE_NAME;
		std::cout << " was opened\n";

		std::vector<char*> csv_values;
		const int MAXSIZE = 25600; //Max char length of an entry
		char csv_single_value[MAXSIZE];
		while (csv_fileStream.getline(csv_single_value, MAXSIZE, ','))
		{
			csv_values.resize(csv_values.size() + 1); //Expand vector size on the fly
			csv_values.back() = new char[MAXSIZE];
			strcpy(csv_values.back(), csv_single_value);
		}
		csv_fileStream.close();

		for (int i = 0; i < csv_values.size(); i++) {
			std::cout << csv_values[i];

		}

	}
	else {
		std::cout << ("Error in opening CSV file.\n");
	}
	std::cout << "\n";
	std::cout << "======End of CVS File======\n";


}
private: System::Void Append_CSV_Click(System::Object^  sender, System::EventArgs^  e) {
	std::cout << "\n======CVS APPEND CODE WAS CALLED======\n";

	//First open the old CSV file and read in all contents
	std::ifstream csv_fileStream;
	csv_fileStream.open(CSV_FILE_NAME);
	std::vector<char*> csv_values;
	if (csv_fileStream.is_open()) {

		const int MAXSIZE = 25600; //Max char length of an entry
		char csv_single_value[MAXSIZE];
		while (csv_fileStream.getline(csv_single_value, MAXSIZE, ','))
		{
			csv_values.resize(csv_values.size() + 1); //Expand vector size on the fly
			csv_values.back() = new char[MAXSIZE];
			strcpy(csv_values.back(), csv_single_value);
		}
		csv_fileStream.close();
	}
	else {
		std::cout << ("Error in opening CSV file.\n");
	}


	//Now rewrite the buffer and append the text
	std::ofstream csv_fileStream2;
	csv_fileStream2.open(CSV_FILE_NAME);
	for (int i = 0; i < csv_values.size(); i++) {
		csv_fileStream2 << csv_values[i];
	}


	char SCPIcmd[10000]; //Char Array for CMD [FINAL DATA TYPE BEFORE TRANS]

	String^ test = (textBox1->Text); //NATIVE STRING
	IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(test); //PTR TO NATIVE STRING
	char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR
	strcpy(SCPIcmd, nativeString); //COPY CHAR ARRAY TO SCPIcmd 

	csv_fileStream2 << SCPIcmd;
	csv_fileStream2 << "\n";
	csv_fileStream2.close();
}



};
}
