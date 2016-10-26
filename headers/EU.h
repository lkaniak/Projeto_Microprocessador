#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include "REGISTER.h"
#include "instruction_Set.h"
#include "BUS.h"

class EU
{
private:
	static EU* instancia;
	std::vector<REGISTER*> main_registers;
	REGISTER *aux;

	EU();
	~EU();
public:
	static EU* get_instancia();

	void process(std::string op, std::string reg_1, std::string reg_2);
	void process(std::string op, std::string reg_1, int reg_2);
	void process(std::string op, std::string reg_1);
	void process(std::string op, int reg_1);
	void process(std::string op);

	REGISTER *get_aux();

	// TESTE REMOVER
	std::vector<REGISTER*> get_main_registers(){ return main_registers; };
};

