#pragma once
#include <string>

class BUS
{
public:
	BUS();
	~BUS();

	void transfer_to(std::string register);
	std::string transfer_from(std::string register);
};

