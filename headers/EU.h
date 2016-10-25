#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include "REGISTER.h"
#include "instruction_Set.h"

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
	void process(std::string op, std::string reg_1);
	void process(std::string op);

	REGISTER *get_aux();
};

