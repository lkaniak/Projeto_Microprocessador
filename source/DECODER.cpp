#include "..\headers\DECODER.h"

std::vector<std::string> DECODER::decode(std::string instruction)
{
	std::string opcode;
	auto inst_set = instruction_Set::get_instancia();
	Instruction *instr_translated = nullptr;
	Instruction *operator_1_translated = nullptr;
	Instruction *operator_2_translated = nullptr;

	std::vector<std::string> instruction_decoded;

	//Pega a instrucao
	for (auto o : instruction)
	{
		opcode += o;
		if (opcode.size() == 4 || opcode.size() == 6 || opcode.size() == 8)
		{
			instr_translated = inst_set->get_operation_name(opcode);
			if (instr_translated != nullptr)
			{
				instruction_decoded.push_back(instr_translated->get_name());
				break;
			}
		}
	}

	auto new_size = instruction.erase(0, instr_translated->get_opcode().size());

	auto tot_op = instr_translated->get_num_operators();
	if (tot_op == 1)
	{
		instruction_decoded.push_back(inst_set->get_operation_name(instruction)->get_name());
	}
	else if (tot_op == 2)
	{
		// Pega os dois primeiros bits da string
		opcode = instruction.substr(0, 2);
		instruction_decoded.push_back(inst_set->get_operation_name(opcode)->get_name());

		// Remove os bits ja utilizados
		instruction.erase(0, 2);
		instruction.resize(instruction.find_last_of('\0'));
		if (instruction.length() == 2)
		{
			instruction_decoded.push_back(inst_set->get_operation_name(instruction)->get_name());
		}
		else
		{
			auto inst_utils = utils::get_instancia();
			instruction = inst_utils->bin_to_dec(instruction);
			instruction_decoded.push_back(instruction);
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
