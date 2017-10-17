#pragma once
#include <string.h>
#include <iostream>
#include <fstream>
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

//Global Strings for VISA lib. Change scope of these later
char strResult[256] = { 0 };
char noErrString[256] = { "+0,\"No error\"\n" };
char buf[256];



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
	private: System::Windows::Forms::GroupBox^  groupBox1;
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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
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
			this->groupBox1->SuspendLayout();
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
			this->readCSVfile->Location = System::Drawing::Point(240, 61);
			this->readCSVfile->Name = L"readCSVfile";
			this->readCSVfile->Size = System::Drawing::Size(75, 23);
			this->readCSVfile->TabIndex = 10;
			this->readCSVfile->Text = L"Read CSV";
			this->readCSVfile->UseVisualStyleBackColor = true;
			this->readCSVfile->Click += gcnew System::EventHandler(this, &MainForm::readCSVfile_Click);
			// 
			// Append_CSV
			// 
			this->Append_CSV->Location = System::Drawing::Point(240, 90);
			this->Append_CSV->Name = L"Append_CSV";
			this->Append_CSV->Size = System::Drawing::Size(75, 23);
			this->Append_CSV->TabIndex = 11;
			this->Append_CSV->Text = L"Append CSV";
			this->Append_CSV->UseVisualStyleBackColor = true;
			this->Append_CSV->Click += gcnew System::EventHandler(this, &MainForm::Append_CSV_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->SpanTextBox);
			this->groupBox1->Controls->Add(this->CenterTextBox);
			this->groupBox1->Controls->Add(this->StopTextBox);
			this->groupBox1->Controls->Add(this->StartTextBox);
			this->groupBox1->Controls->Add(this->SpanFreqLabel);
			this->groupBox1->Controls->Add(this->CenterFreqLabel);
			this->groupBox1->Controls->Add(this->StopFreqLabel);
			this->groupBox1->Controls->Add(this->StartFreqLabel);
			this->groupBox1->Controls->Add(this->CenterSpanRadio);
			this->groupBox1->Controls->Add(this->StartStopRadio);
			this->groupBox1->Location = System::Drawing::Point(571, 61);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(260, 155);
			this->groupBox1->TabIndex = 12;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Frequency";
			// 
			// SpanTextBox
			// 
			this->SpanTextBox->Location = System::Drawing::Point(80, 124);
			this->SpanTextBox->Name = L"SpanTextBox";
			this->SpanTextBox->Size = System::Drawing::Size(100, 20);
			this->SpanTextBox->TabIndex = 9;
			// 
			// CenterTextBox
			// 
			this->CenterTextBox->Location = System::Drawing::Point(80, 99);
			this->CenterTextBox->Name = L"CenterTextBox";
			this->CenterTextBox->Size = System::Drawing::Size(100, 20);
			this->CenterTextBox->TabIndex = 8;
			// 
			// StopTextBox
			// 
			this->StopTextBox->Location = System::Drawing::Point(80, 75);
			this->StopTextBox->Name = L"StopTextBox";
			this->StopTextBox->Size = System::Drawing::Size(100, 20);
			this->StopTextBox->TabIndex = 7;
			// 
			// StartTextBox
			// 
			this->StartTextBox->Location = System::Drawing::Point(80, 52);
			this->StartTextBox->Name = L"StartTextBox";
			this->StartTextBox->Size = System::Drawing::Size(100, 20);
			this->StartTextBox->TabIndex = 6;
			// 
			// SpanFreqLabel
			// 
			this->SpanFreqLabel->AutoSize = true;
			this->SpanFreqLabel->Location = System::Drawing::Point(7, 127);
			this->SpanFreqLabel->Name = L"SpanFreqLabel";
			this->SpanFreqLabel->Size = System::Drawing::Size(59, 13);
			this->SpanFreqLabel->TabIndex = 5;
			this->SpanFreqLabel->Text = L"Span Freq:";
			// 
			// CenterFreqLabel
			// 
			this->CenterFreqLabel->AutoSize = true;
			this->CenterFreqLabel->Location = System::Drawing::Point(6, 102);
			this->CenterFreqLabel->Name = L"CenterFreqLabel";
			this->CenterFreqLabel->Size = System::Drawing::Size(65, 13);
			this->CenterFreqLabel->TabIndex = 4;
			this->CenterFreqLabel->Text = L"Center Freq:";
			// 
			// StopFreqLabel
			// 
			this->StopFreqLabel->AutoSize = true;
			this->StopFreqLabel->Location = System::Drawing::Point(7, 78);
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
			this->CenterSpanRadio->TabStop = true;
			this->CenterSpanRadio->Text = L"Center/Span";
			this->CenterSpanRadio->UseVisualStyleBackColor = true;
			this->CenterSpanRadio->CheckedChanged += gcnew System::EventHandler(this, &MainForm::CenterSpanRadio_CheckedChanged);
			// 
			// StartStopRadio
			// 
			this->StartStopRadio->AutoSize = true;
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
			this->SetCMDButton->Location = System::Drawing::Point(581, 223);
			this->SetCMDButton->Name = L"SetCMDButton";
			this->SetCMDButton->Size = System::Drawing::Size(112, 23);
			this->SetCMDButton->TabIndex = 13;
			this->SetCMDButton->Text = L"Set Commands";
			this->SetCMDButton->UseVisualStyleBackColor = true;
			this->SetCMDButton->Click += gcnew System::EventHandler(this, &MainForm::SetCMDButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(923, 282);
			this->Controls->Add(this->SetCMDButton);
			this->Controls->Add(this->groupBox1);
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
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
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
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		//Open COM
		ViSession viDefaultRM, Instrument;
		ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
		ViUInt32 actual;
		viOpenDefaultRM(&viDefaultRM);
		viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);

		viScanf(Instrument, "%t", &buf); //Read buffer into memory
		label1->Text = "Command Read";
		std::cout << "The visa buffer was read: \n";
		std::cout << buf;
		std::cout << "\n";
		viClose(Instrument); //Close COM

		String^ nativeVISAREAD;
		nativeVISAREAD = Marshal::PtrToStringAnsi((IntPtr)buf); //Convert to native string
		label4->Text = nativeVISAREAD;
	}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	//label1->Text = "thasdfasd";
}

private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Enter) {
		//LITERALLY COPIED FROM BUTTON FUNCTION

		//Opening COM
		ViSession viDefaultRM, Instrument;
		ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
		ViUInt32 actual;
		viOpenDefaultRM(&viDefaultRM);
		viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);

		//sending a cmd
		char SCPIcmd[10000]; //Char Array for CMD [FINAL DATA TYPE BEFORE TRANS]

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
}

private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
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

		for (int i = 0; i < csv_values.size();i++) {
			std::cout << csv_values[i];
			
		}

	}
	else {
		std::cout<<("Error in opening CSV file.\n");
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

private: System::Void StartStopRadio_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (StartStopRadio->Checked == 1) {
		StartTextBox->Enabled = 1;
		StopTextBox->Enabled = 1;
		SpanTextBox->Enabled = 0;
		CenterTextBox->Enabled = 0;
	}
}
private: System::Void CenterSpanRadio_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (CenterSpanRadio->Checked == 1) {
		StartTextBox->Enabled = 0;
		StopTextBox->Enabled = 0;
		SpanTextBox->Enabled = 1;
		CenterTextBox->Enabled = 1;
	}
}

private: System::Void SetCMDButton_Click(System::Object^  sender, System::EventArgs^  e) {

	if (StartStopRadio->Checked == 1) {
		//Opening COM
		ViSession viDefaultRM, Instrument;
		ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
		ViUInt32 actual;
		viOpenDefaultRM(&viDefaultRM);
		viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);

		//sending a cmd
		char SCPIcmd[256]; //Char Array for CMD [FINAL DATA TYPE BEFORE TRANS]
		

		//Round 1 for start cmd
		String^ test = (StartTextBox->Text); //NATIVE STRING
		test = ":SENS1:FREQ:STAR " + test;
		IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(test); //PTR TO NATIVE STRING
		char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR
		strcpy(SCPIcmd,nativeString); //COPY CHAR ARRAY TO SCPIcmd 
		//char SCPIcmd2[256] = ":SENS1:FREQ:STAR ";
		

		viWrite(Instrument, (ViBuf)SCPIcmd, (ViUInt32)strlen(SCPIcmd), &actual);
		label1->Text = "Command Sent"; //INFORM USER THAT CMD WAS SENT
		std::cout << "The command: ";
		std::cout << SCPIcmd;
		std::cout << " was sent. \n";

		//Round 2 for Stop CMD

		test = (StopTextBox->Text); //NATIVE STRING
		test = ":SENS1:FREQ:STOP " + test;
		ptrToNativeString = Marshal::StringToHGlobalAnsi(test); //PTR TO NATIVE STRING
		nativeString = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR
		strcpy(SCPIcmd, nativeString); //COPY CHAR ARRAY TO SCPIcmd 
									   //char SCPIcmd2[256] = ":SENS1:FREQ:STAR ";


		viWrite(Instrument, (ViBuf)SCPIcmd, (ViUInt32)strlen(SCPIcmd), &actual);
		label1->Text = "Command Sent"; //INFORM USER THAT CMD WAS SENT
		std::cout << "The command: ";
		std::cout << SCPIcmd;
		std::cout << " was sent. \n";


		viClose(Instrument);

	}

	if (CenterSpanRadio->Checked == 1) {
		//Opening COM
		ViSession viDefaultRM, Instrument;
		ViRsrc TxtAddress = DEFAULT_LOGICAL_ADDRESS;
		ViUInt32 actual;
		viOpenDefaultRM(&viDefaultRM);
		viOpen(viDefaultRM, TxtAddress, VI_NULL, VI_NULL, &Instrument);

		//sending a cmd
		char SCPIcmd[256]; //Char Array for CMD [FINAL DATA TYPE BEFORE TRANS]


						   //Round 1 for start cmd
		String^ test = (CenterTextBox->Text); //NATIVE STRING
		test = ":SENS1:FREQ:CENT " + test;
		IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(test); //PTR TO NATIVE STRING
		char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR
		strcpy(SCPIcmd, nativeString); //COPY CHAR ARRAY TO SCPIcmd 
									   //char SCPIcmd2[256] = ":SENS1:FREQ:STAR ";


		viWrite(Instrument, (ViBuf)SCPIcmd, (ViUInt32)strlen(SCPIcmd), &actual);
		label1->Text = "Command Sent"; //INFORM USER THAT CMD WAS SENT
		std::cout << "The command: ";
		std::cout << SCPIcmd;
		std::cout << " was sent. \n";

		//Round 2 for Stop CMD

		test = (SpanTextBox->Text); //NATIVE STRING
		test = ":SENS1:FREQ:SPAN " + test;
		ptrToNativeString = Marshal::StringToHGlobalAnsi(test); //PTR TO NATIVE STRING
		nativeString = static_cast<char*>(ptrToNativeString.ToPointer()); //CAST POINT AS STATIC CHAR
		strcpy(SCPIcmd, nativeString); //COPY CHAR ARRAY TO SCPIcmd 
									   //char SCPIcmd2[256] = ":SENS1:FREQ:STAR ";


		viWrite(Instrument, (ViBuf)SCPIcmd, (ViUInt32)strlen(SCPIcmd), &actual);
		label1->Text = "Command Sent"; //INFORM USER THAT CMD WAS SENT
		std::cout << "The command: ";
		std::cout << SCPIcmd;
		std::cout << " was sent. \n";


		viClose(Instrument);

	}


}
};
}
