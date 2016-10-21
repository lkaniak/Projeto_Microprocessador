#pragma once
#include "Instruction.h"
#include "REGISTER.h"

class ALU
{
private:
	static ALU* instancia;
	REGISTER *first;
	REGISTER *second;
	REGISTER *result;

	ALU();
	~ALU();
public:
	
	static ALU* get_instancia();

	void execute();
	void set_first(int val);
	void set_second(int val);
	int get_result();
	
	REGISTER *get_first();
	REGISTER *get_second();
};

