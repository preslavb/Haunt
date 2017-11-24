#pragma once
#include <vector>
#include <fstream>

class IOManager
{
public:
	static bool ReadFileToBuffer(std::string t_filepath, std::vector<char> &t_buffer);
};

