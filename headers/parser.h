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
#include <sys/stat.h>

#include <iostream>

#include "Operator.h"
#include "instruction_line.h"
#include "utils.h"
#include "instruction_Set.h"



using vecPair_StrInt = std::vector<std::pair<std::string, int>>;
using vecPair_StrStr = std::vector<std::pair<std::string, std::string>>;
using pair_StrPair_IntInt = std::pair<std::string, std::pair<int, int>>;
using pair_StrPair_StrInt = std::pair<std::string, std::pair<std::string, int>>;

class Parser 
{
private:
    static Parser* instancia;
    instruction_Set* instancia_instruction_Set;
    // Vetor de instrucoes <OP, <R1, <R2, <Linha, Pos_Memoria>>>>
    std::vector<instruction_line*> instruction_table;
    // Vetor de constantes <Nome, Valor/Endereco>
    vecPair_StrInt symbol_table;
    // Vetor de OpCodes
    std::string binary_code;
    
    Parser();    
    
    std::string dec_to_bin(const int);
	//modificacao
    std::string get_instruction_opcode(const std::string op, int n_operators);
    std::string get_symbol_opcode(const std::string op);
    
    bool is_operator(const std::string op);
    bool is_valid_symbol(const std::string op, int num_op);
    
    void add_instruction(const std::string si, const std::string op1, const std::string op2, const int line);
    void add_symbol(const std::string si, const int val);

    void check_sintax(std::ifstream &source_file);
	void translate_code(std::string build_file);
    
public:
    static Parser *get_instancia();
    std::string make_object(std::ifstream &source_file, std::string output_file);
	std::vector<instruction_line*> get_intruction_table();
	vecPair_StrInt get_symbol_table();
    ~Parser();
};

#endif /* PARSER_H */

