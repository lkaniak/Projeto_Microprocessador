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
#include "REGISTER.h"
#include "ALU.h"
#include "BUS.h"
#include "EU.h"
#include "BIU.h"

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
    void mov(REGISTER * r1, REGISTER * r2); // MOV R1, R2
    void mov(REGISTER * r1, int num); //MOV R1, CONST
    void add(REGISTER * r1, REGISTER * r2);
    void sub(REGISTER * r1, REGISTER * r2);
    void div(REGISTER * r1, REGISTER * r2);
    void mul(REGISTER * r1, REGISTER * r2);
    
    // Um operador
    void cmp(REGISTER * r1);
    void _and(REGISTER * r1);
    void _or(REGISTER * r1);
    void _xor(REGISTER * r1);
    void push(REGISTER * r1);
    void pop(REGISTER * r1);
    void _not(REGISTER * r1);
    void inc(REGISTER * r1);
    void dec(REGISTER * r1);
    void load(REGISTER * r1);
    void store(REGISTER * r1);
    void interrupt(REGISTER * r1);
    void jmp(int r1);
    void jg(int r1);
    void je(int r1);
    void jne(int r1);
    void jl(int r1);
    void jz(int r1);
    void jnz(int r1);
    void ja(int r1);
    void jb(int r1);
    void ret(int r1);
    void call(int r1);

    // Nenhum operador
    void start();
    void end();

public:
    static instruction_Set *get_instancia();
    instruction_Set();
    ~instruction_Set();

	void execute_instruction(std::string op, REGISTER * r1, REGISTER * r2);
	void execute_instruction(std::string op, REGISTER * r1, int r2);
	void execute_instruction(std::string op, REGISTER * r1);
	void execute_instruction(std::string op, int r1);
	void execute_instruction(std::string op);
    //void execute_instruction(instruction_line op);
    Instruction *get_operation_info(const std::string name, int num_operators);
	Instruction *get_operation_name(const std::string opcode);
};

#endif /* INSTRUCTION_SET_H */
