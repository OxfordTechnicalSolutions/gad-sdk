#include <iostream>
#include <string>

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_handler.hpp"

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

// This is a basic cross-platform sleep function
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


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout<<"Invalid number of command line arguments, requires: <IP> <number of packets>";
		return 1;
	}

	std::string unit_ip   = argv[1]; // Unit to send GAD to
	int num_packets       = std::stoi(argv[2]); // Number of packets to send.

	// Construct the velocity aiding with stream ID 130.
	OxTS::Gal_Cpp::GadVelocity gv(130);

	// Set the required data
	gv.SetVelNed(0.0,0.0,0.0);
	gv.SetVelNedVar(0.1,0.1,0.1);
	gv.SetTimeVoid();
	gv.SetAidingLeverArmFixed(0.0,0.0,1.0);
	gv.SetAidingLeverArmVar(0.01,0.01,0.01);

	// Initialise the handler
	OxTS::Gal_Cpp::GadHandler gh;
	gh.SetEncoderToBin();
	gh.SetOutputModeToUdp(unit_ip);

	// Send the packets
	for (int i = 0; i < num_packets; ++i)
	{
		gh.SendPacket(gv);
		std::cout << "packet " << i << " sent" << std::endl;
		OxTS::sleep(100);
	}

	return 0;
}
