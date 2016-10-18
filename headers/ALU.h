#pragma once
#include "Instruction.h"

class ALU
{
public:
	ALU();
	~ALU();

	void execute(Instruction *instruction);
};

