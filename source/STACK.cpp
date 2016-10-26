#include "../headers/STACK.h"




bool STACK::is_full()
{
	if (this->size == this->max)
	{
		return true;
	}
	return false;
}

bool STACK::is_empty()
{
	if (this->size == 0)
	{
		return true;
	}
	return false;
}

void STACK::push(std::string byte)
{
	if (!this->is_full())
	{
		this->stack.push_back(byte);
		this->size++;
	}
	else
	{
		//throw std::runtime_error("stack is full!");
	}
}

std::string STACK::pop()
{
	std::string byte = nullptr;
	if (!this->is_empty())
	{
		byte = *this->stack.end();
		this->stack.pop_back();
	}
	/*
	if (byte == nullptr)
	{
		throw std::runtime_error("stack is empty!");
	}
	*/
	return byte;
}

STACK::STACK() : size(0), max(30)
{
}

STACK::STACK(int stack_size) : size(0), max(stack_size)
{
}


STACK::~STACK()
{
}
