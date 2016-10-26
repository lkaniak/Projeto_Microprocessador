#pragma once
#include <string>
#include <vector>

#include "Instruction.h"

class BIU;

class QUEUE
{
private:
	std::vector<std::string> instructions;
	int size;
	int max;


	bool is_full();
	bool is_empty();
	void load(std::string Instr);
	void fill();
public:
	QUEUE();
	QUEUE(int max_size);
	~QUEUE();

	std::string get_instruction();	//FIFO
	void clear();
};
