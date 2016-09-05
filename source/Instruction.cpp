/* 
 * File:   Instruction.cpp
 * Author: Rafael Teixeira
 * 
 * Created on September 3, 2016, 9:51 AM
 */

#include "./../headers/Instruction.h"

Instruction::Instruction(const std::string name, const std::string opcode, const int num_operators)
      : name(name),
        opcode(opcode),
        num_operators(num_operators)
{
}


std::string Instruction::get_name() const
{
    return this->name;
}

std::string Instruction::get_opcode() const
{
    return this->opcode;
}

int Instruction::get_num_operators() const
{
    return this->num_operators;
}