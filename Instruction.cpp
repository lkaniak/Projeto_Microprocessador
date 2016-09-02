#include "Instruction.h"

Instruction::Instruction(std::string name, std::string op_code, Instruction * operator_1, Instruction * operator_2, int line, int memory_pos)
	: name(name), op_code(op_code), operator_1(operator_1), operator_2(operator_2), line(line), memory_pos(memory_pos)
{
}


Instruction::~Instruction()
{
	delete this->operator_1;
	this->operator_1 = nullptr;
	delete this->operator_2;
	this->operator_2 = nullptr;
}
