#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

namespace DEBUG
{
	class Debug
	{
	public:
		static void PrintToLog(const std::string& message);
	};
}