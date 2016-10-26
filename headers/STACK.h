#pragma once
#include <vector>
#include <string>
class STACK
{
private:
	std::vector<std::string> stack;
	int size;
	int max;

	bool is_full();
	bool is_empty();

public:
	void push(std::string byte);
	std::string pop();
	STACK();
	STACK(int stack_size);
	~STACK();
};

