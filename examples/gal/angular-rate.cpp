#include <iostream>
#include <string>

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_handler.hpp"

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

namespace OxTS
{
	void sleep(int sleepMs)
	{
#ifdef __linux__
		usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef _WIN32
		Sleep(sleepMs);    // Sleep takes sleep time in ms.
#endif
	}
} // OxTS

enum class OUTPUT_TYPE
{
	UDP = 0,
	CSV = 1
};

int main(int argc, char* argv[])
{
	int num_packets = 30; // Total number of packets to send
	std::string unit_ip = "192.168.25.22"; // Unit to send GAD to
	std::string file_out = "out.gad";    // File to send GAD to
	OUTPUT_TYPE output_type = OUTPUT_TYPE::CSV;   // Set output to UDP or CSV

	//Get from user input if provided
	if (argc > 1)
	{
		unit_ip = argv[1];
	}

	if (argc > 2)
	{
		num_packets = std::stoi(argv[2]);
	}

	if (argc > 3)
	{
		if (!strcmp(argv[3], "csv"))
		{
			output_type = OUTPUT_TYPE::CSV;
		}
	}

	if (argc > 4)
	{
		file_out = argv[4];
	}


	//============================================================================
	// Construct an instance of the angular rate aiding class with stream ID 132.
	OxTS::GadAngularRate gh = OxTS::GadAngularRate(132);
	// Set the angular rate measurement
	gh.SetAngularRate(0.0, 0.0, 0.0);
	// Set the estimated variance on this angular rate measurement
	gh.SetAngularRateVar(0.1);
	// Set the time mode to Void
	gh.SetTimeVoid();
	// Set the aiding source -> IMU frame alignment with the frames aligned.
	gh.SetAidingAlignmentFixed(0.0,0.0,0.0);
	// Set the variance on the alignment to 0.1 deg^2 in HPR.
	gh.SetAidingAlignmentVar(0.1, 0.1, 0.1);
	//============================================================================
	// Initialise the handler
	OxTS::GadHandler handler = OxTS::GadHandler();

	// This switch case sets up the GadHandler to either output binary to UDP or 
	// CSV to file.
	switch (output_type)
	{
	case OUTPUT_TYPE::UDP:
		handler.SetEncoderToBin();
		handler.SetOutputModeToUdp(unit_ip);
		break;
	case OUTPUT_TYPE::CSV:
		handler.SetEncoderToCsv();
		handler.SetOutputModeToFile(file_out);
		break;
	default:
		std::cout << "Output type not known." << std::endl;
		break;
	}

	//============================================================================
	for (int i = 0; i < num_packets; ++i)
	{
		handler.SendPacket(gh);

		if (i % 10 == 0)
			std::cout << i << " packets sent" << std::endl;

		OxTS::sleep(100);
	}

	return 0;
}