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

bool BIU::execute()
{
	auto instruction = queue->get_instruction();
	auto decoded_instruction = decoder->decode(instruction);

	if (decoded_instruction[0]->get_name().compare("END") == 0)
		return true;
	else if (decoded_instruction.size() == 3)
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
	this->increment_ip();

	return false;

}

int BIU::increment_ip()
{
	this->ip->set_value(ip->get_value() + 1);
	return ip->get_value();
}

int BIU::set_ip(int new_ip)
{
	ip->set_value(new_ip);
	queue->clear();
	return ip->get_value();
}

int BIU::get_ip()
{
	return ip->get_value();
}
