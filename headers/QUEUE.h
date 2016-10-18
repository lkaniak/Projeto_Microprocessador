#pragma once
#include <string>
#include <vector>

#include "Instruction.h"

class QUEUE
{
private:
	std::vector<Instruction> instructions;

public:
	QUEUE();
	~QUEUE();

	std::string load();
};
