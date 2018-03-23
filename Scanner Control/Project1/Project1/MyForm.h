#pragma once

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
			//TODO: Add the constructor code here
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
	private: System::Windows::Forms::Label^  Title_label;
	private: System::Windows::Forms::Label^  numRows_label;
	private: System::Windows::Forms::Label^  numCols_label;
	protected:



	private: System::Windows::Forms::TextBox^  NumRows;
	private: System::Windows::Forms::TextBox^  NumCols;
	private: System::Windows::Forms::GroupBox^  customScan_box;


	private: System::Windows::Forms::TextBox^  lastColPos_in;
	private: System::Windows::Forms::TextBox^  firstColPos_in;
	private: System::Windows::Forms::TextBox^  lastRowPos_in;
	private: System::Windows::Forms::TextBox^  firstRowPos_in;
	private: System::Windows::Forms::Label^  lastCol_label;
	private: System::Windows::Forms::Label^  firstCol_label;
	private: System::Windows::Forms::Label^  lastRow_label;
	private: System::Windows::Forms::Label^  firstRow_Label;
	private: System::Windows::Forms::Button^  executeScan_but;

	private: System::Windows::Forms::CheckBox^  customScan_Enable;
	private: System::Windows::Forms::Button^  createGrid_but;
	private: System::Windows::Forms::Button^  sendCmd_but;
	private: System::Windows::Forms::TextBox^  serialCmd;
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
			this->Title_label = (gcnew System::Windows::Forms::Label());
			this->numRows_label = (gcnew System::Windows::Forms::Label());
			this->numCols_label = (gcnew System::Windows::Forms::Label());
			this->NumRows = (gcnew System::Windows::Forms::TextBox());
			this->NumCols = (gcnew System::Windows::Forms::TextBox());
			this->customScan_box = (gcnew System::Windows::Forms::GroupBox());
			this->customScan_Enable = (gcnew System::Windows::Forms::CheckBox());
			this->lastColPos_in = (gcnew System::Windows::Forms::TextBox());
			this->firstColPos_in = (gcnew System::Windows::Forms::TextBox());
			this->lastRowPos_in = (gcnew System::Windows::Forms::TextBox());
			this->firstRowPos_in = (gcnew System::Windows::Forms::TextBox());
			this->lastCol_label = (gcnew System::Windows::Forms::Label());
			this->firstCol_label = (gcnew System::Windows::Forms::Label());
			this->lastRow_label = (gcnew System::Windows::Forms::Label());
			this->firstRow_Label = (gcnew System::Windows::Forms::Label());
			this->executeScan_but = (gcnew System::Windows::Forms::Button());
			this->createGrid_but = (gcnew System::Windows::Forms::Button());
			this->sendCmd_but = (gcnew System::Windows::Forms::Button());
			this->serialCmd = (gcnew System::Windows::Forms::TextBox());
			this->customScan_box->SuspendLayout();
			this->SuspendLayout();
			// 
			// Title_label
			// 
			this->Title_label->AutoSize = true;
			this->Title_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Title_label->Location = System::Drawing::Point(88, 9);
			this->Title_label->Name = L"Title_label";
			this->Title_label->Size = System::Drawing::Size(201, 29);
			this->Title_label->TabIndex = 0;
			this->Title_label->Text = L"Scanner Control";
			this->Title_label->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// numRows_label
			// 
			this->numRows_label->AutoSize = true;
			this->numRows_label->Location = System::Drawing::Point(101, 58);
			this->numRows_label->Name = L"numRows_label";
			this->numRows_label->Size = System::Drawing::Size(56, 13);
			this->numRows_label->TabIndex = 1;
			this->numRows_label->Text = L"# of Rows";
			this->numRows_label->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// numCols_label
			// 
			this->numCols_label->AutoSize = true;
			this->numCols_label->Location = System::Drawing::Point(101, 84);
			this->numCols_label->Name = L"numCols_label";
			this->numCols_label->Size = System::Drawing::Size(69, 13);
			this->numCols_label->TabIndex = 2;
			this->numCols_label->Text = L"# of Columns";
			// 
			// NumRows
			// 
			this->NumRows->Location = System::Drawing::Point(176, 55);
			this->NumRows->Name = L"NumRows";
			this->NumRows->Size = System::Drawing::Size(100, 20);
			this->NumRows->TabIndex = 3;
			// 
			// NumCols
			// 
			this->NumCols->Location = System::Drawing::Point(176, 81);
			this->NumCols->Name = L"NumCols";
			this->NumCols->Size = System::Drawing::Size(100, 20);
			this->NumCols->TabIndex = 4;
			// 
			// customScan_box
			// 
			this->customScan_box->Controls->Add(this->customScan_Enable);
			this->customScan_box->Controls->Add(this->lastColPos_in);
			this->customScan_box->Controls->Add(this->firstColPos_in);
			this->customScan_box->Controls->Add(this->lastRowPos_in);
			this->customScan_box->Controls->Add(this->firstRowPos_in);
			this->customScan_box->Controls->Add(this->lastCol_label);
			this->customScan_box->Controls->Add(this->firstCol_label);
			this->customScan_box->Controls->Add(this->lastRow_label);
			this->customScan_box->Controls->Add(this->firstRow_Label);
			this->customScan_box->Location = System::Drawing::Point(33, 122);
			this->customScan_box->Name = L"customScan_box";
			this->customScan_box->Size = System::Drawing::Size(295, 161);
			this->customScan_box->TabIndex = 5;
			this->customScan_box->TabStop = false;
			this->customScan_box->Text = L"Custom Scan";
			// 
			// customScan_Enable
			// 
			this->customScan_Enable->AutoSize = true;
			this->customScan_Enable->Location = System::Drawing::Point(11, 20);
			this->customScan_Enable->Name = L"customScan_Enable";
			this->customScan_Enable->Size = System::Drawing::Size(59, 17);
			this->customScan_Enable->TabIndex = 8;
			this->customScan_Enable->Text = L"Enable";
			this->customScan_Enable->UseVisualStyleBackColor = true;
			this->customScan_Enable->CheckedChanged += gcnew System::EventHandler(this, &MyForm::customScan_Enable_CheckedChanged);
			// 
			// lastColPos_in
			// 
			this->lastColPos_in->Enabled = false;
			this->lastColPos_in->Location = System::Drawing::Point(179, 132);
			this->lastColPos_in->Name = L"lastColPos_in";
			this->lastColPos_in->Size = System::Drawing::Size(100, 20);
			this->lastColPos_in->TabIndex = 7;
			// 
			// firstColPos_in
			// 
			this->firstColPos_in->Enabled = false;
			this->firstColPos_in->Location = System::Drawing::Point(179, 106);
			this->firstColPos_in->Name = L"firstColPos_in";
			this->firstColPos_in->Size = System::Drawing::Size(100, 20);
			this->firstColPos_in->TabIndex = 6;
			// 
			// lastRowPos_in
			// 
			this->lastRowPos_in->Enabled = false;
			this->lastRowPos_in->Location = System::Drawing::Point(179, 73);
			this->lastRowPos_in->Name = L"lastRowPos_in";
			this->lastRowPos_in->Size = System::Drawing::Size(100, 20);
			this->lastRowPos_in->TabIndex = 5;
			// 
			// firstRowPos_in
			// 
			this->firstRowPos_in->Enabled = false;
			this->firstRowPos_in->Location = System::Drawing::Point(179, 47);
			this->firstRowPos_in->Name = L"firstRowPos_in";
			this->firstRowPos_in->Size = System::Drawing::Size(100, 20);
			this->firstRowPos_in->TabIndex = 4;
			this->firstRowPos_in->TextChanged += gcnew System::EventHandler(this, &MyForm::firstRowPos_in_TextChanged);
			// 
			// lastCol_label
			// 
			this->lastCol_label->AutoSize = true;
			this->lastCol_label->Location = System::Drawing::Point(7, 135);
			this->lastCol_label->Name = L"lastCol_label";
			this->lastCol_label->Size = System::Drawing::Size(158, 13);
			this->lastCol_label->TabIndex = 3;
			this->lastCol_label->Text = L"Position of Last Column (Inches)";
			// 
			// firstCol_label
			// 
			this->firstCol_label->AutoSize = true;
			this->firstCol_label->Location = System::Drawing::Point(7, 109);
			this->firstCol_label->Name = L"firstCol_label";
			this->firstCol_label->Size = System::Drawing::Size(157, 13);
			this->firstCol_label->TabIndex = 2;
			this->firstCol_label->Text = L"Position of First Column (Inches)";
			// 
			// lastRow_label
			// 
			this->lastRow_label->AutoSize = true;
			this->lastRow_label->Location = System::Drawing::Point(7, 76);
			this->lastRow_label->Name = L"lastRow_label";
			this->lastRow_label->Size = System::Drawing::Size(145, 13);
			this->lastRow_label->TabIndex = 1;
			this->lastRow_label->Text = L"Position of Last Row (Inches)";
			// 
			// firstRow_Label
			// 
			this->firstRow_Label->AutoSize = true;
			this->firstRow_Label->Location = System::Drawing::Point(8, 50);
			this->firstRow_Label->Name = L"firstRow_Label";
			this->firstRow_Label->Size = System::Drawing::Size(144, 13);
			this->firstRow_Label->TabIndex = 0;
			this->firstRow_Label->Text = L"Position of First Row (Inches)";
			// 
			// executeScan_but
			// 
			this->executeScan_but->Location = System::Drawing::Point(212, 289);
			this->executeScan_but->Name = L"executeScan_but";
			this->executeScan_but->Size = System::Drawing::Size(75, 23);
			this->executeScan_but->TabIndex = 6;
			this->executeScan_but->Text = L"Go";
			this->executeScan_but->UseVisualStyleBackColor = true;
			// 
			// createGrid_but
			// 
			this->createGrid_but->Location = System::Drawing::Point(104, 289);
			this->createGrid_but->Name = L"createGrid_but";
			this->createGrid_but->Size = System::Drawing::Size(75, 23);
			this->createGrid_but->TabIndex = 7;
			this->createGrid_but->Text = L"Create Grid";
			this->createGrid_but->UseVisualStyleBackColor = true;
			// 
			// sendCmd_but
			// 
			this->sendCmd_but->Location = System::Drawing::Point(376, 103);
			this->sendCmd_but->Name = L"sendCmd_but";
			this->sendCmd_but->Size = System::Drawing::Size(100, 23);
			this->sendCmd_but->TabIndex = 8;
			this->sendCmd_but->Text = L"Send Command";
			this->sendCmd_but->UseVisualStyleBackColor = true;
			this->sendCmd_but->Click += gcnew System::EventHandler(this, &MyForm::sendCmd_but_Click);
			// 
			// serialCmd
			// 
			this->serialCmd->Location = System::Drawing::Point(376, 77);
			this->serialCmd->Name = L"serialCmd";
			this->serialCmd->Size = System::Drawing::Size(100, 20);
			this->serialCmd->TabIndex = 9;
			this->serialCmd->TextChanged += gcnew System::EventHandler(this, &MyForm::serialCmd_TextChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(533, 324);
			this->Controls->Add(this->serialCmd);
			this->Controls->Add(this->sendCmd_but);
			this->Controls->Add(this->createGrid_but);
			this->Controls->Add(this->executeScan_but);
			this->Controls->Add(this->customScan_box);
			this->Controls->Add(this->NumCols);
			this->Controls->Add(this->NumRows);
			this->Controls->Add(this->numCols_label);
			this->Controls->Add(this->numRows_label);
			this->Controls->Add(this->Title_label);
			this->Name = L"MyForm";
			this->Text = L"Scanner GUI";
			this->customScan_box->ResumeLayout(false);
			this->customScan_box->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void customScan_Enable_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (customScan_Enable->Checked == true) {
			firstRowPos_in->Enabled == true;
			lastRowPos_in->Enabled == true;
			firstColPos_in->Enabled == true;
			lastColPos_in->Enabled == true;
		}

		if (customScan_Enable->Checked == false) {
			firstRowPos_in->Enabled == false;
			lastRowPos_in->Enabled == false;
			firstColPos_in->Enabled == false;
			lastColPos_in->Enabled == false;
		}
	}
private: System::Void firstRowPos_in_TextChanged(System::Object^  sender, System::EventArgs^  e) {

}
private: System::Void serialCmd_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	
}
private: System::Void sendCmd_but_Click(System::Object^  sender, System::EventArgs^  e) {
	String ^ cmd = serialCmd->Text;
}
};
}
