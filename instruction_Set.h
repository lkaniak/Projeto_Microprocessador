#pragma once
#include <string>

class instruction_Set
{
private:
	static instruction_Set *instancia;

	// Dois operadores
	void mov(int r1, int r2); // MOV R1, R2
	void mov(int r1, float cst); //MOV R1, CONST
	void add(int r1, int r2);
	void sub(int r1, int r2);
	void div(int r1, int r2);
	void mul(int r1, int r2);
	
	// Um operador
	void cmp(int r1);
	void and(int r1);
	void or (int r1);
	void xor(int r1);
	void push(int r1);
	void pop(int r1);
	void not(int r1);
	void inc(int r1);
	void dec(int r1);
	void load(int r1);
	void store(int r1);
	void interrupt(int r1);
	void jmp(int r1);
	void jg(int r1);
	void je(int r1);
	void jne(int r1);
	void jl(int r1);
	void jz(int r1);
	void jnz(int r1);
	void ja(int r1);
	void jb(int r1);
	void ret(int r1);
	void call(int r1);

	// Nenhum operador
	void start();
	void end();

public:
	static instruction_Set *get_instancia();
	instruction_Set();
	~instruction_Set();

	void execute_instruction(std::string);
};

