#pragma once

//#include "MainForm.h"


namespace Design_Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for TraceControlEdit
	/// </summary>

	public ref class TraceControlEdit : public System::Windows::Forms::Form
	{
	public:
		TraceControlEdit(System::Windows::Forms::Form ^ tempMainForm, int tempTraceNum)
		{
			InitializeComponent();
			mainform = tempMainForm;
			traceIDNumber = tempTraceNum;
			lbl_TraceNumber->Text = "Trace "+ traceIDNumber + " Controls:";
			
			ListBox_TraceType->SelectedIndex = 0;

			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TraceControlEdit()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^  chx_EnableTrace;
	private: System::Windows::Forms::Label^  lbl_TraceNumber;
	private: System::Windows::Forms::GroupBox^  group_Trace_SParam;
	private: System::Windows::Forms::RadioButton^  rad_S22;
	private: System::Windows::Forms::RadioButton^  rad_S21;
	private: System::Windows::Forms::RadioButton^  rad_S11;
	private: System::Windows::Forms::RadioButton^  rad_S12;
	private: System::Windows::Forms::ListBox^  ListBox_TraceType;
	private: System::Windows::Forms::Button^  btn_OK;
	private: System::Windows::Forms::Button^  btn_Cancel;
	private: System::Windows::Forms::Form ^ mainform;
	private: int traceIDNumber;
	private: int* address_traceType;
	private: int* address_traceSParam;
	private: int* address_traceEnable;

	protected:

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
			this->chx_EnableTrace = (gcnew System::Windows::Forms::CheckBox());
			this->lbl_TraceNumber = (gcnew System::Windows::Forms::Label());
			this->group_Trace_SParam = (gcnew System::Windows::Forms::GroupBox());
			this->rad_S22 = (gcnew System::Windows::Forms::RadioButton());
			this->rad_S21 = (gcnew System::Windows::Forms::RadioButton());
			this->rad_S11 = (gcnew System::Windows::Forms::RadioButton());
			this->rad_S12 = (gcnew System::Windows::Forms::RadioButton());
			this->ListBox_TraceType = (gcnew System::Windows::Forms::ListBox());
			this->btn_OK = (gcnew System::Windows::Forms::Button());
			this->btn_Cancel = (gcnew System::Windows::Forms::Button());
			this->group_Trace_SParam->SuspendLayout();
			this->SuspendLayout();
			// 
			// chx_EnableTrace
			// 
			this->chx_EnableTrace->AutoSize = true;
			this->chx_EnableTrace->Checked = true;
			this->chx_EnableTrace->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chx_EnableTrace->Location = System::Drawing::Point(15, 25);
			this->chx_EnableTrace->Name = L"chx_EnableTrace";
			this->chx_EnableTrace->Size = System::Drawing::Size(90, 17);
			this->chx_EnableTrace->TabIndex = 0;
			this->chx_EnableTrace->Text = L"Enable Trace";
			this->chx_EnableTrace->UseMnemonic = false;
			this->chx_EnableTrace->UseVisualStyleBackColor = true;
			// 
			// lbl_TraceNumber
			// 
			this->lbl_TraceNumber->AutoSize = true;
			this->lbl_TraceNumber->Location = System::Drawing::Point(12, 9);
			this->lbl_TraceNumber->Name = L"lbl_TraceNumber";
			this->lbl_TraceNumber->Size = System::Drawing::Size(85, 13);
			this->lbl_TraceNumber->TabIndex = 1;
			this->lbl_TraceNumber->Text = L"Trace 1 Controls";
			// 
			// group_Trace_SParam
			// 
			this->group_Trace_SParam->Controls->Add(this->rad_S22);
			this->group_Trace_SParam->Controls->Add(this->rad_S21);
			this->group_Trace_SParam->Controls->Add(this->rad_S11);
			this->group_Trace_SParam->Controls->Add(this->rad_S12);
			this->group_Trace_SParam->Location = System::Drawing::Point(12, 48);
			this->group_Trace_SParam->Name = L"group_Trace_SParam";
			this->group_Trace_SParam->Size = System::Drawing::Size(131, 72);
			this->group_Trace_SParam->TabIndex = 33;
			this->group_Trace_SParam->TabStop = false;
			this->group_Trace_SParam->Text = L"S-Parameter";
			// 
			// rad_S22
			// 
			this->rad_S22->AutoSize = true;
			this->rad_S22->Location = System::Drawing::Point(66, 42);
			this->rad_S22->Name = L"rad_S22";
			this->rad_S22->Size = System::Drawing::Size(44, 17);
			this->rad_S22->TabIndex = 7;
			this->rad_S22->Text = L"S22";
			this->rad_S22->UseVisualStyleBackColor = true;
			// 
			// rad_S21
			// 
			this->rad_S21->AutoSize = true;
			this->rad_S21->Location = System::Drawing::Point(15, 42);
			this->rad_S21->Name = L"rad_S21";
			this->rad_S21->Size = System::Drawing::Size(44, 17);
			this->rad_S21->TabIndex = 6;
			this->rad_S21->Text = L"S21";
			this->rad_S21->UseVisualStyleBackColor = true;
			// 
			// rad_S11
			// 
			this->rad_S11->AutoSize = true;
			this->rad_S11->Checked = true;
			this->rad_S11->Location = System::Drawing::Point(15, 19);
			this->rad_S11->Name = L"rad_S11";
			this->rad_S11->Size = System::Drawing::Size(44, 17);
			this->rad_S11->TabIndex = 4;
			this->rad_S11->TabStop = true;
			this->rad_S11->Text = L"S11";
			this->rad_S11->UseVisualStyleBackColor = true;
			// 
			// rad_S12
			// 
			this->rad_S12->AutoSize = true;
			this->rad_S12->Location = System::Drawing::Point(65, 19);
			this->rad_S12->Name = L"rad_S12";
			this->rad_S12->Size = System::Drawing::Size(44, 17);
			this->rad_S12->TabIndex = 5;
			this->rad_S12->Text = L"S12";
			this->rad_S12->UseVisualStyleBackColor = true;
			// 
			// ListBox_TraceType
			// 
			this->ListBox_TraceType->FormattingEnabled = true;
			this->ListBox_TraceType->Items->AddRange(gcnew cli::array< System::Object^  >(17) {
				L"Magnitude Logarithmic", L"Magnitude Linear",
					L"Real", L"Imaginary", L"Group Delay", L"SWR", L"Phase", L"Unwrapped Phase", L"P Phase", L"S Linear", L"S Logarithmic", L"S Complex",
					L"Smith", L"S Admittance", L"P Linear", L"P Lograithmic", L"Polar"
			});
			this->ListBox_TraceType->Location = System::Drawing::Point(149, 12);
			this->ListBox_TraceType->Name = L"ListBox_TraceType";
			this->ListBox_TraceType->Size = System::Drawing::Size(131, 108);
			this->ListBox_TraceType->TabIndex = 32;
			// 
			// btn_OK
			// 
			this->btn_OK->Location = System::Drawing::Point(12, 126);
			this->btn_OK->Name = L"btn_OK";
			this->btn_OK->Size = System::Drawing::Size(131, 23);
			this->btn_OK->TabIndex = 34;
			this->btn_OK->Text = L"OK";
			this->btn_OK->UseVisualStyleBackColor = true;
			this->btn_OK->Click += gcnew System::EventHandler(this, &TraceControlEdit::btn_OK_Click);
			// 
			// btn_Cancel
			// 
			this->btn_Cancel->Location = System::Drawing::Point(149, 125);
			this->btn_Cancel->Name = L"btn_Cancel";
			this->btn_Cancel->Size = System::Drawing::Size(131, 23);
			this->btn_Cancel->TabIndex = 35;
			this->btn_Cancel->Text = L"Cancel";
			this->btn_Cancel->UseVisualStyleBackColor = true;
			this->btn_Cancel->Click += gcnew System::EventHandler(this, &TraceControlEdit::btn_Cancel_Click);
			// 
			// TraceControlEdit
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(287, 155);
			this->Controls->Add(this->btn_Cancel);
			this->Controls->Add(this->btn_OK);
			this->Controls->Add(this->group_Trace_SParam);
			this->Controls->Add(this->ListBox_TraceType);
			this->Controls->Add(this->lbl_TraceNumber);
			this->Controls->Add(this->chx_EnableTrace);
			this->Name = L"TraceControlEdit";
			this->Text = L"TraceControlEdit";
			this->group_Trace_SParam->ResumeLayout(false);
			this->group_Trace_SParam->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	//Address are being passed in
	public: System::Void set_memory_address(int* trEnable, int* trType, int* trSParam) {
		address_traceEnable = reinterpret_cast<int*>(trEnable);
		address_traceType = reinterpret_cast<int*>(trType);
		address_traceSParam = reinterpret_cast<int*>(trSParam);
	}


	private: System::Void btn_OK_Click(System::Object^  sender, System::EventArgs^  e) {
		int tempSparam;
		if (rad_S11->Checked) {
			*address_traceSParam = 1;
		}
		else if (rad_S12->Checked) {
			*address_traceSParam = 2;

		}
		else if (rad_S21->Checked) {
			*address_traceSParam = 3;

		}
		else if (rad_S22->Checked) {
			*address_traceSParam = 4;

		}
		
		*address_traceType = ListBox_TraceType->SelectedIndex;
		*address_traceEnable = chx_EnableTrace->Checked;

		this->Hide();//Hide trace control window
		mainform->Show();
	}
	private: System::Void btn_Cancel_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Hide();//Hide trace control window
		mainform->Show();
	}
};
}
