#include "..\headers\DECODER.h"

DECODER *DECODER::instancia = nullptr;

DECODER * DECODER::get_instancia()
{
	if (!instancia)
	{
		instancia = new DECODER();
	}

	return instancia;
}

void DECODER::decode(std::string instruction)
{
	std::string opcode;
	auto inst_set = instruction_Set::get_instancia();
	Instruction *instr_translated = nullptr;
	Instruction *operator_1_translated = nullptr;
	Instruction *operator_2_translated = nullptr;

	//Pega a instrucao
	for (auto o : instruction)
	{
		opcode += o;
		if (opcode.size() == 4 || opcode.size() == 6 || opcode.size() == 8)
		{
			instr_translated = inst_set->get_operation_name(opcode);
			if (instr_translated != nullptr)
				break;
		}
	}

	instruction.erase(0, instr_translated->get_opcode().size());

	// Pega os registradores
	opcode = "";
	for (auto o : instruction)
	{
		opcode += o;
		if (operator_1_translated == nullptr && opcode.size() ==  2)
		{
			operator_1_translated = inst_set->get_operation_name(opcode);
			opcode = "";
		}
		else if (opcode.size() == 2)
		{
			operator_2_translated = inst_set->get_operation_name(opcode);
			break;
		}
	}

	EU::get_instancia()->process(instr_translated->get_name(),
		operator_1_translated->get_name(),
		operator_2_translated->get_name());
}

DECODER::DECODER()
	: limit(4),
	current(0)
{
}


DECODER::~DECODER()
{
}

void DECODER::load()
{

}