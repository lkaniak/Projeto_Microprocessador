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

void ALU::execute(REGISTER *r1, char op)
{
	auto bus = BUS::get_instancia();
	auto flag = FLAGS::get_instancia();
	if (op == '+')
	{
		result->set_value(first->get_value() + second->get_value());
		if (result->get_value() > 127)
		{
			flag->set_flag(2, true);
			while (result->get_value() > 127)
			{
				result->set_value(result->get_value() - 255);
			}
		}
		else
		{
			flag->set_flag(2, false);
		}
	}

	else if (op == '-')
	{
		result->set_value(first->get_value() - second->get_value());
		if (result->get_value() == 0)
		{
			flag->set_flag(1, true);
		}
		else
		{
			flag->set_flag(1, false);
		}
		if (result->get_value() < 0)
		{
			flag->set_flag(3, true);
		}
		else
		{
			flag->set_flag(3, false);
		}
		if (result->get_value() < -127)
		{
			flag->set_flag(2, true);
			while (result->get_value() < -127)
			{
				result->set_value(result->get_value() + 255);
			}
		}
		else
		{
			flag->set_flag(2, false);
		}

	}
	else if (op == '*')
	{
		result->set_value(first->get_value() * second->get_value());
		if (result->get_value() > 127)
		{
			flag->set_flag(2, true);
			while (result->get_value() > 127)
			{
				result->set_value(result->get_value() - 255);
			}
		}
		else
		{
			flag->set_flag(2, false);
		}

	}
	else if (op == '/')
		result->set_value(first->get_value() / second->get_value());
	bus->transfer(result, r1);
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
