#pragma once
#include <string>
#include "REGISTER.h"

class BUS
{
private:
	static BUS* instancia;
	BUS();
	~BUS();


public:
	static BUS* get_instancia();

	void transfer(REGISTER *from, REGISTER *to);
};

