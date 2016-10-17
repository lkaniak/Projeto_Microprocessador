#pragma once
#include <map>
#include <string>

class FLAGS
{
private:
	std::map<std::string, bool> flags;

public:
	FLAGS();
	~FLAGS();

	void set_flag(int flag);
	bool get_flag(int flag);
};

