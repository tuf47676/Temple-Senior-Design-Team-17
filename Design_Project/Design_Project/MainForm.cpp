#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visatype.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visaext.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visaext.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visa.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>
#pragma warning(disable:4996)
#include "MainForm.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	//testing

	std::cout << " _______ _______ _______ __   __                                     \n";
	std::cout << "|       |       |   _   |  |_|  |                                    \n";
	std::cout << "|_     _|    ___|  |_|  |       |                                    \n";
	std::cout << "  |   | |   |___|       |       |                                    \n";
	std::cout << "  |   | |    ___|       |       |                                    \n";
	std::cout << "  |   | |   |___|   _   | ||_|| |                                    \n";
	std::cout << "  |___| |_______|__| |__|_|   |_|                                    \n";
	std::cout << " _______ _______ ______   _______                                    \n";
	std::cout << "|       |       |    _ | |       |                                   \n";
	std::cout << "|____   |    ___|   | || |   _   |                                   \n";
	std::cout << " ____|  |   |___|   |_||_|  | |  |                                   \n";
	std::cout << "| ______|    ___|    __  |  |_|  |                                   \n";
	std::cout << "| |_____|   |___|   |  | |       |                                   \n";
	std::cout << "|_______|_______|___|  |_|_______|                                   \n";
	std::cout << " ___ __   __ _______ _______ ______  _______ __    _ _______ _______ \n";
	std::cout << "|   |  |_|  |       |       |      ||   _   |  |  | |       |       |\n";
	std::cout << "|   |       |    _  |    ___|  _    |  |_|  |   |_| |       |    ___|\n";
	std::cout << "|   |       |   |_| |   |___| | |   |       |       |       |   |___ \n";
	std::cout << "|   |       |    ___|    ___| |_|   |       |  _    |      _|    ___|\n";
	std::cout << "|   | ||_|| |   |   |   |___|       |   _   | | |   |     |_|   |___ \n";
	std::cout << "|___|_|   |_|___|   |_______|______||__| |__|_|  |__|_______|_______|\n";
	std::cout << "\nApplication Start Time: ";

	std::time_t AppStart = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::ctime(&AppStart);
	std::cout << "\n\n";

	//testint
	//std::cout << "Team Zero Impedance";







	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Design_Project::MainForm form;

	Application::Run(%form);




}