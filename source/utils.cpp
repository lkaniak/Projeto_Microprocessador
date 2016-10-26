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

void utils::generate_csv(vecPair_StrInt* Symb, std::vector<instruction_line*> * Instr)
{
	struct stat info;

	if (stat("./build", &info) != 0)
	{
		throw std::runtime_error("Folder './build' does not exist!");
	}

	std::ofstream table;
	std::string str;

	table.open(instruction_table_file);

	str = "sep=,\n";
	table << str;
	str = "Instruction,First operand,Second Operand\n";
	table << str;

	for (auto i_symbol = 0; i_symbol < Instr->size(); i_symbol++)
	{
		str = Instr->at(i_symbol)->get_name();
		str.insert(0, "\"");
		table << str + "\",";
		str = Instr->at(i_symbol)->get_operator_1();
		str.insert(0, "\"");
		table << str + "\",";
		str = Instr->at(i_symbol)->get_operator_2();
		str.insert(0, "\"");
		table << str + "\"\n";
	}

	table.close();
	table.open(symbol_table_file);

	str = "sep=,\n";
	table << str;
	str = "Symbol,Value/Line\n";
	table << str;

	for (auto it = Symb->begin(); it != Symb->end(); it++)
	{
		str = it->first;
		str.insert(0, "\"");
		table << str + "\",";
		str = std::to_string(it->second);
		str.insert(0, "\"");
		table << str + "\"\n";
	}

	table.close();


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

std::string utils::dec_to_bin(const int dec_num)
{
	return std::bitset<8>(dec_num).to_string();
}

std::string utils::bin_to_dec(const std::string str_num)
{
	unsigned num = std::stoi(str_num);
	unsigned res = 0;

	for (int i = 0; num > 0; ++i)
	{
		if ((num % 10) == 1)
			res += (1 << i);

		num /= 10;
	}

	return std::to_string(res);
}
