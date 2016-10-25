#pragma once
#include <string>
#include <vector>

#include "Instruction.h"

class QUEUE
{
private:
	std::vector<Instruction> instructions;
	int size;
	int max;

public:
	QUEUE();
	QUEUE(int max_size);
	~QUEUE();

	bool is_full();
	bool is_empty();
	void load(Instruction Instr);
	void fill_queue();
};
