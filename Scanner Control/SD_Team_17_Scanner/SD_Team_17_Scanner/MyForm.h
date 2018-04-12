#pragma once

#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include "MyForm.h"
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <chrono>
#include <conio.h>
#include <ctime>
#using <System.dll>
#pragma warning(disable:4996)

//Function Prototypes
//
bool InitPort(HANDLE *hComm, char ComPortName[]); //open serial port, set parameters & timeouts
bool SetRxMask(HANDLE *hComm);
bool ClosePort(HANDLE *hComm, char ComPortName[]); //close serial port
bool WriteCmd(HANDLE *hComm, char lpBuffer[], char ComPortName[]);
bool ReadRsp(HANDLE *hComm, char ComPortName[]);
bool GoHome(HANDLE *hComm, char ComPortName[]);
//bool SetHome(HANDLE *hComm, char ComPortName[]);
bool SetAcelandVel(HANDLE *hComm, char ComPortName[]);
double ConvertCmtoSteps(double cm);
bool GoToFirstPos(HANDLE *hComm, char ComPortName[], int xstart_steps, int ystart_steps);
bool GoToNextPos(HANDLE * hComm, char ComPortName[], int xstep_size, int ystep_size,
	int yPoints, int row_size, int y_index, bool new_line);

HANDLE hComm;                          // Handle to the Serial port	
char   ComPortName[] = "COM1";         // Name of the Serial port(May Change) to be opened
BOOL   Status;
DWORD dwEventMask, NoBytesRead;        // Event mask to trigger
char  TempChar, SerialBuffer[256];     // Buffer Containing Rxed Data, Bytes read by ReadFile()
int i = 0;
bool scan = 1;

namespace SD_Team_17_Scanner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	using namespace System::Runtime::InteropServices;


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		//	
		//	TODO: Add the constructor code here
		//	
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  txtbx_XStart;
	private: System::Windows::Forms::TextBox^  txtbx_XStop;
	private: System::Windows::Forms::NumericUpDown^  numbox_Xpoints;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  txtbx_YStart;
	private: System::Windows::Forms::TextBox^  txtbx_YStop;
	private: System::Windows::Forms::NumericUpDown^  numbox_Ypoints;



	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  btn_ScannerHome;
	private: System::Windows::Forms::Button^  Get_UserInput;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  btnFirst_Pos;


	protected:

	protected:



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		double xstart_cm, xstop_cm, ystart_cm, ystop_cm;
		int xstart_steps, xstop_steps, xPoints, xstep_size;
		int ystart_steps, ystop_steps, yPoints, ystep_size;
	private: System::Windows::Forms::Button^  btnStart;
			 int row_size; //need to know row size to return to start of the row



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->txtbx_XStart = (gcnew System::Windows::Forms::TextBox());
			this->txtbx_XStop = (gcnew System::Windows::Forms::TextBox());
			this->numbox_Xpoints = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtbx_YStart = (gcnew System::Windows::Forms::TextBox());
			this->txtbx_YStop = (gcnew System::Windows::Forms::TextBox());
			this->numbox_Ypoints = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btn_ScannerHome = (gcnew System::Windows::Forms::Button());
			this->Get_UserInput = (gcnew System::Windows::Forms::Button());
			this->btnFirst_Pos = (gcnew System::Windows::Forms::Button());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numbox_Xpoints))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numbox_Ypoints))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// txtbx_XStart
			// 
			this->txtbx_XStart->Location = System::Drawing::Point(64, 27);
			this->txtbx_XStart->Name = L"txtbx_XStart";
			this->txtbx_XStart->Size = System::Drawing::Size(100, 20);
			this->txtbx_XStart->TabIndex = 0;
			this->txtbx_XStart->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// txtbx_XStop
			// 
			this->txtbx_XStop->Location = System::Drawing::Point(64, 53);
			this->txtbx_XStop->Name = L"txtbx_XStop";
			this->txtbx_XStop->Size = System::Drawing::Size(100, 20);
			this->txtbx_XStop->TabIndex = 1;
			this->txtbx_XStop->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			// 
			// numbox_Xpoints
			// 
			this->numbox_Xpoints->Location = System::Drawing::Point(64, 79);
			this->numbox_Xpoints->Name = L"numbox_Xpoints";
			this->numbox_Xpoints->Size = System::Drawing::Size(115, 20);
			this->numbox_Xpoints->TabIndex = 2;
			this->numbox_Xpoints->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->numbox_Xpoints);
			this->groupBox1->Controls->Add(this->txtbx_XStop);
			this->groupBox1->Controls->Add(this->txtbx_XStart);
			this->groupBox1->Location = System::Drawing::Point(28, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(207, 115);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"X Coordinate";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(11, 81);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Columns:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(29, 56);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(32, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Stop:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(29, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(32, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Start:";
			// 
			// txtbx_YStart
			// 
			this->txtbx_YStart->Location = System::Drawing::Point(62, 19);
			this->txtbx_YStart->Name = L"txtbx_YStart";
			this->txtbx_YStart->Size = System::Drawing::Size(100, 20);
			this->txtbx_YStart->TabIndex = 4;
			this->txtbx_YStart->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged_1);
			// 
			// txtbx_YStop
			// 
			this->txtbx_YStop->Location = System::Drawing::Point(62, 45);
			this->txtbx_YStop->Name = L"txtbx_YStop";
			this->txtbx_YStop->Size = System::Drawing::Size(100, 20);
			this->txtbx_YStop->TabIndex = 5;
			this->txtbx_YStop->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged_1);
			// 
			// numbox_Ypoints
			// 
			this->numbox_Ypoints->Location = System::Drawing::Point(62, 71);
			this->numbox_Ypoints->Name = L"numbox_Ypoints";
			this->numbox_Ypoints->Size = System::Drawing::Size(115, 20);
			this->numbox_Ypoints->TabIndex = 6;
			this->numbox_Ypoints->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged_1);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->numbox_Ypoints);
			this->groupBox2->Controls->Add(this->txtbx_YStop);
			this->groupBox2->Controls->Add(this->txtbx_YStart);
			this->groupBox2->Location = System::Drawing::Point(28, 133);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(207, 109);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Y Coordinate";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(19, 73);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(37, 13);
			this->label6->TabIndex = 9;
			this->label6->Text = L"Rows:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(24, 48);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(32, 13);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Stop:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(24, 22);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(32, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Start:";
			// 
			// btn_ScannerHome
			// 
			this->btn_ScannerHome->Location = System::Drawing::Point(28, 248);
			this->btn_ScannerHome->Name = L"btn_ScannerHome";
			this->btn_ScannerHome->Size = System::Drawing::Size(75, 23);
			this->btn_ScannerHome->TabIndex = 8;
			this->btn_ScannerHome->Text = L"Go Home";
			this->btn_ScannerHome->UseVisualStyleBackColor = true;
			this->btn_ScannerHome->Click += gcnew System::EventHandler(this, &MyForm::btn_ScannerHome_Click);
			// 
			// Get_UserInput
			// 
			this->Get_UserInput->Location = System::Drawing::Point(160, 248);
			this->Get_UserInput->Name = L"Get_UserInput";
			this->Get_UserInput->Size = System::Drawing::Size(75, 23);
			this->Get_UserInput->TabIndex = 9;
			this->Get_UserInput->Text = L"Load Input";
			this->Get_UserInput->UseVisualStyleBackColor = true;
			this->Get_UserInput->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// btnFirst_Pos
			// 
			this->btnFirst_Pos->Location = System::Drawing::Point(28, 291);
			this->btnFirst_Pos->Name = L"btnFirst_Pos";
			this->btnFirst_Pos->Size = System::Drawing::Size(100, 23);
			this->btnFirst_Pos->TabIndex = 10;
			this->btnFirst_Pos->Text = L"Move To 1st Pos";
			this->btnFirst_Pos->UseVisualStyleBackColor = true;
			this->btnFirst_Pos->Click += gcnew System::EventHandler(this, &MyForm::btnFirst_Pos_Click);
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(160, 290);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(75, 23);
			this->btnStart->TabIndex = 11;
			this->btnStart->Text = L"Start Scan";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &MyForm::btnStart_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(259, 339);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->btnFirst_Pos);
			this->Controls->Add(this->Get_UserInput);
			this->Controls->Add(this->btn_ScannerHome);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numbox_Xpoints))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numbox_Ypoints))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox2_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void numericUpDown1_ValueChanged_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	
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

private: System::Void btnStart_Click(System::Object^  sender, System::EventArgs^  e) {
	bool new_line = false;
	InitPort(&hComm, ComPortName);           //Initialize Serial Port
	SetRxMask(&hComm);					      //Set Receive Mask
	SetAcelandVel(&hComm, ComPortName);

	//execute a for loop to go through all scan points
	for (size_t i = 0; i < yPoints; i++) {
		for (size_t j = 0; j < xPoints; j++) {
			if (j == xPoints - 1) {
				new_line = true;
			}
			else 
				new_line = false;

			Sleep(2000);
			GoToNextPos(&hComm, ComPortName, xstep_size, ystep_size,
				yPoints, row_size, i, new_line);
		}
	}
	ClosePort(&hComm, ComPortName);
}
};
}
