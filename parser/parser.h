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

class Parser {
private:
    static Parser *instancia;
    // Vetor de instrucoes existentes <Nome_Instr <OpCode, Num_Operadores>>
    std::vector<std::pair<std::string, std::pair<int, int>>> instructions;
    // Vetor de registradores <Nome_regist, OpCode>
    std::vector<std::pair<std::string, int>> operators;
    // Vetor de instrucoes <OP, <R1, <R2, <Linha, Pos_Memoria>>>>
    std::vector<std::pair<std::string, std::pair<std::string, std::pair<std::string, std::pair<int, int>>>>> instruction_table;
    // Vetor de constantes <Nome, Valor/Endereco>
    std::vector<std::pair<std::string, int>> symbol_table;
    // Vetor de OpCodes
    std::vector<int> opcode_table;
    
    Parser();
    Parser(const Parser& orig);
    
    
    void load_instructions();
    void load_operators();
    
    std::vector<std::string> split_line(const std::string &text, char sep);
    unsigned long dec_to_bin(int);
    
    bool check_sintax(std::ifstream &source_file);
    bool is_operator(std::string op);
    bool is_valid_symbol(std::string si, int num_op);
    
    void add_instruction(std::string si, std::string op1, std::string op2, int line);
    void add_symbol(std::string si, int val);
    
public:
    static Parser *get_instancia();
    std::string make_object(std::ifstream &source_file);
    
    ~Parser();
};

#endif /* PARSER_H */

