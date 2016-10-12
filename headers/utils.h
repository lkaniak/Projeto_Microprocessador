/* 
 * File:   utils.h
 * Author: Rafael Teixeira
 *
 * Created on September 3, 2016, 10:21 AM
 */

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include "instruction_line.h"

#define instruction_table_file "./build/instruction_table.csv"
#define symbol_table_file "./build/symbol_table.csv"

using vecPair_StrInt = std::vector<std::pair<std::string, int>>;

class utils 
{
private:
    static utils *instancia;

public:
    utils();
    static utils *get_instancia();
	void generate_csv(vecPair_StrInt* Symb, std::vector<instruction_line*> * Instr);
    std::vector<std::string> split_line(const std::string &text, const char sep);
};

#endif /* UTILS_H */

