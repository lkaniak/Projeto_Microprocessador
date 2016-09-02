/* 
 * File:   parser.h
 * Author: Rafael Teixeira
 *
 * Created on August 28, 2016, 10:19 AM
 */

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <exception>
#include <bitset>

#include <iostream>

using vecPair_StrInt = std::vector<std::pair<std::string, int>>;
using vecPair_StrStr = std::vector<std::pair<std::string, std::string>>;
using pair_StrPair_IntInt = std::pair<std::string, std::pair<int, int>>;
using pair_StrPair_StrInt = std::pair<std::string, std::pair<std::string, int>>;

class Parser {
private:
    static Parser *instancia;
    // Vetor de instrucoes existentes <Nome_Instr <OpCode, Num_Operadores>>
    std::vector<pair_StrPair_StrInt> instructions;
    // Vetor de registradores <Nome_regist, OpCode>
    vecPair_StrStr operators;
    // Vetor de instrucoes <OP, <R1, <R2, <Linha, Pos_Memoria>>>>
    std::vector<std::pair<std::string, std::pair<std::string, pair_StrPair_IntInt>>> instruction_table;
    // Vetor de constantes <Nome, Valor/Endereco>
    vecPair_StrInt symbol_table;
    // Vetor de OpCodes
    std::string binary_code;
    
    Parser();    
    
    void load_instructions();
    void load_operators();
    
    std::vector<std::string> split_line(const std::string &text, char sep);
    std::string dec_to_bin(int);
	std::string get_instruction_opcode(std::string op);
	std::string get_symbol_opcode(std::string op);
    
    bool is_operator(std::string op);
    bool is_valid_symbol(std::string si, int num_op);
    
    void add_instruction(std::string si, std::string op1, std::string op2, int line);
    void add_symbol(std::string si, int val);

	bool check_sintax(std::ifstream &source_file);
    
public:
    static Parser *get_instancia();
    std::string make_object(std::ifstream &source_file);
    
    ~Parser();
};

#endif /* PARSER_H */

