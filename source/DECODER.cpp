#include "..\headers\DECODER.h"

std::vector<Instruction*> DECODER::decode(std::string instruction)
{
	std::string opcode;
	auto inst_set = instruction_Set::get_instancia();
	Instruction *instr_translated = nullptr;
	Instruction *operator_1_translated = nullptr;
	Instruction *operator_2_translated = nullptr;

	std::vector<Instruction*> instruction_decoded;

	//Pega a instrucao
	for (auto o : instruction)
	{
		opcode += o;
		if (opcode.size() == 4 || opcode.size() == 6 || opcode.size() == 8)
		{
			instr_translated = inst_set->get_operation_name(opcode);
			if (instr_translated != nullptr)
			{
				instruction_decoded.push_back(instr_translated);
				break;
			}
		}
	}

	instruction.erase(0, instr_translated->get_opcode().size());

	auto tot_op = instr_translated->get_num_operators();
	if (tot_op > 0)
	{
		// Pega os registradores
		opcode = "";
		for (auto o : instruction)
		{
			opcode += o;
			if (operator_1_translated == nullptr && opcode.size() == 2)
			{
				instruction_decoded.push_back(inst_set->get_operation_name(opcode));
				opcode = "";
			}
			else if (tot_op == 2 && opcode.size() == 2)
			{
				instruction_decoded.push_back(inst_set->get_operation_name(opcode));

				break;
			}
		}
	}

	return instruction_decoded;
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