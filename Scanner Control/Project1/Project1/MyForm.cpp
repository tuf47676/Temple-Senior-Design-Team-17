#include "MyForm.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <chrono>
#include <ctime>
#include "Scanner.h"
#include "rs232.h"
#include <libserialport.h>
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visatype.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visaext.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visaext.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\agvisa\include\visa.h"
#pragma warning(disable:4996)

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {

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
	std::time_t AppStart = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::ctime(&AppStart);
	std::cout << "\n\n";

	//code for testing commands
	//
	//char cmd[64];
	int status;
	int num_stopbits = 1;
	char reply[64];
	char *replybuf = (char*)&reply[0];
	int baudrate = 9600;
	const char mode[64] = "8N1";
	int scan = 1;
	char port_name[64]  = "COM1";
	sp_return out, bytes_sent, bytes_rec;
	struct sp_port* comport;
	unsigned int timeout = 1000;

	sp_get_port_by_name(port_name, &comport); //Obtained Port Name
	sp_open(comport, SP_MODE_READ_WRITE); //Open Port
	sp_set_baudrate(comport, baudrate); //Set Buad Rate
	sp_set_bits(comport, 8); //set data bits to 8 for serial port
	sp_set_parity(comport, SP_PARITY_NONE); //set parity to none for serial port
	sp_set_stopbits(comport, num_stopbits); //set number of stop bits to 1
	sp_set_flowcontrol(comport, SP_FLOWCONTROL_NONE);

	while (scan == 1) {

		sp_flush(comport, SP_BUF_BOTH); //flush output and input buffers
		puts("");

		const char cmd[64] = "1FR0x0D";

		//printf("Please Enter a Serial Command: ");
		//scanf("%s", &cmd);

		sp_blocking_write(comport, cmd, strlen(cmd), timeout); //send command
		sp_drain(comport); //wait until all data has been transmitted

		out = sp_blocking_read(comport, reply, strlen(reply), timeout);
		printf("Reply: %s", reply);
		puts("");


		//Scan_Init();
		//set_home(0);
		scan = 0;
	}

	out = sp_close(comport);
	if (out == 0) {
		printf("Comport Closed");
	}
	else printf("Failure");
	

	//while (scan == 1) {
	//	//reset data
	//	//
	//	Sleep(250);
	//	RS232_flushRXTX(0);

	//	//prompt for user input
	//	//
	//	printf("Please enter a serial command: ");
	//	scanf("%s", &cmd);
	//	unsigned char *cmdbuffer = (unsigned char*)&cmd[0];

	//	//send command
	//	//
	//	RS232_SendBuf(0, cmdbuffer, strlen(cmd));
	//	RS232_PollComport(0, reply, 15);
	//	/*status = RS232_PollComport(0, reply, 15);
	//	if (status < 0) {
	//		exit(0);
	//	}
	//	status = RS232_PollComport(0, reply, 60);
	//	if (status < 0) {
	//		exit(0);
	//	}*/

	//	//loop control
	//	//
	//	printf("Response: %s", reply);
	//	puts("");
	//	printf("Scan again? 1: yes 0: no");
	//	puts("");
	//	scanf("%d", &scan);
	//}

	////close com port
	////
	//RS232_CloseComport(0);

	//show form
	//
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project1::MyForm form;
	Application::Run(%form);
}