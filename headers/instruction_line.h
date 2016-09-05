#pragma once

#include <iostream>
#include <string>
#include "Instruction.h"

class instruction_line
{
private:
    const std::string name;
    const Instruction *operator_1;
    const Instruction *operator_2;
    const std::string label;
    const int num;
    const int line;
    const int memory_pos;

public:
    instruction_line(const std::string name, const Instruction *operator_1, const Instruction *operator_2, const int line, const int memory_pos);
    instruction_line(const std::string name, const Instruction *operator_1, const std::string label, const int line, const int memory_pos);
    instruction_line(const std::string name, const Instruction *operator_1, const int num, const int line, const int memory_pos);
    instruction_line(const std::string name, const std::string label, const Instruction *operator_2, const int line, const int memory_pos);
    
    ~instruction_line();

    void execute();
    std::string get_name();
    std::string get_operator_1() const;
    std::string get_operator_2() const;
};

