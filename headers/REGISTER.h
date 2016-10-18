#pragma once
#include <string>

class REGISTER
{
private:
	std::string value;
public:
	REGISTER();
	~REGISTER();

	void get_value();
	void set_value(std::string value);
};

