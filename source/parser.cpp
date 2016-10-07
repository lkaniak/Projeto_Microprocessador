/* 
 * File:   parser.cpp
 * Author: toad
 * 
 * Created on August 28, 2016, 10:19 AM
 */

#define build_file "./build/temp.obj"

#include "./../headers/parser.h"
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
    this->instancia_instruction_Set = instruction_Set::get_instancia();
}

Parser::~Parser()
{
}

std::string Parser::dec_to_bin(const int dec_num)
{
    return std::bitset<8>(dec_num).to_string();
}

std::string Parser::get_instruction_opcode(const std::string op)
{
    auto instruc = this->instancia_instruction_Set->get_operation_info(op);
        if (instruc != nullptr)
        {
            return instruc->get_opcode();
        }
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

std::string Parser::get_symbol_opcode(const std::string op)
{
    for (auto it = this->symbol_table.begin(); it != this->symbol_table.end(); it++)
        if (it->first == op)
            return std::to_string(it->second);
    return std::string();
}

bool Parser::is_operator(const std::string op)
{
    auto instruc = this->instancia_instruction_Set->get_operation_info(op);
    if (instruc != nullptr && instruc->get_num_operators() == -1)
    {
        return true;
    }
    return false;
}

bool Parser::is_valid_symbol(const std::string op, const int num_op)
{
    auto instruc = this->instancia_instruction_Set->get_operation_info(op);
    if (instruc != nullptr)
    {
        if (instruc->get_num_operators() == num_op || instruc->get_num_operators() == -1)
        {
            return true;
        }
    }
    return false;
}

void Parser::add_instruction(const std::string inst, const std::string op1, const std::string op2, const int line)
{
    auto _op1 = this->instancia_instruction_Set->get_operation_info(op1);
    auto _op2 = this->instancia_instruction_Set->get_operation_info(op2);
    if (_op2 != nullptr && _op1 != nullptr)
    {
        this->instruction_table.push_back(new instruction_line(inst, _op1,_op2, line, int(instruction_table.size())));
    }
    else if(_op1 == nullptr)
    {
        this->instruction_table.push_back(new instruction_line(inst, op1,_op2, line, int(instruction_table.size())));
    }
    else
    {
        try
        {
            this->instruction_table.push_back(new instruction_line(inst, _op1,std::stoi(op2), line, int(instruction_table.size())));
        }
        catch (std::exception)
        {
            this->instruction_table.push_back(new instruction_line(inst, _op1,op2, line, int(instruction_table.size())));
        }
    }
}

void Parser::add_symbol(const std::string si, const int val)
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

void Parser::check_sintax(std::ifstream &source_file)
{
    auto line_count = 0;
    std::string line = "";
    auto utils_instancia = utils::get_instancia();
   
    std::cout << "#Looking for start... ";
    // Busca inicio do codigo
    while(line != "START")
    {
        line_count++;
        std::getline(source_file, line);
		if (source_file.eof())
		{
			throw std::runtime_error("START not found");
		}
    }
    
    std::cout << "Found." << std::endl 
            << "#Starting first pass... ";
    
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
            auto instruction_token = utils_instancia->split_line(line, ' ');
            
            // Continua o loop se for linha em branco
            if (instruction_token.size() == 0)
                continue;
            
            if (instruction_token.size() == 2)
            {
                
                // Faz a quebra dos operandos
                auto operand_token = utils_instancia->split_line(instruction_token[1], ',');
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
                            this->add_symbol(operand_token[1], -1);
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
            auto const_token = utils_instancia->split_line(line, ' ');
            this->add_symbol(const_token[0], std::stoi(const_token[1]));
        }
    }
    std::cout << "Done" << std::endl
            << "#Starting second pass... ";
    
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
}

void Parser::translate_code()
{
	struct stat info;

	if (stat("./build", &info) != 0)
	{
		throw std::runtime_error("Folder './build' does not exist!");
	}
	// Segunda passada
	std::ofstream obj_file;
	obj_file.open(build_file);

	for (auto i_symbol = 0; i_symbol < this->instruction_table.size(); i_symbol++)
	{
		std::string op_code;
		op_code = this->get_instruction_opcode(this->instruction_table[i_symbol]->get_name());
		obj_file << op_code;
		op_code = this->get_instruction_opcode(this->instruction_table[i_symbol]->get_operator_1());
		obj_file << op_code;
		op_code = this->get_instruction_opcode(this->instruction_table[i_symbol]->get_operator_2());
		obj_file << op_code;
	}

	obj_file.close();

	std::cout << "Done" << std::endl;
}

std::string Parser::make_object(std::ifstream &source_file)
{
    std::cout << std::endl << "Checking for sintax errors:" << std::endl;
    this->check_sintax(source_file);
	this->translate_code();
    std::cout << "Ok" << std::endl;
    return "";
}

std::vector<instruction_line*> Parser::get_intruction_table()
{
	return this->instruction_table;
}

vecPair_StrInt Parser::get_symbol_table()
{
	return this->symbol_table;
}


