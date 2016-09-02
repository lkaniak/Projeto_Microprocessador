#pragma once

#include <iostream>
class Instruction
{
private:
	const std::string name;
	const std::string op_code;
	const Instruction *operator_1;
	const Instruction *operator_2;
	const int line;
	const int memory_pos;

public:
	Instruction(std::string name, std::string op_code, Instruction *operator_1, Instruction *operator_2, int line, int memory_pos);
	~Instruction();

	void execute();
};

