#pragma once
#include <string>
#include <vector>

#include "Instruction.h"

class QUEUE
{
private:
	std::vector<std::string> instructions;
	int size;
	int max;

public:
	QUEUE();
	QUEUE(int max_size);
	~QUEUE();

	bool is_full();
	bool is_empty();
	void load(std::string Instr);
	std::string get_instruction();	//FIFO
	void fill();
	void clear();
};
