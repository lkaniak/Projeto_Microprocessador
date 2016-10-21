#pragma once
#include <string>

class REGISTER
{
private:
	std::string name;
	int value;
public:
	REGISTER(std::string name);
	REGISTER(std::string name, int v);
	~REGISTER();

	int get_value();
	void set_value(int value);
	std::string get_name();
};

