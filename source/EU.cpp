#include "../headers/EU.h"

EU *EU::instancia = nullptr;

EU::EU()
{
	// TESTE
	//this->main_registers.push_back(new REGISTER("RB", 10));
	//this->main_registers.push_back(new REGISTER("RD", 2));
	// FIM TESTE

	this->main_registers.push_back(new REGISTER("RA"));
	this->main_registers.push_back(new REGISTER("RB"));
	this->main_registers.push_back(new REGISTER("RC"));
	this->main_registers.push_back(new REGISTER("RD"));
}


EU::~EU()
{
}

EU * EU::get_instancia()
{
	if (!instancia)
	{
		instancia = new EU();
	}

	return instancia;
}

void EU::process(std::string op, std::string reg_1, std::string reg_2)
{
	REGISTER* r1 = nullptr;
	REGISTER* r2 = nullptr;
	for (auto it = this->main_registers.cbegin(); it != this->main_registers.cend(); ++it)
	{
		if ((*it)->get_name().compare(reg_1) == 0)
		{
			r1 = *it;
			break;
		}
	}
	for (auto it = this->main_registers.cbegin(); it != this->main_registers.cend(); ++it)
	{
		if ((*it)->get_name().compare(reg_2) == 0)
		{
			r2 = *it;
			break;
		}
	}

	instruction_Set::get_instancia()->execute_instruction(op, r1, r2);
}

void EU::process(std::string op, std::string reg_1, int reg_2)
{
	REGISTER* r1 = nullptr;
	int r2 = reg_2;
	for (auto it = this->main_registers.cbegin(); it != this->main_registers.cend(); ++it)
	{
		if ((*it)->get_name().compare(reg_1) == 0)
		{
			r1 = *it;
			break;
		}
	}

	instruction_Set::get_instancia()->execute_instruction(op, r1, r2);
}

void EU::process(std::string op, std::string reg_1)
{
	REGISTER* r1 = nullptr;
	for (auto it = this->main_registers.cbegin(); it != this->main_registers.cend(); ++it)
	{
		if ((*it)->get_name().compare(reg_1) == 0)
		{
			r1 = *it;
			break;
		}
	}

	instruction_Set::get_instancia()->execute_instruction(op, r1);
}

void EU::process(std::string op)
{
	instruction_Set::get_instancia()->execute_instruction(op);
}

REGISTER * EU::get_aux()
{
	return this->aux;
}
