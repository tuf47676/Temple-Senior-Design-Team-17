#pragma once
#include <cmath>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <Windows.h>


namespace Design_Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CurrenntlyScanning
	/// </summary>
	public ref class CurrentlyScanning : public System::Windows::Forms::Form
	{
	public:
		CurrentlyScanning(System::Windows::Forms::Form ^ tempMainForm, int temp_numbox_X, int temp_numbox_Y)
		{
			InitializeComponent();
			
			numbox_X = temp_numbox_X;
			numbox_Y = temp_numbox_Y;
			totalScanPoints = numbox_X * numbox_Y;
			lbl_FractionComplete->Text = "Completion: 0/" + totalScanPoints;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CurrentlyScanning()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btn_AbortScan;
	protected:
	private: System::Windows::Forms::Label^  lbl_FractionComplete;

	private: System::ComponentModel::Container ^components;
	private: int numbox_X, numbox_Y, totalScanPoints, currentScanPoint;


	public: System::Void updateVisuals(int x, int y, int currentTime) {
		int currentScanPoint = (y*numbox_Y) + x;
		lbl_FractionComplete->Text = "Completion: " + currentScanPoint + "/" + totalScanPoints + "\nX Position: " + x + "\nY Position: " + y;
		Refresh();
	}


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btn_AbortScan = (gcnew System::Windows::Forms::Button());
			this->lbl_FractionComplete = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// btn_AbortScan
			// 
			this->btn_AbortScan->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_AbortScan->Location = System::Drawing::Point(351, 138);
			this->btn_AbortScan->Name = L"btn_AbortScan";
			this->btn_AbortScan->Size = System::Drawing::Size(197, 67);
			this->btn_AbortScan->TabIndex = 0;
			this->btn_AbortScan->Text = L"Abort Scan";
			this->btn_AbortScan->UseVisualStyleBackColor = true;
			this->btn_AbortScan->Click += gcnew System::EventHandler(this, &CurrentlyScanning::btn_AbortScan_Click);
			// 
			// lbl_FractionComplete
			// 
			this->lbl_FractionComplete->AutoSize = true;
			this->lbl_FractionComplete->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lbl_FractionComplete->Location = System::Drawing::Point(235, 84);
			this->lbl_FractionComplete->Name = L"lbl_FractionComplete";
			this->lbl_FractionComplete->Size = System::Drawing::Size(70, 25);
			this->lbl_FractionComplete->TabIndex = 1;
			this->lbl_FractionComplete->Text = L"label1";
			// 
			// CurrentlyScanning
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(560, 217);
			this->Controls->Add(this->lbl_FractionComplete);
			this->Controls->Add(this->btn_AbortScan);
			this->Name = L"CurrentlyScanning";
			this->Text = L"CurrentlyScanning";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btn_AbortScan_Click(System::Object^  sender, System::EventArgs^  e) {

		//doing something
	}
	};


}
