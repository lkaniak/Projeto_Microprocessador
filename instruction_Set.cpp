#include "Instructions.h"

instruction_Set *instruction_Set::instancia = nullptr;

instruction_Set * instruction_Set::get_instancia()
{
	if (!instancia)
	{
		instancia = new instruction_Set();
	}

	return instancia;
}

instruction_Set::instruction_Set()
{
}


instruction_Set::~instruction_Set()
{
}

void instruction_Set::execute_instruction(std::string)
{

}

void instruction_Set::mov(int r1, int r2)
{
}

void instruction_Set::mov(int r1, float cst)
{
}

void instruction_Set::add(int r1, int r2)
{
}

void instruction_Set::sub(int r1, int r2)
{
}

void instruction_Set::div(int r1, int r2)
{
}

void instruction_Set::mul(int r1, int r2)
{
}

void instruction_Set::cmp(int r1)
{
}

void instruction_Set:: and (int r1)
{
}

void instruction_Set:: or (int r1)
{
}

void instruction_Set:: xor (int r1)
{
}

void instruction_Set::push(int r1)
{
}

void instruction_Set::pop(int r1)
{
}

void instruction_Set::not(int r1)
{
}

void instruction_Set::inc(int r1)
{
}

void instruction_Set::dec(int r1)
{
}

void instruction_Set::load(int r1)
{
}

void instruction_Set::store(int r1)
{
}

void instruction_Set::interrupt(int r1)
{
}

void instruction_Set::jmp(int r1)
{
}

void instruction_Set::jg(int r1)
{
}

void instruction_Set::je(int r1)
{
}

void instruction_Set::jne(int r1)
{
}

void instruction_Set::jl(int r1)
{
}

void instruction_Set::jz(int r1)
{
}

void instruction_Set::jnz(int r1)
{
}

void instruction_Set::ja(int r1)
{
}

void instruction_Set::jb(int r1)
{
}

void instruction_Set::ret(int r1)
{
}

void instruction_Set::call(int r1)
{
}

void instruction_Set::start()
{
}

void instruction_Set::end()
{
}
