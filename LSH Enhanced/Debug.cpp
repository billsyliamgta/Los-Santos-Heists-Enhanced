#include "Debug.h"

void DEBUG::Debug::PrintToLog(const std::string& message)
{
	std::ofstream file("debug.log", std::ios::app);

	if (!file)
	{
		std::cerr << "ERROR: Couldn't open debug file." << std::endl;
		return;
	}
	// Get the current time
	std::time_t currentTime = std::time(nullptr);
	// Convert to local time
	std::tm* localTime = std::localtime(&currentTime);
	file << "["
		+ std::to_string(localTime->tm_hour) + ":"
		+ std::to_string(localTime->tm_min) + ":"
		+ (localTime->tm_sec < 10 ? "0" + std::to_string(localTime->tm_sec) : std::to_string(localTime->tm_sec))
		+ "]: "
		+ message
		<< std::endl;
	file.close();
}