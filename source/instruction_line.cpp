#include "./../headers/instruction_line.h"

instruction_line::instruction_line(const std::string name, const Instruction *operator_1, const Instruction *operator_2, const int line, const int memory_pos)
    : name(name), 
      operator_1(operator_1), 
      operator_2(operator_2),
      num(-1),
      line(line), 
      memory_pos(memory_pos)
{
}

instruction_line::instruction_line(const std::string name, const Instruction *operator_1, const int num, const int line, const int memory_pos)
    : name(name), 
      operator_1(operator_1), 
      operator_2(nullptr),
      num(num), 
      line(line), 
      memory_pos(memory_pos)
{
}


instruction_line::~instruction_line()
{
    /*
    delete this->operator_1;
    this->operator_1 = nullptr;
    delete this->operator_2;
    this->operator_2 = nullptr;*/
}

void instruction_line::execute()
{
    
}

std::string instruction_line::get_name()
{
    return this->name;
}

std::string instruction_line::get_operator_1() const
{
    if (this->operator_1 != nullptr)
    {
        return this->operator_1->get_name();
    }
    return "";
}

std::string instruction_line::get_operator_2() const
{
    if (this->operator_2 != nullptr)
    {
        return this->operator_2->get_name();
    }
    else
    {
        return std::to_string(this->num);
    }
}
