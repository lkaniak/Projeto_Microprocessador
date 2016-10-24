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

	REGISTER& operator=(const REGISTER& other)
	{
		this->name = other.name;
		this->value = other.value;

		return *this;
	}

	int get_value();
	void set_value(int value);
	std::string get_name();
};

