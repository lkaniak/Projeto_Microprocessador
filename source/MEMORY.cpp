#include "MEMORY.h"
#include "..\headers\MEMORY.h"



MEMORY::MEMORY()
{
}


MEMORY::~MEMORY()
{
}

std::string MEMORY::load_from_address(std::string add)
{
	return *std::find(this->memory.cbegin(), this->memory.cend(), add);
}
