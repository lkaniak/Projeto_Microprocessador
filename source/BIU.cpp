#include "../headers/BIU.h"



BIU::BIU(std::ifstream *file)
{
	this->ip = new REGISTER("ip");
	this->memory = new MEMORY(255);
	this->memory->load_file(file);
}


BIU::~BIU()
{
}

void BIU::execute()
{
	//auto instruction = queue->load();
	auto instruction = "00100111";
	auto decoded_instruction = decoder->decode(instruction);

	if (decoded_instruction.size() == 3)
	{
		EU::get_instancia()->process(decoded_instruction[0]->get_name(),
			decoded_instruction[1]->get_name(),
			decoded_instruction[2]->get_name());
	}
	else if (decoded_instruction.size() == 2)
	{
		EU::get_instancia()->process(decoded_instruction[0]->get_name(),
			decoded_instruction[1]->get_name());
	}
	else
	{
		EU::get_instancia()->process(decoded_instruction[0]->get_name());
	}

	// Incrementa IP em 1
	this->ip->set_value(ip->get_value() + 1);
}
