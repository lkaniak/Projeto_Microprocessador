#include "BUS.h"

BUS *BUS::instancia = nullptr;

BUS::BUS()
{
}

BUS::~BUS()
{
}

BUS * BUS::get_instancia()
{
	if (!instancia)
	{
		instancia = new BUS();
	}

	return instancia;
}

void BUS::transfer(REGISTER *from, REGISTER *to)
{
	auto f = from->get_value();
	to->set_value(f);
}
