#include "../headers/REGISTER.h"


REGISTER::REGISTER(std::string name)
	:name(name),
	value(0)
{
}

REGISTER::REGISTER(std::string name, int v)
	: name(name),
	value(v)
{
}

REGISTER::~REGISTER()
{
}

int REGISTER::get_value()
{
	return value;
}

void REGISTER::set_value(int value)
{
	this->value = value;
}

std::string REGISTER::get_name()
{
	return name;
}
