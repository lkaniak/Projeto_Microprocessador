#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

class MEMORY
{
private:
	std::vector<std::string> memory;
public:
	MEMORY();
	~MEMORY();

	bool save_to_address(std::string add);
	std::string load_from_address(std::string add);
};

