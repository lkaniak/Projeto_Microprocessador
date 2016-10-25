#pragma once
#include <string>
#include <vector>
#include "Instruction.h"
#include "instruction_Set.h"
#include "EU.h"

class DECODER
{
private:
	static DECODER* instancia;
	std::vector<std::string> instruction_vector;

	// Numero maximo e atual de instrucoes na fila
	int limit;
	int current;

	DECODER();
	~DECODER();
	void load();
public:
	static DECODER* get_instancia();
	void decode(std::string instruction);
};

