#include "../headers/EU.h"

EU *EU::instancia = nullptr;

EU::EU()
{
	// TESTE
	this->main_registers.push_back(new REGISTER("RB", 2));
	this->main_registers.push_back(new REGISTER("RD", 3));
	// FIM TESTE

	this->main_registers.push_back(new REGISTER("RA"));
	//this->main_registers.push_back(new REGISTER("RB"));
	this->main_registers.push_back(new REGISTER("RC"));
	//this->main_registers.push_back(new REGISTER("RD"));
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
	/*REGISTER* r1 = *std::find(main_registers.cbegin(), main_registers.cend(), [reg_1](REGISTER &r) {
		return r.get_name().compare(reg_1) == 0;
	});
	REGISTER* r2 = *std::find(main_registers.cbegin(), main_registers.cend(), [reg_2](REGISTER &r) {
		return r.get_name().compare(reg_2) == 0;
	});*/

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
