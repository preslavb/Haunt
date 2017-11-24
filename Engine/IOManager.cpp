#include "IOManager.h"

bool IOManager::ReadFileToBuffer(std::string t_filepath, std::vector<char>& t_buffer)
{
	std::ifstream file(t_filepath, std::ios::binary);
	if (file.fail())
	{
		perror(t_filepath.c_str());
		return false;
	}

	file.seekg(0, std::ios::end);

	int fileSize = file.tellg();

	file.seekg(0, std::ios::beg);

	fileSize -= file.tellg();

	t_buffer.resize(fileSize);
	file.read(&(t_buffer[0]), fileSize);
	file.close();

	return true;
}
