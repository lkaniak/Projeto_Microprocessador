#include "..\headers\MEMORY.h"

#define file "build/temp.obj"


MEMORY::MEMORY()
{
	auto line = new char[10];
	std::ifstream binary_file;
	binary_file.open(file);

	while (!binary_file.eof())
	{
		binary_file.read(line, 4);
		std::string instr(line, 4);

		if (instr.compare("0001") != 0)
		{
			binary_file.read(line, 4);
			instr += line;
			instr[8] = '\0';

			this->memory.push_back(instr);
		}
		else
		{
			binary_file.read(line, 10);
			instr += line;
			instr[14] = '\0';

			this->memory.push_back(instr);
		}
	}
}

MEMORY::~MEMORY()
{
}

std::string MEMORY::load_from_address(std::string add)
{
	return *std::find(this->memory.cbegin(), this->memory.cend(), add);
}
