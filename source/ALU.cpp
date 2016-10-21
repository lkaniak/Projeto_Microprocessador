#include "../headers/ALU.h"


ALU *ALU::instancia = nullptr;

ALU *ALU::get_instancia()
{
	if (!instancia)
	{
		instancia = new ALU();
	}

	return instancia;
}

void ALU::execute()
{
	result->set_value(first->get_value() + second->get_value());
}

void ALU::set_first(int val)
{
	this->first->set_value(val);
}

void ALU::set_second(int val)
{
	this->second->set_value(val);
}

int ALU::get_result()
{
	return result->get_value();
}

REGISTER * ALU::get_first()
{
	return first;
}

REGISTER * ALU::get_second()
{
	return second;
}

ALU::ALU()
	: first(new REGISTER("ALU_1")),
	second(new REGISTER("ALU_2")),
	result(new REGISTER("ALU_r"))
{
}


ALU::~ALU()
{
}
