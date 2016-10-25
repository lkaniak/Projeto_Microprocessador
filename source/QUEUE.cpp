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

void QUEUE::load(Instruction Instr)
{
	if (!is_full())
	{
		this->instructions.push_back(Instr);
		this->size++;
	}
}

void QUEUE::fill_queue()
{
	//load(instr);
	while (!this->is_full())
	{
		fill_queue();
	}
}


