/* 
 * File:   utils.cpp
 * Author: Rafael Teixeira
 * 
 * Created on September 3, 2016, 10:21 AM
 */

#include "./../headers/utils.h"
#include"./../headers/parser.h"

utils *utils::instancia = nullptr;

utils *utils::get_instancia()
{
    if (!instancia)
    {
        instancia = new utils();
    }
    
    return instancia;
}

void utils::generate_csv(Parser* P)
{
	struct stat info;

	if (stat("./build", &info) != 0)
	{
		throw std::runtime_error("Folder './build' does not exist!");
	}

	std::ofstream tbinstr;
	std::ofstream tbsymb;
	std::string str;
	vecPair_StrInt Symb;	//symbol table
	std::vector<instruction_line*> Instr;	//Instruction table
	
	Symb = P->get_symbol_table();
	Instr = P->get_intruction_table();

	tbinstr.open(instruction_table_file);

	str = "sep=,\n";
	tbinstr << str;
	str = "Instruction,First operand,Second Operand\n";
	tbinstr << str;

	for (auto i_symbol = 0; i_symbol < Instr.size(); i_symbol++)
	{
		str = Instr[i_symbol]->get_name();
		str.insert(0, "\"");
		tbinstr << str + "\",";
		str = Instr[i_symbol]->get_operator_1();
		str.insert(0, "\"");
		tbinstr << str + "\",";
		str = Instr[i_symbol]->get_operator_2();
		str.insert(0, "\"");
		tbinstr << str + "\"\n";
	}

	tbinstr.close();
	tbsymb.open(symbol_table_file);

	str = "sep=,\n";
	tbsymb << str;
	str = "Symbol,Value/Line\n";
	tbsymb << str;

	for (auto it = Symb.begin(); it != Symb.end(); it++)
	{
		str = it->first;
		str.insert(0, "\"");
		tbsymb << str + "\",";
		str = std::to_string(it->second);
		str.insert(0, "\"");
		tbsymb << str + "\"\n";
	}

	tbsymb.close();


}

utils::utils()
{
}

std::vector<std::string> utils::split_line(const std::string &text, const char sep) {
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
