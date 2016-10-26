#include "../headers/QUEUE.h"



QUEUE::QUEUE() : size(0), max(5)
{
}

QUEUE::QUEUE(int max_size) : size(0), max(max_size)
{
}


QUEUE::~QUEUE()
{
}

bool QUEUE::is_full()
{
	if (this->size == this->max)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool QUEUE::is_empty()
{
	if (this->size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void QUEUE::load(std::string Instr)
{
	if (!is_full())
	{
		this->instructions.push_back(Instr);
		this->size++;
	}
}

std::string QUEUE::get_instruction()
{
	std::string Instr;
	if (!this->is_empty())
	{
		Instr = this->instructions.front();
		this->instructions.erase(this->instructions.begin());
		this->size--;
	}
	else 
	{
		throw std::runtime_error("invalid queue access!");
	}
}

void QUEUE::fill()
{
	//load(instr);
	while (!this->is_full())
	{
		fill();
	}
}

void QUEUE::clear()
{
	if (!this->is_empty())
	{
		while (!this->is_empty())
		{
			this->instructions.pop_back();
			this->size--;
		}
	}
	else
	{
		//throw std::runtime_error("queue already empty.");
	}
	
}


