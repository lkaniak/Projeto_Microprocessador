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

		// Se forem instrucoes que nao aceitam imediato
		if (instr.compare("0001") != 0 && instr.find("101") != 0)
		{
			binary_file->read(line, 4);
			instr += line;
			// Se for unico jmp que nao tem como distinguir com 4 bits
			if (instr.find("110000") != 0)
                instr.resize(8);
                //instr[8] = '\0';
			else
			{
				binary_file->read(line, 6);
                instr.resize(14);
				instr[14] = '\0';
			}

			this->memory.push_back(instr);
		}
		// Instrucoes que aceitam imediato
		else if (instr.compare("") != 0)
		{
			binary_file->read(line, 10);
			instr += line;
            instr.resize(14);
            //instr[14] = '\0';

			this->memory.push_back(instr);
		}
	}
}

const int MEMORY::get_size_limit()
{
    return this->memory.size();
}

std::vector<std::string> *MEMORY::get_memory()
{
    return &this->memory;
}
