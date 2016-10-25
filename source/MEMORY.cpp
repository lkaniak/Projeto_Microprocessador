#include "..\headers\MEMORY.h"

MEMORY::MEMORY(int size)
	:size_limit(size)
{
}

MEMORY::~MEMORY()
{
}

std::string MEMORY::load_from_address(int add)
{
	return memory[add];
}

void MEMORY::load_file(std::ifstream *binary_file)
{
	auto line = new char[10];

	while (!binary_file->eof())
	{
		binary_file->read(line, 4);
		std::string instr(line, 4);

		if (instr.compare("0001") != 0)
		{
			binary_file->read(line, 4);
			instr += line;
			instr[8] = '\0';

			this->memory.push_back(instr);
		}
		else
		{
			binary_file->read(line, 10);
			instr += line;
			instr[14] = '\0';

			this->memory.push_back(instr);
		}
	}
}
