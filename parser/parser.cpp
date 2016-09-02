/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   parser.cpp
 * Author: toad
 * 
 * Created on August 28, 2016, 10:19 AM
 */

#define instructions_file "../data/symbols.d"
#define operators_file "../data/operator.d"

#include "parser.h"
Parser *Parser::instancia = nullptr;

Parser *Parser::get_instancia()
{
    if (!instancia)
    {
        instancia = new Parser();
    }
    
    return instancia;
}

Parser::Parser()
{
    load_instructions();
    load_operators();
}

Parser::~Parser()
{
}

void Parser::load_instructions()
{
	std::ifstream symbols_file;
	symbols_file.open(instructions_file);

	if (!symbols_file.is_open())
		throw std::runtime_error("Failed to open symbols file.");

	std::cout << "Loading symbols... ";
	std::string line;
	for (std::getline(symbols_file, line); !symbols_file.eof(); std::getline(symbols_file, line))
	{
		auto line_tokens = split_line(line, ' ');
		this->instructions.push_back(std::make_pair(line_tokens[0], std::make_pair(line_tokens[1], std::stoi(line_tokens[2]))));
	}
	symbols_file.close();
	std::cout << "Done." << std::endl;
}

void Parser::load_operators()
{
	std::ifstream op_file;
	op_file.open(operators_file);

	if (!op_file.is_open())
		throw std::runtime_error("Failed to open operator file.");

	std::cout << "Loading operators... ";
	std::string line;
	for (std::getline(op_file, line); !op_file.eof(); std::getline(op_file, line))
	{
		auto line_tokens = split_line(line, ' ');
		this->operators.push_back(std::make_pair(line_tokens[0], line_tokens[1]));
	}
	op_file.close();
	std::cout << "Done." << std::endl;
}

std::vector<std::string> Parser::split_line(const std::string &text, char sep) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        std::string temp = text.substr(start, end - start);
        if (temp != "") tokens.push_back(temp);
        start = end + 1;
    }
    std::string temp = text.substr(start);
    if (temp != "") tokens.push_back(temp);
    return tokens;
}

std::string Parser::dec_to_bin(int dec_num)
{
	return std::bitset<8>(dec_num).to_string();
}

std::string Parser::get_instruction_opcode(std::string op)
{
	std::string op_bin;
	
	// Verifica tabela de instrucoes
	for (auto it = this->instructions.begin(); it != this->instructions.end(); it++)
		if (it->first == op)
			return it->second.first;

	// Verifica tabela de registradores
	for (auto it = this->operators.begin(); it != this->operators.end(); it++)
		if (it->first == op)
			return it->second;
	try
	{
		return this->dec_to_bin(std::stoi(op));
	}
	catch (const std::invalid_argument)
	{
		if (!op.empty())
			return this->dec_to_bin(std::stoi(this->get_symbol_opcode(op)));
		else
			return "";
	}

	return std::string();
}

std::string Parser::get_symbol_opcode(std::string op)
{
	for (auto it = this->symbol_table.begin(); it != this->symbol_table.end(); it++)
		if (it->first == op)
			return std::to_string(it->second);
	return std::string();
}

bool Parser::is_operator(std::string op)
{
    for (auto it = this->operators.begin(); it != this->operators.end(); it++)
        if (it->first == op)
            return true;
    return false;
}

bool Parser::is_valid_symbol(std::string si, int num_op)
{
    for (auto it = this->instructions.begin(); it != this->instructions.end(); it++)
        if (it->first == si && it->second.second == num_op)
            return true;
    return false;
}

void Parser::add_instruction(std::string inst, std::string op1, std::string op2, int line)
{
    this->instruction_table.push_back(std::make_pair(inst, std::make_pair(op1, std::make_pair(op2, std::make_pair(line, instruction_table.size())))));
}

void Parser::add_symbol(std::string si, int val)
{
	// Verifica se o elemento ja existe, se existir e o endereco for invalido substitui
	for (auto it = this->symbol_table.begin(); it != this->symbol_table.end(); it++)
		if (si == it->first)
			if (it->second == -1)
			{
				it->second = val;
				return;
			}
				
	this->symbol_table.push_back(std::make_pair(si, val));
}

bool Parser::check_sintax(std::ifstream &source_file)
{
    auto line_count = 0;
    std::string line = "";
   
    std::cout << "#Looking for start... ";
    // Busca inicio do codigo
    while(line != "START")
    {
        line_count++;
        std::getline(source_file, line);
        if (source_file.eof())
            throw std::runtime_error("START not found");
    }
    
    std::cout << "Found." << std::endl 
            << "#Starting first pass... ";
    
    //std::getline(source_file, line);
     // Primeira passada
    while (line != "END")
    {
        line_count++;
        std::getline(source_file, line);
        
        // Adiciona label ao encontrar
        if (line.find(':') != std::string::npos)
        {
            line.erase(0, line.find(':') + 1);
            this->add_symbol(line, instruction_table.size() + 1);
        }
        
        // Caso a linha nao tenha comentario
        else if (line.find("//") == std::string::npos)
        {
            auto instruction_token = split_line(line, ' ');
            
            // Continua o loop se for linha em branco
            if (instruction_token.size() == 0)
                continue;
            
            if (instruction_token.size() == 2)
            {
                
                // Faz a quebra dos operandos
                auto operand_token = split_line(instruction_token[1], ',');
                if (operand_token.size() == 2)
                {
                    if (!this->is_valid_symbol(instruction_token[0], 2))
                    {
                        auto error = "Error in line " + std::to_string(line_count) + ". '" 
                            + instruction_token[0] + "' is not an instruction.";
                        throw std::runtime_error(error);
                    }
                
                    // Se o primeiro nao for operando e a instrucao nao for MOV
                    auto op_token = this->is_operator(operand_token[0]);
                    if (!op_token || !this->is_operator(operand_token[1]))
                    {
                        if (instruction_token[0] != "MOV" || !op_token)
                        {
                            auto error = "Error in line " + std::to_string(line_count) +  ". Not an operator.";
                            throw std::runtime_error(error);
                        }
						else
						{
							// Tenta converter para inteiro
							try
							{
								std::stoi(operand_token[1]);
							}
							catch (const std::invalid_argument)
							{
								this->add_symbol(operand_token[1], -1);
							}
						}
                    }
                    this->add_instruction(instruction_token[0], operand_token[0], operand_token[1], line_count);
                }
                else
                {
                    if (!this->is_valid_symbol(instruction_token[0], 1))
                    {
                        auto error = "Error in line " + std::to_string(line_count) + ". '" 
                            + instruction_token[0] + "' is not an instruction.";
                        throw std::runtime_error(error);
                    }
                
                    if (!this->is_operator(operand_token[0]))
                    {
                        // Verifica se token nao eh label, senao cria
                        auto found = false;
                        for(auto it = symbol_table.begin(); it != symbol_table.end(); it++)
                            if (it->first == operand_token[0])
                            {
                                //operand_token[0] = it->second;
                                found = true;
                            }
                        if (!found)
                        {
                            this->add_symbol(line, -1);
                        }
                    }
                                        
                    this->add_instruction(instruction_token[0], operand_token[0], "", line_count);
                }
            }
            else
            {
                if (!this->is_valid_symbol(instruction_token[0], 0))
                {
                    auto error = "Error in line " + std::to_string(line_count) + ". '" 
                            + instruction_token[0] + "' is not an instruction.";
                    throw std::runtime_error(error);
                }
                
                this->add_instruction(instruction_token[0], "", "", line_count);
            }
        }
    }
    this->instruction_table.pop_back();
    // Pega as constantes no final do arquivo
    while (!source_file.eof())
    {
        line_count++;
        std::getline(source_file, line);
        // Ignora se for linha vazia ou comentario
        if (line[0] != '\n' && line[0] != '/' && line != "")
        {
            auto const_token = split_line(line, ' ');
            this->add_symbol(const_token[0], std::stoi(const_token[1]));
        }
    }
    std::cout << "Done" << std::endl
            << "#Starting second pass... ";
    
    std::cout << line_count << " " << instruction_table.size() << std::endl;
    source_file.close();
    line_count = 0;

	// Verifica se todos os operadores foram corretamente mapeados
	for (auto it = this->symbol_table.begin(); it != this->symbol_table.end(); it++)
	{
		if (it->second == -1)
		{
			auto error = "Operator '" + it->first + "' is unkown.";
			throw std::runtime_error(error);
		}
	}
    
    // Segunda passada
	std::string op_bin = "";

    for(auto it_symbol = instruction_table.begin(); it_symbol != instruction_table.end(); it_symbol++)
    {
		this->binary_code += this->get_instruction_opcode(it_symbol->first);
		this->binary_code += this->get_instruction_opcode(it_symbol->second.first);
		this->binary_code += this->get_instruction_opcode(it_symbol->second.second.first);
    }
	std::cout << this->binary_code << std::endl;
        std::cout << this->binary_code.size() << std::endl;
    std::cout << "Done" << std::endl;
    
    return true;
}

std::string Parser::make_object(std::ifstream &source_file)
{
	std::cout << std::endl << "Checking for sintax errors:" << std::endl;
	check_sintax(source_file);
	std::cout << "Ok" << std::endl;
	return "";
}