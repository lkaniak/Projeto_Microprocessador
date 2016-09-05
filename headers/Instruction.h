/* 
 * File:   Instruction.h
 * Author: Rafael Teixeira
 *
 * Created on September 3, 2016, 9:51 AM
 */

#include <string>

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

class Instruction {
private:
    const std::string name;
    const std::string opcode;
    const int num_operators;

public:
    Instruction(std::string name, std::string opcode, int num_operators);
    std::string get_name() const;
    std::string get_opcode() const;
    int get_num_operators() const;

};

#endif /* INSTRUCTION_H */

