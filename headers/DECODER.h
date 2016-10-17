#pragma once
#include <string>
#include "Instruction.h"

class DECODER
{
public:
	DECODER();
	~DECODER();

	Instruction *decode(std::string instruction);
};

