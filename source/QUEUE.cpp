#include "../headers/QUEUE.h"
#include "../headers/BIU.h"


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
	if (this->is_empty())
	{
		this->fill();
	}
	
	Instr = this->instructions.front();
	this->instructions.erase(this->instructions.begin());
	this->size--;

	return Instr;
}

void QUEUE::fill()
{
	auto biu_instancia = BIU::get_instancia();

	while (!this->is_full() && biu_instancia->get_ip_value() < biu_instancia->get_memory_size_limit())
	{
		std::string instr = biu_instancia->get_address_from_memory_with_ip();
		this->load(instr);
		biu_instancia->increment_ip();
	}
}

void QUEUE::clear()
{
	while (!this->is_empty())
	{
		this->instructions.pop_back();
		this->size--;
	}
}


