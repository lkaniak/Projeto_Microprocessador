#include "../headers/FLAGS.h"

FLAGS *FLAGS::instancia = nullptr;

FLAGS::FLAGS()
{
	for (auto i = 0; i < 8; ++i)
	{
		flags[i] = false;
	}
}


FLAGS::~FLAGS()
{
}

FLAGS * FLAGS::get_instancia()
{
	if (!instancia)
	{
		instancia = new FLAGS();
	}
	return instancia;
}

void FLAGS::set_flag(int flag, bool r)
{
	flags[flag] = r;
}

bool FLAGS::get_flag(int flag)
{
	return flags[flag];
}
