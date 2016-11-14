#include "..\headers\MEMORY.h"

MEMORY::MEMORY()
{
	this->size_limit = 40;
}

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

cache::cache()
{
	this->size_limit = 4;
	this->tag = new int[4];
	this->memory = new std::string[4];
}

cache::cache(int size)
{
	this->size_limit = size;
	this->tag = new int[size];
	this->memory = new std::string[size];
}

bool cache::cache_hit(int address)
{
	for (int i = 0; i < this->size_limit; i++)
	{
		if (address == this->tag[i])
		{
			return true;
		}
	}
	return false;
}

int cache::mapping(int address)
{
	return address % this->size_limit;
}

void cache::save_to_cache(int address)
{
	std::vector<std::string>* MP = get_memory();
	this->memory[mapping(address)] = MP->at(address);
	this->tag[mapping(address)] = address;
}

std::string cache::load_from_cache(int address)
{
	if (cache_hit(address))
	{
		return this->memory[mapping(address)];
	}
	else
	{
		return load_from_address(address);
	}
}

std::pair<int*, std::string*> cache::get_cache()
{
	std::pair<int*, std::string*> cache;
	cache.first = this->tag;
	cache.second = this->memory;
	return cache;
}

