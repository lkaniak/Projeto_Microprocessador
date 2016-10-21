/* 
 * File:   Operator.h
 * Author: Rafael Teixeira
 *
 * Created on September 2, 2016, 6:06 PM
 */

#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "utils.h"
#include "instruction_line.h"
#include "Instruction.h"
#include "Operator.h"
#include "ALU.h"
#include "REGISTER.h"
#include "BUS.h"

class instruction_Set
{
private:
    static instruction_Set *instancia;
        
    // Vetor de instrucoes existentes
    std::vector<Instruction*> instructions;
    // Vetor de registradores
    std::vector<Instruction*> operators;
        
    void load_instructions();
    void load_operators();
        
    // Dois operadores
    void mov(Operator r1, Operator r2); // MOV R1, R2
    void mov(Operator r1, int num); //MOV R1, CONST
    void add(REGISTER *r1, REGISTER *r2);
    void sub(Operator r1, Operator r2);
    void div(Operator r1, Operator r2);
    void mul(Operator r1, Operator r2);
    
    // Um operador
    void cmp(Operator r1);
    void _and(Operator r1);
    void _or(Operator r1);
    void _xor(Operator r1);
    void push(Operator r1);
    void pop(Operator r1);
    void _not(Operator r1);
    void inc(Operator r1);
    void dec(Operator r1);
    void load(Operator r1);
    void store(Operator r1);
    void interrupt(Operator r1);
    void jmp(Operator r1);
    void jg(Operator r1);
    void je(Operator r1);
    void jne(Operator r1);
    void jl(Operator r1);
    void jz(Operator r1);
    void jnz(Operator r1);
    void ja(Operator r1);
    void jb(Operator r1);
    void ret(Operator r1);
    void call(Operator r1);

    // Nenhum operador
    void start();
    void end();

public:
    static instruction_Set *get_instancia();
    instruction_Set();
    ~instruction_Set();

    void execute_instruction(std::string op, REGISTER *r1, REGISTER *r2);
    //void execute_instruction(instruction_line op);
    Instruction *get_operation_info(const std::string name);
	Instruction *get_operation_name(const std::string opcode);
};

#endif /* INSTRUCTION_SET_H */
