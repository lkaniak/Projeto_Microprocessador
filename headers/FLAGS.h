#pragma once
#include <map>
#include <string>

class FLAGS
{
private:
	static FLAGS* instancia;
	FLAGS();
	~FLAGS();
	std::map<int, bool> flags;

public:
	static FLAGS* get_instancia();

	void set_flag(int flag, bool r);
	bool get_flag(int flag);
};

